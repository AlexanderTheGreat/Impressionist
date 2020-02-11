//
// ScatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredcirclebrush.h"
#include <math.h>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// circles' distance apart
	int height = 0;
	Point colorChanger;	// used to change color of circle into the color directly under the circle

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_LOOP);

	SetColor(source);

	// initial middle circle
	for (int radius = 0; radius < 720; radius++)
	{
		double area = 3.14 * (radius * radius); // pi * r^2

		glVertex2d(target.x + size * cos(area), target.y + size * sin(area));
	}

	glEnd();

	// scattered circles around the center circle
	for (int i = 0; i < 5; i++)
	{
		glBegin(GL_POLYGON);

		length = (rand() % 30 + (-15)); // distance from center on x axis, consider putting this in for loop below
		height = (rand() % 30 + (-15)); // distance from center on y axis, consider putting this in for loop below

		for (int radius = 0; radius < 720; radius++)
		{
			double area = 3.14 * (radius * radius); // pi * r^2

			// changing color to what is under the scattered circles, instead of under the cursor
			colorChanger = target;
			colorChanger.x = target.x + length;
			colorChanger.y = target.y + height;
			//colorChanger.x = target.x + length + size * cos(area);	// causes very odd issues with the polygon and its colors
			//colorChanger.y = (target.y + size * sin(area)) + height;
			SetColor(colorChanger);

			glVertex2d(target.x + length + size * cos(area), (target.y + size * sin(area)) + height);
		}

		glEnd();
	}

	//printf("SCATTERED CIRCLE\n");	// DEBUGGING PURPOSES ONLY
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}