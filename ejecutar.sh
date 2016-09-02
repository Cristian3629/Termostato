#!/bin/bash

make
python ./cpplint.py --extensions=h,hpp,c,cpp --filter=`cat filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'`
./tp client 192.168.1.10 9090 salon 1000 “2016.08.20­23:59:50” datos.dat
`valgrind ./tp client`
