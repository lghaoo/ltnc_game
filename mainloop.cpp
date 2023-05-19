#include "mainloop.h"

Mainloop::Mainloop()
{
    level1= Map(1);
    level2 = Map(2);
    level3 = Map(3);
    level4 = Map(4);
    level5 = Map(5); 
    game_state = STARTING_SCREEN;

   
   
    tmp  = -1;
    screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  
    play_= new Button("Play",{SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 , 100, 80},"img/button0.png");
    instructions = new  Button("Instructions",{SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 +110, 130, 80},"img/button0.png");
    quit_= new Button("Quit",{SCREEN_WIDTH/2, SCREEN_HEIGHT/2+220,100,80}, "img/button0.png");
     
    level1_ = new Button("Level 1",{270,150,80,70},"img/button0.png");
    level2_ = new Button("Level 2",{270,245,80,70},"img/button0.png");
    level3_ = new Button("Level 3",{270,340,80,70},"img/button0.png");
    level4_ = new Button("Level 4",{270,435,80,70},"img/button0.png");
    level5_ = new Button("Level 5",{270,530,80,70},"img/button0.png");
    
    //quit_= new Button("Quit",{SCREEN_WIDTH/2, SCREEN_HEIGHT/2+130,100,100});
    sound_background = start_game;
    if ( !LoadMusic())
    {
        std::cout<<-1<<std::endl;
    }
    instruc.loadImg("img/instruction.png",gRenderer);
    instruc_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    bg_start.loadImg("img/bg.png",gRenderer);
    bg_start_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    game_over.loadImg("img/game_over.png",gRenderer);

    level_up.loadImg("img/levelup.png",gRenderer);

}

