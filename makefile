Project1: main.o timer.o Calendar.o
	g++ -std=c++11 -pthread -g -Wall main.o timer.o Calendar.o -o Project2

timer.o: timer.h timer.cpp
	g++ -std=c++11 -g -Wall -c timer.cpp

Calendar.o: Calendar.h Calendar.cpp
	g++ -std=c++11 -g -Wall -c Calendar.cpp

main.o: main.cpp timer.h
	g++ -std=c++11 -pthread -g -Wall -c main.cpp

clean:
	rm *.o Project2
	echo clean done
