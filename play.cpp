#include "play.h"
#include <iostream>

#include <bits/stdc++.h>

#include<conio.h>

using namespace std;

// int n = 121;

int truoc[MAX];//mảng đánh dấu đường đi.
int d[MAX];//mảng đánh dấu khoảng cách.
int Matrix[MAX][MAX];//ma trận trọng số
int chuaxet[MAX];//mảng đánh dấu đỉnh đã được gán nhãn.

int Box[11][11];
// int s;//đỉnh đầu.

// int t;//đỉnh cuối



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





void Play::moveToOtherBox(int Box[11][11] , int x, int y)
{
    if(Box[x][y] == 0) return;
    if (x > 1)
    {
    int up_ = x - 1; 
    if(Box[up_][y] != 0) 
    {
        int i = x * sqrt(n) + y - sqrt(n);
        int j = up_ * sqrt(n) + y - sqrt(n);
        Matrix[i][j] = Box[up_][y];
    }
    }
    if ( x < 11)
    {
    int down_ = x + 1;
   
    if(Box[down_][y] != 0) 
    {
        int i = x * sqrt(n) +y - sqrt(n);
        int j = down_ * sqrt(n) + y - sqrt(n);
        Matrix[i][j] = Box[down_][y];
    }
    }
    if ( y > 1)
    {
    int left_ = y - 1;
    if(Box[x][left_] != 0) 
    {
        int i = x * sqrt(n) + y - sqrt(n);
        int j = x * sqrt(n) + left_ - sqrt(n);
        Matrix[i][j] = Box[x][left_];
    }
    }
    if ( y < 11)
    {
    int right_ =  y + 1;
   
    if(Box[x][right_] != 0) 
    {
        int i = x * sqrt(n) + y - sqrt(n);
        int j = x * sqrt(n) + right_ - sqrt(n);
        Matrix[i][j] = Box[x][right_];
    }
    }
}

void Play::Floyd(){

 for (int i = 1; i <= n; i++){
  for (int j = 1; j <= n; j++){
    Matrix[i][j] = VOCUNG;

  }
 }
 

 for (int i = 1 ; i <= 11 ; i++)
 {
    for (int j = 1 ; j <= 11;j++)
    {
        moveToOtherBox(Box , i , j);

    }
 }
 for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
            	if((Matrix[i][j] >  Matrix[i][k] + Matrix[k][j]) && (Matrix[i][k] != VOCUNG) && (Matrix[k][j] != VOCUNG))
                {
            		Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
                }
            }
        }
    }
    hp = Matrix[s][t];

}


void Play::check_hp(vector<Tile*> tiles )
{
    for (Tile* tile : tiles)
    {  
        if (checkCollision(mBox, tile->getBox()))
        {
           if (tile->getType() == 1 &&  tile->get_x1() == false)
            {
                hp -= 1;
                tile->update_x1( true);
            } 
            else if (tile->getType() == 2 && tile->get_x2() == false)
            {
                hp += 3;
                tile->update_x2( true);
            }
            else if(tile->getType() == 3 && tile->get_x3() == false)
            {
                 hp -= 5;
                 tile->update_x3( true);
            }
            else if(tile->getType() == 4 && tile->get_x4() == false)
            {
                hp += 4;   
                tile->update_x4( true);
            }
            else if (tile->getType() == 5 && tile->get_x5() == false)
            {
                hp += 2;
                tile->update_x5( true);
            }
            else if (tile->getType() == 6 && tile->get_x6() == false)
            {
                hp -= 1;
                tile->update_x6( true);
            }
            else if (tile->getType() == 7 && tile->get_x7() == false)
            {
                hp -= 4;
                tile->update_x7( true);
            }
            else if (tile->getType() == 8 && tile->get_x8() == false)
            {
                hp -= 2;
                tile->update_x8( true);
            }
            else if (tile->getType() == 9 && tile->get_x9() == false)
            {
                 hp -= 3;   
                 tile->update_x9( true);
            }
            // else if (tile->getType() == 10 && status_x.get_x10() == false)
            // {
            //      hp -= 1;   
            //      status_x.update_x10( false);
            // }
            
            
            
        }
    }
}


void Play::get_hp(Map newlevel)
{
    // std::string path;
    switch (newlevel.getLevel())
 {
 case 1:
 {
    path = "map/map_level1.txt";
    s = 111;
    t = 21;
    
 }
    break;
case 2:
 {
    path = "map/map_level2.txt";
    s = 8;
    t = 113;

 }
    break;
case 3:
 {
    path = "map/map_level3.txt";
    s = 116;
    t = 17;

 }
    break;
case 4:
 {
    path = "map/map_level4.txt";
    s = 55;
    t = 45;
   

 }
    break;
case 5:
 {
    path = "map/map_level5.txt";
    s = 17;
    t = 72;
 }
    break;
 default:
    break;
 }
      int a = 1;
      int b = 1;
     bool load = true;
     std::ifstream map(path.c_str() );
    if( map.fail() )
    {
        printf( "Unable to load map map in  play file!\n" );
        load = false;
    }
    else
    {
       
        int m = -1;
        while(map>>m)
        {
            if ( b > 11)
            {
                a += 1;
                b = 1;
            }
            switch (m)
            {

            case 1: Box[a][b] = 1;
            break;
            case 0: Box[a][b] = 0;
            break;
            case 2: Box[a][b] = 0;
            break;
            case 3: Box[a][b] = 5;
            break;
            case 4: Box[a][b] = 0;
            break;
            case 5: Box[a][b] = 0;
            break;
            case 6 : Box[a][b] = 1;
            break;
            case 7 : Box[a][b] = 4;
            break;
            case 8 : Box[a][b] = 2;
            break;
            case 9 : Box[a][b] = 3;
            break;
            case 10 : Box[a][b] = 1;
                break;
            
            default:
                break;
            }
            b++;
        }
    
    }
    map.close();

    Floyd();
    // Dijkstra();
    // Result();
   
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

bool Play :: is_game_over()
{
    bool res = false;
    if (hp <= 0  &&  (!checkCollision(mBox,target))) res= true;
    
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