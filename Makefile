EXE 		= ftridend
PYTHON 		= python/ftridend/kernel.so
CPP 		= g++ --std=c++20 
CFLAGS		= -O3 -Wall
LIBS 		= -lflint 
SRC_OBJ 	= schroeder_tree schroeder_forest quasi_shuffle ordered_partition primitives 
PYTHON_SRC 	= setup.py module.cpp schroeder_tree.hpp schroeder_tree.cpp schroeder_forest.hpp schroeder_forest.cpp

KER_OBJ 	= $(addprefix obj/kernel/,$(addsuffix .o,$(SRC_OBJ)))
PYTHON_FILES 	= $(addprefix cpp/python/, $(PYTHONSRC_FILES))

all: $(EXE) # $(PYTHON)

obj/kernel/%.o: cpp/kernel/%.cpp cpp/kernel/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): $(KER_OBJ) cpp/console/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(PYTHON): $(PYTHON_FILES)
	python cpp/python/setup.py build
	mv build/*/ftridend/*.so $(PYTHON)
	-$(RM) -r build

clean:
	-$(RM) $(EXE)
	-$(RM) $(PYTHON)
	-$(RM) $(KER_OBJ)
	-$(RM) cpp/kernel/*~
	-$(RM) cpp/python/*~
	-$(RM) cpp/console/*~
