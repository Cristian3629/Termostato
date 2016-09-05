##Termostato

####Archivos:
- ###File.c
      Este archivo se encarga de encapsular todo lo referente
      al procesamiento del archivo tanto como abrirlo, leerlo,
      procesarlo y liberar sus recursos correspondiente.

- ###Time.c:
      Se encarga de la actualización constante, de la hora ingresada
      por el usuario, cada vez que se envia todas las mediciones
      recibidas por el Termostato.

- ###CalculateTemp.c:

      Se centra en todo el proceso desde "transformar" el número
      hexadecimal recibido hasta llegar al número decimal
      que representa la temperatura.

- ### Principal.c:
      Es el punto de entrada al programa, dado los párametros
      ingresados, este decide si el programa se ejecutará en
      modo cliente o en modo servidor.

- ### cliente.c
      Este es el modulo que modela todo el comportamiento del cliente, envia
      la fecha como la hora y las mediciones capturadas.
