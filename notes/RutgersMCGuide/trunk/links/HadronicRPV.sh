#!/bin/sh

FILENAME=${1}

DATFILE="${FILENAME}.dat"
SLHAFILE="${FILENAME}_temp.slha"
HERWIGFILE="${FILENAME}.hwg"

# Top mass pole
MTP="172"

# Gluino mass, Up-type quark mass,Pseudo-Scalar Higgs, and tangent beta
MGLSS=${3}
MU="3000"
MA="4000"
TANBETA="3"

MQ1="5000" 
MDR=${2}
MUR=${2}
ML1="4000"
MER="300"

MQ3="5000" 
MBR=${2}
MTR=${2}
ML3="4000" 
MLR="300"
A_T="1000"
A_B="9000"
A_L="9000"

MQ2="/"
MSR=""
MCR=""
ML2=""
MMR=""

# Gaugino masses
M1="500"
M2="150"

# Gravitino mass
GRAVITINOMASS="/"
  
PARAM1="${MTP}"
PARAM2="${MGLSS},${MU},${MA},${TANBETA}"
PARAM3="${MQ1},${MDR},${MUR},${ML1},${MER}"
PARAM4="${MQ3},${MBR},${MTR},${ML3},${MLR},${A_T},${A_B},${A_L}"
PARAM5="${MQ2}${MSR}${MCR}${ML2}${MMR}"
PARAM6="${M1},${M2}"
PARAM7="${GRAVITINOMASS}"
    
# Creating SLHA files
./isasusy.x << EOF

'${DATFILE}'
${SLHAFILE}
${HERWIGFILE}
${PARAM1}
${PARAM2}
${PARAM3}
${PARAM4}
${PARAM5}
${PARAM6}
${PARAM7}

EOF

rm $DATFILE
rm $HERWIGFILE
