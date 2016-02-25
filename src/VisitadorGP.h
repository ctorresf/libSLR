/*
 * VisitadorGP.h
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#ifndef VISITADORGP_H_
#define VISITADORGP_H_

#include <spatialindex/SpatialIndex.h>
#include <iostream>
#include "utilities/DrawGnuPlot.h"
using namespace SpatialIndex;
using namespace std;

class VisitadorGP: public SpatialIndex::IVisitor {
public:
	VisitadorGP(DrawGnuPlot *dgp);
	virtual ~VisitadorGP();
	void visitData(const IData& d);
	void visitNode(const INode& n);
	void visitData(std::vector<const IData*>& v);
	void graficaPuntos(std::string color, std::string nombre);
	size_t m_indexIO;
		size_t m_leafIO;
		size_t contador;

private:


	DrawGnuPlot *dgp;
	std::vector<std::pair<double, double> > xy_pts_B;
};

#endif /* VISITADORGP_H_ */
