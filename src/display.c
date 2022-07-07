#include "../include/minestorm.h"

void display_render(t_display_manager* displayManager)
{
	SDL_RenderPresent(displayManager->renderer);
	SDL_SetRenderDrawColor(displayManager->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(displayManager->renderer);

}


t_display_manager* init_display_manager()
{
	t_display_manager* displayManager = malloc(sizeof(t_display_manager));

	displayManager->window   = create_window();
	displayManager->renderer = create_renderer(displayManager->window);
	displayManager->texture  = NULL;	
	
	return displayManager;
}

void init_SDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("SDL_Init error: %s", SDL_GetError());
		return;
	}

	atexit(SDL_Quit); // Tell the program to call SDL_Quit() when program ends
}


SDL_Window* create_window()
{
	SDL_Window* window = SDL_CreateWindow("MineStorm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		return NULL;
	}
	else
	{
		return window;
	}
}


SDL_Renderer* create_renderer(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		return NULL;
	}
	else
	{
		return renderer;
	}
}

TTF_Font* font_create()
{
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("./media/roboto/Roboto-Regular.ttf", 100);
	if (font == NULL)
	{
		SDL_Log("TTF_OpenFont error: %s", SDL_GetError());
		return NULL;
	}
	
	return font;
}


void display_score(t_game_manager* gameManager)
{
	int scoreNumber = gameManager->spaceShip.score;

	char* score = int_to_alpha(scoreNumber);
	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	TTF_Init();
	TTF_Font* font    = font_create();
	SDL_Color color   = {255, 255, 255, 255};
	SDL_Rect textRect = {360, 0, 64, 64};

	SDL_Surface* surface = TTF_RenderText_Blended(font, score, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	free(score);		// Free score because previous int_to_alpha allow memory to char* score
}

void display_space_ship(t_game_manager* gameManager)
{
	if (!gameManager || !gameManager->displayManager || !gameManager->displayManager->renderer)
		return;

        SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	display_first_poly_space_ship(gameManager);
//	display_second_poly_space_ship(gameManager);

	display_AABB(gameManager);

}


void free_display_manager(t_display_manager* displayManager)
{
	if (displayManager != NULL)
	{
		SDL_DestroyRenderer(displayManager->renderer);
		SDL_DestroyWindow(displayManager->window);
		free(displayManager->window);
		free(displayManager->renderer);
		free(displayManager);
	}
}

void display_AABB(t_game_manager* gameManager)
{
	float hHeight 	     = gameManager->spaceShip.AABB->halfHeight.secondPoint.y;
	float hWidth 	     = gameManager->spaceShip.AABB->halfWidth.secondPoint.x;

	// LCR = localCenterReferential
	t_point LCR	      = gameManager->spaceShip.local->centerRef;
	SDL_Renderer* renderer = gameManager->displayManager->renderer;

	t_rectangle* AABB     = gameManager->spaceShip.AABB;
	AABB->halfHeight.firstPoint.x = LCR.x;
	AABB->halfHeight.firstPoint.y = LCR.y;
	AABB->halfWidth.firstPoint.x  = LCR.x;
	AABB->halfWidth.firstPoint.y  = LCR.y;


	if (gameManager->counter % 2 == 1)
	{
		SDL_RenderDrawLine(renderer, LCR.x - hWidth, LCR.y - hHeight, LCR.x - hWidth, LCR.y + hHeight); // bottom left to top left
		SDL_RenderDrawLine(renderer, LCR.x - hWidth, LCR.y + hHeight, LCR.x + hWidth, LCR.y + hHeight); // top left to top right
		SDL_RenderDrawLine(renderer, LCR.x + hWidth, LCR.y + hHeight, LCR.x + hWidth, LCR.y - hHeight); // top right to bottom right
		SDL_RenderDrawLine(renderer, LCR.x + hWidth, LCR.y - hHeight, LCR.x - hWidth, LCR.y - hHeight); // bottom right to bottom left
	}
}


void display_floating_mine(t_game_manager* gameManager)
{
	t_floating_mine* mineList = gameManager->mineList;
	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	SDL_SetRenderDrawColor(renderer, 30, 231, 219, 255);

	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		if (mineList[i].alive == true && mineList[i].finished == false)
			display_every_poly_floating_mine(gameManager, mineList[i]);
		else if (mineList[i].alive == false && mineList[i].finished == false)
			draw_circle(mineList[i].local.centerRef, 4, renderer);
	
	}
}


void display_first_poly_space_ship(t_game_manager* gameManager)
{
        t_space_ship* spaceShip  = &gameManager->spaceShip;
		SDL_Renderer* renderer   = gameManager->displayManager->renderer;
		t_point* pointArray		 = gameManager->spaceShip.firstPoly.pointArray;

        t_point topDot    = pointArray[0];
        t_point centerDot = pointArray[1];
        t_point bottomDot = pointArray[2];

        topDot          = localToWorldPoint(*spaceShip->local, topDot);
        bottomDot       = localToWorldPoint(*spaceShip->local, bottomDot);
        centerDot       = localToWorldPoint(*spaceShip->local, centerDot);

        SDL_RenderDrawLine(renderer, topDot.x, topDot.y, bottomDot.x, bottomDot.y);
		SDL_RenderDrawLine(renderer, topDot.x, topDot.y, centerDot.x, centerDot.y);
        SDL_RenderDrawLine(renderer, bottomDot.x, bottomDot.y, centerDot.x, centerDot.y);
}

