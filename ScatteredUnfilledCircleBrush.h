#pragma once
//
// ScatteredCircleBrush.h
//
// The header file for Line Brush. 
//

#ifndef SCATTEREDUNFILLEDCIRCLEBRUSH_H
#define SCATTEREDUNFILLEDCIRCLEBRUSH_H

#include "ImpBrush.h"

class ScatteredUnfilledCircleBrush : public ImpBrush
{
public:
	ScatteredUnfilledCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif