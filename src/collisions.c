
#include "../include/minestorm.h"

bool lineLine(t_line firstLine, t_line secondLine)
{
	float firstVectorX = firstLine.directorVector.x;
	float firstVectorY = firstLine.directorVector.y;
	float secondVectorX = secondLine.directorVector.x;
	float secondVectorY = secondLine.directorVector.y;


    t_vector2 vectorfirstPointLineTosecondPointLine;
    vectorfirstPointLineTosecondPointLine.x = secondLine.dot.x - firstLine.dot.x;
    vectorfirstPointLineTosecondPointLine.y = secondLine.dot.y - firstLine.dot.y;
    float vectorfirstPointLineTosecondPointLineX = vectorfirstPointLineTosecondPointLine.x;
    float vectorfirstPointLineTosecondPointLineY = vectorfirstPointLineTosecondPointLine.y;

    // Si ils ne sont pas colineaire, alors il y a collision
	if (firstVectorX * secondVectorY - secondVectorX * firstVectorY == 0 
	&& vectorfirstPointLineTosecondPointLineX * secondVectorY - secondVectorX * vectorfirstPointLineTosecondPointLineY != 0)
		return false;
	else
		return true;

}


bool lineSegment(t_line line, t_segment segment)
{
    t_vector2 normalVectorOfLine = rotateVectorWith90Angle(line.directorVector);

    // definition de nos 2 vecteurs dans le plan grace aux points du segment ainsi que le point de la ligne
	float dotLineX = line.dot.x;
	float dotLineY = line.dot.y;

	float firstPointSegmentX = segment.firstPoint.x;
	float firstPointSegmentY = segment.firstPoint.y;

	float secondPointSegmentX = segment.secondPoint.x;
	float secondPointSegmentY = segment.secondPoint.y;

    t_vector2 firstVector;
    firstVector.x = firstPointSegmentX - dotLineX;
    firstVector.y = firstPointSegmentY - dotLineY;

    t_vector2 secondVector;
    secondVector.x = secondPointSegmentX - dotLineX;
    secondVector.y = secondPointSegmentY - dotLineY;


    // calcul des deux produits scalaire
    float firstPointProduct = calculateDotProduct(normalVectorOfLine, firstVector);
    float secondPointProduct = calculateDotProduct(normalVectorOfLine, secondVector);

//    float epsilon = -0.5;

    // Si le produit de nos deux produits scalaire est superieur a 0 (epsilon) alors il n'y a pas de collisions
    // (signifie que nos deux cos sont inferieur a 90 et donc que notre resultat est positif
    // le segment est que d'un cote de la ligne)
    if (firstPointProduct * secondPointProduct >= 0)
        return false;
    else
        return true;

}


bool segmentSegment(t_segment firstSegment, t_segment secondSegment)
{

    // If both vectors (segments) are colinear and not superimposed, there is no collision
    if (segmentSegmentColinear(firstSegment, secondSegment) && segmentSegmentSuperimposed(firstSegment, secondSegment) == false)
        return false;
    // If a segment is on the other side of the other segment (the two points of the segment both in one side of the other segment),
    // there is no collision
    if (segmentSegmentOnTheSide(firstSegment, secondSegment))
        return false;
    else 
        return true;
}


bool segmentSegmentColinear(t_segment firstSegment, t_segment secondSegment)
{
	float firstPointFirstSegmentX = firstSegment.firstPoint.x;
	float firstPointFirstSegmentY = firstSegment.firstPoint.y;

	float secondPointFirstSegmentX = secondSegment.secondPoint.x;
	float secondPointFirstSegmentY = secondSegment.secondPoint.y;

	float firstPointSecondSegmentX = firstSegment.firstPoint.x;
	float firstPointSecondSegmentY = firstSegment.firstPoint.y;

	float secondPointSecondSegmentX = secondSegment.secondPoint.x;
	float secondPointSecondSegmentY = secondSegment.secondPoint.y;



    t_vector2 firstVector;
    firstVector.x = firstPointFirstSegmentX - secondPointFirstSegmentX;
    firstVector.y = firstPointFirstSegmentY - secondPointFirstSegmentY;

    t_vector2 secondVector;
    secondVector.x = firstPointSecondSegmentX - secondPointSecondSegmentX;
    secondVector.y = firstPointSecondSegmentY - secondPointSecondSegmentY;


	if (firstVector.x * secondVector.y - secondVector.x * firstVector.y != 0)
        return true;
    else
        return false;

}


