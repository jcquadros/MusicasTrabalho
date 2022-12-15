
libtads.a: tads/Musica.c tads/Vector.c tads/Artista.c tads/Menu.c tads/Playlist.c tads/Musica.h tads/Vector.h tads/Artista.h tads/Menu.h  tads/Playlist.h
	gcc -c tads/Musica.c -o tads/Musica.o -Wall -Wno-unused-result
	gcc -c tads/Vector.c -o tads/Vector.o -Wall -Wno-unused-result
	gcc -c tads/Artista.c -o tads/Artista.o -Wall -Wno-unused-result
	gcc -c tads/Menu.c -o tads/Menu.o -Wall -Wno-unused-result
	gcc -c tads/Playlist.c -o tads/Playlist.o -Wall -Wno-unused-result
	ar -crs libtads.a tads/Musica.o tads/Vector.o tads/Artista.o tads/Menu.o tads/Playlist.o
all: libtads.a main.c
	gcc -o main main.c -I tads -L . -ltads -Wall -Wno-unused-result -lm
run:
	./main data/artists_full.csv data/tracks_full.csv
val:
	valgrind ./main data/artists_full.csv data/tracks_full.csv
clean:
	rm -f *.a *.o tads/*.o main