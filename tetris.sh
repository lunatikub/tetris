#!/bin/bash

MAX=100
PAD=1

generate_influence ()
{
    echo "#define _Il  (-$1)" > tetris_influence.h
    echo "#define _Ie  ($2)"  >> tetris_influence.h
    echo "#define _Idr (-$3)" >> tetris_influence.h
    echo "#define _Idc (-$4)" >> tetris_influence.h
    echo "#define _IL  (-$5)" >> tetris_influence.h
    echo "#define _IW  (-$6)" >> tetris_influence.h
    echo "#define _ID  (-$7)" >> tetris_influence.h
    echo "#define _IR  (-$8)" >> tetris_influence.h
}

tetris_average ()
{
    avg=0
    max=0
    min=9999

    for i in $(seq 1 $MAX)
    do
        echo -en "$i/$MAX\r"
        nr=$(./tetris)

        [ $nr -gt $max ] && max=$nr
        [ $nr -lt $min ] && min=$nr
        avg=$((nr + avg))
    done

    echo "$1 $2 $3 $4 $5 $6 $7 $8 ::: $((avg/MAX)) $max $min" >> TETRIS.csv
}

echo -n "" > TETRIS.csv

for l in $(seq 12 $PDA 14)
do
    for e in $(seq 5 $PAD 6)
    do
        for dr in $(seq 8 $PAD 12)
        do
            for dc in $(seq 8 $PAD 12)
            do
                for L in $(seq 12 $PAD 15)
                do
                    for W in $(seq 8 $PAD 12)
                    do
                        for R in $(seq 10 $PAD 25)
                        do
                            echo "$l $e $dr $dc $L $W 1.61 $R"
                            generate_influence $l $e $dr $dc $L $W 1.61 $R
                            make >/dev/null
                            tetris_average $l $e $dr $dc $L $W 1.61 $R
                        done
                    done
                done
            done
        done
    done
done

exit 0
