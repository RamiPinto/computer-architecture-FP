CC=g++
CFLAGS= -std=c++14 -o3 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -fopenmp
RM=rm -f *o

nasteroids-par: nasteroids-par.cpp
	     $(CC) $(CFLAGS) -o nasteroids-par nasteroids-par.cpp

clean:
	$(RM) nasteroids-seq
	$(RM) nasteroids-par