// secondSegment is our line
bool segmentSegmentOnTheSide(t_segment firstSegment, t_segment secondSegment)
{
    // Passage de notre secondSegment en vecteur
    t_vector2 secondSegmentVector;
    secondSegmentVector.x = secondSegment.firstPoint.x - secondSegment.secondPoint.x;
    secondSegmentVector.y = secondSegment.firstPoint.y - secondSegment.secondPoint.y;


    // definition de notre droite 
    t_line line;
    line.directorVector = secondSegmentVector;
    line.dot = secondSegment.firstPoint;


    // obtenir le vecteur normal de notre droite;
    t_vector2 normalVectorOfLine = rotateVectorWith90Angle(line.directorVector);


    // definition de nos 2 vecteurs dans le plan grace aux points du segment ainsi que le point de la ligne
    float dotLineX = line.dot.x;
    float dotLineY = line.dot.y;

    float firstPointSegmentX = firstSegment.firstPoint.x;
    float firstPointSegmentY = firstSegment.firstPoint.y;

    float secondPointSegmentX = firstSegment.secondPoint.x;
    float secondPointSegmentY = firstSegment.secondPoint.y;

    t_vector2 firstVector;
    firstVector.x = firstPointSegmentX - dotLineX;
    firstVector.y = firstPointSegmentY - dotLineY;

    t_vector2 secondVector;
    secondVector.x = secondPointSegmentX - dotLineX;
    secondVector.y = secondPointSegmentY - dotLineY;


    // calcul des deux produits scalaire
    float firstPointProduct = calculateDotProduct(normalVectorOfLine, firstVector);
    float secondPointProduct = calculateDotProduct(normalVectorOfLine, secondVector);

//    float epsilon = -0.5;

    // Si le produit de nos deux produits scalaire est superieur a 0 (epsilon) alors il n'y a pas de collisions
    // (signifie que nos deux cos sont inferieur a 90 et donc que notre resultat est positif,
    // le segment est que d'un cote de la ligne)
    if (firstPointProduct * secondPointProduct >= 0)
        return true;
    else
        return false;




}


bool dotDot(t_point firstPoint, t_point secondPoint)
{
    if (firstPoint.x > secondPoint.x - epsilon
        && firstPoint.x < secondPoint.x + epsilon
        && firstPoint.y > secondPoint.y - epsilon
        && firstPoint.y < secondPoint.y + epsilon)
            return true;
    else
            return false;


}

bool dotLine(t_point dot, t_line line)
{
    t_vector2 vectorDotLineToDot;
    vectorDotLineToDot.x = dot.x - line.dot.x;
    vectorDotLineToDot.y = dot.y - line.dot.y;

    float vectorDotLineToDotX = vectorDotLineToDot.x;
    float vectorDotLineToDotY = vectorDotLineToDot.y;
    float directorVectorX     = line.directorVector.x;
    float directorVectorY     = line.directorVector.y;

    // Si ils sont colineaires, cela signifie que le point est sur la droite, donc il y a collision
    if (vectorDotLineToDotX * directorVectorY - directorVectorX * vectorDotLineToDotY == 0)
        return true;
    else 
        return false;


}



