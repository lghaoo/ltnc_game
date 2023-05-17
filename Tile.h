
#ifndef TILE_H_
#define TILE_H_


#include "BaseObject.h"
#include "Common.h"

//Tile constants
const int TOTAL_TILES = 121;
const int TILE_CLIP_WIDTH = 62;
const int TILE_CLIP_HEIGHT = 62;
const int TILE_WIDTH = 62;
const int TILE_HEIGHT = 62;
const int TOTAL_TILE_SPRITES = 11;

//The tile
class Tile
{
    public:
        //Initializes position and type
        Tile( int x, int y, int tileType );
        ~Tile();

        //Shows the tile
        void render( SDL_Rect& camera, SDL_Rect gTileClips[] );

        //Get the tile type
        int getType();

        //Get the collision box
        SDL_Rect getBox();

        bool get_x1() {return x1;}
        bool get_x2() {return x2;}
        bool get_x3() {return x3;}
        bool get_x4() {return x4;}
        bool get_x5() {return x5;}
        bool get_x6() {return x6;}
        bool get_x7() {return x7;}
        bool get_x8() {return x8;}
        bool get_x9() {return x9;}
        bool get_x10() {return x10;}

        void update_x1( bool x);
        void update_x2( bool x);
        void update_x3( bool x);
        void update_x4( bool x);
        void update_x5( bool x);
        void update_x6( bool x);
        void update_x7( bool x);
        void update_x8( bool x);
        void update_x9( bool x);
        void update_x10(bool x);
        

        
       
        





    private:
        //The attributes of the tile
        SDL_Rect mBox;

        BaseObject gTileTexture;

        //The tile type
        int mType;

        bool x1 = false;
        bool x2 = false;
        bool x3 = false;
        bool x4 = false;
        bool x5 = false;
        bool x6 = false;
        bool x7 = false;
        bool x8 = false;
        bool x9 = false;
        bool x10 = true;
};

bool touchesWall( SDL_Rect box, vector<Tile*> tiles);

class Map {
    // Map is a set of tiles
private:
    vector<Tile*> tile_set;
    SDL_Rect tile_clips[TOTAL_TILE_SPRITES];
    int level;
    //int x1 = -1, x2 = -1,y1 = -1,y2 = -1;

    
    
public:
    int LEVEL_WIDTH = 682;
    int LEVEL_HEIGHT = 682;
    Map() {}
    Map(int _level);
    vector<Tile*> get_tile_set() {return tile_set;};
    bool set_tiles(std::string file_path);
    void render(SDL_Rect& camera);
    
    int getLevel() ;
    
};
    

    


#endif