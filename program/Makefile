EXE 	= schroeder
CPP 	= g++ --std=c++20
CFLAGS	= -O3 -Wall 
ALL 	= $(EXE)


obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): obj/schroeder_tree.o obj/schroeder_forest.o obj/quasi_shuffle.o obj/tridend_schroeder_algebra.o src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	-$(RM) obj/*.o $(EXE)