bool dotSegment(t_point dot, t_segment segment)
{
    t_vector2 vectorfirstPointSegmentToDot;
    vectorfirstPointSegmentToDot.x = dot.x - segment.firstPoint.x;
    vectorfirstPointSegmentToDot.y = dot.y - segment.firstPoint.y;

    t_vector2 vectorsecondPointSegmentToDot;
    vectorsecondPointSegmentToDot.x = dot.x - segment.secondPoint.x;
    vectorsecondPointSegmentToDot.y = dot.y - segment.secondPoint.y;

    t_vector2 vectorSegment;
    vectorSegment.x = segment.secondPoint.x - segment.firstPoint.x;
    vectorSegment.y = segment.secondPoint.y - segment.firstPoint.y;

    float vectorfirstPointSegmentToDotX = vectorfirstPointSegmentToDot.x;
    float vectorfirstPointSegmentToDotY = vectorfirstPointSegmentToDot.y;
    float vectorSegmentX              = vectorSegment.x;
    float vectorSegmentY              = vectorSegment.y;



    float lengthOfVectorfirstPointSegmentToDot = calculateLengthOfVector(vectorfirstPointSegmentToDot);
    float lengthOfVectorsecondPointSegmentToDot= calculateLengthOfVector(vectorsecondPointSegmentToDot);
    float lengthOfVectorSegment              = calculateLengthOfVector(vectorSegment);



    // Si nos deux vecteurs sont colineaires, cela veut dire que notre point est forcement sur la droite sous-tendant de notre segment,
    // si la longueur entre le premier point du segment et notre point est inferieur a la longueur
    // de notre segment, ALORS cela veut dire que notre point est sur notre segment (collision)
    if (vectorfirstPointSegmentToDotX * vectorSegmentY - vectorSegmentX * vectorfirstPointSegmentToDotY == 0
        && lengthOfVectorfirstPointSegmentToDot < lengthOfVectorSegment
        && lengthOfVectorsecondPointSegmentToDot < lengthOfVectorSegment)
        return true;
    else
        return false;


}


bool dotCircle(t_point dot, t_circle circle)
{
    t_vector2 vectorradius;
    vectorradius.x = circle.radius.secondPoint.x - circle.radius.firstPoint.x;
    vectorradius.y = circle.radius.secondPoint.y - circle.radius.firstPoint.y;

    t_vector2 vectorCenterCircleToDot;
    vectorCenterCircleToDot.x = dot.x - circle.centerOfCircle.x;
    vectorCenterCircleToDot.y = dot.y - circle.centerOfCircle.y;

    float lengthOfVectorradius    = calculateLengthOfVector(vectorradius);
    float lengthOfVectorCenterCircleToDot = calculateLengthOfVector(vectorCenterCircleToDot);

    if (lengthOfVectorCenterCircleToDot < lengthOfVectorradius)
        return true;
    else
        return false;

}



bool dotRectangle(t_point dot, t_rectangle rectangle)
{


    // calculate the length of our 2 half segments of the rectangle
    float lengthOfSegmentHalfHeight = distanceBetweenTwoPoints(rectangle.halfHeight.firstPoint, rectangle.halfHeight.secondPoint);
    float lengthOfSegmentHalfWidth  = distanceBetweenTwoPoints(rectangle.halfWidth.firstPoint, rectangle.halfWidth.secondPoint);

    float limitMaxX = rectangle.halfWidth.secondPoint.x;
    float limitMinX = limitMaxX - (lengthOfSegmentHalfWidth * 2);
    float limitMaxY = rectangle.halfHeight.secondPoint.y;
    float limitMinY = limitMaxY - (lengthOfSegmentHalfHeight * 2);

    if (dot.x < limitMaxX
     && dot.x > limitMinX
     && dot.y < limitMaxY
     && dot.y > limitMinY)
        return true;
    else
        return false;


}


bool circleLine(t_circle circle, t_line line)
{
    t_vector2 normalVectorOfLine = rotateVectorWith90Angle(line.directorVector);


    t_segment radius = circle.radius;
    // definition de nos 2 vecteurs dans le plan grace aux points du segment ainsi que le point de la ligne
	float dotLineX = line.dot.x;
	float dotLineY = line.dot.y;

	float firstPointSegmentX = radius.firstPoint.x;
	float firstPointSegmentY = radius.firstPoint.y;

	float secondPointSegmentX = radius.secondPoint.x;
	float secondPointSegmentY = radius.secondPoint.y;

    t_vector2 firstVector;
    firstVector.x = firstPointSegmentX - dotLineX;
    firstVector.y = firstPointSegmentY - dotLineY;

    t_vector2 secondVector;
    secondVector.x = secondPointSegmentX - dotLineX;
    secondVector.y = secondPointSegmentY - dotLineY;


    // calcul des deux produits scalaire
    float firstPointProduct = calculateDotProduct(normalVectorOfLine, firstVector);
    float secondPointProduct = calculateDotProduct(normalVectorOfLine, secondVector);

//    float epsilon = -0.5;

    // Si le produit de nos deux produits scalaire est superieur a 0 (epsilon) alors il n'y a pas de collisions (signifie que nos deux cos
    // sont inferieur a 90 et donc que notre resultat est positif
    // le segment est que d'un cote de la ligne)
    if (firstPointProduct * secondPointProduct >= 0)
        return false;
    else
        return true;

}


