/*
 * ConvexHullObject.cpp
 *
 *  Created on: 25-09-2015
 *      Author: claudio
 */

#include "ConvexHullObject.h"


int SpatialIndex::RTree::ConvexHullObject::inicial=0;

bool SpatialIndex::RTree::ConvexHullObject::comparacionX (NodePtr i,NodePtr j) {
	return  i->m_nodeMBR.m_pLow[0] < j->m_nodeMBR.m_pLow[0];
}

bool SpatialIndex::RTree::ConvexHullObject::comparacionXRojo (NodePtr i,NodePtr j) {
	return  i->m_nodeMBR.m_pLow[0] > j->m_nodeMBR.m_pLow[0];
}

SpatialIndex::RTree::ConvexHullObject::ConvexHullObject(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root) {
	this->tree = tree;
	this->root = root;
	madeOfPoints= root->isLeaf();
	nodosAccesados=0;
//	chOptimist = new std::vector<std::pair<double, double> > ();
//	chPessimist = new std::vector<std::pair<double, double> > ();
//	nodes = new std::vector<SpatialIndex::RTree::NodePtr> ();

	id = inicial++;
	std::cout <<"id: "<< id << std::endl;
	std::stringstream ss;
	ss << id << " imagen ConvexHullObject " << root->m_level;
	DrawGnuPlot dgp0(ss.str());
	dgp0.setRange(-200, 5000, -200, 5000);


	if(madeOfPoints){
		nodes.push_back(root);
	}else{
		for (uint32_t cChild = 0; cChild < root->m_children; ++cChild) {
			nodosAccesados++;
			nodes.push_back(tree->readNode(root->m_pIdentifier[cChild]));
			dgp0.drawRectangle(tree->readNode(root->m_pIdentifier[cChild])->m_nodeMBR.m_pLow,tree->readNode(root->m_pIdentifier[cChild])->m_nodeMBR.m_pHigh, "#00FF00");
		}
	}
dgp0.print();

////////////////////////////////////////////////////////////////////////
//// Ordenar lista de MBR
////////////////////////////////////////////////////////////////////////
	std::sort(nodes.begin(), nodes.end(), comparacionX);


	//std::cout <<" fin constructor" << std::endl;

}

SpatialIndex::RTree::ConvexHullObject::~ConvexHullObject() {
	// TODO Auto-generated destructor stub
}

bool SpatialIndex::RTree::ConvexHullObject::isMadeOfPoints(){
	return madeOfPoints;
}

bool SpatialIndex::RTree::ConvexHullObject::isMadeOfRectangles(){
	return !madeOfPoints;
}

std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObject::getCHOptimist(){
	//re escribir
	return this->chOptimist;
}

std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObject::getCHPessimist(){
	//re escribir
	return this->chPessimist;
}

void SpatialIndex::RTree::ConvexHullObject::filter(){
	//re escribir
}
