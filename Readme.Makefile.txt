You will use this exact Makefile for your homework 2. Failure to do so will result in deduction of 10 points. Do not alter the Makefile in anyway. Do NOT rename it to anything like makefile or makefile.txt or Makefile.txt. 

You have to name your main files (one for file for each program) as follows:

QueryTrees.cpp

TestTrees.cpp

TestRangeQuery.cpp

Threre is no exception in the above rule. Make sure that the files are spelled exactly like that. The names are case sensitive. Failure to do so will result in the deduction of 5 points. Your main files should include (via means of includes) all the code. No other will be needed to be compilled.

The Makefile makes it easier for us to compile your program and test them. Makes it also easier for you.

Here what happens if you compile using the provided files:
-----LINUX TERMINAL----
bash-3.2$ make all
make QueryTrees
g++ -g -std=c++0x -Wall -I.   -c QueryTrees.cpp -o QueryTrees.o
g++ -g -std=c++0x -Wall -o ./QueryTrees QueryTrees.o -I.  -L/usr/lib -L/usr/local/lib -lm 
make TestTrees
g++ -g -std=c++0x -Wall -I.   -c TestTrees.cpp -o TestTrees.o
g++ -g -std=c++0x -Wall -o ./TestTrees TestTrees.o -I.  -L/usr/lib -L/usr/local/lib -lm 
make TestRangeQuery
g++ -g -std=c++0x -Wall -I.   -c TestRangeQuery.cpp -o TestRangeQuery.o
g++ -g -std=c++0x -Wall -o ./TestRangeQuery TestRangeQuery.o -I.  -L/usr/lib -L/usr/local/lib -lm 
bash-3.2$ make run1bst
./QueryTrees rebase210.txt BST
Input filename is rebase210.txt
I will run the BST code
bash-3.2$ make run1avl
./QueryTrees rebase210.txt AVL
Input filename is rebase210.txt
I will run the AVL code
bash-3.2$ make run2bst
./TestTrees rebase210.txt sequences.txt BST
Input file is rebase210.txt, and query file is sequences.txt
I will run the BST code 
bash-3.2$ make run2avl
./TestTrees rebase210.txt sequences.txt AVL
Input file is rebase210.txt, and query file is sequences.txt
I will run the AVL code 
bash-3.2$ make run3
./TestRangeQuery rebase210.txt CC\'TCGAGG T\'CCGGA
Input file is rebase210.txt String 1 is CC'TCGAGG   and string 2 is T'CCGGA
bash-3.2$ make clean
(rm -f *.o; rm -f TestTrees; rm -f QueryTrees; rm -f TestRangeQuery)
bash-3.2$ make QueryTrees
g++ -g -std=c++0x -Wall -I.   -c QueryTrees.cpp -o QueryTrees.o
g++ -g -std=c++0x -Wall -o ./QueryTrees QueryTrees.o -I.  -L/usr/lib -L/usr/local/lib -lm 
bash-3.2$ make run1bst
./QueryTrees rebase210.txt BST
Input filename is rebase210.txt
I will run the BST code
----END LINUX TERMINAL---

By typing make all everything is compiled. The executables if compiled correctly will be placed in QueryTrees, TestTrees and TestRangeQuery.
By typing make clean the directory is cleaned from object files and executables. Call this command before you compile.

You can run each program by means of the Makefile if you with, but you can also use the command line option. So for instance if you type

make run1bst

then program QueryTrees will run with the option BST. Of course you can also type

QueryTrees rebase210.txt BST

to achieve the same result.

Similary all programs can be run by appropriate commands (see above examples).

Finally, you can compile one program individually by just typing make <Program Name>, for example

make QueryTrees

