
CXX = g++
CXXFLAGS = -Wall -g


main: test.o  
	$(CXX) $(CXXFLAGS) -o test test.o 

# The test.o target can be written more simply

test.o: test.cpp stacktrace.h
	$(CXX) $(CXXFLAGS) -c test.cpp


clean:
	rm -f main *.o
