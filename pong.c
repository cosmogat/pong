/* 23-02-2013 */
/* billy */
/* pong.c */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

int main () {
  int tam_x = 1024, tam_y = 576, desp = 4, punts1 = 0, punts2 = 0, inclinacio = 3;
  char text1[5], text2[5];
  SDL_Surface *pant, *barreta1_sur, *barreta2_sur, *fons_sur, *pilota_sur, *marcador1_sur, *marcador2_sur;
  SDL_Event event;
  SDL_Rect barreta1_rec, barreta2_rec, fons_rec, pilota_rec, marcador1_rec, marcador2_rec;
  Uint8 *estatTecles;
  SDL_Color color;
  typedef struct {
    int sent;
    int incl;
  } Pilota;
  Pilota pil;
  color.r = color.g = color.b = 255;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Error en SDL_Init(): %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  if (TTF_Init() < 0) {
    fprintf(stderr, "Error en TTF_Init(): %s\n", SDL_GetError());
    exit(1);
  }
  atexit(TTF_Quit);
  pant = SDL_SetVideoMode(tam_x, tam_y, 0, SDL_HWSURFACE | SDL_FULLSCREEN);
  /* pant = SDL_SetVideoMode(tam_x, tam_y, 0, SDL_HWSURFACE | SDL_ANYFORMAT); */
  if (pant == NULL) {
    fprintf(stderr, "Error al crear la superficie: %s\n", SDL_GetError());
    exit(1);
  }
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
    fprintf(stderr, "No es pot establir el mode d'audio: %s.\n", SDL_GetError());
    exit(1);
  }
  SDL_WM_SetCaption("Pong...", NULL);
  barreta1_sur = SDL_LoadBMP("./img/barreta.bmp");
  if (barreta1_sur == NULL) {
    fprintf(stderr, "No es pot carregar la imatge: %s\n", SDL_GetError());
    exit(1);
  }
  barreta2_sur = SDL_LoadBMP("./img/barreta.bmp");
  if (barreta2_sur == NULL) {
    fprintf(stderr, "No es pot carregar la imatge: %s\n", SDL_GetError());
    exit(1);
  }
  fons_sur = SDL_LoadBMP("./img/fons.bmp");
  if (barreta2_sur == NULL) {
    fprintf(stderr, "No es pot carregar la imatge: %s\n", SDL_GetError());
    exit(1);
  }
  pilota_sur = SDL_LoadBMP("./img/pilota.bmp");
  if (barreta2_sur == NULL) {
    fprintf(stderr, "No es pot carregar la imatge: %s\n", SDL_GetError());
    exit(1);
  }
  SDL_EnableKeyRepeat(1, 1);
  TTF_Font *font = TTF_OpenFont("./ttf/large9.ttf", 100);
  Mix_Chunk *soBe = Mix_LoadWAV("./wav/be.wav");
  Mix_Chunk *soMal = Mix_LoadWAV("./wav/mal.wav");
  fons_rec.x = 0;
  fons_rec.y = 0;
  fons_rec.w = fons_sur->w;
  fons_rec.h = fons_sur->h;
  barreta1_rec.x = (Uint16) tam_x * 0.94;
  barreta1_rec.y = (Uint16) tam_y * 0.5 - 40;
  barreta1_rec.w = barreta1_sur->w;
  barreta1_rec.h = barreta1_sur->h;
  barreta2_rec.x = (Uint16) tam_x * 0.06 - 20;
  barreta2_rec.y = (Uint16) tam_y * 0.5 - 40;
  barreta2_rec.w = barreta2_sur->w;
  barreta2_rec.h = barreta2_sur->h;
  pilota_rec.x = (Uint16) tam_x * 0.5;
  pilota_rec.y = (Uint16) tam_y * 0.5;
  pilota_rec.w = barreta2_sur->w;
  pilota_rec.h = barreta2_sur->h;
  pil.incl = 0;
  pil.sent = 1;
  Mix_VolumeChunk(soBe, 100);
  Mix_VolumeChunk(soMal, 100);
  Mix_AllocateChannels(2);
  while (1) {
    pilota_rec.x += (pil.sent * desp);
    pilota_rec.y = pilota_rec.y + pil.incl;
    if (pilota_rec.x <= 0 || pilota_rec.x >= tam_x) {
      if (pilota_rec.x <= 0)
	punts1++;
      else
	punts2++;
      Mix_PlayChannel(1, soMal, 0.5);
      SDL_Delay(500);
      pilota_rec.x = tam_x * 0.5;
      pilota_rec.y = tam_y * 0.5;
      pil.incl = 0;
      pil.sent = -pil.sent;
    }
    if ((pilota_rec.x <= (barreta2_rec.x + barreta2_rec.w)) && (pilota_rec.x >= (barreta2_rec.x - 10)) && (pilota_rec.y >= barreta2_rec.y) && (pilota_rec.y <= (barreta2_rec.y + barreta2_rec.h))) {
      pil.sent = 1;
      if (pil.incl == 0)
	pil.incl = inclinacio;
      Mix_PlayChannel(1, soBe, 0.5);
    }
    if ((pilota_rec.x >= barreta1_rec.x) && (pilota_rec.x <= barreta1_rec.x + 10) && (pilota_rec.y >= barreta1_rec.y) && (pilota_rec.y <= (barreta1_rec.y + barreta1_rec.h))) {
      pil.sent = -1;
      if (pil.incl == 0)
	pil.incl = inclinacio;
      Mix_PlayChannel(1, soBe, 0.5);
    }
    if ((pilota_rec.y <= 6) || (pilota_rec.y >= (tam_y - 6))) {
      pil.incl = -pil.incl;
      Mix_PlayChannel(1, soBe, 0.5);
    }
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
	estatTecles = SDL_GetKeyState(NULL);
	if (estatTecles[SDLK_k] && barreta1_rec.y < (tam_y - 80))
	  barreta1_rec.y+=desp;
	if (estatTecles[SDLK_i])
	  barreta1_rec.y-=desp;
	if (estatTecles[SDLK_s] && barreta2_rec.y < (tam_y - 80))
	  barreta2_rec.y+=desp;
	if (estatTecles[SDLK_w])
	  barreta2_rec.y-=desp;
	if (estatTecles[SDLK_m] && desp < 6) {
	  desp++;
	  pilota_rec.x = tam_x * 0.5;
	  pilota_rec.y = tam_y * 0.5;
	}
	if (estatTecles[SDLK_n] && desp > 4) {
	  desp--;
	  pilota_rec.x = tam_x * 0.5;
	  pilota_rec.y = tam_y * 0.5;
	}
	pilota_rec.x += (pil.sent * desp);
	pilota_rec.y = pilota_rec.y + pil.incl;
	if (pilota_rec.x <= 0 || pilota_rec.x >= tam_x) {
	  if (pilota_rec.x <= 0)
	    punts1++;
	  else
	    punts2++;
	  Mix_PlayChannel(1, soMal, 0.5);
	  SDL_Delay(500);
	  pilota_rec.x = tam_x * 0.5;
	  pilota_rec.y = tam_y * 0.5;
	  pil.incl = 0;
	  pil.sent = -pil.sent;
	}
	if ((pilota_rec.x <= (barreta2_rec.x + barreta2_rec.w)) && (pilota_rec.x >= (barreta2_rec.x - 10)) && (pilota_rec.y >= barreta2_rec.y) && (pilota_rec.y <= (barreta2_rec.y + barreta2_rec.h))) {
	  pil.sent = 1;
	  if (pil.incl == 0)
	    pil.incl = inclinacio;
	  Mix_PlayChannel(1, soBe, 0.5);
	}
	if ((pilota_rec.x >= barreta1_rec.x) && (pilota_rec.x <= barreta1_rec.x + 10) && (pilota_rec.y >= barreta1_rec.y) && (pilota_rec.y <= (barreta1_rec.y + barreta1_rec.h))) {
	  pil.sent = -1;
	  if (pil.incl == 0)
	    pil.incl = inclinacio;
	  Mix_PlayChannel(1, soBe, 0.5);
	}
	if ((pilota_rec.y <= 6) || (pilota_rec.y >= (tam_y - 6))) {
	  pil.incl = -pil.incl;
	  Mix_PlayChannel(1, soBe, 0.5);
	}
      }
      sprintf(text1, "%d", punts1);
      sprintf(text2, "%d", punts2);
      marcador1_sur = TTF_RenderText_Blended(font, text1, color);
      marcador2_sur = TTF_RenderText_Blended(font, text2, color);
      marcador1_rec.x = 0.75 * tam_x;
      marcador2_rec.x = 0.25 * tam_x;
      marcador1_rec.y = marcador2_rec.y = 0.05 * tam_y;
      marcador1_rec.h = marcador1_sur->h;
      marcador1_rec.w = marcador1_sur->w;
      marcador2_rec.h = marcador2_sur->h;
      marcador2_rec.w = marcador2_sur->w;
      SDL_BlitSurface(fons_sur, NULL, pant, &fons_rec);
      SDL_BlitSurface(barreta1_sur, NULL, pant, &barreta1_rec);
      SDL_BlitSurface(barreta2_sur, NULL, pant, &barreta2_rec);
      SDL_BlitSurface(pilota_sur, NULL, pant, &pilota_rec);
      SDL_BlitSurface(marcador1_sur, NULL, pant, &marcador1_rec);
      SDL_BlitSurface(marcador2_sur, NULL, pant, &marcador2_rec);
      SDL_Flip(pant);
      if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
	return 0;
    }
    sprintf(text1, "%d", punts1);
    sprintf(text2, "%d", punts2);
    marcador1_sur = TTF_RenderText_Blended(font, text1, color);
    marcador2_sur = TTF_RenderText_Blended(font, text2, color);
    marcador1_rec.x = 0.75 * tam_x;
    marcador2_rec.x = 0.25 * tam_x;
    marcador1_rec.y = marcador2_rec.y = 0.05 * tam_y;
    marcador1_rec.h = marcador1_sur->h;
    marcador1_rec.w = marcador1_sur->w;
    marcador2_rec.h = marcador2_sur->h;
    marcador2_rec.w = marcador2_sur->w;
    SDL_BlitSurface(marcador1_sur, NULL, pant, &marcador1_rec);
    SDL_BlitSurface(marcador2_sur, NULL, pant, &marcador2_rec);
    SDL_BlitSurface(fons_sur, NULL, pant, &fons_rec);
    SDL_BlitSurface(barreta1_sur, NULL, pant, &barreta1_rec);
    SDL_BlitSurface(barreta2_sur, NULL, pant, &barreta2_rec);
    SDL_BlitSurface(pilota_sur, NULL, pant, &pilota_rec);
    SDL_BlitSurface(marcador1_sur, NULL, pant, &marcador1_rec);
    SDL_BlitSurface(marcador2_sur, NULL, pant, &marcador2_rec);
    SDL_Flip(pant);
  }
  return 0;
}
