include ../../makeconf

INCPATH = -I../../include -I../THIRD_PARTY
CFLAGS = $(MOREFLAGS) $(WARNLEVEL) -pedantic $(INCPATH)

SOURCES.C    =  binTree.cpp\
		dijkstraGraph.cpp\
		heap.cpp\
		list.cpp\
		clusterGraph.cpp\
		graph.cpp\
		jqsort.cpp\
		matrix.cpp

OBJECTS.O    =  $(SOURCES.C:.cpp=.o)

../OBJECTS/primitives.o: $(OBJECTS.O)
	$(LD) -r -o ../OBJECTS/primitives.o $(OBJECTS.O)

depend:
	makedepend -- $(CFLAGS) -- $(SOURCES.C)
	$(RM) -f Makefile.bak

clean :
	$(RM) -f *.o ../OBJECTS/primitives.o

.cpp.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

# DO NOT DELETE

binTree.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
binTree.o: /usr/include/_G_config.h /usr/include/wchar.h
binTree.o: ../../include/binTree.h
dijkstraGraph.o: ../../include/dijkstraGraph.h ../../include/heap.h
dijkstraGraph.o: ../../include/j_mesh.h /usr/include/stdio.h
dijkstraGraph.o: /usr/include/features.h /usr/include/libio.h
dijkstraGraph.o: /usr/include/_G_config.h /usr/include/wchar.h
dijkstraGraph.o: /usr/include/math.h /usr/include/limits.h
dijkstraGraph.o: ../../include/graph.h ../../include/list.h
heap.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
heap.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/stdlib.h
heap.o: /usr/include/alloca.h ../../include/heap.h ../../include/j_mesh.h
heap.o: /usr/include/math.h /usr/include/limits.h
list.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
list.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/stdlib.h
list.o: /usr/include/alloca.h ../../include/list.h ../../include/jqsort.h
clusterGraph.o: ../../include/clusterGraph.h ../../include/heap.h
clusterGraph.o: ../../include/j_mesh.h /usr/include/stdio.h
clusterGraph.o: /usr/include/features.h /usr/include/libio.h
clusterGraph.o: /usr/include/_G_config.h /usr/include/wchar.h
clusterGraph.o: /usr/include/math.h /usr/include/limits.h
clusterGraph.o: ../../include/graph.h ../../include/list.h
graph.o: ../../include/graph.h ../../include/list.h /usr/include/stdio.h
graph.o: /usr/include/features.h /usr/include/libio.h
graph.o: /usr/include/_G_config.h /usr/include/wchar.h
matrix.o: /usr/include/math.h /usr/include/features.h ../../include/matrix.h
matrix.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
matrix.o: /usr/include/wchar.h ../../include/list.h
