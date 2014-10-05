//
//  clipper.h
//
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "simpleCanvas.h"
#include <vector>

enum BoundryType
{
	East,
	North,
	South,
	West
};

/**
*Vertex Struct
*/
struct Vertex
{
	float x, y;
};
/*
*A line
*/
struct Line
{

	bool IsEdge;
	BoundryType BoundryType;
	Vertex* Start;
	Vertex* End;

	Line(Vertex * Start, Vertex* End, bool IsEdge) : IsEdge(IsEdge), Start(Start), End(End)
	{
		if (End->x > Start->x)
		{
			BoundryType = South;
		}
		else if (End->x < Start->x)         //Changed from the example
		{
			BoundryType = North;
		}
		else if (End->y > Start->y)
		{
			BoundryType = East;
		}
		else if (End->y < Start->y)
		{
			BoundryType = West;
		}
		else
		{
			throw std::invalid_argument("Start and end Vertexes are the same!");
		}
	}
};

/**
 * Simple class that performs clipping
 *
 */
class clipper {

private:
	void ClipSide(std::vector<Vertex>* outputVertexes, std::vector<Vertex> inputVertacies, Line* Edge);
	/*
	*Creates a Clipping window
	*Index 0 = Left
	*Index 1 = Top
	*Index 2 = Right
	*Index 3 = Bottom
	*/
	std::vector<Line*>* GenerateClipWindow(Vertex* BottomLeft, Vertex* TopRight);


	/**
	* Determines If a given vertex is inside of the given clipboundry
	*/
	bool Inside(Vertex testVertex, Line ClipBoundry);

	//Intersection point is outptu tointersectPt
	void Intersect(Line testLine, Line ClipBoundry, Vertex  *intersectPt);


	void SwapOutputInput(std::vector<Vertex>* input, std::vector<Vertex>* output);

	void addVertexOutput(Vertex* newVertex, std::vector<Vertex>* outVertexArr);

	//Keeps tracks of pointers to any Vertexes
	std::vector<Vertex*>* dynamicVertexes;
public:


    /**
     * Constructor
     */
    clipper ();

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
    int clipPolygon(int in, const float inx[], const float iny[],
                    float outx[], float outy[],
		    float x0, float y0, float x1, float y1);

};

#endif
