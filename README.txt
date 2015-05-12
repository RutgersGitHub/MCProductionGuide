# Instructions to check out tdr package
1. svn co -N svn+ssh://<cernusername>@svn.cern.ch/reps/tdr2 . 
2. svn update utils
3. svn update -N --force notes
4. open the file utils/trunk/general/cms-tdr.cls and search for "% CMS definitions"
   and add the following package
   \usepackage{listings}
5. cd notes
