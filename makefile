#
# PROGRAM:    assign6
# PROGRAMMER: Saad Rasheed
# LOGON ID:   z1783832
#

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
memory: memory.o block.o
	g++ $(CCFLAGS) -o memory memory.o block.o

# Rules to compile source code file to object code
memory.o: memory.cpp block.h
	g++ $(CCFLAGS) -c memory.cpp

block.o: block.cpp block.h
	g++ $(CCFLAGS) -c block.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o memory







