#ifndef _DISPLAY_H_
#define _DISPLAY_H_



void display_render(t_display_manager* displayManager);

t_display_manager* init_display_manager();

void init_SDL();

SDL_Window* create_window();

SDL_Renderer* create_renderer(SDL_Window* window);

TTF_Font* font_create();

void display_score(t_game_manager* gameManager);

void display_space_ship(t_game_manager* gameManager);

void free_display_manager(t_display_manager* displayManager);

void display_AABB(t_game_manager* gameManager);

void display_floating_mine(t_game_manager* gameManager);

void display_first_poly_space_ship(t_game_manager* gameManager);

//void display_second_poly_space_ship(t_game_manager* gameManager);

void display_every_poly_floating_mine(t_game_manager* gameManager, t_floating_mine);

void draw_circle(t_point point, int rad, SDL_Renderer* renderer);

void display_bullet(t_game_manager* gameManager);

#endif
