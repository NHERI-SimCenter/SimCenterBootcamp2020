CC=/usr/local/opt/llvm/bin/clang 

INCLUDES=-I/usr/local/opt/llvm/include
COPTS=-fopenmp -L/usr/local/opt/llvm/lib -O3

help:
	@echo "usage: "
	@echo ""
	@echo "   make help       ... displays this message"
	@echo "   make all        ... compiles pi and pi-omp"
	@echo "   make pi         ... compiles only pi.c -> pi"
	@echo "   make pi-omp     ... compiles only pi-omp.c -> pi-omp"
	@echo "   make clean      ... removes all executables"
	@echo "   make run        ... demos both versions (compiles if necessary)"
	@echo ""

all: pi pi-omp

clean:
	rm -f pi pi-omp a.out

run: all
	@echo "*** running pi ...\n"
	time ./pi
	@echo
	@echo "*** running pi-omp with 1 thread ...\n"
	time ./pi-omp 1
	@echo
	@echo "*** running pi-omp with 2 threads ...\n"
	time ./pi-omp 2
	@echo
	@echo "*** running pi-omp with 4 threads ...\n"
	time ./pi-omp 4
	@echo
	@echo "*** running pi-omp with 8 threads ...\n"
	time ./pi-omp 8
	@echo
	@echo "*** done"
	
pi: pi.c Makefile
	${CC} pi.c -o pi ${INCLUDES} ${COPTS}

pi-omp: pi-omp.c Makefile
	${CC} pi-omp.c -o pi-omp ${INCLUDES} ${COPTS}

