#include "../include/minestorm.h"


void init_space_ship(t_space_ship* spaceShip)
{
	t_referential* referential = malloc(sizeof(t_referential));
	referential->centerRef.x = 640;
	referential->centerRef.y = 360;

	referential->vecRefX.x = 1;
	referential->vecRefX.y = 0;

	referential->vecRefY.x = 0;
	referential->vecRefY.y = 1;

	spaceShip->firstPoly 			    = init_first_poly_space_ship();
//	spaceShip->secondPoly			    = init_second_poly_space_ship();
	spaceShip->local 	    		    = referential;
	spaceShip->AABB 	    		    = malloc(sizeof(t_rectangle));
	spaceShip->AABB->halfHeight.secondPoint.y = 30;
	spaceShip->AABB->halfWidth.secondPoint.x  = 30;
	spaceShip->mass 			    = 1000;
	spaceShip->velocity.y 		    = 0;
	spaceShip->velocity.x 		    = 0;
	spaceShip->score			    = 0;
	spaceShip->life 			    = 3;
}


void rotate_space_ship_left(t_game_manager* gameManager)
{
    t_referential* local = gameManager->spaceShip.local;

    local->vecRefX = rotateVectorWithAngle(local->vecRefX, 300.f * gameManager->deltaTime);

    local->vecRefY = rotateVectorWith90Angle(local->vecRefX);
    
}

void rotate_space_ship_right(t_game_manager* gameManager)
{
    t_referential* local = gameManager->spaceShip.local;

    local->vecRefX = rotateVectorWithAngle(local->vecRefX, - 300.f * gameManager->deltaTime);

    local->vecRefY = rotateVectorWith90Angle(local->vecRefX);
    
}

void forward_space_ship(t_game_manager* gameManager)
{
    float deltaTime = gameManager->deltaTime;

    unsigned int mass = gameManager->spaceShip.mass;

	t_vector2 vecVelocitySpaceShip 		= gameManager->spaceShip.velocity;
    t_vector2 vecDirectionSpaceShip 	= gameManager->spaceShip.local->vecRefY;


    t_vector2 inertia;
    inertia.x = vecVelocitySpaceShip.x + (vecDirectionSpaceShip.x / mass) * (100.f * deltaTime);
    inertia.y = vecVelocitySpaceShip.y + (vecDirectionSpaceShip.y / mass) * (100.f * deltaTime);


  /*  printf("MA ||| x : %f\t\t y : %f\n", (refVectorY.x / mass) * (100.f * delta_time), (refVectorY.y / mass) * (100.f * delta_time));
    printf("INERTIA ||| x : %f\t\t y : %f\n", inertia.x, inertia.y);
    printf("Velocity ||| x : %f\t\t y : %f\n", gameManager->spaceShip.velocity.x, gameManager->spaceShip.velocity.y);
    printf("Axis ||| j : %f\t\t i : %f\n\n", gameManager->spaceShip.local->vecRefY.y, gameManager->spaceShip.local->vecRefX.x);*/

    // 0.1 Isart
    if (calculateLengthOfVector(inertia) < 0.05)
    {
	    gameManager->spaceShip.local->centerRef.x += inertia.x;
	    gameManager->spaceShip.local->centerRef.y += inertia.y;
	
	    gameManager->spaceShip.velocity = inertia;
    }
}


void free_space_ship(t_space_ship* spaceShip)
{
	if (spaceShip != NULL)
	{
		free(spaceShip->local);
		//free(spaceShip->firstPoly);
		//free(spaceShip->sP.;

	}
}

void collision_AABB_space_ship(t_game_manager* gameManager, t_rectangle* rectangle)
{

	float hHeight 	     = 200;
	float hWidth 	     = 200;

	// LCR = localCenterReferential
	t_point LCR;
	LCR.x = 400;
	LCR.y = 400;
	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	t_rectangle AABB       = define_rectangle(gameManager->spaceShip.local->centerRef, 0, 0, 30, 30);

	if (rectangleRectangle(AABB, *rectangle))
	{
		SDL_SetRenderDrawColor(renderer, 207, 13, 13, 255);
	}

	SDL_RenderDrawLine(renderer, LCR.x - hWidth, LCR.y - hHeight, LCR.x - hWidth, LCR.y + hHeight); // bottom left to top left
	SDL_RenderDrawLine(renderer, LCR.x - hWidth, LCR.y + hHeight, LCR.x + hWidth, LCR.y + hHeight); // top left to top right
	SDL_RenderDrawLine(renderer, LCR.x + hWidth, LCR.y + hHeight, LCR.x + hWidth, LCR.y - hHeight); // top right to bottom right
	SDL_RenderDrawLine(renderer, LCR.x + hWidth, LCR.y - hHeight, LCR.x - hWidth, LCR.y - hHeight); // bottom right to bottom left
	
}


void space_ship_not_moving(t_game_manager* gameManager)
{
    t_vector2 velocity = gameManager->spaceShip.velocity;

    if (velocity.x == 0 && velocity.y == 0)
    {
	return;
    }

    t_vector2 inertia;

    inertia.x = velocity.x  * 0.9995; //* (200.f * delta_time);
    inertia.y = velocity.y  * 0.9995; //* (200.f * delta_time);
    
    gameManager->spaceShip.local->centerRef.x += inertia.x;
    gameManager->spaceShip.local->centerRef.y += inertia.y;

    gameManager->spaceShip.velocity = inertia;	
	
}

t_convex_polygon init_first_poly_space_ship()
{
        t_convex_polygon fP;

        fP.pointArray          = malloc(3 * sizeof(t_point));
        fP.pointArray[0].x = 0;
        fP.pointArray[0].y = 30;
        fP.pointArray[1].x = -15;
        fP.pointArray[1].y = -15;
        fP.pointArray[2].x = 15;
        fP.pointArray[2].y = -15;

	return fP;
}

t_convex_polygon init_second_poly_space_ship()
{
        t_convex_polygon sP;
        
	sP.pointArray          = malloc(3 * sizeof(t_point));
        sP.pointArray[0].x = 0;
        sP.pointArray[0].y = 30;
        sP.pointArray[1].x = 0;
        sP.pointArray[1].y = -10;
        sP.pointArray[2].x = 15;
        sP.pointArray[2].y = -25;
	
	return sP;
}
