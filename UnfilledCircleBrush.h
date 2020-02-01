#pragma once
//
// CircleBrush.h
//
// The header file for Line Brush. 
//

#ifndef UNFILLEDCIRCLEBRUSH_H
#define UNFILLEDCIRCLEBRUSH_H

#include "ImpBrush.h"

class UnfilledCircleBrush : public ImpBrush
{
public:
	UnfilledCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif