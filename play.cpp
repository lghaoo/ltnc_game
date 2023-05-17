#include "play.h"
#include <iostream>
#include <cmath>
#include <string>


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


// void Play::check_hp(vector<Tile*> tiles)
// {
//     for (Tile* tile : tiles)
//     {  
//         if (checkCollision(mBox, tile->getBox()))
//         {
//            if (tile->getType() == 1 && status_x.get_x1() == false)
//             {
//                 hp -= 1;
//                 status_x.update_x1( true);
//             } 
//             else if (tile->getType() == 2 && status_x.get_x2() == false)
//             {
//                 hp += 3;
//                 status_x.update_x2( true);
//             }
//             else if(tile->getType() == 3 && status_x.get_x3() == false)
//             {
//                  hp -= 5;
//                  status_x.update_x3( true);
//             }
//             else if(tile->getType() == 4 && status_x.get_x4() == false)
//             {
//                 hp += 4;   
//                 status_x.update_x4( true);
//             }
//             else if (tile->getType() == 5 && status_x.get_x5() == false)
//             {
//                 hp += 2;
//                 status_x.update_x5( true);
//             }
//             else if (tile->getType() == 6 && status_x.get_x6() == false)
//             {
//                 hp -= 1;
//                 status_x.update_x6( true);
//             }
//             else if (tile->getType() == 7 && status_x.get_x7() == false)
//             {
//                 hp -= 4;
//                 status_x.update_x7( true);
//             }
//             else if (tile->getType() == 8 && status_x.get_x8() == false)
//             {
//                 hp -= 2;
//                 status_x.update_x8( true);
//             }
//             else if (tile->getType() == 9 && status_x.get_x9() == false)
//             {
//                  hp -= 3;   
//                  status_x.update_x9( true);
//             }
//             // else if (tile->getType() == 10 && status_x.get_x10() == false)
//             // {
//             //      hp -= 1;   
//             //      status_x.update_x10( false);
//             // }
            
            
            
//         }
//     }
// }


int Play::get_hp(Map level)
{
    switch (level.getLevel())
    {
    case 1:
        hp = 23;
        break;
    case 2:
        hp = 17;
        break;
    case 3:
        hp = 15;
        break;
    case 4:
        hp = 7;
        break;
    
    
    default:
        break;
    }

}

SDL_Rect Play::get_target(vector<Tile*>tiles)
{
    for (Tile* tile : tiles)
    {
        if(tile->getType() == 6)
        {
            target = tile->getBox();
        }
    }

}

bool Play::win()
{
    int res = false;
    

    if (checkCollision(mBox , target) && hp >= 0) res = true;

    return res;     
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
   step = new TextObject(GREEN_COLOR,"step: " + to_string(hp),{mBox.x + 5 ,mBox.y - 10,30,15},25,"font/Regular.ttf");
   //hp_ = new TextObject(GREEN_COLOR,to_string(hp),{mBox.x + 20 ,mBox.y,20,20},15,"font/Southern.ttf");
  mTexture.render(gRenderer,mBox.x, mBox.y,NULL,&mBox,0,NULL,SDL_FLIP_NONE);
   step->render_text_texture();
   //hp_->render_text_texture();
  
  
    

}


int Play::getPosX() { return mBox.x; }
int Play::getPosY() { return mBox.y; } 