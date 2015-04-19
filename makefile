main: main.o parser.o ParseTreeNode.o parser.h.gch ParseTreeNode.h.gch 
	g++ main.o parser.o ParseTreeNode.o -o main -g

main.o: main.cpp
	g++ -c main.cpp -g

parser.o: parser.cpp parser.h.gch
	g++ -c parser.cpp -g

parser.h.gch:  parser.h
	g++ -c parser.h -g

ParseTreeNode.o: ParseTreeNode.cpp ParseTreeNode.h.gch
	g++ -c ParseTreeNode.cpp ParseTreeNode.h -g

ParseTreeNode.h.gch: ParseTreeNode.h
	g++ -c ParseTreeNode.h -g

clean:
	rm *.o
