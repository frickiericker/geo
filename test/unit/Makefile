PROJECT_ROOT=   ../..

INCLUDES=       -I $(PROJECT_ROOT)/include \
                -I $(PROJECT_ROOT)/third_party/Catch/include

OBJECTS=        main.o point.o vector.o

EXTRA_CXXFLAGS= $(INCLUDES) \
                -std=c++14 -W -Wall -Wextra -Wconversion -Werror -pedantic-errors \
                -O2

DRIVER=         ./unittest
RM=             rm -f

.PHONY:    run clean
.SUFFIXES: .cc .o

all: $(DRIVER)
	$(DRIVER)

clean:
	$(RM) $(DRIVER) $(OBJECTS)

.cc.o:
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) -c -o $@ $<

$(DRIVER): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) -o $(DRIVER) $(OBJECTS) $(LDFLAGS)

# Dependencies
point.cc: \
    $(PROJECT_ROOT)/include/geo/point.hpp \
    $(PROJECT_ROOT)/include/geo/point.ipp \
    $(PROJECT_ROOT)/include/geo/vector.hpp \
    $(PROJECT_ROOT)/include/geo/vector.ipp \
    $(PROJECT_ROOT)/include/geo/assert.hpp \
    $(PROJECT_ROOT)/include/geo/standard_kernel.hpp \
    $(PROJECT_ROOT)/include/geo/internal/basic_coordinates.hpp \
    $(PROJECT_ROOT)/include/geo/internal/coordinates_storage.hpp \
    $(PROJECT_ROOT)/include/geo/internal/coordinates_storage.ipp \
    $(PROJECT_ROOT)/include/geo/internal/linear_operations.hpp \
    $(PROJECT_ROOT)/include/geo/internal/linear_operations.ipp

vector.cc: \
    $(PROJECT_ROOT)/include/geo/vector.hpp \
    $(PROJECT_ROOT)/include/geo/vector.ipp \
    $(PROJECT_ROOT)/include/geo/assert.hpp \
    $(PROJECT_ROOT)/include/geo/standard_kernel.hpp \
    $(PROJECT_ROOT)/include/geo/internal/basic_coordinates.hpp \
    $(PROJECT_ROOT)/include/geo/internal/coordinates_storage.hpp \
    $(PROJECT_ROOT)/include/geo/internal/coordinates_storage.ipp \
    $(PROJECT_ROOT)/include/geo/internal/linear_operations.hpp \
    $(PROJECT_ROOT)/include/geo/internal/linear_operations.ipp
