#!/bin/bash 

# ; usato se voglio separare più comandi SU UNA STESSA LINEA

#comando shift -> faccio uno shift a  destra delle variabili
#perdo primo var ($1) sostituendolo con ciò che avevo al posto successivo
# nel $2 e così via fino al dopo aver spostato $ultimoVal, lo slot
#viene cancellato ma l'ultima var è ora nel penultimo posto

# $$ usato per file temporanei
##tmp_$$ ha ID diversi se sto startando molti shell assieme

# $? -> valore dell'ultimo programma
#usa find e poi scrivi echo $? sul terminale per capire se
#il find ha trovato errori o meno

#$1 name of file

#set -x  #inizio debugging parziale
echo "num lines and longest line count:"

#$p = $(wc  -L -l $1) 
#cut -d" " -f12 $p

wc  -l -L $1  #questo fa il suo dovere

g=$(wc  -L -l $1 | tr -s " ") 
echo $g #fin qua fa quel che dovrebbe fare

#cut -d" " -f1-2 $g  # non trova file/directory??

#versione alternativa stampa SOLO un valore invece delle prime 2 colonne
#wc  -L -l $1 | tr -s " " | cut -d" " -f1-2 #questo torna solo la prima col
wc  -L -l $1 | tr -s " " | cut -d" " -f2-3
# il primissimo elemento è uno spazio percè il wc è formattato
#e ha uno spazio davanti

# only one type of list may be specified, non importa come, prende
#SOLO ed esclusivamente il primo elemento
#come fare per mostrare le prime due colonne

#come mai questo comando mi torna vuoto?
#nel debug esegue prima il cut e POI il wc però usando il pipe
#l'ordine dovrebbe essere wc -> cut e non viceversa

#set +x #fine debugging parziale

exit 0
