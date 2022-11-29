#include "window.h"

bool window_init(struct Window* self) {

   SDL_Init(SDL_INIT_VIDEO);
   IMG_Init(IMG_INIT_PNG);
   TTF_Init();
   SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );

   self->window = SDL_CreateWindow("Pentris²", 0, 60, 1900, 2000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   if (self->window != NULL) {
      SDL_SetWindowFullscreen(self->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
      self->fullscreen = true;
      SDL_GetWindowSize(self->window, &(self->width), &(self->height));
      return true;
   } else {
      return false;
   }
}

void handle_events(struct Window* self) {
   SDL_Event event;

   for (int i = 0; i < CONTROLS_COUNT; i++) {
      if (self->action[i] == PRESSED) {
         self->action[i] = TOGGLED;
      }
   }

   while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
         self->action[QUIT] = PRESSED;
         break;
      case SDL_KEYDOWN:
         switch (event.key.keysym.sym) {
         case SDLK_q:
            self->action[MAP_ROTATION_CCW] = PRESSED;
            break;
         case SDLK_d:
            self->action[MAP_ROTATION_CW] = PRESSED;
            break;
         case SDLK_z:
            self->action[POLY_UP] = PRESSED;
            break;
         case SDLK_s:
            self->action[POLY_DOWN] = PRESSED;
            break;
         case SDLK_LCTRL:
            self->action[POLY_INVERT_ROTATION] = PRESSED;
            break;
         case SDLK_SPACE:
            self->action[POLY_SPEEDUP] = PRESSED;
            break;
         case SDLK_ESCAPE:
            self->action[MENU] = PRESSED;
            break;
         case SDLK_F11:
            if (self->fullscreen == true) {
               SDL_SetWindowFullscreen(self->window, 0);
               self->fullscreen = false;
            } else {
               SDL_SetWindowFullscreen(self->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
               self->fullscreen = true;
            }
            break;
         }
         break;
      case SDL_KEYUP:
         switch (event.key.keysym.sym) {
         case SDLK_q:
            self->action[MAP_ROTATION_CCW] = NONE;
            break;
         case SDLK_d:
            self->action[MAP_ROTATION_CW] = NONE;
            break;
         case SDLK_z:
            self->action[POLY_UP] = NONE;
            break;
         case SDLK_s:
            self->action[POLY_DOWN] = NONE;
            break;
         case SDLK_LCTRL:
            self->action[POLY_INVERT_ROTATION] = NONE;
            break;
         case SDLK_SPACE:
            self->action[POLY_SPEEDUP] = NONE;
            break;
         case SDLK_ESCAPE:
            self->action[MENU] = NONE;
            break;
         }
         break;
      case SDL_MOUSEBUTTONDOWN:
         switch (event.button.button) {
         case SDL_BUTTON_LEFT:
            self->action[POLY_ROTATION_LEFT] = PRESSED;
            break;
         case SDL_BUTTON_RIGHT:
            self->action[POLY_ROTATION_RIGHT] = PRESSED;
            break;
         }
         break;
      case SDL_MOUSEBUTTONUP:
         switch (event.button.button) {
         case SDL_BUTTON_LEFT:
            self->action[POLY_ROTATION_LEFT] = NONE;
            break;
         case SDL_BUTTON_RIGHT:
            self->action[POLY_ROTATION_RIGHT] = NONE;
            break;
         }
         break;
      }
   }
}

void window_destroy(struct Window* self) {

}