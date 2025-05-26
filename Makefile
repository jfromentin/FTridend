EXE 		= ftridend
SAGE 		= sage/ftridend/kernel.so
CPP 		= g++ --std=c++20
CFLAGS		= -O3 -Wall
SRC_OBJ 	= schroeder_tree schroeder_forest quasi_shuffle tridend_schroeder_algebra
SAGE_SRC_FILES 	= setup.py module.cpp schroeder_tree.hpp schroeder_tree.cpp schroeder_forest.hpp schroeder_forest.cpp

KER_OBJ 	= $(addprefix obj/kernel/,$(addsuffix .o,$(SRC_OBJ)))
SAGE_FILES 	= $(addprefix cpp/sage/, $(SAGE_SRC_FILES))

all: $(EXE) $(SAGE)

obj/kernel/%.o: cpp/kernel/%.cpp cpp/kernel/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): $(KER_OBJ) cpp/console/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(SAGE): $(SAGE_FILES)
	sage -python cpp/sage/setup.py build
	mv build/*/ftridend/*.so $(SAGE)
	-$(RM) -r build

clean:
	-$(RM) $(EXE)
	-$(RM) $(SAGE)
	-$(RM) $(KER_OBJ)
	-$(RM) cpp/kernel/*~
	-$(RM) cpp/sage/*~
	-$(RM) cpp/console/*~
