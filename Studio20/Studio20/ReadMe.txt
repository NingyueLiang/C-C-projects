Studio 20 ReadMe.txt
1. Joe Pan; Frank Liang

2. Because the PasswordProxy is public inherited from the AbstractFile. For AbstractFile, the destructor is virtual and the PasswordProxy is the only place held the pointer to the real file,
so that if we didn't delete the pointer, it will cause memory leak.

3. I create an Abstract file of image type with name = test file and content = { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' };
Then I creat a patried to read