bool circleCircle(t_circle firstCircle, t_circle secondCircle)
{
    t_segment radiusOfFirstCircle = firstCircle.radius;
    t_segment radiusOfSecondCircle = secondCircle.radius;



    float lengthOfRadiusOfFirstCircle         = distanceBetweenTwoPoints(radiusOfFirstCircle.firstPoint, radiusOfFirstCircle.secondPoint);
    float lengthOfRadiusOfSecondCircle        = distanceBetweenTwoPoints(radiusOfSecondCircle.firstPoint, radiusOfSecondCircle.secondPoint);   
    float distanceBetweenBothCenterOfCircle   = distanceBetweenTwoPoints(firstCircle.centerOfCircle, secondCircle.centerOfCircle);
    
    
    if (distanceBetweenBothCenterOfCircle < lengthOfRadiusOfFirstCircle + lengthOfRadiusOfSecondCircle)
        return true;
    else
        return false;
    
}


bool rectangleRectangle(t_rectangle firstRectangle, t_rectangle secondRectangle)
{
    // Dots of firstRectangle  : A = top, B = right, C = bottom, D = left
    // Dots of secondRectangle : E = top, F = right
    // FR = firstRectaingle
    // SR = secondRectangle

    t_point centerFR = firstRectangle.centerOfRectangle;
    t_point centerSR = secondRectangle.centerOfRectangle;
    t_point A 	   = firstRectangle.halfHeight.secondPoint;
    t_point B  	   = firstRectangle.halfWidth.secondPoint;
    t_point E 	   = secondRectangle.halfHeight.secondPoint;
    t_point F 	   = secondRectangle.halfWidth.secondPoint;

    // calculate the length of both half segments of the firstRectangle
    float lengthHalfHeightFR = distanceBetweenTwoPoints(centerFR, A);
    float lengthHalfWidthFR  = distanceBetweenTwoPoints(centerFR, B);

    t_point D  = centerFR;
    D.x -= lengthHalfWidthFR;

    t_point C  = centerFR;
    C.y -= lengthHalfHeightFR;

    // calculate the length of both half segments of the secondRectangle
    float lengthHalfHeightSR = distanceBetweenTwoPoints(centerSR, E);
    float lengthHalfWidthSR  = distanceBetweenTwoPoints(centerSR, F);

    // set the limits for the collisions between both rectangles
    float maxSecRecX = F.x;
    float minSecRecX = maxSecRecX - (lengthHalfWidthSR * 2);
    float maxSecRecY = E.y;
    float minSecRecY = maxSecRecY - (lengthHalfHeightSR * 2);
    
    // If the top dot hit
    if ((A.y <= maxSecRecY && A.y >= minSecRecY && D.x <= maxSecRecX && D.x >= minSecRecX)
     || (C.y <= maxSecRecY && C.y >= minSecRecY && D.x <= maxSecRecX && D.x >= minSecRecX)
     || (C.y <= maxSecRecY && C.y >= minSecRecY && B.x <= maxSecRecX && B.x >= minSecRecX)
     || (B.x <= maxSecRecX && B.x >= minSecRecX && A.y <= maxSecRecY && A.y >= minSecRecY))
	     	return true;
    else
        return false;
}


bool segmentSegmentSuperimposed(t_segment firstSegment, t_segment secondSegment)
{
    // here two segments AB and CD (firstSegment == AB and secondSegment = CD)
    float lengthOfAB = distanceBetweenTwoPoints(firstSegment.firstPoint, firstSegment.secondPoint);
    float lengthOfAC = distanceBetweenTwoPoints(firstSegment.firstPoint, secondSegment.firstPoint);
    float lengthOfBC = distanceBetweenTwoPoints(firstSegment.secondPoint, secondSegment.firstPoint);
    float lengthOfAD = distanceBetweenTwoPoints(firstSegment.firstPoint, secondSegment.secondPoint);
    float lengthOfBD = distanceBetweenTwoPoints(firstSegment.secondPoint, secondSegment.secondPoint);


    if ((lengthOfAB >= lengthOfAC && lengthOfAB >= lengthOfBC && lengthOfAC + lengthOfBC == lengthOfAB)
     || (lengthOfAB >= lengthOfAD && lengthOfAB >= lengthOfBD && lengthOfAD + lengthOfBD == lengthOfAB))
       return true;
    else
       return false; 

}


