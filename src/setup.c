#include "../include/minestorm.h"




t_game_manager* init_game_manager()
{
    t_game_manager* gameManager = malloc(sizeof(t_game_manager));


	gameManager->displayManager = init_display_manager();
    gameManager->world          = init_basic_referential();
    init_space_ship(&gameManager->spaceShip);
    gameManager->mineList 	= init_floating_mine_list();
    gameManager->running        = true;
    gameManager->counter	= 0;
    gameManager->bulletList     = init_bullet_list(gameManager);

    return gameManager;
}




t_referential init_basic_referential()
{
	t_referential world;

        world.centerRef.x = 0;
	world.centerRef.y = 0;

	world.vecRefX.x = 1;
	world.vecRefX.y = 0;

	world.vecRefY.x = 0;
	world.vecRefY.y = 1;

	return world;

}

void free_game_manager(t_game_manager* gameManager)
{

	free_space_ship(&gameManager->spaceShip);
	free_display_manager(gameManager->displayManager);
	free_floating_mine_list(gameManager->mineList);
	free(gameManager);
}


