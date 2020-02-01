//
// ScatteredUnfilledCircleBrush.cpp
//
// The implementation of Scattered Unfilled Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredunfilledcirclebrush.h"
#include <math.h>

extern float frand();

ScatteredUnfilledCircleBrush::ScatteredUnfilledCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredUnfilledCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredUnfilledCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// circles' distance apart
	int height = 0;
	Point colorChanger;	// used to change color of circle into the color directly under the circle

	if (pDoc == NULL) {
		printf("ScatteredUnfilledCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINE_LOOP);

	SetColor(source);
	for (int i = 0; i < 5; i++)
	{
		length = (rand() % 30 + (-15)); // distance from center on x axis, consider putting this in for loop below
		height = (rand() % 30 + (-15)); // distance from center on y axis, consider putting this in for loop below

		for (int radius = 0; radius < 360; radius++)
		{
			double area = size * 3.14 * radius / 360;	// allows for an unfilled circle

			// changing color to what is under the scattered circles, instead of under the cursor
			colorChanger = target;
			colorChanger.x = target.x + length + size * cos(area);
			colorChanger.y = (target.y + size * sin(area)) + height;
			SetColor(colorChanger);

			//glVertex2d(target.x + size * cos(area), target.y + size * sin(area));
			glVertex2d(target.x + length + size * cos(area), (target.y + size * sin(area)) + height);

		}
	}
	printf("SCATTERED UNFILLED CIRCLE\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void ScatteredUnfilledCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}