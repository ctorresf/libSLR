/*
 * ConvexHullObjectLeftUpperCorner.h
 *
 *  Created on: 25-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLOBJECTLEFTUPPERCORNER_H_
#define CONVEXHULL_CONVEXHULLOBJECTLEFTUPPERCORNER_H_

#include "ConvexHullObject.h"

namespace SpatialIndex
{
	namespace RTree
	{
	class MyRTree;

	class ConvexHullObjectLeftUpperCorner: public ConvexHullObject
	{
	public:
		ConvexHullObjectLeftUpperCorner(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root);
		virtual ~ConvexHullObjectLeftUpperCorner();
		virtual std::vector<std::pair<double, double> > getCHOptimist();
		virtual std::vector<std::pair<double, double> > getCHPessimist();
		virtual void filter();
	};
	}
}
#endif /* CONVEXHULL_CONVEXHULLOBJECTLEFTUPPERCORNER_H_ */
