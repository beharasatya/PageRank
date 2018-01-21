pagerank: pagerank.c readData.o list.o Graph.o
	gcc -o pagerank pagerank.c readData.o list.o Graph.o

readData.o: readData.c readData.h list.h graph.h
	gcc -Wall -Werror -c readData.c 

graph.o: Graph.c Graph.h
	gcc -Wall -Werror -c Graph.c

list.o: list.c list.h
	gcc -Wall -Werror -c list.c

clean:
	rm -f list.o readData.o list.o Graph.o