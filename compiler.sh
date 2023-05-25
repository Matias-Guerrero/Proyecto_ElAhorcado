#!/bin/bash

# Script para compilar el programa desde git bash

# Ingresar el nombre del ejecutable
read -p "Ingrese el nombre del ejecutable: " executable

# Archivos a compilar
FILES="avance.c Struct/struct.h Map/Map.c ArrayList/arraylist.c List/list.c"

# Compilacion con gcc
gcc -g $FILES -o $executable

# Verificar si hubo errores
if [ $? -eq 0 ]; then
    echo "Compilacion exitosa"
else
    echo "Hubo errores en la compilacion"
fi

# Ejectuar el programa en una ventana nueva
# cmd.exe /c $executable.exe