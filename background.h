#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "Common.h"
#include "BaseObject.h"
#include "SDL.h"
#include "SDL_image.h"

class Background
{
    private:
       BaseObject background_texture;
       BaseObject menu_bg_texture;
       SDL_Rect background_rect;
       SDL_Rect menu_bg_rect;
    public:
       Background();
       ~Background();
       void load_texture();
       void render();
       void render_menu();
       void free_menu();

};

#endif