studio 19 answers here
1.Joe Pan; Frank Liang

2. First we create an image file with content { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3' }. Then, we use the read() method and store the return value to a local variable store_content. 
Then, we make an edit to thefile’s contents and rewrite thefile with the modified contents. After that, we compare the content in th store_content with the read() method's return value on the modified image
The two contents are not equal, which shows the read() method works.

3. In a visitor, it lets its visiting object to call accept() method which takes the visitor itself as a parameter. 
Then, for the visiting object, it will choose the concrete accept() method for its file_type. In the concrete accept method, the visiting object will let the input visitor to call the 
concrete visit_<file_type> () method according to its file type and take the visiting object itself as a parameter. Next, back to the visiting object, it will call the concrete visit_<file_type> method on its visiting object.
This is a double dispatch process.

4.The visitor let its visiting object to execute a member function of the visiting object using the state of another object (the visitor). The visiting object function is passed 
a pointer to the visitor, giving it access to the visitor’s state. Then, we can implement the functionality in the visitor's state.

5. If we have too many unique visitors, when we add a new file type, we not only have to add accept method in the abstract file class, but also have to add a lot of visit_<new type> methods
in the these visitors in total(1 for each). If we have too many types, we have to implement a lot of accept methods for the visitor.