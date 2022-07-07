#ifndef _SPACE_SHIP_H_
#define _SPACE_SHIP_H_



void init_space_ship(t_space_ship* spaceShip);

void rotate_space_ship_left(t_game_manager* gameManager);

void rotate_space_ship_right(t_game_manager* gameManager);

void forward_space_ship(t_game_manager* gameManager);

void free_space_ship(t_space_ship* spaceShip);

void space_ship_inertia(t_space_ship* spaceShip);

void collision_AABB_space_ship(t_game_manager* gameManager, t_rectangle* rectangle);

void space_ship_not_moving(t_game_manager* gameManager);

t_convex_polygon init_first_poly_space_ship();

t_convex_polygon init_second_poly_space_ship();







#endif
