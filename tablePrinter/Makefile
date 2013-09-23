
CXX = g++
CXXFLAGS = -Wall -g


main: main.o table_printer.o 
	$(CXX) $(CXXFLAGS) -o main main.o table_printer.o

# The main.o target can be written more simply

main.o: main.cpp table_printer.h
	$(CXX) $(CXXFLAGS) -c main.cpp

table_printer.o: table_printer.h

clean:
	rm -f main *.o