/*void display_second_poly_space_ship(t_game_manager* gameManager)
{
        t_space_ship* spaceShip  = &gameManager->spaceShip;
        t_referential world     = gameManager->world;
	SDL_Renderer* renderer	 = gameManager->displayManager->renderer;

        t_point topDot    = spaceShip->secondPoly.pointArray[0];
        t_point centerDot = spaceShip->secondPoly.pointArray[1];
        t_point bottomDot = spaceShip->secondPoly.pointArray[2];

        topDot          = localToWorldPoint(world, *spaceShip->local, topDot);
        bottomDot       = localToWorldPoint(world, *spaceShip->local, bottomDot);
        centerDot       = localToWorldPoint(world, *spaceShip->local, centerDot);

        SDL_RenderDrawLine(renderer, topDot.x, topDot.y, bottomDot.x, bottomDot.y);
        SDL_RenderDrawLine(renderer, bottomDot.x, bottomDot.y, centerDot.x, centerDot.y);
	SDL_RenderDrawLine(renderer, topDot.x, topDot.y, centerDot.x, centerDot.y);
}*/

void display_every_poly_floating_mine(t_game_manager* gameManager, t_floating_mine mine)
{
	if (mine.alive == false)
		return;

	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	t_referential L        = mine.local;

	t_point O = L.centerRef;
	//Draw first poly

/*	SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 30, 231, 219, 255);
	if ((space_ship_hit_floating_mine_loop(gameManager, mine, mine.firstPoly)
	&&  floating_mine_hit_space_ship(gameManager, mine, mine.firstPoly)))
	{
		SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 255, 0, 0, 255);
	}*/

        t_point B = localToWorldPoint(L, mine.firstPoly.pointArray[1]);
        t_point C = localToWorldPoint(L, mine.firstPoly.pointArray[2]);
        t_point D = localToWorldPoint(L, mine.firstPoly.pointArray[3]);
 
        SDL_RenderDrawLine(renderer, O.x, O.y, B.x, B.y);
        SDL_RenderDrawLine(renderer, B.x, B.y, C.x, C.y);
        SDL_RenderDrawLine(renderer, C.x, C.y, D.x, D.y);
 

	//Draw second poly

/*	SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 30, 231, 219, 255);
	if (space_ship_hit_floating_mine_loop(gameManager, mine, mine.secondPoly)
		&& floating_mine_hit_space_ship(gameManager, mine, mine.secondPoly))
	{
		SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 255, 0, 0, 255);
	}*/

       	B = localToWorldPoint(L, mine.secondPoly.pointArray[1]);
        C = localToWorldPoint(L, mine.secondPoly.pointArray[2]);
        D = localToWorldPoint(L, mine.secondPoly.pointArray[3]);
 
        SDL_RenderDrawLine(renderer, O.x, O.y, B.x, B.y);
        SDL_RenderDrawLine(renderer, B.x, B.y, C.x, C.y);
        SDL_RenderDrawLine(renderer, C.x, C.y, D.x, D.y);


	//Draw third poly

/*	SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 30, 231, 219, 255);
	if (space_ship_hit_floating_mine_loop(gameManager, mine, mine.thirdPoly)
		&& floating_mine_hit_space_ship(gameManager, mine, mine.thirdPoly))
	{
		SDL_SetRenderDrawColor(gameManager->displayManager->renderer, 255, 0, 0, 255);
	}
*/
        B = localToWorldPoint(L, mine.thirdPoly.pointArray[1]);
        C = localToWorldPoint(L, mine.thirdPoly.pointArray[2]);
        D = localToWorldPoint(L, mine.thirdPoly.pointArray[3]);
 
        SDL_RenderDrawLine(renderer, O.x, O.y, B.x, B.y);
	SDL_RenderDrawLine(renderer, B.x, B.y, C.x, C.y);
	SDL_RenderDrawLine(renderer, C.x, C.y, D.x, D.y);
}



void draw_circle(t_point dot, int rad, SDL_Renderer* renderer)
{
	int x_center     = dot.x;
	int y_center     = dot.y;
	while (rad != 0)
	{
		int x = 0;
		int y = rad;
		int m = 5 - 4*rad;
	
		while (x <= y)
		{
			SDL_RenderDrawPoint(renderer, x + x_center, y + y_center);
			SDL_RenderDrawPoint(renderer, y + x_center, x + y_center );
			SDL_RenderDrawPoint(renderer, -x + x_center, y + y_center );
			SDL_RenderDrawPoint(renderer, -y + x_center, x + y_center );
			SDL_RenderDrawPoint(renderer, x + x_center, -y + y_center );
			SDL_RenderDrawPoint(renderer, y + x_center, -x + y_center );
			SDL_RenderDrawPoint(renderer, -x + x_center, -y + y_center );
			SDL_RenderDrawPoint(renderer, -y + x_center, -x + y_center );
	
			if (m > 0)
			{
				y -= 1;
				m -= 8*y;	
				
			}
			x += 1;
			m += 8*x + 4;
		}
		
		rad -= 0.5;
	}
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}



void display_bullet(t_game_manager* gameManager)
{
	t_bullet* bulletList   = gameManager->bulletList;
	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		if (bulletList[i].alive == true)
		{
			draw_circle(bulletList[i].center, bulletList[i].rad, renderer);
		}
	}
}
