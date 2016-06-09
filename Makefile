########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++0x -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.





#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I. 


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


#ZEROTH PROGRAM
ALL_OBJ0=QueryTrees.o
PROGRAM_0=QueryTrees
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=TestTrees.o
PROGRAM_1=TestTrees
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=TestRangeQuery.o
PROGRAM_2=TestRangeQuery
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)


#Compiling all

all: 	
		make $(PROGRAM_0)
		make $(PROGRAM_1)
		make $(PROGRAM_2)

run1bst: 	
		./$(PROGRAM_0) rebase210.txt BST

run1avl: 	
		./$(PROGRAM_0) rebase210.txt AVL

run2bst: 	
		./$(PROGRAM_1) rebase210.txt sequences.txt BST

run2avl: 	
		./$(PROGRAM_1) rebase210.txt sequences.txt AVL

run3: 	
		./$(PROGRAM_2) rebase210.txt CC\'TCGAGG T\'CCGGA




#Clean obj files

clean:
	(rm -f *.o; rm -f TestTrees; rm -f QueryTrees; rm -f TestRangeQuery)



(:
