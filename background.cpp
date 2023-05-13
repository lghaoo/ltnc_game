#include "background.h"

Background::Background()
{
    load_texture();
    background_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int w = menu_bg_texture.getWidth();
    int h = menu_bg_texture.getHeight();
    menu_bg_rect = {90,0, w, h*1.4};
}
Background::~Background()
{
    background_texture.free();
}

void Background::load_texture()
{
    background_texture.loadImg("img/bg_game.png",gRenderer);
    menu_bg_texture.loadImg("img/bg_choose.png",gRenderer);
}

void Background::render()
{
    background_texture.render(gRenderer,0,0,NULL,&background_rect);
}
void Background::render_menu()
{
    menu_bg_texture.render(gRenderer,menu_bg_rect.x , menu_bg_rect.y  ,NULL,&menu_bg_rect);
}
void Background::free_menu()
{
    menu_bg_texture.free();
}
