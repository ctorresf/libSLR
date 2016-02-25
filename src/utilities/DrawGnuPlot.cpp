/*
 * DrawGnuPlot.cpp
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#include "DrawGnuPlot.h"

DrawGnuPlot::DrawGnuPlot() {
	contFigures = 1;
	gp << "set multiplot" << std::endl;
}

DrawGnuPlot::DrawGnuPlot(std::string fileName) {
	contFigures = 1;
	this->setOutput(fileName);
	gp << "set multiplot" << std::endl;
}

DrawGnuPlot::~DrawGnuPlot() {
	// TODO Auto-generated destructor stub
}

void DrawGnuPlot::setRange(double xMin, double xMax, double yMin, double yMax) {
	gp << "set xrange [" << xMin <<":"<< xMax << "]\n";
	gp << "set yrange [" << yMin <<":" << yMax << "]\n";
//	std::cout << "set xrange [" << xMin <<":"<< xMax << "]\n";
//	std::cout << "set yrange [" << yMin <<":" << yMax << "]\n";
}

void DrawGnuPlot::setOutput(std::string fileName) {
	//gp << "unset multiplot" << std::endl;
	gp << "set term png\n";
	gp << "set output \"" << fileName << ".png\"" << std::endl;
	//gp << "set multiplot" << std::endl;
}

void DrawGnuPlot::drawRectangle(double *pLow, double *pHigh,
		std::string color) {

	gp << "set object " << contFigures++ << " rect from " << pLow[0] << ","
			<< pLow[1] << " to " << pHigh[0] << ","
			<< pHigh[1] << " fs empty border rgb \"" << color
			<< "\" lw 1 \n";
//	std::cout << "set object " << contFigures++ << " rect from " << pLow[0] << ","
//			<< pLow[1] << " to " << pHigh[0] << ","
//			<< pHigh[1] << " fs empty border rgb \"" << color
//			<< "\" lw 1 \n";
}

void DrawGnuPlot::drawPoints(std::vector<std::pair<double, double> > xy_pts_B,
		std::string color, std::string nombre) {

//	std::cout <<"aaa" << std::endl;
	gp << "plot " << gp.file1d(xy_pts_B) << "with points lc rgb \"" << color
			//<< "\" title 'circle'\n";
			<< "\" title '" << nombre << "' " << std::endl;

//	std::cout << "plot " << gp.file1d(xy_pts_B) << "with points lc rgb \"" << color << "\" " << std::endl;
}

void DrawGnuPlot::print() {
	gp << "plot 0 " << std::endl;
}

void DrawGnuPlot::drawLine(double pendiente, double b){
	gp << "f(x)="<< pendiente<<"*x + " << b << "\n";
	gp << "plot f(x)" << std::endl;
//	std::cout << "f(x)="<< pendiente<<"*x + " << b << "\n";
}

void DrawGnuPlot::drawPoint(double x, double y){
	gp << "plot \"<echo '"<<x <<" " << y <<"'\"   with points ls 1" << std::endl;
}
//plot "<echo ' 2 3\n 4 5'" with lines
void DrawGnuPlot::drawLine(double x1, double y1, double x2, double y2){
	gp << "plot \"<echo '"<<x1 << " "<< y1 <<"\\n" <<x2 << " " << y2 <<"'\"   with lines  lc rgb '#00ff00'" << std::endl;
}
