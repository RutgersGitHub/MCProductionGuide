#!/bin/csh

# Shown for c shell
setenv WORKING_DIRECTORY $PWD

setenv SCRAM_ARCH slc5_amd64_gcc481
setenv VO_CMS_SW_DIR /cms/base/cmssoft
setenv COIN_FULL_INDIRECT_RENDERING 1

# To setup the default cmssw release and enable SRM-Client Tools
source $VO_CMS_SW_DIR/cmsset_default.csh

setenv MYREL CMSSW_7_0_0
setenv MYPROJECT private
setenv MYBASE ${MYPROJECT}/${MYREL}

# The following command for eval is equivalent to cmsenv
cd ~${USER}/${MYBASE}/src
eval `scramv1 runtime -csh`
cd $WORKING_DIRECTORY

setenv PATH ${PATH}:/usr/local/bin/cms-git-tools
