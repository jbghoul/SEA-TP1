ROOTDIR=../libhw
LIBNAME=hw
LIBFILE=$(ROOTDIR)/lib/lib$(LIBNAME).a

CC      = gcc
CFLAGS  = -Wall -pedantic -g -m32
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -l$(LIBNAME)

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= main exercice1 exercice2 exercice3 TestPile exercice4 \
exercice5-6

all: $(BINARIES)

###------------------------------
### Main rules 
###------------------------------------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

Makefile.depends:
	$(CC) -MM *.c $(INCDIR) > Makefile.depends

include Makefile.depends

main: main.o $(LIBFILE)



###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) *.o $(BINARIES) Makefile.depends