void space_ship_hit_border(t_space_ship* spaceShip)
{
	t_point* centerRef = &(spaceShip->local->centerRef);

	if (centerRef->x < 0)
	{
		centerRef->x = 1280;
	}
	if (centerRef->x > 1280)
	{
		centerRef->x = 0;
	}
	if (centerRef->y < 0)
	{
		centerRef->y = 720;
	}
	if (centerRef->y > 720)
	{
		centerRef->y = 0;
	}
}

void floating_mine_hit_border(t_floating_mine* mineList)
{
	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		t_point* centerMine = &mineList[i].local.centerRef;

		if (centerMine->x < 0)
			centerMine->x = 1280;
		if (centerMine->x > 1280)
			centerMine->x = 0;
		if (centerMine->y < 0)
			centerMine->y = 720;
		if (centerMine->y > 720)
			centerMine->y = 0;
	}
}


bool space_ship_hit_floating_mine(t_game_manager* gameManager)
{
	t_floating_mine* mineList = gameManager->mineList;

	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		if (mineList[i].alive == true && mineList[i].finished == false)
		{
			if (space_ship_hit_floating_mine_loop(gameManager, mineList[i], mineList[i].firstPoly)
			||  space_ship_hit_floating_mine_loop(gameManager, mineList[i], mineList[i].secondPoly)	
			||  space_ship_hit_floating_mine_loop(gameManager, mineList[i], mineList[i].thirdPoly))
				return true;
		}

	}
	return false;
}



