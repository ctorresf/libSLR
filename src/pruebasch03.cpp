//============================================================================
// Name        : prueba14MyRTreeLibrary.cpp
// Author      : Claudio Torres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include <spatialindex/SpatialIndex.h>
//
#include "rtree/MyRTree.h"
#include "utilities/DrawGnuPlot.h"
#include "utilities/UtilitiesRTree.h"
#include "VisitadorGP.h"
#include "Query.h"
#include <sstream>
//#include "convexHull/ConvexHullObject.h"
//#include "convexHull/ConvexHullObjectLeftLowerCorner.h"
//#include "convexHull/ConvexHullObjectLeftUpperCorner.h"
//#include "convexHull/ConvexHullAlgorithm.h"
//#include "convexHull/ConvexHullObjectRightUpperCorner.h"
//#include "convexHull/ConvexHullObjectRigthLowerCorner.h"
#include "convexHull/ConvexHullAlgorithm.h"
//#include "rtree/Node.h"

using namespace std;
//screen revisar

// example of a Strategy pattern.
// traverses the tree by level.
class MyQueryStrategy : public SpatialIndex::IQueryStrategy
{
private:
	queue<id_type> ids;
	int cont;
	int level;
	DrawGnuPlot *dgp;

public:
	MyQueryStrategy(DrawGnuPlot *dgp) {
			this->dgp = dgp;
			level = -1;
			cont = 1;
		}
	void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext)
	{

		IShape* ps;
		entry.getShape(&ps);
		Region* pr = dynamic_cast<Region*>(ps);

		//cout << pr->m_pLow[0] << " " << pr->m_pLow[1] << endl;
		//cout << pr->m_pHigh[0] << " " << pr->m_pLow[1] << endl;
	//	cout << pr->m_pHigh[0] << " " << pr->m_pHigh[1] << endl;
		//cout << pr->m_pLow[0] << " " << pr->m_pHigh[1] << endl;
		//cout << pr->m_pLow[0] << " " << pr->m_pLow[1]
		//cout << endl << endl << endl;
			// print node MBRs gnuplot style!

		cout << "set object "<<cont++ <<" rect from "<< pr->m_pLow[0] <<","<<
				pr->m_pLow[1] <<" to " << pr->m_pHigh[0]<<","
				<< pr->m_pHigh[1]<<" lw 5" <<endl;

		const INode* n = dynamic_cast<const INode*>(&entry);


		if( level == -1){
			level = n->getLevel();
		}
		if(((level-n->getLevel()) <= 2)){
			cout << "aaa" << endl;
		}
		cout << "level: " << n->getLevel() << "resta "<< (level-n->getLevel()) << endl;
		// traverse only index nodes at levels 2 and higher.
		if ((n != 0 && n->getLevel() > 1) && ((level-n->getLevel()) <= 2) )
		{
			if((level-n->getLevel()) == 2){
				cout << "::" << pr->m_pLow[0] << endl;
							dgp->drawRectangle(pr->m_pLow,pr->m_pHigh, "#00FF00");
							cout << "level: " << n->getLevel() << "resta "<< (level-n->getLevel()) << endl;
			}

			for (uint32_t cChild = 0; cChild < n->getChildrenCount(); cChild++)
			{
				ids.push(n->getChildIdentifier(cChild));
			}
		}

		if (! ids.empty())
		{
			nextEntry = ids.front(); ids.pop();
			hasNext = true;
		}
		else
		{
			hasNext = false;
		}


		delete ps;
	}
};

int main(int argv, char **argc) {
	cout << "!!!Convex Hull sep. algorithm!!!" << endl;
	std::string numero="3";
	std::string megas="10";
	std::string interseccion="50";
	std::string baseNameR = "arbol" + numero + "rojo"+megas+"mbInterseccion"
				+ interseccion;
		std::string baseNameB = "arbol" + numero + "azul"+megas+"mbInterseccion"
				+ interseccion;

		cout << "prueba a arbol " << numero << " con interseccion de "
				<< interseccion << "%" << endl;

		//creo el archivo del rtree
		IStorageManager* diskfileR;
		IStorageManager* diskfileB;
		StorageManager::IBuffer* fileR;
		StorageManager::IBuffer* fileB;

		//////////////////////////////////////////////////////////////////////
		// leo los rtree
		//////////////////////////////////////////////////////////////////////
		//	cout <<"aaa"<< endl;
		diskfileR = SpatialIndex::StorageManager::loadDiskStorageManager(baseNameR);
		fileR = StorageManager::createNewRandomEvictionsBuffer(*diskfileR, 10,
				false);
		//	cout <<"aaa"<< endl;
		diskfileB = SpatialIndex::StorageManager::loadDiskStorageManager(baseNameB);
		fileB = StorageManager::createNewRandomEvictionsBuffer(*diskfileB, 10,
				false);
		//	cout <<"aaa"<< endl;
		SpatialIndex::RTree::MyRTree* redTree = UtilitiesRTree::cargaTree(baseNameR,
				diskfileR, fileR);
		SpatialIndex::RTree::MyRTree* blueTree = UtilitiesRTree::cargaTree(
				baseNameB, diskfileB, fileB);
		//////////////////////////////////////////////////////////////////////
		//std::cout <<"ejecucion:"<< std::endl;

		ConvexHullAlgorithm cha;

		cha.runAlgorithm1(redTree, blueTree);

		///////////////////////////////////////////////////////////////////////
		delete redTree;
		delete blueTree;
		delete fileR;
		delete fileB;
		delete diskfileR;
		delete diskfileB;


		/////////////////////////////////////////////////////////////////////////
		std::string baseNameR2 = "arbol1rojo10mbInterseccion50P2";
			std::string baseNameB2 = "arbol1azul10mbInterseccion50P2";

			//cout << "prueba a arbol 2"  << endl;

			//creo el archivo del rtree
			IStorageManager* diskfileR2;
			IStorageManager* diskfileB2;
			StorageManager::IBuffer* fileR2;
			StorageManager::IBuffer* fileB2;

			//////////////////////////////////////////////////////////////////////
			// leo los rtree
			//////////////////////////////////////////////////////////////////////
				//cout <<"aaa"<< endl;
			diskfileR2 = SpatialIndex::StorageManager::loadDiskStorageManager(baseNameR2);
			fileR2 = StorageManager::createNewRandomEvictionsBuffer(*diskfileR2, 10,
					false);
				//cout <<"aaa"<< endl;
			diskfileB2 = SpatialIndex::StorageManager::loadDiskStorageManager(baseNameB2);
			fileB2 = StorageManager::createNewRandomEvictionsBuffer(*diskfileB2, 10,
					false);
				//cout <<"aaa"<< endl;
			SpatialIndex::RTree::MyRTree* redTree2 = UtilitiesRTree::cargaTree(baseNameR2,
					diskfileR2, fileR2);
			SpatialIndex::RTree::MyRTree* blueTree2 = UtilitiesRTree::cargaTree(
					baseNameB2, diskfileB2, fileB2);
			//////////////////////////////////////////////////////////////////////
			//std::cout <<"ejecucion2:"<< std::endl;

			ConvexHullAlgorithm cha2;

			cha2.runAlgorithmSide(redTree2, blueTree2);

			//////////////////////////////////////////////////////////////////////
			delete redTree2;
			delete blueTree2;
			delete fileR2;
			delete fileB2;
			delete diskfileR2;
			delete diskfileB2;

		/////////////////////////////////////////////////////////////////////////

	return 0;
}
