#
# Makefile for os/demo_thread thread demonstration programs
#

# Makefile comments have a # as the first character of the line.

# This is a rule to make the "yell" program, which depends
# on the file "yell.c".  Make will execute the command:
#  "g++ yell.c -o yell -lpthread".  Note the leading tab
# before the command is required.

yell: yell.c
	gcc yell.c -o yell -lpthread

# A rule to make the "chase" program
chase: chase.C
	g++ chase.C -o chase -lpthread -lcurses

way: way.C
	g++ way.C -o way -lpthread

noway: noway.C
	g++ noway.C -o noway -lpthread

keyfork: keyfork.C
	g++ keyfork.C -o keyfork -lpthread

prime: prime.C
	g++ prime.C -o prime -lpthread

order_out: order_out.C
	g++ order_out.C -o order_out -lpthread

order_in: order_in.C
	g++ order_in.C -o order_in -lpthread

# The "readwrite" program depends on both "readwrite.C"
# and "rwlock.o".  Making readwrite may require rwlock.o
# to be remade as well.  "rwlock.o" depends on "rwlock.C"
# and "rwlock.h".

readwrite: readwrite.C rwlock.o
	g++ readwrite.C rwlock.o -o readwrite -lpthread
rwlock.o: rwlock.C rwlock.h
	g++ -c rwlock.C

philosophers: philosophers.C phillock.o
	g++ philosophers.C phillock.o -o philosophers -lpthread
phillock.o: phillock.C phillock.h
	g++ -c phillock.C

# Makefiles often include a phony target "clean" that removes
# all the .o files and executables.  Type 'make clean' to do this.
.PHONY: clean
clean:
	rm -f yell chase keyfork way noway prime prime2 order_in order_out readwrite rwlock.o philosophers phillock.o

# Makefiles often include a phony target "all" that makes everything
# Usually this is the first target, so that just typing 'make' will make all,
# but here you need to explicitly type 'make all'
.PHONY: all
all: yell chase way noway keyfork prime prime2 order_in order_out readwrite philosophers 
