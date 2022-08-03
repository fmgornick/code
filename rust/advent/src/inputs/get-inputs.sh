#!/bin/sh
if [ $# -eq 0 ]; then echo "must supply cookies file"; exit; fi
cookies=$1
curl -b $1 https://adventofcode.com/2021/day/\[1-25\]/input -o "day#1.txt"
for i in {1..9}; do mv "day$i.txt" "day0$i.txt"; done
