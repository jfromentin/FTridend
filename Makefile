EXE 			= ftridend
PYTHON 			= python/ftridend.so
CPP 			= g++ --std=c++20 
CFLAGS			= -O3 -Wall
LIBS 			= #-lflint 
SRC_OBJ 		= packed_word schroeder_tree schroeder_forest quasi_shuffle ordered_partition primitives
PYTHON_SRC 		= setup.py module.cpp schroeder_tree.hpp schroeder_tree.cpp schroeder_forest.hpp schroeder_forest.cpp schroeder_vector.hpp schroeder_vector.cpp
PYTHON_DOC		= schroeder_tree schroeder_forest schroeder_vector
KER_OBJ 		= $(addprefix obj/kernel/,$(addsuffix .o,$(SRC_OBJ)))
PYTHON_FILES 		= $(addprefix cpp/python/, $(PYTHON_SRC))
PYHTON_DOC_FILES	= $(addprefix cpp/python/deoc, $(PYTHON_DOC))

all: $(EXE) $(PYTHON)

obj/kernel/%.o: cpp/kernel/%.cpp cpp/kernel/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): $(KER_OBJ) cpp/console/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(PYTHON): $(PYTHON_FILES) $(PYTHON_DOC_FILES)
	python3 cpp/python/setup.py build
	mv build/*/ftridend*.so $(PYTHON)
	-$(RM) -r build

clean:
	-$(RM) $(EXE)
	-$(RM) $(PYTHON)
	-$(RM) $(KER_OBJ)
	-$(RM) cpp/kernel/*~
	-$(RM) cpp/python/*~
	-$(RM) cpp/console/*~
