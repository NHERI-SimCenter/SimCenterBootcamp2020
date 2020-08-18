
FLAGS = -D_DEBUG

all:
	g++ $(FLAGS) Vector.cpp -c -o Vector.o
	g++ $(FLAGS) Matrix.cpp -c -o Matrix.o
	g++ $(FLAGS) main.cpp Vector.o Matrix.o

test: all
	./a.out

clean:
	rm *~ *.o