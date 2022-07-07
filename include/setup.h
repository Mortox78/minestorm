#ifndef _SETUP_H_
#define _SETUP_H_
#include "display.h"



t_game_manager* init_game_manager();


t_referential init_basic_referential();


void free_game_manager(t_game_manager* gameManager);


#endif
