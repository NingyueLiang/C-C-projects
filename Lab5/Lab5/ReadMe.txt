Lab 5 Readme

Frank Liang & Joe Pan fliang@wustl.edu; panfengzhou@wustl.edu
50%/50% work together 

Test Case:

Test LSCommand:
1. $  help ls
Output: LSCommand will display names of all files in the file system, LS can be invoked with the command: ls 
(with additional option, '-m', which will display asingle file per line along with the metadata associated with that file)

2. test on a file system ($  touch a.txt b.img asdafdsfs.txt asdsdf.img)
$  ls
Output: 
a.txt               asdafdsfs.txt
asdsdf.img          b.img

$  ls -m
Output:
a.txt               text                0
asdafdsfs.txt       text                0
asdsdf.img          image               0
b.img               image               0

The output is reasonable.

Test RemoveCommand:
1. 
$  touch 1.txt touch 2.img
$  ls
1.txt               2.img
$ rm 1.txt

Output:
$  ls
2.img

2. help rm
RemoveCommand will remove the file with the provided name from the file system: rm <filename>

The outputs are reasonable.