void Mainloop::render_game()
{
    
    

    switch (game_state)
    {
    case STARTING_SCREEN:
    {
       
        
        instruc.free();
        bg_start.render(gRenderer,0,0,NULL,&bg_start_rect);
        play_ ->render();
        instructions ->render();
        quit_ -> render();
    }
        break;
    case INSTRUCTION:
    {
        
        instruc.loadImg("img/instruction.png",gRenderer);
        instruc_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        instruc.render(gRenderer,0,0,NULL,&instruc_rect);
        quit_intro = new TextObject(GREEN_COLOR,"quit",{SCREEN_WIDTH/2 + 150,SCREEN_HEIGHT/2 + 170,70,70},70,"font/Southern.ttf");
        quit_intro->render_text_texture();
        
    }
    break;
    case CHOOSING_LEVEL:

    {
        bg_start.free();
        
        play_ ->free();
        instructions ->free();
        
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
        
        back_ground.render();
        map.render(screen);
        
        car.render(screen);

    }
    break;
    case WIN:
    {


        play_next= new Button("  ",{ 270, 430, 86,84},"img/play_next2.png");

        menu = new Button (" ", {130,433,55,70},"img/menu1.png");

        exit = new Button(" ",{430,435,55,70},"img/exit.png");
        
        replay = new Button (" ",{270,420,76,84},"img/replay1.png");



        back_ground.render();
        level_up_rect = {200, 100,level_up.getWidth()*1.5,level_up.getHeight()*1.5};
       
        level_up.render(gRenderer,70,0,NULL,&level_up_rect);

        

       if ( tmp == 1 || tmp == 2 || tmp == 3 || tmp == 4)
       {
        play_next->render();
        menu->render();
        exit->render();
       
      
       }
       else if ( tmp == 5)
       {
        replay->render();
        menu->render();
        exit->render();
        
       }
    }
    break;
    case GAME_OVER:
    {
        game_over_rect = { 0, 0, game_over.getWidth()*1.2,game_over.getHeight()*1.2};
      
        back_ground.render();
        game_over.render(gRenderer,40,85,NULL,&game_over_rect);
   
        menu = new Button (" ", {130,433,55,70},"img/menu1.png");

        exit = new Button(" ",{430,435,55,70},"img/exit.png");
        
        replay = new Button (" ",{270,420,76,84},"img/replay1.png");

        menu->render();
        exit->render();
        replay->render();



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
                     Mix_PlayChannel(-1, button_select_sound, 0);

                    update_game_state(CHOOSING_LEVEL);
                }
                else if (instructions ->is_press( x ,y))
                {
                    Mix_PlayChannel(-1, button_select_sound, 0);

                    update_game_state(INSTRUCTION);
                }
                else if (quit_ ->is_press(x,y))
                {
                    Mix_PlayChannel(-1, button_select_sound, 0);

                    update_game_state(QUITTING_THE_GAME);

                }
            }
           

        }
            break;
        case INSTRUCTION:
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x , &y);
                if (quit_intro->is_press(x,y))
                {
                    update_game_state(STARTING_SCREEN);
                }
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
                     Mix_PlayChannel(-1, button_select_sound, 0 );
                    map = level1;
                    tmp = 1;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level2_->is_press(x,y))
                {
                     Mix_PlayChannel(-1, button_select_sound, 0);
                    map = level2;
                    tmp = 2;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level3_->is_press(x,y))
                {
                     Mix_PlayChannel(-1, button_select_sound, 0);
                    map = level3;
                    tmp = 3;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if(level4_->is_press(x,y))
                {
                     Mix_PlayChannel(-1, button_select_sound, 0);
                   map = level4;
                   tmp = 4;
                    update_game_state(PLAYING_THE_GAME);
                }
                else if (level5_->is_press(x,y))
                {
                     Mix_PlayChannel(-1, button_select_sound, 0);
                    map = level5;
                    tmp = 5;
                    update_game_state(PLAYING_THE_GAME);
                }
                car.init(map);
                
                car.get_hp1(map);
                car.get_target(map.get_tile_set());

                
            }
        }
        break;
        case PLAYING_THE_GAME:
        {
             
            
            car.handleEvent(event);
            

        }
        break;

        case WIN:
        {
          
            Mix_PlayMusic(game_win, -1);
           if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if ( play_next->is_press(x,y))
                {
                    switch (tmp)
                    {
                    case 1 : 
                    {
                         map = level2;
                       
                         update_game_state(NEXT);
                    }
                        break;
                    case 2:
                    {
                        map = level3;
                      
                         update_game_state(NEXT);

                    } 
                        break;
                    case 3:
                    {
                         map = level4;
                      
                         update_game_state(NEXT);
                    }
                        break;
                    case 4: 
                    {
                        map = level5;
                     
                        update_game_state(NEXT);
                    }

                    break;
                    
                    default:
                        break;
                    }
                   
                }
                else if(replay->is_press(x,y))
                {
                    update_game_state(REPLAYING);

                }
                else if (menu->is_press(x,y))
                {
                    update_game_state(CHOOSING_LEVEL);
                }
                else if (exit->is_press(x,y))
                {
                    update_game_state(QUITTING_THE_GAME);
                }

            }
            break;

            case GAME_OVER:
            {
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(replay->is_press(x,y))
                    {
                       update_game_state(REPLAYING);

                     }
                    else if (menu->is_press(x,y))
                    {
                        update_game_state(CHOOSING_LEVEL);
                    }
                    else if (exit->is_press(x,y))
                    {
                        update_game_state(QUITTING_THE_GAME);
                    }
                // }
            }


        }
        break;
        
        default:
            break;
        }
    }
    if (game_state == PLAYING_THE_GAME)
    {
          car.move(map.get_tile_set(), map);
         
            car.check_hp(map.get_tile_set());
            if ( car.is_game_over()) update_game_state(GAME_OVER);
            else if(car.win()) update_game_state(WIN);

    }
    if (game_state == NEXT)
    {
       
        screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        car.init(map);
        car.get_hp1(map);
        car.get_target(map.get_tile_set());
       
       
        update_game_state(PLAYING_THE_GAME);
    }

    }
    if ( game_state == REPLAYING)
    {
        
        screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        car.init(map);
        car.get_hp1(map);

         car.get_target(map.get_tile_set());
        
       
        update_game_state(PLAYING_THE_GAME);
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