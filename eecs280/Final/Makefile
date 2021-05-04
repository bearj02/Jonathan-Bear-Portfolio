# Makefile
# Build rules for EECS 280 project 2

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = --std=c++11 -Wall -Werror -pedantic -g

Problem1.exe: Problem1.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem2.exe: Problem2.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem3.exe: Problem3.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem4.exe: Problem4.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem5.exe: Problem5.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem6.exe: Problem6.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Problem7.exe: Problem7.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

  Problem7_4.exe: Problem7_4.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf *.exe *.out.txt *.out.ppm *.dSYM *.stackdump

# Run style check tools
CPPCHECK ?= cppcheck
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := \
  Problem1.cpp \
  Problem2.cpp \
  Problem3.cpp \
  Problem4.cpp \
  Problem5.cpp
style :
	$(CPPCHECK) \
    --language=c++ \
    --std=c++11 \
    --error-exitcode=1 \
    $(FILES)
	$(OCLINT) \
    -no-analytics \
    -rule=LongLine \
    -rule=HighNcssMethod \
    -rule=DeepNestedBlock \
    -rule=TooManyParameters \
    -rc=LONG_LINE=90 \
    -rc=NCSS_METHOD=40 \
    -rc=NESTED_BLOCK_DEPTH=4 \
    -rc=TOO_MANY_PARAMETERS=4 \
    -max-priority-1 0 \
    -max-priority-2 0 \
    -max-priority-3 0 \
    $(FILES) \
    -- -xc++ --std=c++11
	$(CPD) \
    --minimum-tokens 100 \
    --language cpp \
    --failOnViolation true \
    --files $(FILES)
	@echo "########################################"
	@echo "EECS 280 style checks PASS"

sync :
	rsync \
  -rtv \
  --delete \
  --exclude '.git*' \
  --filter=':- .gitignore' \
  ../p2-computer-vision/ \
  bearj@login.engin.umich.edu:p2-copy/