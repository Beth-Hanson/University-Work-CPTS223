#
# Makefile framework for CptS223
#
# Hacked up by Aaron Crandall, 2017
#  Aaron S. Crandall <acrandal@wsu.edu
#

# Variables
GPP         = g++
CFLAGS      = -g -std=c++11
GTESTFLAGS  = -lpthread -lgtest
RM          = rm -f
BINNAME     = helloworld
TESTNAME    = test_helloworld

# Default is what happenes when you call make with no options
#  In this case, it requires that 'all' is completed
default: all

# All is the normal default for most Makefiles
#  In this case, it requires that Hello is completed
all: build

# Hello depends upon helloworld.cpp, then runs the command:
#  g++ -g -std=c++11 -o HelloWorld helloworld.cpp
build: $(BINNAME).cpp
	$(GPP) $(CFLAGS) -o $(BINNAME) $(BINNAME).cpp

# Run your program
run: build
	@echo "Running the $(BINNAME) program"
	./$(BINNAME)

test: build
	@echo "Testing the $(BINNAME) program."
	$(GPP) $(CFLAGS) -o $(TESTNAME) $(TESTNAME).cpp $(GTESTFLAGS)
	./$(TESTNAME)

# If you call "make clean" it will remove the built program
clean veryclean:
	$(RM) $(BINNAME) $(TESTNAME)

