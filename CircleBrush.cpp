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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	double alpha = pDoc->getAlpha();
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);	// best
	//glBegin(GL_POINTS);
	//SetColor(source);
	//while(size>=0) // works with points
	//{
	// setting alpha and color
	memcpy(alphaColor, pDoc->GetOriginalPixel(source), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
	alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
	glColor4ubv(alphaColor);

		for (int radius = 0; radius < 720; radius++)	// 720 allows for a nice round circle
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