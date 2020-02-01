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

extern float frand();

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

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	int thickness = pDoc->getThickness();
	int angleOffset = 0;	// allows for proper rotation
	double radians = 0;
	radians = 180 / (3.14 * angle);

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);

	SetColor(source);
	
	// TODO: allow for changing angle

	// adding and subtracting size allows for starting point to be in the middle as opposed to the side
	glVertex2d(target.x, target.y);	// bottom left
	glVertex2d(target.x, target.y + thickness);	// top left
	glVertex2d(target.x + size, target.y + thickness);	// top right
	glVertex2d(target.x + size, target.y);	// bottom right

	//printf("LINES\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}