/*-------------------------------------------TOUT CE QUI EST EN COMMENTAIRE EST UTILE POUR LE DEBUGGAGE-----------------------------------------------*/
bool space_ship_hit_floating_mine_loop(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly)
{
	int indexfirstPoint  = 2;
	int indexsecondPoint = 0;
	int indexVecDot    = 1;
//	float sizeDraw     = 1;
	
	t_referential world   = gameManager->world;
        t_referential* localSS  = gameManager->spaceShip.local;
	t_referential localFM  = mine.local;
        t_point* pointArray       = gameManager->spaceShip.firstPoly.pointArray;
	
	t_point* pointArrayMine;

	if (poly.pointArray == mine.firstPoly.pointArray)
		pointArrayMine   = mine.firstPoly.pointArray;
	else if (poly.pointArray == mine.secondPoly.pointArray)
		pointArrayMine   = mine.secondPoly.pointArray;
	else if (poly.pointArray == mine.thirdPoly.pointArray)
		pointArrayMine   = mine.thirdPoly.pointArray;


//	SDL_Renderer* renderer = gameManager->displayManager->renderer;
	
	for (int i = 0; i < 3; ++i)
	{
/*		if (i == 1)
			sizeDraw = 2;
		if (i == 2)
			sizeDraw = 0.2;*/
//		printf("indexfirstPoint : %d\nindexsecondPoint : %d\nindexVecDot : %d\n\n\n", indexfirstPoint, indexsecondPoint, indexVecDot);
		t_point A = localToWorldPoint( *localSS, pointArray[indexfirstPoint]);
		t_point B = localToWorldPoint( *localSS, pointArray[indexsecondPoint]);
		t_point C = localToWorldPoint( *localSS, pointArray[indexVecDot]);

		t_vector2 vector       = get_vector_from_points(B, C);
		t_vector2 normalVec    = getNormalVector(vector);
		normalVec 	       = unitaryVector(normalVec);

		t_vector2 OSA = get_vector_from_points(world.centerRef, A);
		t_vector2 OSB = get_vector_from_points(world.centerRef, B);
//		t_vector2 OSC = get_vector_from_points(world.centerRef, C);

		float dProduct1 = calculateDotProduct(normalVec, OSA);
		float dProduct2 = calculateDotProduct(normalVec, OSB);
//		float dProduct3 = calculateDotProduct(normalVec, OSC);
	
//		printf("dProduct1 : %f\ndProduct2 : %f\n\n", dProduct1, dProduct2);

		t_range rangeTriangle = get_range(dProduct1, dProduct2);

		t_range rangeFM;

/*		t_point D  = B;
		D.x -= vector.x * sizeDraw;
		D.y -= vector.y * sizeDraw;

		t_point drawLine = D;
		drawLine.x += (normalVec.x * 1500);
		drawLine.y += (normalVec.y * 1500);

		t_point drawLine2  = D;
		drawLine2.x -= (normalVec.x * 1500);
		drawLine2.y	-= (normalVec.y * 1500);

		t_point F = D;
		F.x += multiplicateScaleAndVector(normalVec, dProduct1 - dProduct2).x;
		F.y += multiplicateScaleAndVector(normalVec, dProduct1 - dProduct2).y;*/

/*		t_point G = D;
		G.x += multiplicateScaleAndVector(normalVec, dProduct3 - dProduct2).x;
		G.y += multiplicateScaleAndVector(normalVec, dProduct3 - dProduct2).y;*/

/*		t_point H = D;
 		H.x += multiplicateScaleAndVector(normalVec, dProduct2 - dProduct1).x;
		H.y += multiplicateScaleAndVector(normalVec, dProduct2 - dProduct1).y;*/


/*		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(renderer, drawLine.x, drawLine.y, drawLine2.x, drawLine2.y);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(renderer, A.x, A.y, F.x, F.y);
//		SDL_RenderDrawLine(renderer, C.x, C.y, G.x, G.y);
		SDL_RenderDrawLine(renderer, B.x, B.y, D.x, D.y);

		SDL_SetRenderDrawColor(renderer, 30, 231, 219, 255);*/


		for (int j = 0; j < 4; ++j)
		{
			t_point dotMine = localToWorldPoint( localFM, pointArrayMine[j]);
			t_vector2 vecDotMine = get_vector_from_points(world.centerRef, dotMine);

			float dProductMine = calculateDotProduct(normalVec, vecDotMine);
//			dProductMine = fabs()

//			printf("test %f test\n", dProductMine);
			if (j == 0)
			{
				rangeFM.min = dProductMine;
				rangeFM.max = dProductMine;
			}
			else if ((dProductMine > rangeFM.max && dProductMine > rangeFM.min))
				rangeFM.max = dProductMine;
			else if ((dProductMine < rangeFM.min && dProductMine < rangeFM.max))
				rangeFM.min = dProductMine;

/*			t_point E = D;
			E.x += multiplicateScaleAndVector(normalVec, dProductMine - dProduct2).x;
			E.y += multiplicateScaleAndVector(normalVec, dProductMine - dProduct2).y;
			SDL_SetRenderDrawColor(renderer, 183, 25, 225, 255);
			SDL_RenderDrawLine(renderer, dotMine.x, dotMine.y, E.x, E.y);*/
		}
		
//		printf("rangeFM.min : %f\nrangeFM.max : %f\n", rangeFM.min, rangeFM.max);
//		printf("test SS %f et %f test SS\n", dProduct1, dProduct2);
//		printf("rangeTriangle.min : %f\nrangeTriangle.max : %f\n\n\n\n", rangeTriangle.min, rangeTriangle.max);


//		SDL_SetRenderDrawColor(renderer, 30, 231, 219, 255);
		if (bothRangeCollide(rangeTriangle, rangeFM) == false)
			return false;
		if (indexfirstPoint == 2)
			indexfirstPoint = -1;
		if (indexVecDot == 2)
			indexVecDot = -1;
		++indexfirstPoint;
		++indexsecondPoint;
		++indexVecDot;
	}
//	printf("OUI COLLISIONS");
        return true;
}

