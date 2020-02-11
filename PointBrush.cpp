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
	//SetColor(source);

	// setting alpha
	GLubyte alphaColor[3];
	GLubyte temp[3];	// source's color

	memcpy(alphaColor, pDoc->GetOriginalPixel(target), 3);
	memcpy(temp, pDoc->GetOriginalPixel(source), 3);	

	//Resultant R = R1 * ( 1 – alpha * A2 ) + R2 * alpha * A2
	// A2 = alpha mask
	// piazza: result_pixel_color = alpha * pixel_color_from_image_1 + (1-alpha) * pixel_color_from_image_2
	printf("\n");
	std::cout << "alpha: " << alpha << "\n";

	std::cout << "temp[0]: " << (double)temp[0] << "\n";
	std::cout << "temp[1]: " << (double)temp[1] << "\n";
	std::cout << "temp[2]: " << (double)temp[2] << "\n";
	std::cout << "alphaColor[0]: " << (double)alphaColor[0] << "\n";
	std::cout << "alphaColor[1]: " << (double)alphaColor[1] << "\n";
	std::cout << "alphaColor[2]: " << (double)alphaColor[2] << "\n";

	std::cout << "Final[0]: " << alpha * (double)temp[0] + (1 - alpha) * (double)alphaColor[0] << "\n";
	std::cout << "Final[1]: " << alpha * (double)temp[1] + (1 - alpha) * (double)alphaColor[1] << "\n";
	std::cout << "Final[2]: " << alpha * (double)temp[2] + (1 - alpha) * (double)alphaColor[2] << "\n";

	std::cout << "Final[0] (split): " << alpha * (double)temp[0] <<"+"<< (1 - alpha) * (double)alphaColor[0] << "\n";

	alphaColor[0] = (alpha * temp[0] + (1-alpha) * alphaColor[0]); // R
	alphaColor[1] = (alpha * temp[1] + (1-alpha) * alphaColor[1]); // G
	alphaColor[2] = (alpha * temp[2] + (1-alpha) * alphaColor[2]); // B

	// Try and figure out how to get color under the cursor
	// Maybe you need to color each pixel of the point individually?

	glColor3ubv(alphaColor);

	//SetColor(source);

	glVertex2d(target.x, target.y);

	//printf("POINTS\n");	// DEBUGGING PURPOSES ONLY

	glEnd();
}

void PointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}