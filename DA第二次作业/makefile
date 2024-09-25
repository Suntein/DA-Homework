.PHONY: clean
Chicken:Chicken.o
	g++ Chicken.o -o Chicken 
Chicken.o:Chicken.cpp
	g++ -std=c++11 -c Chicken.cpp
clean:
	rm -f Chicken *.o