
#include "BaseObject.h"
#include "Common.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

BaseObject::BaseObject()
{
    pTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPosX = 0;
    mPosY = 0;
}
BaseObject::~BaseObject()
{
    free();

}
void BaseObject::setDimension(int w, int h)
{
    mWidth = w;
    mHeight = h;
}
 bool BaseObject :: loadImg( std::string path, SDL_Renderer* screen)
{
    free();

    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface= IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface , SDL_TRUE,SDL_MapRGB(load_surface->format, 255, 255 , 255));//thu
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if ( new_texture != NULL)//thu
        {
            mWidth = load_surface ->w;
            mHeight = load_surface -> h;
        }
        SDL_FreeSurface(load_surface);
        
    }
    else
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
    }
    pTexture = new_texture;
    return pTexture != NULL;
}


bool BaseObject::loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
                                    std::string textureText,
                                    SDL_Color textColor) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font, textureText.c_str(), textColor);
  if (NULL == textSurface) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
  } else {
    // Create texture from surface pixels
    pTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (NULL == pTexture) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  }

  // Return success
  return pTexture != NULL;
}

void BaseObject::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, SDL_Rect *dst_rect,
                      double angle, SDL_Point *center, SDL_RendererFlip flip)
{

  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  // Set clip rendering dimensions
  if (NULL != dst_rect) {
    renderQuad.w = dst_rect->w;
    renderQuad.h = dst_rect->h;
  } else if(NULL != clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, pTexture, clip, &renderQuad, -angle, center, flip);

}
void BaseObject::renderCenter(SDL_Renderer *renderer, int x_center, int y_center,
                            int w, int h, SDL_Rect *clip, double angle,
                            SDL_Point *center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen, w, h for sprites
  SDL_Rect renderQuad = {x_center - w / 2, y_center - h / 2, mWidth, mHeight};

  // Set clip rendering dimensions
  if (NULL != clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  // Render to screen
  SDL_RenderCopyEx(renderer, pTexture, clip, &renderQuad, -angle, center, flip);
}
void BaseObject::setPosition(int newX, int newY)
{
    mPosX = newX;
    mPosY= newY;
}
int BaseObject::getHeight() {return mHeight;}
int BaseObject::getWidth() {return mWidth;}
int BaseObject ::getX() { return mPosX;}
int BaseObject ::getY() {return mPosY;}


void BaseObject :: free()
{
    if (pTexture != NULL)
    {
        SDL_DestroyTexture(pTexture);
        pTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

}
void BaseObject::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(pTexture, alpha);
}
bool checkCollision(SDL_Rect a, SDL_Rect b) {
  return SDL_HasIntersection(&a, &b);
}
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font* gFont[TOTAL_FONT] = {NULL, NULL, NULL, NULL, NULL};
//Mix_Music *gMusic;
// Level player are currently in
int gLevel = 0;
int gMenuID = 0;