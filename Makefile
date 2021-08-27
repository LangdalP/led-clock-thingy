CC=g++
# -g is debug info
CFLAGS=-std=c++17 -Wall -O3

RGB_LIB_DISTRIBUTION=libs/rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

clockthingy: clockthingy.o $(RGB_LIBRARY)
	$(CC) $(CFLAGS) clockthingy.o -o clockthingy $(LDFLAGS)

clockthingy.o: main.cxx gfxutils.cxx
	$(CC) $(CFLAGS) -c main.cxx -o clockthingy.o

 $(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

clean:
	rm -f hello hello.o


