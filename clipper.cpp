//
//  clipper.cpp
//
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//

#include "clipper.h"
#include <iostream>

/**
 * Simple class that performs clipping
 *
 */

/**
 * Constructor
 */
clipper::clipper ()
{
}

/*
*Creates a Clipping window
*Index 0 = Left
*Index 1 = Top
*Index 2 = Right
*Index 3 = Bottom
*/
std::vector<Line*>* clipper::GenerateClipWindow(Vertex* BottomLeft, Vertex* TopRight)
{
	std::vector<Line*>* ClipWindow = new std::vector<Line*>();

	//Generate missing vertexes
	Vertex* TopLeft = new Vertex();
	TopLeft->x = BottomLeft->x;
	TopLeft->y = TopRight->y;

	Vertex* BottomRight = new Vertex();
	BottomRight->x = TopRight->x;
	BottomRight->y = BottomLeft->y;

	//Genereate Line
	Line* LeftLine = new Line(TopLeft,BottomLeft, true);
	Line* RightLine = new Line(BottomRight, TopRight, true);
	Line* BottomLine = new Line(BottomLeft, BottomRight, true);
	Line* TopLine = new Line(TopRight, TopLeft, true);

	//Add lines
	ClipWindow->push_back(LeftLine);
	ClipWindow->push_back(TopLine);
	ClipWindow->push_back(RightLine);
	ClipWindow->push_back(BottomLine);

	return ClipWindow;
}

/**
* clipPolygon
*
* Clip the polygon with vertex count in and vertices inx/iny
* against the rectangular clipping region specified by lower-left corner
* (x0,y0) and upper-right corner (x1,y1). The resulting vertices are
* placed in outx/outy.
*
* The routine should return the vertex count of the polygon
* resulting from the clipping.
*
* @param testVertex The vertex being tested
* @param ClipBoundry - The line to use to determine if
*
* @return True If the test vertex is inside false otherwise
*
*/
bool clipper::Inside(Vertex testVertex, Line ClipBoundry)
{
	if (ClipBoundry.BoundryType == South)
	{
		if (testVertex.y >= ClipBoundry.Start->y) return true;
	}
	if (ClipBoundry.BoundryType == North)
	{
		if (testVertex.y <= ClipBoundry.Start->y) return true;
	}
	if (ClipBoundry.BoundryType == East)
	{
		if (testVertex.x <= ClipBoundry.End->x) return true;
	}
	if (ClipBoundry.BoundryType == West)
	{
		if (testVertex.x >= ClipBoundry.End->x) return true;
	}
	return false;
}

/**
 * clipPolygon
 *
 * Clip the polygon with vertex count in and vertices inx/iny
 * against the rectangular clipping region specified by lower-left corner
 * (x0,y0) and upper-right corner (x1,y1). The resulting vertices are
 * placed in outx/outy.
 *
 * The routine should return the vertex count of the polygon
 * resulting from the clipping.
 *
 * @param in the number of vertices in the polygon to be clipped
 * @param inx - x coords of vertices of polygon to be clipped.
 * @param iny - y coords of vertices of polygon to be clipped.
 * @param outx - x coords of vertices of polygon resulting after clipping.
 * @param outy - y coords of vertices of polygon resulting after clipping.
 * @param x0 - x coord of lower left of clipping rectangle.
 * @param y0 - y coord of lower left of clipping rectangle.
 * @param x1 - x coord of upper right of clipping rectangle.
 * @param y1 - y coord of upper right of clipping rectangle.
 *
 * @return number of vertices in the polygon resulting after clipping
 *
 */
int clipper::clipPolygon(int in, const float inx[], const float iny[],
                float outx[], float outy[],
		float x0, float y0, float x1, float y1)
{
	//Generate bottmleft and topright vertacies
	Vertex BottomLeft = Vertex();
	Vertex TopRight = Vertex();

	BottomLeft.x = x0;
	BottomLeft.y = y0;
	TopRight.x = x1;
	TopRight.y = y1;

	std::vector<Line*>* ClippingWindow;

	//DELETE ALL OF MY CONTENTS AFTER FUNCTION COMPLETES
	std::vector<Vertex> vertacies = std::vector<Vertex>();
	std::vector<Vertex> outputVertacies = std::vector<Vertex>();

	//First lets construct the vertacies based on what we have been passed
	for (int c = 0; c < in; c++)
	{
		//Create the vertex
		Vertex *temp = new Vertex();
		temp->x = inx[c];
		temp->y = iny[c];

		//Push Vertex
		vertacies.push_back(*temp);
	}

	
	//Now lets generate all of the clipping window edges
	ClippingWindow = GenerateClipWindow(&BottomLeft, &TopRight);

	//Left
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(0));
	//Top
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(1));
	//Right
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(2));
	//Bottom
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(3));

	Vertex* test = new Vertex();
	test->x = 3.0;
	test->y = 2.0;

	Vertex* test2 = new Vertex();
	test2->x = 6.0;
	test2->y = 2.0;

	Line* testL = new Line(test, test2, true);
	testL->Start = test;
	testL->End  = test;

	Vertex* third = new Vertex();
	third->x = 4.0;
	third->y = 1.0;
	
//	bool tInside = this->Inside(*third, *testL);
	std::cout << Inside(*third, *testL) << std::endl;

    return 0;  // should return number of vertices in clipped poly.
}

//Clips a set of vertexes HEY MANNY TOMMMOROW  http://www.cs.rit.edu/~icss571/clipTrans/PolyClipBack.html  start at this page and implement the SutherlandHodmanPolygoclip thingy
void ClipSide(std::vector<Vertex>* outputVertexes, std::vector<Vertex> inputVertacies, Line* Edge)
{

}
//Create vertex Start

//Create vertex End

//Create line pass in vertex start and end