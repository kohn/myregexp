GTEST_DIR = gtest
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
CXX = g++

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

TESTS = main_test

all: $(TESTS)

clean:
	rm *.o $(TESTS)

main_test: main.o Parser.o ParseTreeNode.o Automata.o State.o regexp.o test.o gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c main.cpp

Parser.o: Parser.cpp Parser.h ParseTreeNode.h Automata.h State.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Parser.cpp

ParseTreeNode.o: ParseTreeNode.cpp ParseTreeNode.h Automata.h State.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ParseTreeNode.cpp

Automata.o: Automata.cpp Automata.h ParseTreeNode.h State.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Automata.cpp

State.o: State.cpp State.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c State.cpp

regexp.o: regexp.cpp regexp.h Automata.h ParseTreeNode.h State.h Parser.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c regexp.cpp

test.o: test.cpp Automata.h State.h regexp.h
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c test.cpp

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc
gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

