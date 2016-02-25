/*
 * ConvexHullAlgorithm.cpp
 *
 *  Created on: 23-09-2015
 *      Author: claudio
 */

#include "ConvexHullAlgorithm.h"

ConvexHullAlgorithm::ConvexHullAlgorithm() {
	// TODO Auto-generated constructor stub
	//SpatialIndex::RTree::ConvexHullObject::inicial=0;
}

ConvexHullAlgorithm::~ConvexHullAlgorithm() {
	// TODO Auto-generated destructor stub
}

void ConvexHullAlgorithm::runAlgorithm1(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree){
//CORNER ALGORITHM

	SpatialIndex::RTree::ConvexHullObject *b;

	b = new SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner(blueTree,
			blueTree->obtenerRaiz());

	SpatialIndex::RTree::ConvexHullObject *r;

	r = new SpatialIndex::RTree::ConvexHullObjectRigthLowerCorner(redTree,
			redTree->obtenerRaiz());

	if( algoritmoCH(r,b)){
		std::cout << "\nson linealmente separables" << std::endl;
	}else{
		std::cout << "\nno son linealmente separables" << std::endl;
	}

	std::cout << "\nAZUL:\nnodos accesados: " << b->nodosAccesados << std::endl;
	std::cout << "puntos recuperados: " << b->chPessimist.size() << std::endl;

	std::cout << "\nROJO:\nnodos accesados: " << r->nodosAccesados << std::endl;
	std::cout << "puntos recuperados: " << r->chPessimist.size() << std::endl;
}

void ConvexHullAlgorithm::runAlgorithmSide(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree){

	//side algorithm
	SpatialIndex::RTree::ConvexHullObject *b;

	b = new SpatialIndex::RTree::ConvexHullObjectLeftSide(blueTree,
			blueTree->obtenerRaiz());

	SpatialIndex::RTree::ConvexHullObject *r;

	r = new SpatialIndex::RTree::ConvexHullObjectRightSide(redTree,
			redTree->obtenerRaiz());

	if( algoritmoCH(r,b)){
		std::cout << "\nson linealmente separables" << std::endl;
	}else{
		std::cout << "\nno son linealmente separables" << std::endl;
	}

	std::cout << "\nAZUL:\nnodos accesados: " << b->nodosAccesados << std::endl;
	std::cout << "puntos recuperados: " << b->chPessimist.size() << std::endl;

	std::cout << "\nROJO:\nnodos accesados: " << r->nodosAccesados << std::endl;
	std::cout << "puntos recuperados: " << r->chPessimist.size() << std::endl;
}

bool ConvexHullAlgorithm::algoritmoCH(SpatialIndex::RTree::ConvexHullObject* r, SpatialIndex::RTree::ConvexHullObject* b){
	std::cout<< "algoritmo de cerradura convexa" << std::endl;

	while( true ){
		//std::cout <<"lvel red: " << (r->nodes[0]->m_level) << std::endl;
		if( Geometry::seIntersecan(b->getCHOptimist(), r->getCHOptimist())){
			return true;
		}else{
			if( r->isMadeOfPoints() && b->isMadeOfPoints() ){
				return false;
			}

			if( Geometry::seIntersecan(b->getCHPessimist(), r->getCHPessimist()) ){
				return false;
			}
			b->filter();
			r->filter();
		}

	}
}

bool ConvexHullAlgorithm::algoritmoCHSide(SpatialIndex::RTree::ConvexHullObject* r, SpatialIndex::RTree::ConvexHullObject* b){
	std::cout<< "algoritmo de cerradura convexa" << std::endl;

	while( true ){
		//std::cout <<"lvel red: " << (r->nodes[0]->m_level) << std::endl;
		if( Geometry::seIntersecan(b->getCHOptimist(), r->getCHOptimist())){
			return true;
		}else{
			if( r->isMadeOfPoints() && b->isMadeOfPoints() ){
				return false;
			}

			if( Geometry::seIntersecan(b->getCHPessimist(), r->getCHPessimist()) ){
				return false;
			}
			b->filter();
			r->filter();
		}

	}

}

void ConvexHullAlgorithm::prueba1(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree){

	SpatialIndex::RTree::ConvexHullObject *b;

	b = new SpatialIndex::RTree::ConvexHullObjectLeftSide(blueTree,
			blueTree->obtenerRaiz());

	SpatialIndex::RTree::ConvexHullObject *r;

	r = new SpatialIndex::RTree::ConvexHullObjectRightSide(redTree,
			redTree->obtenerRaiz());

	std::cout << "lalala"<< std::endl;
	b->getCHOptimist();

	b->getCHPessimist();

	b->filter();


	while(! b->madeOfPoints){
		b->getCHPessimist();

		b->filter();
	}
	b->getCHPessimist();
	std::cout << "nodos accesados: " << b->nodosAccesados << std::endl;
	std::cout << "puntos recuperados: " << b->chPessimist.size() << std::endl;



		std::cout << "lalala"<< std::endl;
		r->getCHOptimist();

		r->getCHPessimist();

		r->filter();


		while(! r->madeOfPoints){
			r->getCHPessimist();

			r->filter();
		}
		r->getCHPessimist();
		std::cout << "ROJO\nnodos accesados: " << r->nodosAccesados << std::endl;
		std::cout << "puntos recuperados: " << r->chPessimist.size() << std::endl;
}

void ConvexHullAlgorithm::prueba2(SpatialIndex::RTree::MyRTree* redTree, SpatialIndex::RTree::MyRTree* blueTree){
	SpatialIndex::RTree::ConvexHullObject *b;

	b = new SpatialIndex::RTree::ConvexHullObjectLeftSide(blueTree,
			blueTree->obtenerRaiz());

	SpatialIndex::RTree::ConvexHullObject *r;

	r = new SpatialIndex::RTree::ConvexHullObjectRightSide(redTree,
			redTree->obtenerRaiz());

	while( b->isMadeOfRectangles()){
		b->getCHOptimist();

		b->getCHPessimist();

		b->filter();
	}

		std::cout << "nodos accesados: " << b->nodosAccesados << std::endl;
		std::cout << "puntos recuperados: " << b->chPessimist.size() << std::endl;

		while( r->isMadeOfRectangles()){
			r->getCHOptimist();

			r->getCHPessimist();

			r->filter();
		}

			std::cout << "nodos accesados: " << r->nodosAccesados << std::endl;
			std::cout << "puntos recuperados: " << r->chPessimist.size() << std::endl;

	//return false;
}
