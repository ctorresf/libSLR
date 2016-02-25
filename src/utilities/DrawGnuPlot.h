/*
 * DrawGnuPlot.h
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#ifndef UTILITIES_DRAWGNUPLOT_H_
#define UTILITIES_DRAWGNUPLOT_H_

#include <iostream>
#include "gnuplot-iostream.h"

class DrawGnuPlot {
public:
	DrawGnuPlot();
	DrawGnuPlot(std::string fileName);
	virtual ~DrawGnuPlot();
	void setRange(double xMin, double xMax, double yMin, double yMax);
	void drawRectangle(double *pLow, double *pHigh, std::string color);
	void drawPoints(std::vector<std::pair<double, double> > xy_pts_B, std::string color, std::string nombre);
	void drawPoint(double x, double y);
	void print();
	void drawLine(double pendiente, double b);
	void drawLine(double x1, double y1, double x2, double y2);

private:
	Gnuplot gp;
	int contFigures;
	void setOutput(std::string fileName);
};

#endif /* UTILITIES_DRAWGNUPLOT_H_ */
