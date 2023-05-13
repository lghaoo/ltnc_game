#ifndef UTILS_H_
#define UTILS_H_

#include "BaseObject.h"

void logSDLError(std::ostream& os, const std::string& message, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
#endif