bool floating_mine_hit_space_ship(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly)
{
	t_space_ship spaceShip = gameManager->spaceShip;
	t_referential world    = gameManager->world;
	t_referential localSS  = *spaceShip.local;
	t_referential localFM  = mine.local;
	t_point* pointArraySS      = spaceShip.firstPoly.pointArray;

	t_point* pointArrayFM;
	if (poly.pointArray == mine.firstPoly.pointArray)
		pointArrayFM = mine.firstPoly.pointArray;
	else if (poly.pointArray == mine.secondPoly.pointArray)
		pointArrayFM = mine.secondPoly.pointArray;
	else if (poly.pointArray == mine.thirdPoly.pointArray)
		pointArrayFM = mine.thirdPoly.pointArray;



	int indexfirstPoint  = 3;
	int indexsecondPoint = 0;
	int indexVecDot    = 1;
	int indexProjDot   = 2;
	
	for (int i = 0; i < 4; ++i)
	{
		t_point A = localToWorldPoint(localFM, pointArrayFM[indexfirstPoint]);
		t_point B = localToWorldPoint(localFM, pointArrayFM[indexsecondPoint]);
		t_point C = localToWorldPoint(localFM, pointArrayFM[indexVecDot]);
		t_point D = localToWorldPoint(localFM, pointArrayFM[indexProjDot]);

		t_vector2 vector       = get_vector_from_points(B, C);
		t_vector2 normalVec    = getNormalVector(vector);
		normalVec 	       = unitaryVector(normalVec);

		t_vector2 OSA = get_vector_from_points(world.centerRef, A);
		t_vector2 OSB = get_vector_from_points(world.centerRef, B);
		t_vector2 OSC = get_vector_from_points(world.centerRef, C);
		t_vector2 OSD = get_vector_from_points(world.centerRef, D);

		float dProduct1 = calculateDotProduct(normalVec, OSA);
		float dProduct2 = calculateDotProduct(normalVec, OSB);
		float dProduct3 = calculateDotProduct(normalVec, OSC);
		float dProduct4 = calculateDotProduct(normalVec, OSD);

		t_range rangeFM1 = get_range(dProduct1, dProduct2);

		t_range rangeFM2 = get_range(dProduct3, dProduct4);

		t_range rangeFM  = get_range_from_two_ranges(rangeFM1, rangeFM2);

		t_range rangeTriangle;

		for (int j = 0; j < 3; ++j)
		{
			t_point dotSS = localToWorldPoint(localSS, pointArraySS[j]);
			t_vector2 vecDotSS = get_vector_from_points(world.centerRef, dotSS);
		
			float dProductSS = calculateDotProduct(normalVec, vecDotSS);
		
//			printf("test %f test\n", dProductMine);
			if (j == 0)
			{
				rangeTriangle.min = dProductSS;
				rangeTriangle.max = dProductSS;
			}
			else if ((dProductSS > rangeTriangle.max && dProductSS > rangeTriangle.min))
				rangeTriangle.max = dProductSS;
			else if ((dProductSS < rangeTriangle.min && dProductSS < rangeTriangle.max))
				rangeTriangle.min = dProductSS;
	
		}

		if (bothRangeCollide(rangeTriangle, rangeFM) == false)
			return false;
		if (indexfirstPoint == 3)
			indexfirstPoint = -1;
		if (indexVecDot == 3)
			indexVecDot = -1;
		if (indexProjDot == 3)
			indexProjDot = -1;
		++indexfirstPoint;
		++indexsecondPoint;
		++indexVecDot;
		++indexProjDot;
	}
//	printf(" TRUE");
	return true;
}

void bullet_hit_border(t_game_manager* gameManager)
{
	t_bullet* bulletList = gameManager->bulletList;

	for (int i = 0; i < NUMBER_BULLET; ++i)
	{
		t_point* C = &bulletList[i].center;
		if (bulletList[i].alive == true)
		{
			if (C->x > 1280)
				C->x = 0;
			if (C->x < 0)
				C->x = 1280;
			if (C->y > 720)
				C->y = 0;
			if (C->y < 0)
				C->y = 720;
		}
	}
}


