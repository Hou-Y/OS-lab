#!/bin/bash 

# ; usato se voglio separare più comandi SU UNA STESSA LINEA

#comando shift -> faccio uno shift a  destra delle variabili
#perdo primo var ($1) sostituendolo con ciò che avevo al posto successivo
# nel $2 e così via fino al dopo aver spostato $ultimoVal, lo slot
#viene cancellato ma l'ultima var è ora nel penultimo posto

# $$ usato per file temporanei
##tmp_$$ ha ID diversi se sto startando molti shell assieme

# $1 directory
#$2 function
#$3 name output

# $? -> valore dell'ultimo programma
#usa find e poi scrivi echo $? sul terminale per capire se
#il find ha trovato errori o meno

set -x  #inizio debugging parziale
echo "directory $1"
#find $1 -name $2 | wc -l | sort -k1 -nk2  > $3
for i in $(find $1 -type f) #search the occurences INSIDE the files! 
#Not the NAME of the file itself 
do #vedi $2 come se fosse un quasi regex, se vuoi trovare il file
#che contiene la parola fork seguito o preceduto da ciò che voglio
#devo scrivere *fork* altrimenti trova SOLO i file che contengono
#esclusivamente 
    p=$(grep -Hnr $2)   
    p1=$(wc -l $2 |grep k1)
    echo "$p $p1" > $3
    #(grep -Hn $2 ; wc -l |grep k1 ) |cat > $3
    #così come ottengo il numero totale di linee??
done
sort -k1 -nk2 $3 > $3
#find $1 -name $2 | wc -l  > $3
#come mostrare la linea in cui appare il coso senza for
set +x #fine debugging parziale

exit 0
