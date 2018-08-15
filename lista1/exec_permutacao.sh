#!/bin/bash

rm permutacao_tempo

for i in {1..13}
  do
    echo "Executando com N = $i"
    { time ./permutacao $i >/dev/null; } 2>&1 | grep real >> permutacao_tempos
  done
