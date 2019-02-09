#
# Makefile framework for CptS223
#
# Hacked up by Aaron Crandall, 2017
#  Aaron S. Crandall <acrandal@wsu.edu
#

# Variables
GPP         = g++
CFLAGS      = -g -std=c++11 -Wall -Wshadow -Wconversion
GTESTFLAGS  = -pthread -lgtest
RM          = rm -f
BINNAME     = main
TESTNAME    = test_main
TESTFLAGS   = -fprofile-arcs -ftest-coverage
BINDIR      = bin
LCOVINFO    = coverage.info
COVHTMLDIR  = coverage_report

SHELL := /bin/bash

# Default is what happenes when you call make with no options
#  In this case, it requires that 'all' is completed
default: all

# All is the normal default for most Makefiles
#  In this case, it requires that Hello is completed
all: build

build:
	@echo "Nothing to do for build"

# Run your program
# Note: this will first execute the 'build' target to ensure a program to run
run: build
	@echo "Nothing to do for run"

# Builds the test driver system with gtest and gmock
test:
	@echo "Test checks for PDF file in this HW directory"
	if [[ -n `find . -iname *.pdf` ]]; \
	then echo '-- Found an solutions PDF file' && exit 0; \
	else echo '-- No solutions PDF file yet' && exit 1; \
	fi
