#!/bin/sh

FILENAME=${1}

DATFILE="${FILENAME}.dat"
SLHAFILE="${FILENAME}.slha"
HERWIGFILE="${FILENAME}.hwg"

# Squark mass, Gluino, A0, and tangent beta
MZERO=$2        # Mass of all scalar fermions at the Grand Unified Scale
MHALF=$3        # Mass of all gauginos at the Grand Unified Scale
A0=$4
TANBETA=$5
SIGNMU=$6

# Top mass pole
MTP=$7

PARAM1="1"
PARAM2="${MZERO},${MHALF},${A0},${TANBETA},${SIGNMU},${MTP}"

# Creating SLHA files
./isasugra.x << EOF

'${DATFILE}'
${SLHAFILE}
${HERWIGFILE}
${PARAM1}
${PARAM2}
EOF

rm $DATFILE
rm $HERWIGFILE

cat ISALHD.out | awk '{if(NR >= 15) print}' >> ${FILENAME}.slha
rm ISALHD.out
