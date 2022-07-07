
Description :
Minestorm is a 2D video game released in 1982 on vectrex, you control a space ship and you have to survive against waves of dangerous mines.


How to build it :
clone it
go in the folder "minestorm/GP1_NOVO_S" and then write in the terminal : "make"


How to launch the game :
Go in the folder "minestorm/GP1_NOVO_S" and then write in the terminal : "./bin/minestorm"


Technical uses :
SAT theorem
Collision rectangle/rectangle
first law of Newton (inertia)

Features :
Only the space ship, the bullets, and the floating_mine are presents
floating_mine have differents sizes
There is only one level that was done manually (14 mines, 2 big mines, 4 mediums, 8 small)
The player can rotate left/right, forward, have inertia, can shoots
the player can die from collision with other mines
score at the end ONLY when the player die


bug knowns :
- inertia : when you forward for one second, then still forward and turn left or right, the inertia doesn't work too much, the space ship slide
- bullet  : when there are too much mines on the screen, we can't shoot (reduce number of mine in order to be able to shoot)


maths :
- fichier vector.c pour la boite a outils avec :
	- struct vector2 + toutes les methodes pour manier les vecteurs (produit scalaire / vecteur normal / etc...)
	- struct line
	- struct segment
	- struct circle
	- struct range
	- 2 ranges qui entrent en collision
	- les rectangles pour la AABB sont defini par des t_rectangle
	- il n'y a pas d'orientedRectangle
	- struct convexPolygon
	- struct referential
	

- fichier collisions.c pour les methodes de collisions avec les structs precedemment cites (rectangle-rectangle / circle-circle / etc...).


- fichier space_ship.c pour la methode d'applicate du modele dynamique newtonien (dans la fonction space_ship_inertia)
et dans la fonction forward_space_ship pour le "drift"

- les 4 methodes de changement de referentiel local <--> world sont presentes dans le fichier vector.c
	les noms de fonctions :
		- worldToLocalVector
		- localToWorldVector
		- worldToLocalDot
		- localToWorldDot


- les methodes SAT de collisions sont dans le fichier collisions.c
	- space_ship_hit_floating_mine
	- space_ship_hit_floating_mine_loop (Avec outil de debuggage visuel fonctionnel)
	- floating_mine_hit_space_ship
	- floating_mine_hit_bullet
	- floating_mine_poly_hit_bullet

AABB uniquement pour le vaisseau + un gros rectangle de test fourni dans le main.c (la methode de collision rectangle/rectangle est fonctionnel)
fonction collision_AABB_space_ship dans le fichier space_ship.c pour tester et afficher la collision entre le rectangle de test et la AABB du vaisseau


- display.c pour l'affichage de la AABB quand on appuie sur la touche 'C'


- dans le fichier entities.c :
	- init_bullet_list
	- init_floating_mine_list

- space_ship.c
	- init_space_ship

- setup.c
	- init_game_manager



















