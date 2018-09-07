MAIN = run_test

OBJECTS = \
  main.o \
  vector_test.o \
  point_test.o \
  neighbor_searcher_test.o

DBGFLAGS = \
  -g \
  -fsanitize=address,undefined

OPTFLAGS = \
  -O2

INCLUDES = \
  -I ../include

CXXFLAGS = \
  -std=c++11 \
  -pedantic \
  -Wall \
  -Wextra \
  -Wconversion \
  -Wsign-conversion \
  -Wshadow \
  $(DBGFLAGS) \
  $(OPTFLAGS) \
  $(INCLUDES)

ARTIFACTS = \
  $(MAIN) \
  $(OBJECTS) \
  *.dSYM

.SUFFIXES: .cc
.PHONY: test clean

test: $(MAIN)
	@./$(MAIN)

clean:
	rm -rf $(ARTIFACTS)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

vector_test.o: ../include/geo.hpp
point_test.o: ../include/geo.hpp
neighbor_searcher_test.o: ../include/geo.hpp ../plugin/neighbor_searcher.hpp
