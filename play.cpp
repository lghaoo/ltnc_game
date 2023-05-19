#include "play.h"
#include <iostream>

#include <bits/stdc++.h>

#include<conio.h>

using namespace std;

#define MAX 121

#define TRUE 1

#define FALSE  0

#define VOCUNG 1e9

int n = 121;

long long truoc[MAX];//mảng đánh dấu đường đi.

long long d[MAX];//mảng đánh dấu khoảng cách.

long long Matrix[MAX][MAX];//ma trận trọng số

long long chuaxet[MAX];//mảng đánh dấu đỉnh đã được gán nhãn.

int Box[11][11];
int s;//đỉnh đầu.

int t;//đỉnh cuối



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


void Play::getRoad(Map level)
{
    switch  (level.getLevel())
    {
    case 1 : getmap("map/map_level1.txt");
        break;
    case 2 : getmap("map/map_level2.txt");
        break;
    case 3 : getmap("map/map_level3.txt");
        break;
    case 4 : getmap("map/map_level4.txt");
        break;
    case 5 : getmap("map/map_level5.txt");
        break;
    
    default:
        break;
    }

}
 
void Play::getmap(string path)
{
    int a = 1;
    int b= 1;
    
     bool load = true;
    std::ifstream map( path.c_str() );
    if( map.fail() )
    {
        printf( "Unable to load map map in  play file!\n" );
        load = false;
    }
    else
    {
        int m;
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
    
     
     
        b++;
    }
    map.close();

}

void Play::moveToOtherBox(int Box[11][11] , int x, int y)
{
    if(Box[x][y] == 0) return;
    int up_1 = x - 1;
    if(Box[up_1][y] != 0) 
    {
        int i = x * 11 + y - 11;
        int j = up_1 * 11 + y - 11;
        Matrix[i][j] = Box[up_1][y];
    }
    int down_1 = x + 1;
    if(Box[down_1][y] != 0) 
    {
        int i = x * 11 +y -11;
        int j = down_1 * 11 + y -11;
        Matrix[i][j] = Box[down_1][y];
    }
    int left_1 = y - 1;
    if(Box[x][left_1] != 0) 
    {
        int i = x * 11 + y - 11;
        int j = x * 11 + left_1 -11;
        Matrix[i][j] = Box[x][left_1];
    }

    int right_1 =  y + 1;
    if(Box[x][right_1] != 0) 
    {
        int i = x * 11 + y - 11;
        int j = x * 11 + right_1 - 11;
        Matrix[i][j] = Box[x][right_1];
    }
}


void Play::Init(){


 
 //nhập đỉnh đầu và đỉnh cuối của đồ thị.

 //nhập ma trận của đồ thị.
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
 for (int i = 1 ; i <= 11 ; i++)
 {
    for (int j = 1 ; j <= 11;j++)
    {
        cout << Box[i][j]<<' ';
    }
    cout <<endl;
 }
 
//  for (int i = 1; i <= n; i++){
//   for (int j = 1; j <= n; j++){
//     if (Matrix[i][j] > 1000) Matrix[i][j] = VOCUNG;
//     if ( Matrix[i][j] == VOCUNG)
//       cout <<0<<' ';
//     else cout <<Matrix[i][j]<<' ';

//   }
//   cout <<endl;
//  }


}

void Play::Result(){

 cout<<"Duong di ngan nhat tu "<<s<<" den "<<t << " la"<<endl;

 cout<<t <<"<=";//in đỉnh cuối dưới dạng char.

 int i = truoc[t];

 while (i != s){

  cout<<i<<"<=";//in ra kết quả dưới dạng char.

  i = truoc[i];

 }

 cout<<s;//in đỉnh đầu dưới dạng char.

 cout<<endl<<"Do dai duong di la : "<< d[t];
 hp = d[t];

}

void Dijkstra(){

 int u, minp;

 //khởi tạo nhãn tạm thời cho các đỉnh.

 for (int v = 1; v <= n; v++){

  d[v] = Matrix[s][v];

  truoc[v] = s;

  chuaxet[v] = FALSE;

 }

 truoc[s] = 0;

 d[s] = 0;

 chuaxet[s] = TRUE;

 //bươc lặp

 while (!chuaxet[t]) {

  minp = VOCUNG;

  //tìm đỉnh u sao cho d[u] là nhỏ nhất

  for (int v = 1; v <= n; v++){

   if ((!chuaxet[v]) && (minp > d[v])){

    u = v;

    minp = d[v];

   }

  }

  chuaxet[u] = TRUE;// u la dinh co nhan tam thoi nho nhat

  if (!chuaxet[t]){

   //gán nhãn lại cho các đỉnh.

   for (int v = 1; v <= n; v++){

    if ((!chuaxet[v]) && (d[u] + Matrix[u][v] < d[v])){

     d[v] = d[u] + Matrix[u][v];

     truoc[v] = u;

    }

   }

  }

 }

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
    switch (newlevel.getLevel())
 {
 case 1:
 {
    s = 111;
    t = 21;

 }
    break;
case 2:
 {
    s = 8;
    t = 113;

 }
    break;
case 3:
 {
    s = 116;
    t = 17;

 }
    break;
case 4:
 {
    s = 55;
    t = 45;

 }
    break;
case 5:
 {
    s = 17;
    t = 72;

 }
    break;
 default:
    break;
 }
    Init();
    Dijkstra();
    Result();
    
   
}

void Play::get_hp1(Map level)
{
    
   switch (level.getLevel())
    {
    case 1:
        hp = 23;
        break;
    case 2:
        hp = 23;
        break;
    case 3:
        hp = 17;
        break;
    case 4:
        hp = 20;
        break;
    case 5:
        hp = 23;
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

bool Play :: is_game_over()
{
    bool res = false;
    if (hp < 0  &&  (!checkCollision(mBox,target))) res= true;
    
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