#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_


bool lineLine(t_line firstLine, t_line secondLine);

bool lineSegment(t_line line, t_segment segment);

bool segmentSegment(t_segment firstSegment, t_segment secondSegment);

bool segmentSegmentColinear(t_segment firstSegment, t_segment secondSegment);

bool segmentSegmentOnTheSide(t_segment firstSegment, t_segment secondSegment);

bool dotDot(t_point firstDot, t_point secondDot);

bool dotLine(t_point dot, t_line line);

bool dotSegment(t_point dot, t_segment);

bool dotCircle(t_point dot, t_circle circle);

bool dotRectangle(t_point dot, t_rectangle rectangle);

bool circleLine(t_circle circle, t_line line);

bool segmentSegmentSuperimposed(t_segment firstSegment, t_segment secondSegment);

void space_ship_hit_border(t_space_ship* spaceShip);

bool rectangleRectangle(t_rectangle firstRectangle, t_rectangle secondRectangle);

void floating_mine_hit_border(t_floating_mine* mineList);

bool space_ship_hit_floating_mine(t_game_manager* gameManager);

//bool space_ship_firstPoly_hit_point(t_game_manager* gameManager, t_floating_mine mine);

bool space_ship_hit_floating_mine_loop(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly);

bool floating_mine_hit_space_ship(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly);

void bullet_hit_border(t_game_manager* gameManager);

void floating_mine_hit_bullet(t_game_manager* gameManager);

bool floating_mine_poly_hit_bullet(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly, t_bullet bullet);




#endif
