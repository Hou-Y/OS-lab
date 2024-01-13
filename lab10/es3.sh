#!/bin/bash

# Check input parameters
if [ $# -ne 2 ] # -ne  = Not Equal ; $# = numero di elementi nell'array dei parametri
#controllo se il numero di parametri è pari a 2, se non lo è -> messaggio di errore
then
  echo "Usage: $0 <user> <dir>"
  exit 1
fi

# Scan all files of the given user in the given folder
set -x
for file in $(find $2 -user $1 -type f); do # trova file di utente nella directory e in tutte le sottodirectory

    # Check if file contains target string
    #grep -e "^\*\*\*Da Modificare*" $file
    grep -e "^\*\*\*Da Modificare" $file
    #grep stampa solo le RIGHE di un file che matchano un pattern
    #questo grep serve per trovare il nome del file ($file) anche se stampa le righe

    # If that is the case edit and rename the file
    if [ $? -eq 0 ] # -eq = Equal
    #se output di ultimo comando eseguito è pari a zero
    #nel nostro caso (grep) se è stato 
    then
      grep -v '^*\*\*Da Modificare' $file > /tmp/tmp$$.txt
 #grep -v select non-matching LINES (dritto dal manuale)
 # > ->sposto l'output in un file temporaneo 
 # $$ -> nome del processo per identificarlo
 
 	#ricordati di dare i permessi di esecuzione al file!!!
 	
      mv /tmp/tmp$$.txt $file"_mod"
      # lo risposto dove dovrebbe ma con _mod
      # $file è l'INTERO PATH (dal home fino al file) che identifica il FILE
      rm -f $file
    fi
done
set +x

exit 0
