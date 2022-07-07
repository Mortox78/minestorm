#ifndef _MINESTORM_H_
#define _MINESTORM_H_


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include "../include/int_to_alpha.h"
#include "vector.h"

#define NUMBER_MINE 14
#define SIZE_MINE 3
#define NUMBER_BULLET 10

typedef struct s_bullet t_bullet;

typedef struct s_bullet
{
	t_vector2 velocity;
	unsigned int rad;
	t_point center;
	float timeSpent;
	bool alive;

}t_bullet;


typedef struct s_floating_mine
{
	t_convex_polygon firstPoly;
	t_convex_polygon secondPoly;
	t_convex_polygon thirdPoly;
	bool alive;
	t_point center;
	t_vector2 vecMove;
	t_referential local;
	bool finished;
	int size;

}t_floating_mine;


typedef struct s_space_ship
{
	t_referential*    local;
	t_convex_polygon  firstPoly;
//	t_convex_polygon  secondPoly;
	t_rectangle*	  AABB;
	unsigned int mass;
	t_vector2 velocity;
	int score;
	int life;


}t_space_ship;


typedef struct s_display_manager
{
	SDL_Window* window;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	

}t_display_manager;

typedef struct s_game_manager
{
	t_display_manager* displayManager;
	t_referential world;
    	t_space_ship spaceShip;
	t_floating_mine* mineList;
	t_bullet* bulletList;
	bool running;
	unsigned int counter;
	float deltaTime;

}t_game_manager;










#include "entities.h"
#include "collisions.h"
#include "space_ship.h"
#include "display.h"
#include "setup.h"
#include "input.h"





#endif
