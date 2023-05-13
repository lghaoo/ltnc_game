#include "mainloop.h"

Mainloop::Mainloop()
{
    level1= Map(1);
    level2 = Map(2);
    level3 = Map(3);
    level4 = Map(4);
    level5 = Map(5); 
    game_state = STARTING_SCREEN;
    map = level1;

    screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  

    you_win = new TextObject(RED_COLOR,"congratulations !!",{SCREEN_WIDTH/2,50,300,100},100,"font/Southern.ttf");
    you_lose = new TextObject(RED_COLOR,"oh, you lose :< ",{SCREEN_WIDTH/2,50,300,100},100,"font/Southern.ttf");

    play_= new Button("PLay",{SCREEN_WIDTH/2 +100, SCREEN_HEIGHT/2 +130, 100, 100});
    
    quit_= new Button("Quit",{SCREEN_WIDTH/2, SCREEN_HEIGHT/2+130,100,100});
    replay_ = new Button("Replay",{SCREEN_WIDTH/2, SCREEN_HEIGHT/2,100,100});

    level1_ = new Button("Level 1",{270,150,80,70});
    level2_ = new Button("Level 2",{270,245,80,70});
    level3_ = new Button("Level 3",{270,340,80,70});
    level4_ = new Button("Level 4",{270,435,80,70});
    level5_ = new Button("Level 5",{270,530,80,70});

    bg_start.loadImg("img/bg.png",gRenderer);
    bg_start_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
}

void Mainloop::render_game()
{
    
    

    switch (game_state)
    {
    case STARTING_SCREEN:
    {
        bg_start.render(gRenderer,0,0,NULL,&bg_start_rect);
        play_ ->render();
    }
        break;
    case CHOOSING_LEVEL:

    {
        bg_start.free();
        
        play_ ->free();
        
        back_ground.render();
        back_ground.render_menu();
        level1_->render();
        level2_->render();
        level3_->render();
        level4_->render();
        level5_->render();
    }
    break;
    case PLAYING_THE_GAME:
    {
        back_ground.free_menu();
        back_ground.render();
        map.render(screen);
        
        car.render(screen);


    }
    break;
    
    default:
        break;
    }

}

void Mainloop::handle_event(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            update_game_state(QUITTING_THE_GAME);
        }
        switch (game_state)
        {
        case STARTING_SCREEN:
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x , &y);
                if (play_ ->is_press(x,y))
                {
                    update_game_state(CHOOSING_LEVEL);
                };
            }

        }
            break;
        case CHOOSING_LEVEL:
        {
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(level1_->is_press(x,y))
                {
                    map = level1;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level2_->is_press(x,y))
                {
                    map = level2;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level3_->is_press(x,y))
                {
                    map = level3;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if(level4_->is_press(x,y))
                {
                   map = level4;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level5_->is_press(x,y))
                {
                    map = level5;
                    update_game_state(PLAYING_THE_GAME);
                }
            }
        }
        break;
        case PLAYING_THE_GAME:
        {
            car.handleEvent(event);


        }
        
        default:
            break;
        }
    }
}

GameState Mainloop::get_game_state()
{
    return game_state;
}
void Mainloop::update_game_state(GameState new_state)
{
    game_state = new_state;
}