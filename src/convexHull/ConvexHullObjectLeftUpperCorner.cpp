/*
 * ConvexHullObjectLeftUpperCorner.cpp
 *
 *  Created on: 25-09-2015
 *      Author: claudio
 */

#include "ConvexHullObjectLeftUpperCorner.h"
#include "../utilities/Geometry.h"

SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner::ConvexHullObjectLeftUpperCorner(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root): ConvexHullObject(tree, root){

}

SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner::~ConvexHullObjectLeftUpperCorner() {
	// TODO Auto-generated destructor stub
}


std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner::getCHOptimist(){
//	std::cout <<"ConvexHullObjectLeftUpperCorner::getCHOptimist()"<<std::endl;

	////////////////////////////////////////////////////////////////////////
	//// Obtener cerradura convexa optimista
	////////////////////////////////////////////////////////////////////////
	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObjectLeftUpperCorner Optimista " << nodes[0]->m_level;
	DrawGnuPlot dgp1(ss.str());
	dgp1.setRange(-200, 5000, -200, 5000);

	std::vector<std::pair<double, double> > puntosCHOptimista;

	//inserto el primer punto, esquina inferior izquierda
	//como no estoy alamcrnando los puntos, solo lo imprimo

	dgp1.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);
	//punto esquina superior derecha
	dgp1.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);
	//punto esquina inferior derecha
	dgp1.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);
//	std::cout <<"tamaño nodes  :: " << nodes.size()<<std::endl;
	//inserto el primer punto de las esquinas superirores derechas de los mbr.
	puntosCHOptimista.push_back(
			std::make_pair(nodes[0]->m_nodeMBR.m_pLow[0],
					nodes[0]->m_nodeMBR.m_pHigh[1]));
	//std::cout <<"aaa  ::getCHOptimist()"<<std::endl;
	for (unsigned int i = 1; i < nodes.size(); i++) {

		if (nodes[i]->m_nodeMBR.m_pLow[0]
				== puntosCHOptimista.back().first) {
			if (nodes[i]->m_nodeMBR.m_pHigh[1]
					!= puntosCHOptimista.back().second) {
				//si el x es igual
				if (nodes[i]->m_nodeMBR.m_pHigh[1]
						> puntosCHOptimista.back().second) {

					puntosCHOptimista.pop_back(); //elimino el ultimo
					//inserto en lugar del otro
					puntosCHOptimista.push_back(
							std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0],
									nodes[i]->m_nodeMBR.m_pHigh[1]));
				}
			}
		} else {
			if (nodes[i]->m_nodeMBR.m_pHigh[1]
					> puntosCHOptimista.back().second) {
				puntosCHOptimista.push_back(
						std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0],
								nodes[i]->m_nodeMBR.m_pHigh[1]));
			}

		}

		//std::cout << rectangulos[i]->m_nodeMBR.m_pLow[0] << std::endl;

		//verificar que sea el poligono convexo

		for (int k = puntosCHOptimista.size()-1; k > 1; k--) {
			/*
			 * ecuacion de la recta
			 *  Y = m*X + n
			 *
			 *  con:
			 *  	m= (y2-y1)/(x2-x1)
			 *  	n= y1 - m*x1
			 *
			 */
			double x1 = puntosCHOptimista[k - 2].first;
			double y1 = puntosCHOptimista[k - 2].second;
			double x2 = puntosCHOptimista[k].first;
			double y2 = puntosCHOptimista[k].second;
			double m = (y2 - y1) / (x2 - x1);
			double n = y1 - m * x1;

			//compruebo que sea convexo
			if (puntosCHOptimista[k - 1].second
					<= m * puntosCHOptimista[k - 1].first + n) {
				puntosCHOptimista.erase(puntosCHOptimista.begin()+k-1);
			}else{
			//	std::cout << puntosCHOptimista.size() << " D:"<< (k-1) << " " << puntosCHOptimista[k - 1].second << " " << (m * puntosCHOptimista[k - 1].first + n) << std::endl;
			}

		}
	}


	//dibujar lineas entre los puntos
	for (unsigned int i = 0; i < puntosCHOptimista.size() - 1; i++) {
		//std::cout << "## " << puntosCHOptimista[i].first << std::endl;
		dgp1.drawPoint(puntosCHOptimista[i].first, puntosCHOptimista[i].second);
		dgp1.drawLine(puntosCHOptimista[i].first, puntosCHOptimista[i].second,
				puntosCHOptimista[i + 1].first,
				puntosCHOptimista[i + 1].second);
	}

	dgp1.drawLine(puntosCHOptimista.back().first,
			puntosCHOptimista.back().second, root->m_nodeMBR.m_pHigh[0],
			root->m_nodeMBR.m_pHigh[1]);

	dgp1.drawLine(puntosCHOptimista.front().first,
			puntosCHOptimista.front().second, root->m_nodeMBR.m_pLow[0],
			root->m_nodeMBR.m_pLow[1]);

	dgp1.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1],
			root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);

	dgp1.drawLine(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1],
			root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);

	dgp1.print();

	this->chOptimist = puntosCHOptimista;

	return puntosCHOptimista;

}
bool comparacionParesX(std::pair<double, double> i, std::pair<double, double> j){
	return i.first < j.first;
}
std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner::getCHPessimist(){
//	std::cout <<"ConvexHullObjectLeftUpperCorner::getCHPessimist()"<<std::endl;
	////////////////////////////////////////////////////////////////////////
		//// Obtener cerradura convexa pesimista
		////////////////////////////////////////////////////////////////////////
	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObjectLeftUpperCorner Pesimista " << nodes[0]->m_level;
		DrawGnuPlot dgp2(ss.str());
			dgp2.setRange(-200, 5000, -200, 5000);
			//Parte : ceradura convexa pesimista
			//std::cout << "pesimista blue" << std::endl;

			std::vector<std::pair<double, double> > puntosCHPesimista;

			//inserto el primer punto, esquina inferior izquierda
			//como no estoy alamcrnando los puntos, solo lo imprimo
			dgp2.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);
			//punto esquina superior derecha
			dgp2.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);
			//punto esquina inferior derecha
			dgp2.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);

			//inserto el primer punto de las esquinas superirores derechas de los mbr.
			//puntosCHPesimista.push_back(rectangulos[0]);

			std::vector<std::pair<double, double> > auxCHPesimista1;
			std::vector<std::pair<double, double> > auxCHPesimista2;

			for (unsigned int i = 0; i < nodes.size(); i++) {
				//esquina inferior izquierda
				auxCHPesimista1.push_back(
						std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0],
								nodes[i]->m_nodeMBR.m_pLow[1]));

				if (!nodes[i]->isLeaf()) { //si es hoja, ambas esquinas son iguales
					//esquina superior derecha
					auxCHPesimista2.push_back(
							std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
									nodes[i]->m_nodeMBR.m_pHigh[1]));
				}


				//std::cout <<"ingresando "<< puntosCHPesimista.back().first << "," << puntosCHPesimista.back().second << std::endl;

			}

		//ordenando
		std::sort(auxCHPesimista1.begin(), auxCHPesimista1.end(), comparacionParesX);
		//ordenando
		std::sort(auxCHPesimista2.begin(), auxCHPesimista2.end(), comparacionParesX);
