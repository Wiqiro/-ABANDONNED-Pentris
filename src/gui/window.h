#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


enum Controls {
   MAP_ROTATION_CW,
   MAP_ROTATION_CCW,
   POLY_ROTATION_LEFT,
   POLY_ROTATION_RIGHT,
   POLY_INVERT_ROTATION,
   POLY_UP,
   POLY_DOWN,
   POLY_SPEEDUP,
   MENU,
   QUIT,

   CONTROLS_COUNT,
};

enum InputState {
   NONE,
   PRESSED,
   TOGGLED,
};

struct Window {
   SDL_Window* window;
   enum InputState action[CONTROLS_COUNT];

   //SDL_DisplayMode DM;

   int width;
   int height;
   bool fullscreen;
};


bool window_init(struct Window* self);

void handle_events(struct Window* self);

void window_destroy(struct Window* self);

#endif