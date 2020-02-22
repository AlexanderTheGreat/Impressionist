//
// ScatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredpointbrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();	// size of circle
	int length = 0;	// points' distance apart on x axis
	int height = 0;	// points' distance apart on y axis
	Point colorChanger;	// used to change color of circle into the color directly under the circle
	double alpha = pDoc->getAlpha();
	GLubyte alphaColor[4];

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);

	// scattered points around the center point
	for (int i = 0; i < 5; i++)
	{
		length = (rand() % 30 + (-15)); // distance from center on x axis
		height = (rand() % 30 + (-15)); // distance from center on y axis

		for (int radius = 0; radius < 720; radius++)
		{
			// changing color to what is under the scattered points, instead of under the cursor
			colorChanger = target;
			colorChanger.x = target.x + length + size;
			colorChanger.y = (target.y + size) + height;
			//SetColor(colorChanger);

			// setting alpha and color
			memcpy(alphaColor, pDoc->GetOriginalPixel(colorChanger), 3);	// copying the RGB values of the pixel to the first 3 indicies of alphaColor
			alphaColor[3] = static_cast<GLubyte>(alpha * 255.0);	// setting the last index of alphaColor to the alpha value, casted as a ubyte
			glColor4ubv(alphaColor);

			glVertex2d(target.x + (length * 0.1 * size), (target.y) + (height * 0.1 * size));
		}
	}

	printf("SCATTERED POINTS\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}