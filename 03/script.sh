#!/bin/bash 

cd casosdeteste/
for i in {1..63}
do
QTD="$(head -1 $i.in)"
INPUT="$(head -50 $i.in)"
OUTPUT="$(head -50 $i.out)"
RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
cd ..
#echo "${OUTPUT}" 
MYOUTPUT="$(echo "${INPUT}" | ./lab04)"
echo "${MYOUTPUT}"
if [[ "$MYOUTPUT" != "$OUTPUT" ]]
then
#echo -e "${GREEN}all OK${NC}"
#else
echo -e "${RED}$i.in isnt OK${NC}"
fi
cd casosdeteste/
done 
# for i in *.in
# do
#	QTD = head -1 i.in
#	INPUT = head -100 i.in
#	echo QTD |  
# done

