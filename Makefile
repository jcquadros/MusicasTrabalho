libtads.a: tads/Musica.c tads/Vector.c tads/Artista.c tads/Menu.c tads/Playlist.c tads/Musica.h tads/Vector.h tads/Artista.h tads/Menu.h  tads/Playlist.h
	gcc -c tads/Musica.c -o tads/Musica.o
	gcc -c tads/Vector.c -o tads/Vector.o
	gcc -c tads/Artista.c -o tads/Artista.o
	gcc -c tads/Menu.c -o tads/Menu.o
	gcc -c tads/Playlist.c -o tads/Playlist.o
	ar -crs libtads.a tads/Musica.o tads/Vector.o tads/Artista.o tads/Menu.o tads/Playlist.o
all: libtads.a main.c
	gcc -o main main.c -I tads -L . -ltads
run:
	./main
val:
	valgrind ./main
clean:
	rm -f *.a *.o tads/*.o main