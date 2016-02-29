Project1: main.o timer.o
	g++ -std=c++11 -pthread -g -Wall main.o timer.o -o Project1

main.o: main.cpp timer.h
	g++ -std=c++11 -pthread -g -Wall -c main.cpp

timer.o: timer.h timer.cpp
	g++ -std=c++11 -g -Wall -c timer.cpp

clean:
	rm *.o Project1
	echo clean done
