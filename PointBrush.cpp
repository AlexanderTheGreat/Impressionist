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
	int size = pDoc->getSize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize((float)size);

	BrushMove(source, target);
}

void PointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	double alpha = pDoc->getAlpha();
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
	glBegin(GL_POINTS);

	// setting alpha and color
	memcpy(alphaColor, pDoc->GetOriginalPixel(source), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
	alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
	glColor4ubv(alphaColor);

	glVertex2d(target.x, target.y);

	glEnd();
}

void PointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}