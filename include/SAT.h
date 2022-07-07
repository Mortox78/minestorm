#ifndef _SAT_H_
#define _SAT_H_

#include "vector.h"
#include "minestorm.h"


bool SAT_polygon_point(t_referential localRef, t_convex_polygon poly, t_point point);



bool SAT_polygon_polygon(t_convex_polygon firstPoly, t_referential firstLocalRef, t_convex_polygon secondPoly, t_referential secondLocalRef);

bool polygons_collide(t_convex_polygon firstPoly, t_referential firstLocalRef, t_convex_polygon secondPoly, t_referential secondLocalRef);



bool SAT_polygon_circle(t_referential localRef, t_convex_polygon poly, t_circle circle);

bool SAT_circle_polygon(t_referential localRef, t_convex_polygon poly, t_circle circle);



t_range get_range_pointArray_normalVec(t_referential localRef, t_vector2 normalVec, t_point* pointArray, int numberPoints);

t_range get_range_circle_normalVec(t_vector2 normalVec, t_circle circle);

t_point get_closest_pointArray_point(t_referential localRef, t_point* pointArray, t_point center, int numberPoints);




#endif