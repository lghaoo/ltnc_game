#include "Tile.h"
#include <fstream>
#include <iostream>
#include <sstream>

Tile::Tile(int x, int y, int tileType) {
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;

    gTileTexture.loadImg("map/tileset.png",gRenderer);
    if (!gTileTexture.loadImg("map/tileset.png",gRenderer))
    {
        std:: cout << "unable load tileset"<< std::endl;
    }
}

Tile::~Tile() {
    gTileTexture.free();
}

void Tile::render(SDL_Rect& camera, SDL_Rect gTileClips[]) {
    //If the tile is on screen
   // if(checkCollision(mBox, camera) && mType != -1) {
        //Show the tile
        gTileTexture.render(gRenderer, mBox.x , mBox.y , &gTileClips[mType]);
   // }
}

int Tile::getType() {
    return mType;
}

SDL_Rect Tile::getBox() {
    return mBox;
}

bool touchesWall( SDL_Rect box, vector<Tile*> tiles )
{
    //Go through the tiles
    for(Tile* tile : tiles)
    {
        //If the tile is a wall type tile
        if(tile->getType() == 0)
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tile->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Map::Map(int _level) {
    level = _level;
    switch(level) {
        case 1:
            set_tiles("map/map_level1.txt");
            break;
        case 2:
            set_tiles("map/map_level2.txt");
            break;
        case 3:
            set_tiles("map/map_level3.txt");
            break;
        case 4:
            set_tiles("map/map_level4.txt");
            break;
        case 5:
            set_tiles("map/map_level5.txt");
        default: break;
    }
}

bool Map::set_tiles(std::string file_path) {
        //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( file_path.c_str() );

    //If the map couldn't be loaded
    if( map.fail() )
    {
        printf( "Unable to load map map!\n" );
        tilesLoaded = false;
    }
        else
    {
       for( int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;

            //Read tile from map file
            map >> tileType;

            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }

            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
            {
                tile_set.push_back(new Tile(x,y,tileType));
                
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }


            //Move to next tile spot
            x += TILE_WIDTH;

            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_HEIGHT;
            }
        }

        //Clip the sprite sheet
        if( tilesLoaded )
        {
            tile_clips[1].x = 0;
            tile_clips[1].y = 0;
            tile_clips[1].w = TILE_WIDTH;
            tile_clips[1].h = TILE_HEIGHT;

            tile_clips[2].x = TILE_WIDTH;
            tile_clips[2].y = 0;
            tile_clips[2].w = TILE_WIDTH;
            tile_clips[2].h = TILE_HEIGHT;

            tile_clips[3].x = TILE_WIDTH*2;
            tile_clips[3].y = 0;
            tile_clips[3].w = TILE_WIDTH;
            tile_clips[3].h = TILE_HEIGHT;

            tile_clips[4].x = TILE_WIDTH*3;
            tile_clips[4].y = 0;
            tile_clips[4].w = TILE_WIDTH;
            tile_clips[4].h = TILE_HEIGHT;

            tile_clips[5].x = TILE_WIDTH*4;
            tile_clips[5].y = 0;
            tile_clips[5].w = TILE_WIDTH;
            tile_clips[5].h = TILE_HEIGHT;

            tile_clips[6].x = TILE_WIDTH*5;
            tile_clips[6].y = 0;
            tile_clips[6].w = TILE_WIDTH;
            tile_clips[6].h = TILE_HEIGHT;

            tile_clips[7].x = TILE_WIDTH*6;
            tile_clips[7].y = 0;
            tile_clips[7].w = TILE_WIDTH;
            tile_clips[7].h = TILE_HEIGHT;

            tile_clips[8].x = TILE_WIDTH*7;
            tile_clips[8].y = 0;
            tile_clips[8].w = TILE_WIDTH;
            tile_clips[8].h = TILE_HEIGHT;

            tile_clips[9].x = TILE_WIDTH*8;
            tile_clips[9].y = 0;
            tile_clips[9].w = TILE_WIDTH;
            tile_clips[9].h = TILE_HEIGHT;

            tile_clips[10].x = TILE_WIDTH*9;
            tile_clips[10].y = 0;
            tile_clips[10].w = TILE_WIDTH;
            tile_clips[10].h = TILE_HEIGHT;
        }
    }

    //Close the map
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

//In giá trị của x1 và y1 trong phương thức render để kiểm tra
void Map::render(SDL_Rect& camera) {
    for(Tile* tile : tile_set) {
        tile -> render(camera, tile_clips);
        
        
    }
}

int Map::getLevel()
{
    return level;
}