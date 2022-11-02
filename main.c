#include <stdio.h>
#include "biblioteca/Tracks.h"

int main(void) {
	FILE* f = TrackAbreArquivo();
	Track track = NULL;
	TrackLe(track, f);
  return 0;
}