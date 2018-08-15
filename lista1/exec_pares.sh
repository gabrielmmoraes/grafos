#!/bin/bash

COUNTER=2

rm pares_tempo

while [ $COUNTER -lt 100000000 ]
  do
    echo "Executando com N = $COUNTER"
    { time ./pares $COUNTER >/dev/null; } 2>&1 | grep real | cut -d$'\t' -f 2 >> pares_tempo
    let "COUNTER <<= 1"
  done
