//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"
#include <iostream>

extern float frand();

PointBrush::PointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void PointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	double alpha = pDoc->getAlpha();
	int size = pDoc->getSize();

	

	glPointSize(size);

	BrushMove(source, target);
}

void PointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	double alpha = pDoc->getAlpha();

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
	glBegin(GL_POINTS);
	SetColor(source);

	////// DOESNT WORK////////////////
	/*
	glAlphaFunc(GL_GREATER, alpha);
	glEnable(GL_ALPHA_TEST); 
	*/
	//printf("ALPHA: %lf\n", alpha);
	//////////////////////////////////

	glVertex2d(target.x, target.y);


	//printf("POINTS\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void PointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}