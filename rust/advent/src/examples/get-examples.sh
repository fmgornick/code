#!/bin/sh

# this script is very imperfect (and prolly useless)
if [ $# -eq 0 ]; then echo "must supply cookies file"; exit; fi
cookies=$1
for i in {1..25}
  do curl -sb cookie https://adventofcode.com/2021/day/$i | awk '/<pre><code>/,/<\/code><\/pre>/; /<\/code><\/pre>/{exit}' | cut -d '>' -f 3 > "day$i.txt"
done
for i in {1..9}; do mv "day$i.txt" "day0$i.txt"; done
