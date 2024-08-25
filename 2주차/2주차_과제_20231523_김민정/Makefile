cc=gcc
cflags = -W -g
target = main

objects = main.o count_page.o writing_arr.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o count_page.o writing_arr.o : reading.h

.PHONY : clean
clean :
	rm $(target) $(objects)
