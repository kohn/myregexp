main: main.o Parser.o ParseTreeNode.o Automata.o State.o
	g++ main.o parser.o ParseTreeNode.o Automata.o State.o -o main -g

main.o: main.cpp
	g++ -c main.cpp -g

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp -g

ParseTreeNode.o: ParseTreeNode.cpp ParseTreeNode.h
	g++ -c ParseTreeNode.cpp ParseTreeNode.h -g

Automata.o: Automata.cpp Automata.h
	g++ -c Automata.cpp -g

State.o: State.cpp State.h
	g++ -c State.cpp -g

clean:
	rm *.o
	rm *.h.gch
