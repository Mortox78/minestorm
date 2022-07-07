#include "../include/minestorm.h"

t_floating_mine* init_floating_mine_list()
{
//	int mine_size = 10;
	t_floating_mine* mineList = calloc(NUMBER_MINE, sizeof(t_floating_mine));

	int sizeMine = 3;

	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		if (i == 2)
			sizeMine = 2;
		if (i == 6)
			sizeMine = 1;

		mineList[i] = init_floating_mine(sizeMine);

	}

	return mineList;
}

t_floating_mine init_floating_mine(int sizeMine)
{
	t_floating_mine mine;

	srand(SDL_GetTicks());

	mine.local 		   = init_basic_referential();
	mine.local.centerRef.x = (rand() % 1280);
	mine.local.centerRef.y = (rand() % 720);



//	printf("%f VEC X et VEC Y %f\n\n", mine.vecMove.x, mine.vecMove.y);

	SDL_Delay(1);
	
	mine.firstPoly  = init_first_poly_floating_mine(sizeMine);
	mine.secondPoly = init_second_poly_floating_mine(sizeMine);
	mine.thirdPoly  = init_third_poly_floating_mine(sizeMine);
	mine.finished   = false;
	mine.size 	= sizeMine;

	if (sizeMine == 3)
	{
		mine.alive = true;
		mine.vecMove.x = ((float)rand()/(float)(RAND_MAX));
		mine.vecMove.y = ((float)rand()/(float)(RAND_MAX));
	}
	else if (sizeMine == 2)
	{
		mine.alive = false;
		mine.vecMove.x = ((float)rand()/(float)(RAND_MAX)) * 2;
		mine.vecMove.y = ((float)rand()/(float)(RAND_MAX)) * 2;
	}
	else
	{
		mine.alive = false;
		mine.vecMove.x = ((float)rand()/(float)(RAND_MAX)) * 3;
		mine.vecMove.y = ((float)rand()/(float)(RAND_MAX)) * 3;
	}
	return mine;
}


void floating_mine_moving(t_game_manager* gameManager)
{
	t_floating_mine* mineList = gameManager->mineList;
	float deltaTime = gameManager->deltaTime;
	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		if (mineList[i].alive == true)
		{
			mineList[i].local.centerRef.x += mineList[i].vecMove.x * 60.f * deltaTime;
			mineList[i].local.centerRef.y += mineList[i].vecMove.y * 60.f * deltaTime; 
		}
	}
}

t_convex_polygon init_first_poly_floating_mine(float size)
{
        t_convex_polygon fP;

        fP.pointArray          = malloc(4 * sizeof(t_point));
        fP.pointArray[0].x = 0  * size;
        fP.pointArray[0].y = 0  * size;
        fP.pointArray[1].x = -5 * size;
        fP.pointArray[1].y = 5  * size;
        fP.pointArray[2].x = 0;
        fP.pointArray[2].y = 20  * size;
	fP.pointArray[3].x = 5 * size;
	fP.pointArray[3].y = 5 * size;


	return fP;
}

t_convex_polygon init_second_poly_floating_mine(float size)
{
        t_convex_polygon sP;

        sP.pointArray          = malloc(4 * sizeof(t_point));
        sP.pointArray[0].x = 0;
        sP.pointArray[0].y = 0  * size;
        sP.pointArray[1].x = 5   * size;
        sP.pointArray[1].y = 5   * size;
        sP.pointArray[2].x = 17  * size;
        sP.pointArray[2].y = -13 * size;
        sP.pointArray[3].x = 0;
        sP.pointArray[3].y = -5 * size;

	return sP;
}

t_convex_polygon init_third_poly_floating_mine(float size)
{
	t_convex_polygon tP;

        tP.pointArray          = malloc(4 * sizeof(t_point));
        tP.pointArray[0].x = 0   * size;
        tP.pointArray[0].y = 0   * size;
        tP.pointArray[1].x = 0   * size;
        tP.pointArray[1].y = -5  * size;
        tP.pointArray[2].x = -17 * size;
        tP.pointArray[2].y = -13 * size;
        tP.pointArray[3].x = -5  * size;
        tP.pointArray[3].y = 5   * size;

	return tP;
}

t_bullet* init_bullet_list(t_game_manager* gameManager)
{
	t_bullet* bulletList = calloc(NUMBER_BULLET, sizeof(t_bullet));

	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		bulletList[i] = init_bullet();
	}

	return bulletList;
}

t_bullet init_bullet()
{
	t_bullet bullet;

	bullet.velocity.x = 0;
	bullet.velocity.y = 0;
	bullet.rad 		 = 3;
	bullet.timeSpent 	 = 0;
	bullet.alive		 = false;

	return bullet;
}

void shoot_bullet(t_game_manager* gameManager)
{
	if (gameManager == NULL || too_early_to_shoot(gameManager))
		return;

	t_bullet* bulletList  = gameManager->bulletList;
	t_referential localSS = *gameManager->spaceShip.local;
	t_point center          = localToWorldPoint(localSS, gameManager->spaceShip.firstPoly.pointArray[0]);
	
	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		if (bulletList[i].alive == false)
		{
			bulletList[i].alive    = true;
			bulletList[i].velocity = gameManager->spaceShip.local->vecRefY;
			bulletList[i].center   = center;
			return;
		}
	}
}


void destroy_bullet(t_game_manager* gameManager)
{
	t_bullet* bulletList = gameManager->bulletList;
	
	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		if (bulletList[i].timeSpent > 0.5)
		{
			bulletList[i].alive     	 = false;
			bulletList[i].timeSpent 	 = 0;
			bulletList[i].velocity.x  = 0;
			bulletList[i].velocity.y  = 0;
			bulletList[i].center.x	 = 0;
			bulletList[i].center.y 	 = 0;
		}
	}
}

void bullet_moving(t_game_manager* gameManager)
{
	t_bullet* bulletList = gameManager->bulletList;
	float deltaTime      = gameManager->deltaTime;

	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		if (bulletList[i].alive == true)
		{
			bulletList[i].center.x += (bulletList[i].velocity.x / 4) + (200.f * deltaTime);
			bulletList[i].center.y += (bulletList[i].velocity.y / 4) + (200.f * deltaTime);
			bulletList[i].timeSpent += deltaTime;
		}
	}
}

void free_floating_mine_list(t_floating_mine* mineList)
{
	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		free(mineList[i].firstPoly.pointArray);
		free(mineList[i].secondPoly.pointArray);
		free(mineList[i].thirdPoly.pointArray);
	}
}


	bool finished;
bool too_early_to_shoot(t_game_manager* gameManager)
{
	t_bullet* bulletList = gameManager->bulletList;

	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		if (bulletList[i].alive == true && bulletList[i].timeSpent < 0.2)
			return true;
	}
	
	return false;
}


void search_mine_to_activate(t_floating_mine* mineList, t_floating_mine mineTouched)
{
	int indexActivate = 0;
	int indexSize;
	int indexPart;

	if (mineTouched.size == 3)
	{
		indexSize = 2;
		indexPart = 6;
	}
	else if (mineTouched.size == 2)
	{
		indexSize = 6;
		indexPart = 14;
	}
	else
		return;



	while (indexSize < indexPart)
	{
		if (mineList[indexSize].alive == false && mineList[indexSize].finished == false)
		{
			mineList[indexSize].alive = true;
			++indexActivate;
		}
		if (indexActivate == 2)
			return;

		++indexSize;
	}
}
