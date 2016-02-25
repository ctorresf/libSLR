/*
 * ConvexHullObject.h
 *
 *  Created on: 25-09-2015
 *      Author: claudio
 */

#ifndef CONVEXHULL_CONVEXHULLOBJECT_H_
#define CONVEXHULL_CONVEXHULLOBJECT_H_

//#include "Node.h"
#include "../utilities/DrawGnuPlot.h"
#include "../rtree/MyRTree.h"
//#include "Node.h"
//#include <iostream>

namespace SpatialIndex
{
	namespace RTree
	{
//	class MyRTree;
//	class Node;

	class ConvexHullObject {
	public:
		ConvexHullObject(MyRTree* tree, NodePtr root);
		virtual ~ConvexHullObject();
		virtual std::vector<std::pair<double, double> > getCHOptimist();
		virtual std::vector<std::pair<double, double> > getCHPessimist();
		virtual void filter();
		bool isMadeOfPoints();
		bool isMadeOfRectangles();
		static bool comparacionX (NodePtr i, NodePtr j);
		static bool comparacionXRojo (NodePtr i, NodePtr j);
	//private:
		SpatialIndex::RTree::MyRTree* tree;
		std::vector<std::pair<double, double> > chOptimist;
		std::vector<std::pair<double, double> > chPessimist;
		std::vector<SpatialIndex::RTree::NodePtr> nodes;
		SpatialIndex::RTree::NodePtr root;
		bool madeOfPoints;

		double nodosAccesados;

		int id;
		static int inicial;

	};
	}

}

#endif /* CONVEXHULL_CONVEXHULLOBJECT_H_ */