//		std::cout <<"a: "<< auxCHPesimista1.size() << " b: " << auxCHPesimista2.size() << std::endl ;
		puntosCHPesimista.push_back(auxCHPesimista1[0]);

		//insertando puntos
		for (int i = 0; auxCHPesimista1.size()>0 || auxCHPesimista2.size()>0; i++) {
			//std::cout << "$$ " <<  auxCHPesimista1.size() << "  " << auxCHPesimista2.size() << std::endl;
			if( auxCHPesimista1.size( ) <= 0){

				if( puntosCHPesimista.back().second < auxCHPesimista2.front().second){

					if( puntosCHPesimista.back().first == auxCHPesimista2.front().first){
						puntosCHPesimista.pop_back();
					}

					puntosCHPesimista.push_back(auxCHPesimista2.front());

				}
				auxCHPesimista2.erase(auxCHPesimista2.begin());

			}else{
				if( auxCHPesimista2.size( ) <= 0){

					if (puntosCHPesimista.back().second
							< auxCHPesimista1.front().second) {

						if (puntosCHPesimista.back().first
								== auxCHPesimista1.front().first) {
							puntosCHPesimista.pop_back();
						}

						puntosCHPesimista.push_back(auxCHPesimista1.front());

					}
					auxCHPesimista1.erase(auxCHPesimista1.begin());

				}else{

					if (auxCHPesimista1.front().first < auxCHPesimista2.front().first) {
						if (puntosCHPesimista.back().second
								< auxCHPesimista1.front().second) {

							if (puntosCHPesimista.back().first
									== auxCHPesimista1.front().first) {
								puntosCHPesimista.pop_back();
							}

							puntosCHPesimista.push_back(auxCHPesimista1.front());

						}
						auxCHPesimista1.erase(auxCHPesimista1.begin());

					} else {

						if (puntosCHPesimista.back().second
								< auxCHPesimista2.front().second) {

							if (puntosCHPesimista.back().first
									== auxCHPesimista2.front().first) {
								puntosCHPesimista.pop_back();
							}

							puntosCHPesimista.push_back(auxCHPesimista2.front());

						}

						auxCHPesimista2.erase(auxCHPesimista2.begin());

					}

				}
			}


			//verificar que sea el poligono convexo
//			std::cout <<"l: " << puntosCHPesimista.size() <<std::endl;
			for(int k= puntosCHPesimista.size()-1; k>1; k--){
				/*
				 * ecuacion de la recta
				 *  Y = m*X + n
				 *
				 *  con:
				 *  	m= (y2-y1)/(x2-x1)
				 *  	n= y1 - m*x1
				 *
				 */
				double x1 = puntosCHPesimista[k-2].first;
				double y1 = puntosCHPesimista[k-2].second;
				double x2 = puntosCHPesimista[k].first;
				double y2 = puntosCHPesimista[k].second;
				double m = (y2-y1)/(x2-x1);
				double n = y1- m*x1;

				//compruebo que sea convexo
				if( puntosCHPesimista[k-1].second < m*puntosCHPesimista[k-1].first + n){
					puntosCHPesimista.erase(puntosCHPesimista.begin()+k-1);
				}

			}

		}

		for (unsigned int i = 0; i < puntosCHPesimista.size()-1; i++) {
//			std::cout << "## " << puntosCHPesimista[i].first << ","
//					<< puntosCHPesimista[i].second << std::endl;
			dgp2.drawPoint(puntosCHPesimista[i].first, puntosCHPesimista[i].second);

			dgp2.drawLine(puntosCHPesimista[i].first, puntosCHPesimista[i].second,puntosCHPesimista[i+1].first, puntosCHPesimista[i+1].second);

		}
		dgp2.drawPoint(puntosCHPesimista.back().first, puntosCHPesimista.back().second);

		dgp2.drawLine(puntosCHPesimista.back().first,
				puntosCHPesimista.back().second,
				root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);

		dgp2.drawLine(puntosCHPesimista.front().first,
				puntosCHPesimista.front().second,
				root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);

		dgp2.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1],
				root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);

		dgp2.drawLine(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1],
				root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);