void floating_mine_hit_bullet(t_game_manager* gameManager)
{
	t_space_ship* spaceShip   = &gameManager->spaceShip;
	t_bullet* bulletList      = gameManager->bulletList;
	t_floating_mine* mineList = gameManager->mineList;

	for (int i = 0; i < NUMBER_MINE; ++i)
	{
		t_convex_polygon fP = mineList[i].firstPoly;
		t_convex_polygon sP = mineList[i].secondPoly;
		t_convex_polygon tP = mineList[i].thirdPoly;
		
		for (int j = 0; j < NUMBER_BULLET; ++j)
		{
			if (mineList[i].alive == false || mineList[i].finished == true)
				break;
			if (bulletList[j].alive == true)
			{
				if (floating_mine_poly_hit_bullet(gameManager, mineList[i], fP, bulletList[j])
				||  floating_mine_poly_hit_bullet(gameManager, mineList[i], sP, bulletList[j])	
				||  floating_mine_poly_hit_bullet(gameManager, mineList[i], tP, bulletList[j]))
				{
					if (mineList[i].size == 3)
						spaceShip->score += 100;
					else if (mineList[i].size == 2)
						spaceShip->score += 135;
					else if (mineList[i].size == 1)
						spaceShip->score += 200;


					mineList[i].alive    = false;
					mineList[i].finished = true;
					bulletList[j].alive  = false;
					search_mine_to_activate(mineList, mineList[i]);
					break;
				}
			}
		}
	}
}

bool floating_mine_poly_hit_bullet(t_game_manager* gameManager, t_floating_mine mine, t_convex_polygon poly, t_bullet bullet)
{
	t_referential world    = gameManager->world;
	t_referential localFM  = mine.local;
	t_point centerBullet     = bullet.center;

	t_point* pointArrayFM;
	if (poly.pointArray == mine.firstPoly.pointArray)
		pointArrayFM = mine.firstPoly.pointArray;
	else if (poly.pointArray == mine.secondPoly.pointArray)
		pointArrayFM = mine.secondPoly.pointArray;
	else if (poly.pointArray == mine.thirdPoly.pointArray)
		pointArrayFM = mine.thirdPoly.pointArray;

	int indexfirstPoint  = 3;
	int indexsecondPoint = 0;
	int indexVecDot    = 1;
	int indexProjDot   = 2;
	
	for (int i = 0; i < 4; ++i)
	{
		t_point A = localToWorldPoint(localFM, pointArrayFM[indexfirstPoint]);
		t_point B = localToWorldPoint(localFM, pointArrayFM[indexsecondPoint]);
		t_point C = localToWorldPoint(localFM, pointArrayFM[indexVecDot]);
		t_point D = localToWorldPoint(localFM, pointArrayFM[indexProjDot]);

		t_vector2 vector       = get_vector_from_points(B, C);
		t_vector2 normalVec    = getNormalVector(vector);
		normalVec 	       = unitaryVector(normalVec);

		t_vector2 OSA = get_vector_from_points(world.centerRef, A);
		t_vector2 OSB = get_vector_from_points(world.centerRef, B);
		t_vector2 OSC = get_vector_from_points(world.centerRef, C);
		t_vector2 OSD = get_vector_from_points(world.centerRef, D);

		float dProduct1 = calculateDotProduct(normalVec, OSA);
		float dProduct2 = calculateDotProduct(normalVec, OSB);
		float dProduct3 = calculateDotProduct(normalVec, OSC);
		float dProduct4 = calculateDotProduct(normalVec, OSD);

		t_range rangeFM1 = get_range(dProduct1, dProduct2);

		t_range rangeFM2 = get_range(dProduct3, dProduct4);

		t_range rangeFM  = get_range_from_two_ranges(rangeFM1, rangeFM2);

		/*----------------------------*/
		
		// on prend deux points du cercle (bullet)
		t_vector2 OC = get_vector_from_points(world.centerRef, centerBullet);
		t_vector2 OD1 = OC;
		OD1.x  -= (4 * normalVec.x);
		OD1.y  -= (4 * normalVec.y);

		t_vector2 OD2 = OC;
		OD2.x  += (4 * normalVec.x);
		OD2.y  += (4 * normalVec.y);


		float dProductBullet1 = calculateDotProduct(normalVec, OD1);
		float dProductBullet2 = calculateDotProduct(normalVec, OD2);

		t_range rangeBullet = get_range(dProductBullet1, dProductBullet2);

		if (bothRangeCollide(rangeBullet, rangeFM) == false)
			return false;
		if (indexfirstPoint == 3)
			indexfirstPoint = -1;
		if (indexVecDot == 3)
			indexVecDot = -1;
		if (indexProjDot == 3)
			indexProjDot = -1;
		++indexfirstPoint;
		++indexsecondPoint;
		++indexVecDot;
		++indexProjDot;
	}

	return true;
}