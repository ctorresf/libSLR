/*
 * ConvexHullObjectRigthLowerCorner.h
 *
 *  Created on: 26-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLOBJECTRIGTHLOWERCORNER_H_
#define CONVEXHULL_CONVEXHULLOBJECTRIGTHLOWERCORNER_H_

#include "ConvexHullObject.h"
#include "../utilities/Geometry.h"

namespace SpatialIndex {
	namespace RTree {
	class ConvexHullObjectRigthLowerCorner: public ConvexHullObject {
	public:
		ConvexHullObjectRigthLowerCorner(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root);
		virtual ~ConvexHullObjectRigthLowerCorner();virtual std::vector<std::pair<double, double> > getCHOptimist();
		virtual std::vector<std::pair<double, double> > getCHPessimist();
		virtual void filter();
		static bool comparacionParesXRojo(std::pair<double, double> i, std::pair<double, double> j);
	};

	}/* namespace RTree */
} /* namespace SpatialIndex */

#endif /* CONVEXHULL_CONVEXHULLOBJECTRIGTHLOWERCORNER_H_ */
