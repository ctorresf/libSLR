/*
 * Utilities.cpp
 *
 *  Created on: 22-06-2015
 *      Author: claudio
 */

#include "UtilitiesRTree.h"

UtilitiesRTree::UtilitiesRTree() {
	// TODO Auto-generated constructor stub

}

UtilitiesRTree::~UtilitiesRTree() {
	// TODO Auto-generated destructor stub
}

SpatialIndex::RTree::MyRTree *UtilitiesRTree::creaRTree(std::string baseName,SpatialIndex::IStorageManager* diskfile, SpatialIndex::StorageManager::IBuffer* file){
//	diskfile = StorageManager::createNewDiskStorageManager(
//			baseName, 4096);
//	file =
//			StorageManager::createNewRandomEvictionsBuffer(*diskfile, 10,
//					false);
	SpatialIndex::id_type indexIdentifier;
	SpatialIndex::RTree::MyRTree* tree = dynamic_cast<SpatialIndex::RTree::MyRTree*>(SpatialIndex::RTree::createNewRTree(*file, 0.7, 7, 7, 2,
			SpatialIndex::RTree::RV_RSTAR, indexIdentifier));

	return tree;
}

SpatialIndex::RTree::MyRTree *UtilitiesRTree::cargaTree(std::string baseName,SpatialIndex::IStorageManager* diskfile, SpatialIndex::StorageManager::IBuffer* file){
//	SpatialIndex::IStorageManager* diskfile = SpatialIndex::StorageManager::loadDiskStorageManager(
//			baseName);
//	SpatialIndex::StorageManager::IBuffer* file =
//			SpatialIndex::StorageManager::createNewRandomEvictionsBuffer(*diskfile, 10,
//					false);
	//ISpatialIndex* tree = RTree::loadRTree(*file, 1);
	return dynamic_cast<SpatialIndex::RTree::MyRTree*>(SpatialIndex::RTree::loadRTree(*file, 1));
}

void UtilitiesRTree::llenaRTree( SpatialIndex::RTree::MyRTree *tree, int xMin, int xMax,
		int yMin, int yMax, double cantidadElementos){
	SpatialIndex::id_type id;
	double plow[2], phigh[2];
	SpatialIndex::Region r;
	//llenar el Red Tree
	for (double var = 0; var < cantidadElementos; ++var) {
		int x1 = xMin+(rand() % (xMax-xMin));
		int y1 = yMin+(rand() % (yMax-yMin));
		plow[0] = x1;
		plow[1] = y1;
		phigh[0] = x1;
		phigh[1] = y1;
		r = SpatialIndex::Region(plow, phigh, 2);

		std::ostringstream os;
		os << r;
		std::string data = os.str();
		//cout << var << endl;
		tree->insertData(data.size() + 1,
				reinterpret_cast<const byte*>(data.c_str()), r, id);

	}
}

void UtilitiesRTree::llena2RTreeIntersectados(SpatialIndex::RTree::MyRTree *treeLow, SpatialIndex::RTree::MyRTree *treeHigh,
			int xLowMin, int xLowMax, int yLowMin, int yLowMax,
			int xHighMin, int xHighMax, int yHighMin, int yHighMax,
			double nElements, double m, int b){

	SpatialIndex::id_type id;
	double plow[2], phigh[2];
	SpatialIndex::Region r;
	//llenar el Low Tree
	for (double var = 0; var < nElements; ++var) {
		int x1 = xLowMin+(rand() % (xLowMax-xLowMin));
		int y1 = yLowMin+(rand() % (yLowMax-yLowMin));

		//el punto debe estar abajo de la linea
		while( y1 > (m*x1+b) ){
			y1 = yLowMin+(rand() % (yLowMax-yLowMin));
		}

		plow[0] = x1;
		plow[1] = y1;
		phigh[0] = x1;
		phigh[1] = y1;
		r = SpatialIndex::Region(plow, phigh, 2);

		std::ostringstream os;
		os << r;
		std::string data = os.str();
		//cout << var << endl;
		treeLow->insertData(data.size() + 1,
				reinterpret_cast<const byte*>(data.c_str()), r, id);

	}

	//llenar el High Tree
	for (double var = 0; var < nElements; ++var) {
		int x1 = xHighMin+(rand() % (xHighMax-xHighMin));
		int y1 = yHighMin+(rand() % (yHighMax-yHighMin));

		//el punto debe arriba abajo de la linea
		while( y1 < (m*x1+b) ){
			y1 = yHighMin+(rand() % (yHighMax-yHighMin));
		}

		plow[0] = x1;
		plow[1] = y1;
		phigh[0] = x1;
		phigh[1] = y1;
		r = SpatialIndex::Region(plow, phigh, 2);

		std::ostringstream os;
		os << r;
		std::string data = os.str();
		//cout << var << endl;
		treeHigh->insertData(data.size() + 1,
				reinterpret_cast<const byte*>(data.c_str()), r, id);

	}

}
