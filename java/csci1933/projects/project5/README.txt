Fletcher Gornick, GORNI025

For this project I created a few hash functions as well as altering the code a 
bit.  I changed up the TextScan.java file to just return one long space-separated
string of words, making it easier to manipulate in my Hash Table Class.

In addition to the add(), display(), main(), constructors and hash functions, I
also created an addFile() function that adds the entire file to the HashTable, 
making it much easier.

Finally, I overloaded the add() method, making it so you can also input which hash
function you would prefer to use, I figured it would be much easier that way.

In order to run the code, you just need to type...
javac HashTable.java
java HashTable

After doing this, the screen should pop up and tell you to press enter to see the 
HashTable for the "gettysburg.txt" file.  After pressing enter, it will display 
the Table of length and show the collision information.  The screen will then 
prompt you again to press enter to see the Table for the "keywords.txt" file, the
program will again display the table and collision information.

If you'd like, you can change which hash function is used, or the size of the hash
table as well as the file that gets hashed.  For my program it seems as though 
any hash function works fine for "keywords.txt" and hash4() is best for all the 
other files.  

But yeah that's pretty much it, feel free to play around with the table sizes,
files, and hash functions.
