#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'screensaver'
# 'make clean'  removes all .o and executable files
##

#Compiler in use
CC=g++

#Compile time Flags
CFLAGS= -pthread -g

#Libraries to include during Cmpilation 
LIBRARIES= -lglut -lGL -lGLU -lGLEW -lm -std=c++11

#The C++ source files
SOURCES= Anothertry.cpp 

#The C++ object files
objects= $(SOURCES:.c=.o)

#Main executable file screensaver
BouncingBalls: $(objects)
	g++ $(CFLAGS) $(objects) $(LIBRARIES) -o ./BouncingBalls

.PHONY : clean
clean:
	rm BouncingBalls	

.PHONY : print


#‘make print’ will execute the lpr command if either source file has changed
#since the last ‘make print’. The automatic variable ‘$?’ is used to print only those files
#that have changed
print: *.c
	lpr -p $?
	touch print
