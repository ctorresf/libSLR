/*
 * VisitadorGP.cpp
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#include "VisitadorGP.h"

VisitadorGP::VisitadorGP(DrawGnuPlot *dgp) {
	m_indexIO = 0;
	m_leafIO = 0;
	this->dgp = dgp;
	contador=0;
}

VisitadorGP::~VisitadorGP() {
	// TODO Auto-generated destructor stub
}

void VisitadorGP::visitNode(const INode& n) {
	if (n.isLeaf())
		m_leafIO++;
	else
		m_indexIO++;
}

void VisitadorGP::visitData(const IData& d) {
	IShape* pS;
	d.getShape(&pS);
	// do something.
	Region r;
	pS->getMBR(r);

//	cout << "punto " << contador++ << ": " << r.m_pHigh[0] << " - " << r.m_pHigh[1] << endl;
	//cout << r.m_pHigh[0] << " " << r.m_pHigh[1] << endl;
	xy_pts_B.push_back(std::make_pair(r.m_pHigh[0], r.m_pHigh[1]));
	contador++;
	//cout<< "contador " << contador << endl;
	delete pS;

	// data should be an array of characters representing a Region as a string.
	byte* pData = 0;
	uint32_t cLen = 0;
	d.getData(cLen, &pData);
	// do something.
	//string s = reinterpret_cast<char*>(pData);
	//cout << s << endl;
	delete[] pData;

	//cout << d.getIdentifier() << endl;
	// the ID of this data entry is an answer to the query. I will just print it to stdout.
}

void VisitadorGP::visitData(std::vector<const IData*>& v) {
	cout << v[0]->getIdentifier() << " " << v[1]->getIdentifier() << endl;
}

void VisitadorGP::graficaPuntos(std::string color, std::string nombre) {
	dgp->drawPoints(xy_pts_B, color, nombre);
	//std::cout << "tamaño " << xy_pts_B.size() << "  - " << contador << endl;
	//std::cout << "fin" << endl;
/*	gp << "set xrange [-20:120]\n";
	gp << "set yrange [-20:120]\n";
	gp << "set term png\n";
	gp << "set output \"grafica Puntos.png\"\n";
	gp << "plot " << gp.file1d(xy_pts_B) << "with points title 'circle'\n";
	std::cout << "fin " << std::endl;*/
}
