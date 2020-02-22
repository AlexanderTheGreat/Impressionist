//
// UnfilledCircleBrush.cpp
//
// The implementation of Unfilled Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "unfilledcirclebrush.h"
#include <math.h>

extern float frand();

UnfilledCircleBrush::UnfilledCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void UnfilledCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BrushMove(source, target);
}

void UnfilledCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// circles' distance apart
	int height = 0;
	Point colorChanger;	// used to change color of circle into the color directly under the circle
	double alpha = pDoc->getAlpha();
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("UnfilledCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINE_LOOP);

	SetColor(source);

	for (int radius = 0; radius < 360; radius++)
	{
		double area = size * 3.14 * radius / 360;	// allows for an unfilled circle

		// setting alpha and color
		memcpy(alphaColor, pDoc->GetOriginalPixel(colorChanger), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
		alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
		glColor4ubv(alphaColor);

		glVertex2d(target.x + size * cos(area), target.y + size * sin(area));
	}

	printf("UNFILLED CIRCLE\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void UnfilledCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}