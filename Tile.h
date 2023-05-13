
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

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        BaseObject gTileTexture;

        //The tile type
        int mType;
};

bool touchesWall( SDL_Rect box, vector<Tile*> tiles);

class Map {
    // Map is a set of tiles
private:
    vector<Tile*> tile_set;
    SDL_Rect tile_clips[TOTAL_TILE_SPRITES];
    int level;
    int x1 = -1, x2 = -1,y1 = -1,y2 = -1;

    
    
public:
    int LEVEL_WIDTH = 682;
    int LEVEL_HEIGHT = 682;
    Map() {}
    Map(int _level);
    vector<Tile*> get_tile_set() {return tile_set;};
    bool set_tiles(std::string file_path);
    void render(SDL_Rect& camera);
    int get_pos_start_x_();
    int get_pos_start_y_();
    int get_pos_x_target();  
    int get_pos_y_target(); 
    
};
    
//void get_position_start(Map level);
    


#endif