cc=gcc
cflags = -W -g
target = animal

objects = main.o dog.o turtle.o blackcow.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o dog.o turtle.o blackcow.o : animal.h

.PHONY : clean
clean :
	rm $(target) $(objects)
