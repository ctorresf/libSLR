/*
 * ConvexHullObjectRightSide.h
 *
 *  Created on: 26-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLOBJECTRIGHTSIDE_H_
#define CONVEXHULL_CONVEXHULLOBJECTRIGHTSIDE_H_

#include "ConvexHullObject.h"
#include "../utilities/Geometry.h"

namespace SpatialIndex {
namespace RTree
{
	class ConvexHullObjectRightSide: public ConvexHullObject {
	public:
		ConvexHullObjectRightSide(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root);
		virtual ~ConvexHullObjectRightSide();
		virtual std::vector<std::pair<double, double> > getCHOptimist();
		virtual std::vector<std::pair<double, double> > getCHPessimist();
		virtual void filter();
		static bool comparacionParesXRojo(std::pair<double, double> i, std::pair<double, double> j);
	};

}
} /* namespace SpatialIndex */

#endif /* CONVEXHULL_CONVEXHULLOBJECTRIGHTSIDE_H_ */
