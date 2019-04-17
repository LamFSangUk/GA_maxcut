CC = g++
CFLAGS = -W -Wall -O3
TARGET = maxcut
OBJECTS = main.o graph.o timelimitation.o ga.o population.o chromosome.o

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

run: $(TARGET)
	./maxcut < maxcut.in > maxcut.out

main.o : global.h timelimitation.h ga.h graph.h main.cpp
graph.o : global.h graph.h graph.cpp
timelimitation.o : timelimitation.h
ga.o : global.h population.h ga.h ga.cpp
population.o : global.h chromosome.h population.h population.cpp
chromosome.o : global.h population.h chromosome.h chromosome.cpp

clean:
	rm *.o $(TARGET)
