/*
 * Utilities.h
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#ifndef UTILITIESRTREE_H_
#define UTILITIESRTREE_H_

#include <spatialindex/SpatialIndex.h>
#include <iostream>
#include "../rtree/MyRTree.h"
//using namespace SpatialIndex;
using namespace std;

class UtilitiesRTree {
public:
	UtilitiesRTree();
	virtual ~UtilitiesRTree();
	static SpatialIndex::RTree::MyRTree *creaRTree(std::string baseName,SpatialIndex::IStorageManager* diskfile, SpatialIndex::StorageManager::IBuffer* file);
	static SpatialIndex::RTree::MyRTree *cargaTree(std::string baseName,SpatialIndex::IStorageManager* diskfile, SpatialIndex::StorageManager::IBuffer* file);
	static void llenaRTree( SpatialIndex::RTree::MyRTree *tree, int xMin, int xMax,
			int yMin, int yMax, double cantidadElementos);
	static void llena2RTreeIntersectados(SpatialIndex::RTree::MyRTree *treeLow, SpatialIndex::RTree::MyRTree *treeHigh,
			int xLowMin, int xLowMax, int yLowMin, int yLowMax,
			int xHighMin, int xHighMax, int yHighMin, int yHighMax,
			double nElements, double m, int b); //m es la pendiente de la recta y b es donde corta al eje y

};

#endif /* UTILITIESRTREE_H_ */
