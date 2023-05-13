#include "menu.h"
#include <iostream>

TextObject::TextObject(SDL_Color _text_color, std::string _text_string, SDL_Rect _text_rect, int font_size, std::string _font_path)
{
    font= TTF_OpenFont(_font_path.c_str(),font_size);
    Background_rect= {0, 0 ,100,100};
    text_rect = _text_rect;
    text_color = _text_color;
    text_string = _text_string;
    Load_text_texture();

}
TextObject::~TextObject()
{
    text_texture.free();
}

void TextObject::update_text(std :: string new_text)
{
    text_string = new_text;
    Load_text_texture();
}
void TextObject::Load_text_texture()
{
    if (font != NULL)
    {
        text_texture.loadFromRenderedText(gRenderer,font,text_string,text_color);
    }
    else
     std::cout<<"unable loading font";
}
void TextObject::render_text_texture()
{
    text_texture.render(gRenderer, text_rect.x, text_rect.y, NULL, &text_rect);
}

Button::Button(std::string _button_name, SDL_Rect _button_rect)
{
    button_name = _button_name;
    button_rect = {_button_rect.x,_button_rect.y,_button_rect.w+50,_button_rect.h +10};

    SDL_Rect text_rect = {button_rect.x + 20, button_rect.y + 5, _button_rect.w , _button_rect.h -5 };
    button_textbox = new TextObject(WHITE_COLOR, button_name, text_rect, 25, "font/Southern.ttf");
    load_texture();

}
bool Button::is_press(int mouse_x, int mouse_y)
{
    return mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
        && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h;
}
void Button::load_texture()
{
    button_texture.loadImg("img/button0.png",gRenderer);
}

void Button::render() {
    button_texture.render(gRenderer, button_rect.x, button_rect.y, NULL, &button_rect);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &button_rect);
    button_textbox->render_text_texture();
}
void Button::free()
{
    button_texture.free();
}
