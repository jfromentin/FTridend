EXE 	= schroeder
CPP 	= g++
CFLAGS	= -O3 -Wall --std=c++20
ALL 	= $(EXE)


obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): obj/schroeder_tree.o obj/schroeder_forest.o src/quasi_shuffle.o src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	-$(RM) obj/*.o $(EXE)

