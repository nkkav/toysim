#!/bin/bash

for bench in "fibo"
#for bench in "popcount"
do
  cd ${bench}
  make clean
  rm -f *.toyx
  make ${bench}.toyx BENCH=${bench}
  ../../toy.x --load=${bench}.toyx
  cp -f toy.stats toy_${bench}.stats
  cd ..
done

if [ "$SECONDS" -eq 1 ]
then
  units=second
else
  units=seconds
fi
echo "This script has been running for $SECONDS $units."

echo "Ran all tests."
exit 0
