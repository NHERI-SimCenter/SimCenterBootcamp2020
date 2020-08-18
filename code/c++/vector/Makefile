
FLAGS = -D_DEBUG

all:
	g++ $(FLAGS) Vector.cpp -c -o Vector.o
	g++ $(FLAGS) main.cpp Vector.o

test: all
	./a.out

clean:
	rm *~ *.o