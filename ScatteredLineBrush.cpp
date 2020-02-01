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

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// points' distance apart on x axis
	int height = 0;	// points' distance apart on y axis
	Point colorChanger;	// used to change color of circle into the color directly under the circle

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
	SetColor(source);


	// scattered points around the center point
	for (int i = 0; i < 5; i++)
	{
		length = (rand() % 30 + (-15)); // distance from center on x axis
		height = (rand() % 30 + (-15)); // distance from center on y axis

			// changing color to what is under the scattered lines, instead of under the cursor
			colorChanger = target;
			colorChanger.x = (target.x + size) + length;
			colorChanger.y = target.y + height;
			SetColor(colorChanger);

			//glVertex2d(target.x + length, (target.y) + height); // from scattered points
			printf("length: %d\n", length);	// DEBUGGING PURPOSES ONLY
			printf("height: %d\n", height);	// DEBUGGING PURPOSES ONLY

			//std::cout << "Point 1: (" << (target.x + size) + length << ", " << (target.y + height) << ")\n";	// DEBUGGING PURPOSES ONLY

			glVertex2d((target.x + size) + length, target.y + height);

			//std::cout << "Point 2: (" << (target.x - size) + length << ", " << (target.y + height) << ")\n";	// DEBUGGING PURPOSES ONLY

			glVertex2d((target.x - size) + length, target.y + height);
	}

	printf("SCATTERED LINES\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}