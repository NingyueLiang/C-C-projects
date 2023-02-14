OOP File System

Frank Liang & Joe Pan 

Luckily no errors; Warning: C26451: Cast a 4 byte to a 8 byte value. Might cause overflow, but after consulting our professor, this won't happen in the case, as long as it work normally.

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

Test Touch Command:

1. 
$  help touch
touch creates a file, touch can be invoked with the command Usage: touch <filename>
2.
$  touch 1.txt
$  touch 2.txt -p
What is the password?
12
$  ls
1.txt               2.txt
$  ds 2.txt
Please enter the password!
12
    (2.txt is empty)
The output is reasonable and correct

Test Cat Command & ds Command:
1. 
$  cat 1.txt
Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.
hello
:q

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ds 1.txt

2.
$  cat 1.txt
Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.
hello
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ds 1.txt
hello

3.Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  cat 1.txt -a
hello

Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.

world!
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ds 1.txt
hello
world!

The answer is reasonable, the following line is appended at the end of the content.

Test Copy Command:
1.
$  touch 1.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  cat 1.txt
Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.
Hello
World
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  cp 1.txt 2

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ls
1.txt               2.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ds 2.txt
Hello
World

The outputs are all correct and reasonable.

Test Rename Command:
Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  touch 1.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ls
1.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  rn 1.txt 2

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  ls
2.txt

All outcomes are reasonable and correct.

----------------------------------------------------------------Unit test All pass 
Test Grep:
$  touch 1.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  cat 1.txt
Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.
hello sdfs Hellp
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  touch 2.txt -p
What is the password?
1

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  cat 2.txt
Enter data you would like to write to this file. Enter :wq to save the file and exit, enter :q to exit without saving.
Hello a help
:wq
Please enter the password!
1

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  grep Hello
Please enter the password!
1
2.txt

Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
$  grep Hellp
1.txt
Please enter the password!
1

The results are as expected and reasonable.
