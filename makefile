CXX = g++
CXXFLAGS = -Wall

proj5: Lqueue.h driver.cpp Race.h Racer.o Racecar.o Formula.o Truck.o
	$(CXX) $(CXXFLAGS) Lqueue.h Race.h Racer.o Racecar.o Formula.o Truck.o driver.cpp -o proj5

##Race.o: Racer.o Racecar.o Race.h Race.cpp Lqueue.h
##	$(CXX) $(CXXFLAGS) -c Race.cpp

Formula.o: Formula.h Formula.cpp Racer.o
	$(CXX) $(CXXFLAGS) -c Formula.cpp

Truck.o: Truck.h Truck.cpp Racer.o
	$(CXX) $(CXXFLAGS) -c Truck.cpp

Racecar.o: Racecar.h Racecar.cpp Racer.o
	$(CXX) $(CXXFLAGS) -c Racecar.cpp

Racer.o: Racer.h Racer.cpp
	$(CXX) $(CXXFLAGS) -c Racer.cpp

run:
	./proj5

clean:
	rm *~

cleaner:
	rm *~
	rm *.o
val:
	valgrind ./proj5
