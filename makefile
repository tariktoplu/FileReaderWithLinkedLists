hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/Exception.o -c ./src/Exception.cpp
	g++ -I ./include/ -o ./lib/GenList.o -c ./src/GenList.cpp
	g++ -I ./include/ -o ./lib/GenNode.o -c ./src/GenNode.cpp
	g++ -I ./include/ -o ./lib/KromozomList.o -c ./src/KromozomList.cpp
	g++ -I ./include/ -o ./lib/KromozomNode.o -c ./src/KromozomNode.cpp
	g++ -I ./include/ -o ./lib/NoSuchElement.o -c ./src/NoSuchElement.cpp
	g++ -I ./include/ -o ./bin/Main ./src/Main.cpp ./lib/*.o
	
calistir:
	./bin/Main
