#!/bin/sh

for i in $(seq 1 $1)
do
    echo $i Processing...
    xelatex -shell-escape -interaction=nonstopmode source.tex >> xelatex.log
    echo $i Done.
done
