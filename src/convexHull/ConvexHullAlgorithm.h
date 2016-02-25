/*
 * ConvexHullAlgorithm.h
 *
 *  Created on: 23-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLALGORITHM_H_
#define CONVEXHULL_CONVEXHULLALGORITHM_H_

#include <iostream>

#include "../rtree/MyRTree.h"
#include "ConvexHullObject.h"
#include "ConvexHullObjectLeftUpperCorner.h"
#include "ConvexHullObjectRigthLowerCorner.h"
#include "ConvexHullObjectLeftSide.h"
#include "ConvexHullObjectRightSide.h"

class ConvexHullAlgorithm {
public:
	ConvexHullAlgorithm();
	virtual ~ConvexHullAlgorithm();
	void runAlgorithm1(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree);
	void runAlgorithmSide(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree);
	bool algoritmoCH(SpatialIndex::RTree::ConvexHullObject* r, SpatialIndex::RTree::ConvexHullObject* b);
	bool algoritmoCHSide(SpatialIndex::RTree::ConvexHullObject* r, SpatialIndex::RTree::ConvexHullObject* b);
	void prueba1(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree);
	void prueba2(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree);
};

#endif /* CONVEXHULL_CONVEXHULLALGORITHM_H_ */
