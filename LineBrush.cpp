//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "linebrush.h"
#include <iostream>

#define PI 3.141592654

extern float frand();

// modifies the polygon to allow rotatation based on a given angle
void angleModifier(Point &vertex, double radians)
{
	Point temp = vertex;

	vertex.x = temp.x * cos(radians) - temp.y * sin(radians);
	vertex.y = temp.x * sin(radians) + temp.y * cos(radians);
}

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//int size = pDoc->getSize();

	//glPointSize((float)size);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	double radians = angle * PI / 180;
	int thickness = pDoc->getThickness();
	double alpha = pDoc->getAlpha();
	int tempX = 0;
	int tempY = 0;
	Point topRight, topLeft, bottomRight, bottomLeft;	// points of the polygon that are modifyable
	topRight = topLeft = bottomRight = bottomLeft = target;
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);
	//SetColor(source);
	
	// used to subtract from vertices to set origin to (0,0) (cursor)
	tempX = target.x;
	tempY = target.y;

	//initializing the points
	topLeft.y += thickness;
	topRight.x += size;
	topRight.y += thickness;
	bottomRight.x += size;

	// allows for the cursor to be in the center of the placed line
	topLeft.x -= size;
	bottomLeft.x -= size;
	bottomLeft.y -= thickness;
	bottomRight.y -= thickness;

	// setting center of the line to (0,0) temporarily, and translating the other points
	bottomLeft.x -= tempX;
	bottomLeft.y -= tempY;
	topLeft.x -= tempX;
	topLeft.y -= tempY;
	topRight.x -= tempX;
	topRight.y -= tempY;
	bottomRight.x -= tempX;
	bottomRight.y -= tempY;

	// rotating the each vertex around the center (cursor)
	angleModifier(bottomLeft, radians);
	angleModifier(topLeft, radians);
	angleModifier(topRight, radians);
	angleModifier(bottomRight, radians);
	
	// setting alpha and color
	memcpy(alphaColor, pDoc->GetOriginalPixel(source), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
	alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
	glColor4ubv(alphaColor);

	// adding back the initial values of x and y to re-translate the polygon back to its original spot, and then displaying the line
	glVertex2d(bottomLeft.x + tempX, bottomLeft.y + tempY);	// bottom left
	glVertex2d(topLeft.x + tempX, topLeft.y + tempY);	// top left
	glVertex2d(topRight.x + tempX, topRight.y + tempY);	// top right
	glVertex2d(bottomRight.x + tempX, bottomRight.y + tempY);	// bottom right

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}