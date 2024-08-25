cc=g++
cflags = -W -g
target = main

objects = main.o str.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.cpp
	$(cc) $(cflags) -c -o $@ $<

main.o str.o : str.h
.PHONY : clean
clean :
	rm $(target) $(objects)
