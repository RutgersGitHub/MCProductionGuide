# Setup tdr command for Bourne-shell or Korn shell
eval `./tdr runtime -sh`

# For c-shell or tc shell
eval `./tdr runtime -csh`

# You may edit the RutgersMCGuide latex file with command 
emacs -nw RutgersMCGuide/trunk/RutgersMCGuide.tex

# Command to compile the RutgersMCGeneration pdf file
# The file will be save to tmp/RutgersMCGuide_tmp.pdf
tdr --style=note --noclean build RutgersMCGuide
