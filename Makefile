LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc

FLAGS= -march=native -O3 -Wall -fPIC -fopenmp

INCFLAGS = -I$(INCLUDE)

all: libvd

libvd: libvd-build

libvd-build: \
aux

	$(CC) -fPIC -shared -o $(LIB)/libvd.so \
$(OBJ)/bic.o

aux: $(SRC)/bic.c
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/bic.c -o $(OBJ)/bic.o

## Cleaning-up

clean:
	rm -f $(LIB)/lib*.so; rm -f $(OBJ)/*.o

cython:
	cython libvd_py.pyx

bindings:
	$(CC) -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing $(INCFLAGS) -I/usr/include/python2.7 -L$(LIB) -lvd -o $(LIB)/libvd_py.so libvd_py.c
