#include <stdio.h>
#include "../include/SAT.h"
#include "../include/vector.h"
#include "../include/minestorm.h"


bool SAT_polygon_point(t_referential localRef, t_convex_polygon poly, t_point point)
{
    t_point* polyArray  = poly.pointArray;

    int firstPoint  = -1;
    int secondPoint = 0;

    do
    {
		++firstPoint;
		++secondPoint;
		if (secondPoint == poly.numberPoints)
		{
			secondPoint = 0;
		}

		// get the normal vector
		t_point A 			  = localToWorldPoint(localRef, polyArray[firstPoint]);
		t_point B 			  = localToWorldPoint(localRef, polyArray[secondPoint]);
		t_vector2 normalVec   = get_vector_from_points(A, B);
		normalVec 			  = unitaryVector(normalVec);


		// get the range of the point
		t_vector2 vecPoint    = {point.x, point.y};
		float dotProductPoint = calculateDotProduct(normalVec, vecPoint);
		t_range rangePoint    = {dotProductPoint, dotProductPoint};

		// get the range of the convex polygon
		t_range rangePoly     = get_range_pointArray_normalVec(localRef, normalVec, polyArray, poly.numberPoints);

		// we test if both ranges collide
		if (bothRangeCollide(rangePoly, rangePoint))
		{
			return 1;
		}

    }
    while (secondPoint != 0);

	return 0;
}

bool SAT_polygon_polygon(t_convex_polygon firstPoly, t_referential firstLocalRef, t_convex_polygon secondPoly, t_referential secondLocalRef)
{
	t_point* firstPolyArray  = firstPoly.pointArray;
	t_point* secondPolyArray = secondPoly.pointArray;

    int firstPoint  = -1;
    int secondPoint = 0;

    do
    {
		++firstPoint;
		++secondPoint;
		if (secondPoint == firstPoly.numberPoints)
		{
			secondPoint = 0;
		}

		// get the normal vector
		t_point A 			  = localToWorldPoint(firstLocalRef, firstPolyArray[firstPoint]);
		t_point B 			  = localToWorldPoint(firstLocalRef, firstPolyArray[secondPoint]);
		t_vector2 normalVec   = get_vector_from_points(A, B);
		normalVec 			  = unitaryVector(normalVec);

		// get the ranges of both polygons
		t_range rangeFirstPoly 		= get_range_pointArray_normalVec(firstLocalRef, normalVec, firstPolyArray, firstPoly.numberPoints);
		t_range rangeSecondPoly     = get_range_pointArray_normalVec(secondLocalRef, normalVec, secondPolyArray, secondPoly.numberPoints);

		// test if ranges collide
		if (bothRangeCollide(rangeFirstPoly, rangeSecondPoly))
		{
			return 1;
		}
    }
    while (secondPoint != 0);

	return 0;
}

bool polygons_collide(t_convex_polygon firstPoly, t_referential firstLocalRef, t_convex_polygon secondPoly, t_referential secondLocalRef)
{
	if (SAT_polygon_polygon(firstPoly, firstLocalRef, secondPoly, secondLocalRef)
	&&  SAT_polygon_polygon(secondPoly, secondLocalRef, firstPoly, firstLocalRef))
	{
		return 1;
	}
	else
		return 0;
}

bool SAT_polygon_circle(t_referential localRef, t_convex_polygon poly, t_circle circle)
{
	t_point* polyArray  = poly.pointArray;

    int firstPoint  = -1;
    int secondPoint = 0;

    do
    {
		++firstPoint;
		++secondPoint;
		if (secondPoint == poly.numberPoints)
		{
			secondPoint = 0;
		}

		// get the normal vector
		t_point A 			  = localToWorldPoint(localRef, polyArray[firstPoint]);
		t_point B 			  = localToWorldPoint(localRef, polyArray[secondPoint]);
		t_vector2 normalVec   = get_vector_from_points(A, B);
		normalVec 			  = unitaryVector(normalVec);

		// get the range of the poly
		t_range rangePoly 		= get_range_pointArray_normalVec(localRef, normalVec, polyArray, poly.numberPoints);

		// get the range of the circle
		t_range rangeCircle		= get_range_circle_normalVec(normalVec, circle);

		// test if ranges collide
		if (bothRangeCollide(rangePoly, rangeCircle))
		{
			return 1;
		}
    }
    while (secondPoint != 0);

	return 0;
}

bool SAT_circle_polygon(t_referential localRef, t_convex_polygon poly, t_circle circle)
{
	t_point* polyArray   = poly.pointArray;

	// get the closest point (between centerOfCircle and poly)
	t_point closestPoint = get_closest_pointArray_point(localRef, polyArray, circle.centerOfCircle, poly.numberPoints);

	// get the "normal vec"
	t_vector2 mainVec    = get_vector_from_points(closestPoint, circle.centerOfCircle);
	mainVec			     = unitaryVector(mainVec);

	// get the ranges
	t_range rangeCircle  = get_range_circle_normalVec(mainVec, circle);
	t_range rangePoly    = get_range_pointArray_normalVec(localRef, mainVec, polyArray, poly.numberPoints);

	// test if ranges collide
	if (bothRangeCollide(rangeCircle, rangePoly))
	{
		return 1;
	}

	return 0;
}




t_range get_range_pointArray_normalVec(t_referential localRef, t_vector2 normalVec, t_point* pointArray, int numberPoints)
{
	t_range rangePoly;

	for (int i = 0; i < numberPoints; ++i)
	{
		t_point A 					  = localToWorldPoint(localRef, pointArray[i]);
		t_vector2 vecWorldToPointPoly = {A.x, A.y};
		float dotProductPoly	      = calculateDotProduct(normalVec, vecWorldToPointPoly);

		if (i == 0)
		{
			rangePoly.min = dotProductPoly;
			rangePoly.max = dotProductPoly;
		}
		else
		{
			add_new_float_to_range(rangePoly, dotProductPoly);
		}
	}

	return rangePoly;
}

t_range get_range_circle_normalVec(t_vector2 normalVec, t_circle circle)
{
	int radius = distanceBetweenTwoPoints(circle.radius.firstPoint, circle.radius.secondPoint);
	// get our first vector
	t_vector2 firstVec;
	firstVec.x = circle.centerOfCircle.x - (radius * normalVec.x);
	firstVec.y = circle.centerOfCircle.y - (radius * normalVec.y);

	// get our second vector
	t_vector2 secondVec;
	secondVec.x = circle.centerOfCircle.x + (radius * normalVec.x);
	secondVec.y = circle.centerOfCircle.y + (radius * normalVec.y);

	// get the 2 vectors of our circle (in order to get the range)
	float dotProductFirstVec  = calculateDotProduct(normalVec, firstVec);
	float dotProductSecondVec = calculateDotProduct(normalVec, secondVec);

	// get our range
	t_range rangeCircle = get_range(dotProductFirstVec, dotProductSecondVec);

	return rangeCircle;
}

t_point get_closest_pointArray_point(t_referential localRef, t_point* pointArray, t_point center, int numberPoints)
{
	float distanceClosestPoint = 0;
	int indexArray   			= 0;

	for (int i = 0; i < numberPoints; ++i)
	{
		t_point A = localToWorldPoint(localRef, pointArray[i]);

		if(distanceBetweenTwoPoints(center, A) > distanceClosestPoint)
		{
			distanceClosestPoint = distanceBetweenTwoPoints(A, center);
			indexArray 			 = i;
		}
	}
	
	return localToWorldPoint(localRef, pointArray[indexArray]);
}