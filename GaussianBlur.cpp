//
// GaussianBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "gaussianblur.h"
#include <iostream>

#define PI 3.141592654

extern float frand();

GaussianBlur::GaussianBlur(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void GaussianBlur::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	SetColor(source);

	glBegin(GL_POINTS);

	glVertex2d(90, 50);
	glVertex2d(0, 40);
	glVertex2d(180, 90);

	glVertex2d(120, 100);

	glVertex2d(50, 50);
	glVertex2d(target.x, target.y);

	glEnd();

	//BrushMove(source, target);
}

void GaussianBlur::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	double standardDeviation = 1.0;

	printf("GAUSSIAN BLUR\n");
}

void GaussianBlur::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}