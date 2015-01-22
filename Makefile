CC= g++
CFLAGS=  -O3 -g -Wall -pedantic -MMD
KRUSKALOBJS= kruskal.o util.o tnode.o
DEPENDS = ${KRUSKALOBJS:.o=.d}

kruskal: $(KRUSKALOBJS)
	  $(CC) $(CFLAGS) -o kruskal $(KRUSKALOBJS) -lm

-include ${DEPENDS}

.PHONY: clean

clean: 
	rm -f *.o kruskal ${DEPENDS}

