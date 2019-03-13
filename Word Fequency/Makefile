CFLAGS += -Wall -g
CXXFLAGS += -std=c++11 -pthread -Wall -g
CPPFLAGS += -isystem ${GTEST}/include -I${GTEST} 
PROG1 = wf1
PROG2 = wf2
OBJ1 = reader.o dict.o word.o 
OBJ2 = reader.o tree.o word.o
HDR1 = reader.h dict.h word.h
HDR2 = reader.h word.h tree.h
TEST = test

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJ1) wf1.o
	$(CC) $(OBJ1) wf.o -o $@

wf1.o: wf.c
	$(CC) $^ -c $(CFLAGS) -D DICT=dict

$(OBJ1): $(HDR1)

$(PROG2): $(OBJ2) wf2.o
	$(CC) $(OBJ2) wf.o -o $@

wf2.o: wf.c
	$(CC) $^ -c $(CFLAGS) -D DICT=tree_dict

$(OBJ2): $(HDR2)

clean:
	$(RM) *.o $(PROG1) $(PROG2) $(TEST)
    
$(TEST): dict.o tree.o word.o unittest.o gtest-all.o gtest_main.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

gtest-all.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ${GTEST}/src/gtest-all.cc

gtest_main.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ${GTEST}/src/gtest_main.cc

unittest.o: unittest.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I${GTEST}/include -c $^
