1. Joe Pan; Frank Liang

2. An ImageFile object with the name "test" was created. The object was written with 'X' on diagonals. Append does not work for ImageFile.
The result is as expected:
X X
 X
X X
test_img
9

3. It is easy to add new functions with interface without modification to the client. The implementation of an interface used by the client can change at run-time, which is more flexible.

4. Under createFile function, besides "txt" and "img", new conditions should be added to accomodate other types of files.