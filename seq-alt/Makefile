CC=g++
CFLAGS= -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors
RM=rm -f *o

nasteroids-seq: nasteroids-seq.cpp
			$(CC) $(CFLAGS) -o nasteroids-seq nasteroids-seq.cpp
nasteroids-par: nasteroids-par.cpp
	     $(CC) $(CFLAGS) -o nasteroids-par nasteroids-par.cpp

clean:
	$(RM) nasteroids-seq
	$(RM) nasteroids-par
