
#include "../include/minestorm.h"



int main()
{
	t_game_manager* gameManager       = init_game_manager();

	Uint32 time = 0;


	// retirer pour tester AABB (collision rectangle/rectangle)
//	t_dot dot = {400, 400};
//	t_rectangle rectangle = define_rectangle(dot, 0, 0, 200, 200);


	while (gameManager->running)
	{
		Uint32 current_time = SDL_GetTicks();
	        float deltaTime = (time > 0) ? ((current_time - time) / 1000.f) : 1.0f / 60.0f;
	        time = current_time;
		gameManager->deltaTime = deltaTime;

        	player_keyboard(gameManager);
		space_ship_hit_border(&gameManager->spaceShip);

		display_floating_mine(gameManager);
		floating_mine_moving(gameManager);
		floating_mine_hit_border(gameManager->mineList);

		display_bullet(gameManager);
		bullet_moving(gameManager);
		floating_mine_hit_bullet(gameManager);
		destroy_bullet(gameManager);
		bullet_hit_border(gameManager);

		display_space_ship(gameManager);
		// retirer commentaire pour tester collision AABB
//		collision_AABB_space_ship(gameManager, &rectangle);
		display_render(gameManager->displayManager);
	
		if (space_ship_hit_floating_mine(gameManager))
		{
			gameManager->running = false;
		}
	}

	time = 0;
	double index;



	while (index < 2.5)
	{
		Uint32 current_time = SDL_GetTicks();
	        float deltaTime = (time > 0) ? ((current_time - time) / 1000.f) : 1.0f / 60.0f;
	        time = current_time;
		display_score(gameManager);
		display_render(gameManager->displayManager);
		index += deltaTime;
	}
	free_game_manager(gameManager);

	return 0;
}
