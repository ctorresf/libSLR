/*
 * Query.h
 *
 *  Created on: 20-06-2015
 *      Author: claudio
 */

#ifndef QUERY_H_
#define QUERY_H_
//librerias varias
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <spatialindex/SpatialIndex.h>
#include "utilities/DrawGnuPlot.h"
using namespace SpatialIndex;

class Query: public SpatialIndex::IQueryStrategy {
public:
	Query(DrawGnuPlot *dgp);
	virtual ~Query();
	void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext);
	void defineColor(std::string color);
	void imprime();
	void getPoints(double *pLow, double *pHigh);

private:
	DrawGnuPlot *dgp;
	std::string color;
	int cont;
	double m_pLow[2];
	double m_pHigh[2];
};

#endif /* QUERY_H_ */