//		std::cout <<"ff: " << puntosCHPesimista.size() <<std::endl;
		chPessimist = puntosCHPesimista;
		return puntosCHPesimista;
}

void SpatialIndex::RTree::ConvexHullObjectLeftUpperCorner::filter(){
//	std::cout <<"ConvexHullObjectLeftUpperCorner::filter() "<< nodes[0]->m_level<<std::endl;

	if(this->madeOfPoints){
		return;
	}


	std::vector<SpatialIndex::RTree::NodePtr> newNodes;

	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObject " << nodes[0]->m_level;

	DrawGnuPlot dgp0(ss.str());
	dgp0.setRange(-200, 5000, -200, 5000);

	//std::cout << "node n°  total: " << nodes.size()<< std::endl;
	for(uint32_t i=0;i<nodes.size(); i++){

		std::vector<std::pair<double, double> > lineas;
		//ingreso una linea desde la esquina superior izquierda del mbr
		//a la esquina superior isquierda del MBR superior
		lineas.push_back(std::make_pair(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1]));
		lineas.push_back(std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0], nodes[i]->m_nodeMBR.m_pHigh[1]));

		//dgp0.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1],nodes[i]->m_nodeMBR.m_pLow[0], nodes[i]->m_nodeMBR.m_pHigh[1]);
		//std::cout << "node n° " << i << " total: " << nodes.size()<< std::endl;
		if( ! Geometry::seIntersecan(this->chPessimist, lineas)){
			//dgp0.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1],nodes[i]->m_nodeMBR.m_pLow[0], nodes[i]->m_nodeMBR.m_pHigh[1]);
			for (uint32_t cChild = 0; cChild < nodes[i]->m_children; ++cChild) {
				nodosAccesados++;
				NodePtr child = tree->readNode(nodes[i]->m_pIdentifier[cChild]);
				std::vector<std::pair<double, double> > lineas2;
				lineas2.push_back(std::make_pair(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1]));
				lineas2.push_back(std::make_pair(child->m_nodeMBR.m_pLow[0], child->m_nodeMBR.m_pHigh[1]));
				if( ! Geometry::seIntersecan(this->chPessimist, lineas2)){
					newNodes.push_back(child);
					dgp0.drawRectangle(child->m_nodeMBR.m_pLow,child->m_nodeMBR.m_pHigh, "#00FF00");
				}
				//delete lineas2;
//				newNodes.push_back(tree->readNode(nodes[i]->m_pIdentifier[cChild]));
//				dgp0.drawRectangle(tree->readNode(nodes[i]->m_pIdentifier[cChild])->m_nodeMBR.m_pLow,tree->readNode(nodes[i]->m_pIdentifier[cChild])->m_nodeMBR.m_pHigh, "#00FF00");
			}
		}

	}
	dgp0.print();
	nodes = newNodes;

	////////////////////////////////////////////////////////////////////////
	//// Ordenar lista de MBR
	////////////////////////////////////////////////////////////////////////
		std::sort(nodes.begin(), nodes.end(), comparacionX);

	this->madeOfPoints = nodes[0]->isLeaf();

}
