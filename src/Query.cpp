/*
 * Query.cpp
 *
 *  Created on: 20-06-2015
 *      Author: claudio
 */

#include "Query.h"
#include <iostream>

Query::Query(DrawGnuPlot *dgp) {

	this->dgp = dgp;

/*	gp << "set term png\n";
	gp << "set output \"" << archivo << ".png\"\n";
	gp << "set xrange [-20:150]\n";
	gp << "set yrange [-20:150]\n";
	std::cout << "set term png\n";
	std::cout << "set output \"" << archivo << ".png\"\n";
	std::cout << "set xrange [-20:150]\n";
	std::cout << "set yrange [-20:150]\n";*/
	//gp << "plot 12"<< std::endl;
	cont = 1;
}

Query::~Query() {
	// TODO Auto-generated destructor stub
}

void Query::getNextEntry(const IEntry& entry, id_type& nextEntry,
		bool& hasNext) {
	IShape* ps;
	entry.getShape(&ps);
	Region* pr = dynamic_cast<Region*>(ps);

	//dibujo el rectangulo
	dgp->drawRectangle(pr->m_pLow, pr->m_pHigh, color);

/*	gp << "set object " << cont++ << " rect from " << pr->m_pLow[0] << ","
			<< pr->m_pLow[1] << " to " << pr->m_pHigh[0] << ","
			<< pr->m_pHigh[1] << " fs empty border rgb \"" << color
			<< "\" lw 1 \n";
	std::cout << "set object " << cont++ << " rect from " << pr->m_pLow[0]
			<< "," << pr->m_pLow[1] << " to " << pr->m_pHigh[0] << ","
			<< pr->m_pHigh[1] << " fs empty border rgb \"" << color
			<< "\" lw 1 \n";*/

	hasNext = false;

	//gp << "plot 0 "<< std::endl;
// copiar los puntos del rectangulo
	std::memcpy(m_pLow, pr->m_pLow, 2*sizeof(double));
	std::memcpy(m_pHigh, pr->m_pHigh, 2*sizeof(double));

}

void Query::defineColor(std::string color) {
	this->color = color;
}

void Query::imprime() {
	dgp->print();
/*	gp << "plot 0 " << std::endl;
	std::cout << "plot 0 \n";
	std::cout << "fin" << cont << std::endl;*/

}

void Query::getPoints(double *pLow, double *pHigh) {
	std::memcpy(pLow, m_pLow, 2 * sizeof(double));
	std::memcpy(pHigh, m_pHigh, 2 * sizeof(double));
}
