PROJECT			= ftridend

EXE			= $(PROJECT)
TEST			= $(PROJECT)_test
PY_MODULE		= $(PROJECT).so

CPP 			= g++
CFLAGS			= -O3 -Wall -g --std=c++20 -Icpp

KERNEL_FILES		= bset schroeder_tree
CONSOLE_FILES		=
TEST_FILES		= test bset
PY_MODULE_FILES		= module schroeder_tree
PY_MODULE_DOC_FILES	= schroeder_tree

KERNEL_OBJS  		= $(addprefix obj/kernel/, $(addsuffix .o, $(KERNEL_FILES)))
CONSOLE_OBJS  		= $(addprefix obj/console/, $(addsuffix .o, $(CONSOLE_FILES)))
TEST_OBJS  		= $(addprefix obj/test/, $(addsuffix .o, $(TEST_FILES)))
PY_MODULE_SRC  		= $(addprefix cpp/python/, $(addsuffix .cpp, $(PY_MODULE_FILES)))
PY_MODULE_DOC_SRC	= $(addprefix cpp/python/doc, $(PY_MODULE_DOC_FILES))

all: $(EXE) $(TEST)

obj/kernel/%.o: cpp/kernel/%.cpp cpp/kernel/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

obj/console/%.o: cpp/console/%.cpp cpp/console/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

obj/test/%.o: cpp/test/%.cpp cpp/test/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@


$(EXE): $(KERNEL_OBJS) $(CONSOLE_OBJS) cpp/console/main.cpp 
	$(CPP) $(CFLAGS) $(INC) $^ -o $@ $(LFLAGS)

$(TEST): $(KERNEL_OBJS) $(TEST_OBJS) cpp/test/main.cpp 
	$(CPP) $(CFLAGS) $(INC) $^ -o $@ $(LFLAGS)

$(PY_MODULE): cpp/python/setup.py $(PY_MODULE_SRC) $(KER_OBJ)
	$(PYTHON) cpp/python/setup.py build
	mv build/*/$(PROJECT)*.so $(PY_MODULE)
	-$(RM) -r build


clean:
	-$(RM) $(EXE)
	-$(RM) $(TEST)	
	-$(RM) $(PY_MODULE)
	-$(RM) *~
	-$(RM) obj/kernel/*.o
	-$(RM) obj/console/*.o
	-$(RM) obj/test/*.o
	-$(RM) cpp/kernel/*~
	-$(RM) cpp/console/*~
	-$(RM) cpp/test/*~
	-$(RM) cpp/python/*~	

