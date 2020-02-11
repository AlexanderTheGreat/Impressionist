//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);	// best
	//glBegin(GL_POINTS);
	SetColor(source);
	//while(size>=0) // works with points
	//{
		for (int radius = 0; radius < 720; radius++)
		{
			double area = 3.14 * (radius * radius); // pi * r^2

			glVertex2d(target.x + size * cos(area), target.y + size * sin(area));
		}
		//size--;	// works with points
	//}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}