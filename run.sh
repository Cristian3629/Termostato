#!/bin/bash

if [ "$1" == "--help" ] || [ $# -lt 2 ]; then
	echo -e "Uso: run.sh puerto [valgrind]\n"
	exit -1
fi

server_host=127.0.0.1
port=$1
mode=$2
server_cmd="./tp server"
client_cmd="./tp client"
valgrind_error_code=42

if [ "$mode" == "valgrind" ]; then
	valgrind_prefix="valgrind --gen-suppressions=all --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=$valgrind_error_code --db-attach=no --leak-check=full --leak-resolution=med"
	server_cmd="$valgrind_prefix --log-file=valgrind_server.out $server_cmd"
	client_cmd="$valgrind_prefix --log-file=valgrind_client.out $client_cmd"
fi


if [ -f "server.args" ]; then
	server_args=$(cat server.args)
fi
echo -n "Running Server: "
echo "$server_cmd $port $server_args 1>__server_stdout__ 2>__server_stderr__  &"
$server_cmd $port $server_args 1>__server_stdout__ 2>__server_stderr__  & server_pid=$!
sleep 1
ps $! > /dev/null
server_status=$? 
if [ $server_pid -gt 0 ] && [ $server_status -eq 0 ]; then
	echo "Server OK. PID: $server_pid"
	server_pid=$!
else
	echo "ERROR: The server was not initialized. Server result code: $server_status"
	exit 2
fi


if [ -f "client.args" ]; then
	client_args=$(cat client.args)
fi
if [ -f "client.in" ]; then
	client_in="0<client.in"
fi
echo -n "Running Client: "
echo "$client_cmd $server_host $port $client_args $client_in 1>__client_stdout__ 2>__client_stderr__"
$client_cmd $server_host $port $client_args $client_in 1>__client_stdout__ 2>__client_stderr__
client_status=$?

echo "Client exit code: $client_status"
if [ "$mode" == "valgrind" ] && [ $client_status -eq $valgrind_error_code ]; then
	echo "ERROR: Valgrind error detected in client execution."
	exit 2
fi

sleep 1

ps -p $server_pid >/dev/null
server_running=$?
if [ $server_running -ne 0 ]; then
	wait $server_pid
	server_status=$?
        echo "Server exit code: $server_status"
	if [ "$mode" == "valgrind" ] && [ $server_status -eq $valgrind_error_code ]; then
        	echo "ERROR: Valgrind error detected in server execution."
        	exit 2
	fi
else
	echo "Server ERROR"
	kill -9 $server_pid
fi

