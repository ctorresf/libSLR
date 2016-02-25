/*
 * ConvexHullObjectLeftSide.h
 *
 *  Created on: 26-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLOBJECTLEFTSIDE_H_
#define CONVEXHULL_CONVEXHULLOBJECTLEFTSIDE_H_

#include "ConvexHullObject.h"
#include "../utilities/Geometry.h"

namespace SpatialIndex {
namespace RTree
{
	class ConvexHullObjectLeftSide: public ConvexHullObject {
	public:
		ConvexHullObjectLeftSide(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root);
		virtual ~ConvexHullObjectLeftSide();
		virtual std::vector<std::pair<double, double> > getCHOptimist();
		virtual std::vector<std::pair<double, double> > getCHPessimist();
		virtual void filter();
		static bool comparacionParesX(std::pair<double, double> i, std::pair<double, double> j);
	};
}
} /* namespace SpatialIndex */

#endif /* CONVEXHULL_CONVEXHULLOBJECTLEFTSIDE_H_ */
