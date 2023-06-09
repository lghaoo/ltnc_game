#ifndef ANIMAL_H_
#define ANIMAL_H_


#include "BaseObject.h"
#include "Common.h"

class TextObject 
{
  private:
    TTF_Font* font;
    SDL_Rect Background_rect, text_rect;
    SDL_Color text_color;
    std:: string text_string;
    BaseObject text_texture;

  public:
    TextObject(SDL_Color _text_color, std::string _text_string, SDL_Rect _text_rect, int font_size, std::string _font_path);
    ~TextObject();

    void update_text(std::string new_text);
    void Load_text_texture();
    void render_text_texture();
    SDL_Rect get_rect() const {return text_rect;};
    std::string get_text() const {return text_string;};
    SDL_Color get_color() const {return text_color;};
     bool is_press(int mouse_x, int mouse_y);

};

class Button
{
  private:
    TextObject* button_textbox;
    SDL_Rect src_rect, button_rect;
    std::string button_name;
    BaseObject button_texture;

  public:
    Button() {}
    Button( std::string button_name, SDL_Rect _button_rect, std::string path);

    void load_texture(std::string path);
    bool is_press(int mouse_x, int mouse_y);
    void render();
    void free();

};
#endif 