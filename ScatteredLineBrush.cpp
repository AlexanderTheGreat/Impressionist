//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlinebrush.h"
#include <iostream>

#define PI 3.141592654

extern float frand();

// modifies the polygon to allow rotatation based on a given angle
void angleModifier2(Point& vertex, double radians)
{
	Point temp = vertex;

	vertex.x = temp.x * cos(radians) - temp.y * sin(radians);
	vertex.y = temp.x * sin(radians) + temp.y * cos(radians);
}

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int angle = pDoc->getAngle();
	double radians = angle * PI / 180;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// points' distance apart on x axis
	int height = 0;	// points' distance apart on y axis
	int thickness = pDoc->getThickness();
	int tempX = 0;
	int tempY = 0;
	Point topRight, topLeft, bottomRight, bottomLeft;	// points of the polygon that are modifyable
	topRight = topLeft = bottomRight = bottomLeft = target;
	Point colorChanger;	// used to change color of circle into the color directly under the circle
	double alpha = pDoc->getAlpha();
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}


	// used to subtract from vertices to set origin to (0,0) (cursor)



	for (int i = 0; i < 5; i++)
	{
		glBegin(GL_POLYGON);

		length = (rand() % 30 + (-15)); // distance from center on x axis
		height = (rand() % 30 + (-15)); // distance from center on y axis


		tempX = target.x;
		tempY = target.y;
		topRight = topLeft = bottomRight = bottomLeft = target;

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
		angleModifier2(bottomLeft, radians);
		angleModifier2(topLeft, radians);
		angleModifier2(topRight, radians);
		angleModifier2(bottomRight, radians);

		colorChanger = target;
		colorChanger.x = (target.x) + length;
		colorChanger.y = target.y + height;
		//SetColor(colorChanger);

		// setting alpha and color
		memcpy(alphaColor, pDoc->GetOriginalPixel(colorChanger), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
		alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
		glColor4ubv(alphaColor);

		// adding back the initial values of x and y to re-translate the polygon back to its original spot, and then displaying the line
		glVertex2d((bottomLeft.x + tempX) + (length * 0.1 * size), (bottomLeft.y + tempY) + (height * 0.1 * size));	// bottom left
		glVertex2d((topLeft.x + tempX) + (length * 0.1 * size), (topLeft.y + tempY) + (height * 0.1 * size));	// top left
		glVertex2d((topRight.x + tempX) + (length * 0.1 * size), (topRight.y + tempY) + (height * 0.1 * size));	// top right
		glVertex2d((bottomRight.x + tempX) + (length * 0.1 * size), (bottomRight.y + tempY) + (height * 0.1 * size));	// bottom right

		glEnd();
	}

	//glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}