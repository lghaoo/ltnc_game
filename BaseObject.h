
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <vector>



using namespace std;
 
 class BaseObject
 {
    public:
       BaseObject();
       ~BaseObject();
      
       // Create image from font string
      bool loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
                            std::string textureText, SDL_Color textColor);
       // Loads image at specified path
       virtual bool loadImg(std:: string path, SDL_Renderer* screen);

       // Renders texture at given point
      void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL, SDL_Rect* dst_rect = NULL,
              double angle = 0.0, SDL_Point *center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

      void renderCenter(SDL_Renderer *renderer, int x_center, int y_center, int w,
                    int h, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

      void free();

      

      bool is_press(int mouse_x, int mouse_y);


       int getWidth();
       int getHeight();
       int getX();
       int getY();

       void setDimension(int w, int h);
       void setPosition(int newX, int newY);




    //protected:
       SDL_Texture* pTexture; //thông tin ảnh

      int mWidth;
      int mHeight;
      int mPosX;
      int mPosY;
 };

 
 bool checkCollision(SDL_Rect a, SDL_Rect b);

extern vector<BaseObject> allTextures;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

enum FontType {
  NEXA_LIGHT = 0,
  NEXA_BOLD,
  NEXA_LIGHT_10,
  NEXA_BOLD_10,
  NEXA_BOLD_20,
  TOTAL_FONT
};

extern TTF_Font *gFont[TOTAL_FONT];





#endif