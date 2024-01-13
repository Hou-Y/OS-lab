#!/bin/bash

#$1 name of directory
set -x
for i in $(ls $1) #per eseguire una funzione dentro le parentesi
#per ogni cosa dentro la directory
do
  mv $1/$i   $1/$(echo $i | tr A-Z a-z)
    #sostituisco le maiuscole con le minuscole
    #devo spostare i nomi in standard input?
done 
set +x
#mv $1/$i $1/$(echo $i | tr A-Z a-z)
#arrivo fino alla foglia e vado indietro guardando solo i file
