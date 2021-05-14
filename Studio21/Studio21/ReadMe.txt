Studio 21 ReadMe.txt 

1. Joe Pan; Frank Liang

2. The virtual destructor is to avoid memory leak when a derived class with a base class pointer is deleted so that the derived class does not remain undeleted.
  
3. Since the CommandPrompt is not interacting with any concrete classes, when a new file system, file factory, or concrete command is introduced, there is no need to modify CommandPrompt, which makes it much more reuseable.

4. A SimpleFileSystem, a SimpleFileFactory, and a TouchCommand object is dynamically allocated, and a CommandPrompt is configured with the above functions. When the CommandPrompt is run, a file called "test.txt" is created with the touch function. After the CommandPrompt is quit, test.txt is written with "Hello World!" and the content is displayed with a BasicDisplayVisitor.
