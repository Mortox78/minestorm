#include "../include/minestorm.h"


void player_keyboard(t_game_manager* gameManager)
{
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
		switch (event.type)
 	           {
 	               case SDL_QUIT:  							//When user close the app
 	                   gameManager->running = false;
 	                   break;
		       case SDL_KEYDOWN:
			   if (event.key.keysym.sym == SDLK_c)
			   {
				gameManager->counter++;
			   }
			   break;
		       default:
	                    break;
	            }
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_D])
	{
		rotate_space_ship_right(gameManager);
	}
	if (state[SDL_SCANCODE_G])
	{
		rotate_space_ship_left(gameManager);
	}
	if (state[SDL_SCANCODE_R])
	{
		forward_space_ship(gameManager);
	}
	if (state[SDL_SCANCODE_ESCAPE])
	{
		gameManager->running = false;
	}
	if (state[SDL_SCANCODE_F])
	{
		shoot_bullet(gameManager);
	}
	if (state[SDL_SCANCODE_R] == false)
	{
		space_ship_not_moving(gameManager);
	}
}

