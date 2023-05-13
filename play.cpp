#include "play.h"
#include <iostream>
#include <cmath>


Play::Play()
{
    init();
}
void Play::init()
{
    x_val = 0;
    y_val = 0;
    player_state = WAIK_RIGHT;

   mTexture.loadImg("img/right.png",gRenderer);
   if (mTexture.pTexture == NULL) std::cout<<1<<' ';
    mBox = {62, 0 , PLAYER_WIDTH, PLAYER_HEIGHT};
  
  
    
}



Play::~Play()
{
    mTexture.free();
}
void Play::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
        {
           player_state = WAIK_UP;
            y_val -= PLAYER_SPEED;
          
           
        }
            break;
        case SDLK_DOWN:
        {
            player_state = WAIK_DOWN;
            y_val += PLAYER_SPEED;
           
           
        }
            break;
        case SDLK_LEFT:
        {
            player_state = WAIK_LEFT;
            x_val -= PLAYER_SPEED;
          

            
        }
            break;
        case SDLK_RIGHT:
        {
            player_state = WAIK_RIGHT;
            x_val += PLAYER_SPEED;
          
        }
        break;
        
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
            {
                player_state = WAIK_UP;
               y_val += PLAYER_SPEED;
              
            }
               break;
            case SDLK_DOWN:
            {
                player_state = WAIK_DOWN;
               y_val -= PLAYER_SPEED;
              
             
            }
               break;
            case SDLK_LEFT:
            {
                player_state = WAIK_LEFT;
               x_val += PLAYER_SPEED;
              
              
            }
               break;
            case SDLK_RIGHT:
            {
                player_state = WAIK_RIGHT;
               x_val -= PLAYER_SPEED;
             
             
            }
               break;
        
        default:
            break;
        }
    }
}

void Play::move(vector<Tile*> tiles, Map level) {
    //Increase the velocity
    
        
    mBox.x += x_val;
    
    if(touchesWall(mBox, tiles)) {
        mBox.x -= x_val;
        x_val = 0;
    }

    mBox.y += y_val;
  
    
    if(touchesWall(mBox, tiles)) {
       mBox.y -= y_val;
        y_val = 0;
     
    }
    

}

void Play::render(SDL_Rect &des)
{
   switch(player_state)
   {
    case WAIK_LEFT:
        mTexture.loadImg("img/left.png",gRenderer); 
        break;
    case WAIK_RIGHT:
        mTexture.loadImg("img/right.png",gRenderer);
        break;
    case WAIK_UP:
        mTexture.loadImg("img/up.png",gRenderer);        
        break;
    case WAIK_DOWN:
        mTexture.loadImg("img/down.png",gRenderer);
        break;
    default:
        break;
   }
  
   
  mTexture.render(gRenderer,mBox.x, mBox.y,&mBox);
  
    

}


int Play::getPosX() { return mBox.x; }
int Play::getPosY() { return mBox.y; } 