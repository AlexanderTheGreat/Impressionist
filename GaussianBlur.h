#pragma once
//
// GaussianBlur.h
//
// The header file for Gaussian Blur. 
//

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "ImpBrush.h"

class GaussianBlur : public ImpBrush
{
public:
	GaussianBlur(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif