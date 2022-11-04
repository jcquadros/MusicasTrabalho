FLAGS = -Wall -Wno-unused-result

DEPS = tads/Musica.h tads/Vector.h
OBJ = tads/Musica.o main.o tads/Vector.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(FLAGS)

all: $(OBJ)
	gcc -o main $(OBJ) $(FLAGS)

clean:
	rm -f main tads/*.o main.o

run:
	./main