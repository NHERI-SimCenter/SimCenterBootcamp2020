CC=/usr/local/opt/llvm/bin/clang 

INCLUDES=-I/usr/local/opt/llvm/include
COPTS=-fopenmp -L/usr/local/opt/llvm/lib

help:
	@echo "usage: "
	@echo ""
	@echo "   make help       ... displays this message"
	@echo "   make all        ... compiles hello and hello-omp"
	@echo "   make hello      ... compiles only hello.c -> hello"
	@echo "   make hello-omp  ... compiles only helloThreads.c -> hello-omp"
	@echo "   make clean      ... removes all executables"
	@echo "   make run        ... demos both versions (compiles if necessary)"
	@echo ""

all: hello hello-omp

clean:
	rm -f hello hello-omp a.out

run: all
	@echo "*** running hello ...\n"
	./hello
	@echo
	@echo "*** running hello-omp ...\n"
	./hello-omp
	@echo
	@echo "*** done"
	
hello: hello.c
	${CC} hello.c -o hello ${INCLUDES} ${COPTS}

hello-omp: helloThreads.c
	${CC} helloThreads.c -o hello-omp ${INCLUDES} ${COPTS}

