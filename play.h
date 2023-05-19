#ifndef PLAY_H_
#define PLAY_H_

#include "common.h"
#include "BaseObject.h"
#include "Tile.h"
#include "menu.h"


class Play
{
   
    public:
      Play();
      ~Play();
      enum WaikType
      {
     
        WAIK_RIGHT,
        WAIK_LEFT,
        WAIK_UP,
        WAIK_DOWN,
      };

      static const int PLAYER_WIDTH = 45;
      static const int PLAYER_HEIGHT = 45;
      static const int PLAYER_SPEED = 20;
     
    void init(Map level);

    void handleEvent(SDL_Event& e);

    void move(vector<Tile*> tiles, Map level);

    
    void render(SDL_Rect &des);


    
  
    SDL_Rect get_target(vector<Tile*> tiles);
    void getRoad(Map lelvel);
    void getmap(std:: string path);

    void check_hp(vector<Tile*> tiles);

    bool is_game_over();

    bool win();
    void get_hp(Map level);
    void get_hp1(Map level);
    void moveToOtherBox(int Box[11][11] , int x, int y);
    void Init();
    void Result();
    int getPosX();
    int getPosY();
   private:
   
    SDL_Rect mBox;
    TextObject *step, *hp_;
   
    WaikType player_state;
    
    float x_val, y_val;
  
    BaseObject mTexture;

    SDL_Rect target;

    int hp;

    //Map level;

    
    
};

#endif 