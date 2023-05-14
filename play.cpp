#include "play.h"
#include <iostream>
#include <cmath>


Play::Play()
{
   
}
void Play::init(Map level_)
{
    x_val = 0;
    y_val = 0;
    player_state = WAIK_RIGHT;

   mTexture.loadImg("img/right.png",gRenderer);
   if (mTexture.pTexture == NULL) std::cout<<1<<' ';
   switch (level_.getLevel())
    {
    case 1:
        mBox = {0,620, PLAYER_WIDTH,PLAYER_HEIGHT};
        break;
    case 2:
        mBox = {434,0,PLAYER_WIDTH,PLAYER_HEIGHT};
        break;
    case 3:
        mBox = {310,620,PLAYER_WIDTH,PLAYER_HEIGHT};
        break;
    case 4:
        mBox = {620,248,PLAYER_WIDTH,PLAYER_HEIGHT};
        break;
    case 5:
        mBox = {310,62,PLAYER_WIDTH,PLAYER_HEIGHT};
        break;
    
    default:
        break;
    }
    
   
    
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
    
     mBox.x += x_val;

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + PLAYER_WIDTH > SCREEN_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= x_val;
    }

    //Move the dot up or down
    mBox.y += y_val;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + PLAYER_HEIGHT > SCREEN_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= y_val;
    }

}

int Play::hp(Map level)
{

}

// bool Play::check_target(vector<Tile*>tiles,Map level)
// {
//     switch (level.getLevel())
//     {
//     case 1:
//     {
//         for (Tile* tile : tiles)
//         {
//             if (tile ->getType() == 6)
//             if ( checkCollision(mBox, tile->getBox)) 
//         }
//     }

//         break;
    
//     default:
//         break;
//     }
// }

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
   step = new TextObject(GREEN_COLOR,"step : ",{mBox.x + 5 ,mBox.y,20,20},20,"font/Southern.ttf");
  mTexture.render(gRenderer,mBox.x, mBox.y,NULL,&mBox,0,NULL,SDL_FLIP_NONE);
   step->render_text_texture();
  
  
    

}


int Play::getPosX() { return mBox.x; }
int Play::getPosY() { return mBox.y; } 