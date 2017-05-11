#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "elements.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode(unsigned int width, unsigned int height) {
  if(NULL == SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  reshape(width, height);
}

int main(int argc, char** argv) {
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_WM_SetCaption("DRAKANOPONG", NULL);

    int loop = 1;
    while(loop) {
      Uint32 startTime = SDL_GetTicks();

      /* affichage */
      glClear(GL_COLOR_BUFFER_BIT);

      SDL_GL_SwapBuffers();
      /* ****** */

      SDL_Event e;
      while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
          loop = 0;
          break;
        }

        switch(e.type) {
          case SDL_VIDEORESIZE:
            WINDOW_WIDTH = e.resize.w;
            WINDOW_HEIGHT = e.resize.h;
            setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
            break;

          case SDL_KEYDOWN:
            if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
              loop = 0;
            }
            break;

          default:
            break;
        }
      }

      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      if(elapsedTime < FRAMERATE_MILLISECONDS) {
        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
      }
    }



    SDL_Quit();

    return EXIT_SUCCESS;
}
