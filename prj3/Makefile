CC = g++
CFLAGS = -g -pg -W -Wall -O3
TARGET = maxcut
OBJECTS = main.o graph.o timelimitation.o ga.o population.o chromosome.o

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

run: $(TARGET)
	./maxcut < maxcut.in > maxcut.out

main.o : main.cpp
graph.o : graph.cpp
timelimitation.o : timelimitation.cpp
ga.o : ga.cpp
population.o : population.cpp
chromosome.o : chromosome.cpp

clean:
	rm *.o $(TARGET)
