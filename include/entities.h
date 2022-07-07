#ifndef _ENTITIES_H_
#define _ENTITIES_H_

t_floating_mine* init_floating_mine_list();

t_floating_mine init_floating_mine();

void floating_mine_moving(t_game_manager* gameManager);

t_convex_polygon init_first_poly_floating_mine(float size);

t_convex_polygon init_second_poly_floating_mine(float size);

t_convex_polygon init_third_poly_floating_mine(float size);

t_bullet* init_bullet_list(t_game_manager* gameManager);

t_bullet init_bullet();

void shoot_bullet(t_game_manager* gameManager);

void destroy_bullet(t_game_manager* gameManager);

void bullet_moving(t_game_manager* gameManager);

void free_floating_mine_list(t_floating_mine* mineList);

bool too_early_to_shoot(t_game_manager* gameManager);

void search_mine_to_activate(t_floating_mine* mineList, t_floating_mine mineTouched);



#endif
