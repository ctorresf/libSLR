/*
 * ConvexHullObjectRightSide.cpp
 *
 *  Created on: 26-09-2015
 *      Author: claudio
 */

#include "ConvexHullObjectRightSide.h"

SpatialIndex::RTree::ConvexHullObjectRightSide::ConvexHullObjectRightSide(SpatialIndex::RTree::MyRTree* tree, SpatialIndex::RTree::NodePtr root): ConvexHullObject(tree, root){

}

SpatialIndex::RTree::ConvexHullObjectRightSide::~ConvexHullObjectRightSide() {
	// TODO Auto-generated destructor stub
}

std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObjectRightSide::getCHOptimist(){
	//std::cout <<"ConvexHullObjectRightSide::getCHOptimist()"<<std::endl;

	////////////////////////////////////////////////////////////////////////
	//// Obtener cerradura convexa optimista
	//// primero saco la cerradura del cuadrante superior
	//// y despues del cuadrante inferior
	////////////////////////////////////////////////////////////////////////
	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObjectRightSide Optimista " << nodes[0]->m_level;
	DrawGnuPlot dgp1( ss.str());
	dgp1.setRange(-200, 5000, -200, 5000);

	////////////////////////////////////////////////////////////////
	//// Cuadrante inferior
	////////////////////////////////////////////////////////////////
	std::vector <std::pair<double, double> > puntosCHOptimistaInferior;

	//inserto el primer punto, esquina inferior izquierda
	//como no estoy alamcrnando los puntos, solo lo imprimo
	dgp1.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);
	//punto esquina superior derecha
	dgp1.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);
	//punto esquina superior izquierda
	dgp1.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1]);

	//inserto el primer punto de las esquinas inferiores derechas de los mbr.
	puntosCHOptimistaInferior.push_back(
			std::make_pair(nodes[0]->m_nodeMBR.m_pHigh[0],
					nodes[0]->m_nodeMBR.m_pLow[1]));

	for (unsigned int i = 1; i < nodes.size(); i++) {

		if (nodes[i]->m_nodeMBR.m_pLow[0] == puntosCHOptimistaInferior.back().first) {
			if (nodes[i]->m_nodeMBR.m_pHigh[1]
					!= puntosCHOptimistaInferior.back().second) {
				//si el x es igual
				if (nodes[i]->m_nodeMBR.m_pHigh[1]
						< puntosCHOptimistaInferior.back().second) {

					puntosCHOptimistaInferior.pop_back(); //elimino el ultimo
					//inserto en lugar del otro
					puntosCHOptimistaInferior.push_back(
							std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
									nodes[i]->m_nodeMBR.m_pLow[1]));
				}
			}
		} else {
			if (nodes[i]->m_nodeMBR.m_pHigh[1]
					< puntosCHOptimistaInferior.back().second) {
				puntosCHOptimistaInferior.push_back(
						std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
								nodes[i]->m_nodeMBR.m_pLow[1]));
			}

		}

		//std::cout << rectangulos[i]->m_nodeMBR.m_pLow[0] << std::endl;

		//verificar que sea el poligono convexo

		for (int k = puntosCHOptimistaInferior.size() - 1; k > 1; k--) {
			/*
			 * ecuacion de la recta
			 *  Y = m*X + n
			 *
			 *  con:
			 *  	m= (y2-y1)/(x2-x1)
			 *  	n= y1 - m*x1
			 *
			 */
			double x1 = puntosCHOptimistaInferior[k - 2].first;
			double y1 = puntosCHOptimistaInferior[k - 2].second;
			double x2 = puntosCHOptimistaInferior[k].first;
			double y2 = puntosCHOptimistaInferior[k].second;
			double m = (y2 - y1) / (x2 - x1);
			double n = y1 - m * x1;

			//compruebo que sea convexo
			if (puntosCHOptimistaInferior[k - 1].second
					> m * puntosCHOptimistaInferior[k - 1].first + n) {
				puntosCHOptimistaInferior.erase(puntosCHOptimistaInferior.begin()+k-1);
			}

		}
	}

	////////////////////////////////////////////////////////////////
	//// Cuadrante superior
	////////////////////////////////////////////////////////////////

	std::vector <std::pair<double, double> > puntosCHOptimistaSuperior;

	//inserto el primer punto, esquina inferior izquierda
	//como no estoy alamcrnando los puntos, solo lo imprimo
	dgp1.drawPoint(root->m_nodeMBR.m_pLow[0],root->m_nodeMBR.m_pLow[1]);
	//punto esquina superior derecha
	dgp1.drawPoint(root->m_nodeMBR.m_pHigh[0],root->m_nodeMBR.m_pHigh[1]);
	//punto esquina superior izquierda
	dgp1.drawPoint(root->m_nodeMBR.m_pLow[0],root->m_nodeMBR.m_pHigh[1]);

	//inserto el primer punto de las esquinas inferiores derechas de los mbr.
	puntosCHOptimistaSuperior.push_back(
						std::make_pair(nodes[0]->m_nodeMBR.m_pHigh[0],
								nodes[0]->m_nodeMBR.m_pLow[1]));

	for(unsigned int i=1; i<nodes.size(); i++){

		if( nodes[i]->m_nodeMBR.m_pLow[0] == puntosCHOptimistaSuperior.back().first ){
			if(nodes[i]->m_nodeMBR.m_pHigh[1] != puntosCHOptimistaSuperior.back().second){
				//si el x es igual
				if(nodes[i]->m_nodeMBR.m_pHigh[1] > puntosCHOptimistaSuperior.back().second){

					puntosCHOptimistaSuperior.pop_back(); //elimino el ultimo
					//inserto en lugar del otro
					puntosCHOptimistaSuperior.push_back(
							std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
									nodes[i]->m_nodeMBR.m_pLow[1]));
				}
			}
		}else{
			if(nodes[i]->m_nodeMBR.m_pHigh[1] > puntosCHOptimistaSuperior.back().second){
				puntosCHOptimistaSuperior.push_back(
						std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
								nodes[i]->m_nodeMBR.m_pLow[1]));
			}

		}

		//std::cout << rectangulos[i]->m_nodeMBR.m_pLow[0] << std::endl;

		//verificar que sea el poligono convexo

		for (int k = puntosCHOptimistaSuperior.size()-1; k > 2; k--) {
			/*
			 * ecuacion de la recta
			 *  Y = m*X + n
			 *
			 *  con:
			 *  	m= (y2-y1)/(x2-x1)
			 *  	n= y1 - m*x1
			 *
			 */
			double x1 = puntosCHOptimistaSuperior[k - 2].first;
			double y1 = puntosCHOptimistaSuperior[k - 2].second;
			double x2 = puntosCHOptimistaSuperior[k].first;
			double y2 = puntosCHOptimistaSuperior[k].second;
			double m = (y2 - y1) / (x2 - x1);
			double n = y1 - m * x1;

			//compruebo que sea convexo
			if (puntosCHOptimistaSuperior[k - 1].second
					< m * puntosCHOptimistaSuperior[k - 1].first + n) {
				puntosCHOptimistaSuperior.erase(puntosCHOptimistaSuperior.begin()+k-1);
			}

		}
	}

	////////////////////////////////////////////////////////////////
	//// union de las CH
	///////////////////////////////////////////////////////////////

//	std::cout <<"aaa4  ::getCHOptimist()"<<std::endl;
	chOptimist.erase(chOptimist.begin(), chOptimist.end());

//	std::cout <<"aaa4.1  ::getCHOptimist()"<<std::endl;
	for ( int i = puntosCHOptimistaSuperior.size()-1; i >= 0 ; i--) {
		chOptimist.push_back(puntosCHOptimistaSuperior[i]);
	}

//	std::cout <<"aaa4.05  ::getCHOptimist() " << puntosCHOptimistaInferior.size() <<std::endl;
	for (int i = 0; i < puntosCHOptimistaInferior.size(); i++) {
		//std::cout <<"aaa4.06  ::getCHOptimist()"<< i<<std::endl;
		chOptimist.push_back(puntosCHOptimistaInferior[i]);

	}

	//agrego bordes izquierdos del MBR de la raiz
	chOptimist.push_back(
			std::make_pair(root->m_nodeMBR.m_pLow[0],
					root->m_nodeMBR.m_pLow[1]));
	chOptimist.push_back(
					std::make_pair(root->m_nodeMBR.m_pLow[0],
							root->m_nodeMBR.m_pHigh[1]));

//	std::cout <<"aaa5  ::getCHOptimist()"<<std::endl;
	for (unsigned int i = 0; i < puntosCHOptimistaSuperior.size(); i++) {
		//std::cout << "## " << puntosCHOptimistaSuperior[i].first << std::endl;
		dgp1.drawPoint(nodes[i]->m_nodeMBR.m_pLow[0],
				puntosCHOptimistaSuperior[i].second);
	}
//	std::cout <<"aaa6 ::getCHOptimist()"<<std::endl;
	//dibujar lineas entre los puntos
	for (unsigned int i = 0; i < chOptimist.size(); i++) {
		std::cout << "## " << chOptimist[i].first << "," << chOptimist[i].second << std::endl;
		dgp1.drawPoint(chOptimist[i].first, chOptimist[i].second);
		dgp1.drawLine(chOptimist[i].first, chOptimist[i].second,
				chOptimist[(i + 1)%chOptimist.size()].first,
				chOptimist[(i + 1)%chOptimist.size()].second);
	}
	//std::cout << "puntos: "<< chOptimist.size() << std::endl;
//		dgp1.drawLine(puntosCHOptimistaSuperior.back().first,
//				puntosCHOptimistaSuperior.back().second, root->m_nodeMBR.m_pHigh[0],
//				root->m_nodeMBR.m_pHigh[1]);
//
//		dgp1.drawLine(puntosCHOptimistaSuperior.front().first,
//				puntosCHOptimistaSuperior.front().second, root->m_nodeMBR.m_pLow[0],
//				root->m_nodeMBR.m_pLow[1]);
//
//		dgp1.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1],
//				root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);
//
//		dgp1.drawLine(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1],
//				root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pLow[1]);

	dgp1.print();

	return chOptimist;
}

bool SpatialIndex::RTree::ConvexHullObjectRightSide::comparacionParesXRojo(std::pair<double, double> i, std::pair<double, double> j){
	return i.first > j.first;
}

std::vector<std::pair<double, double> > SpatialIndex::RTree::ConvexHullObjectRightSide::getCHPessimist(){


	////////////////////////////////////////////////////////////////////////
	//// Obtener cerradura convexa pesimista
	//// primero saco la cerradura del cuadrante superior
	//// y despues del cuadrante inferior
	////////////////////////////////////////////////////////////////////////
	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObjectRightSide Pesimista " << nodes[0]->m_level;
	DrawGnuPlot dgp2(ss.str());
	dgp2.setRange(-200, 5000, -200, 5000);
	//Parte : ceradura convexa pesimista
	//std::cout << "pesimista red" << std::endl;

	////////////////////////////////////////////////////////////////
	//// Cuadrante inferior
	////////////////////////////////////////////////////////////////

	std::vector<std::pair<double, double> > puntosCHPesimistaInferior;

	//inserto el primer punto, esquina inferior izquierda
	//como no estoy alamcrnando los puntos, solo lo imprimo
	dgp2.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);
	//punto esquina superior derecha
	dgp2.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);
	//punto esquina superior izquierda
	dgp2.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1]);

	//inserto el primer punto de las esquinas superirores derechas de los mbr.
	//puntosCHPesimista.push_back(rectangulos[0]);

	std::vector<std::pair<double, double> > auxCHPesimista1;
	std::vector<std::pair<double, double> > auxCHPesimista2;

	for (unsigned int i = 0; i < nodes.size(); i++) {
		//esquina inferior izquierda
		auxCHPesimista1.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0],
						nodes[i]->m_nodeMBR.m_pLow[1]));

		//esquina superior derecha
		auxCHPesimista2.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
						nodes[i]->m_nodeMBR.m_pHigh[1]));
		//std::cout << "ingresando " << auxCHPesimista1.back().first << ","
		//	<< auxCHPesimista1.back().second << std::endl;
		//std::cout << "ingresando " << auxCHPesimista2.back().first << ","
		//	<< auxCHPesimista2.back().second << std::endl;

	}

	//ordenando
	std::sort(auxCHPesimista1.begin(), auxCHPesimista1.end(),
			comparacionParesXRojo);
	//ordenando
	std::sort(auxCHPesimista2.begin(), auxCHPesimista2.end(),
			comparacionParesXRojo);

	//		for (unsigned int i = 0; i < auxCHPesimista1.size(); i++) {
	//			std::cout << "a## " << auxCHPesimista1[i].first << ","
	//					<< auxCHPesimista1[i].second << std::endl;
	//
	//		}
	//		for (unsigned int i = 0; i < auxCHPesimista2.size(); i++) {
	//			std::cout << "b## " << auxCHPesimista2[i].first << ","
	//					<< auxCHPesimista2[i].second << std::endl;
	//
	//		}

	puntosCHPesimistaInferior.push_back(auxCHPesimista2[0]);

	//insertando puntos
	for (int i = 0; auxCHPesimista1.size() > 0 || auxCHPesimista2.size() > 0;
			i++) {
		//std::cout << "$$ " <<  auxCHPesimista1.size() << "  " << auxCHPesimista2.size() << std::endl;
		if (auxCHPesimista1.size() <= 0) {
			//				std::cout <<"ingrprobandoesando1 "<< auxCHPesimista1.back().first << "," << auxCHPesimista1.back().second << " - "
			//						<< puntosCHPesimista.back().first << "," << puntosCHPesimista.back().second<< std::endl;
			if (puntosCHPesimistaInferior.back().second
					> auxCHPesimista2.front().second) {

				if (puntosCHPesimistaInferior.back().first
						== auxCHPesimista2.front().first) {
					puntosCHPesimistaInferior.pop_back();
				}

				puntosCHPesimistaInferior.push_back(auxCHPesimista2.front());

			}
			auxCHPesimista2.erase(auxCHPesimista2.begin());

		} else {
			if (auxCHPesimista2.size() <= 0) {
				//					std::cout <<"ingrprobandoesando2 "<< auxCHPesimista2.back().first << "," << auxCHPesimista2.back().second << " - "
				//										<< puntosCHPesimista.back().first << "," << puntosCHPesimista.back().second<< std::endl;
				if (puntosCHPesimistaInferior.back().second
						> auxCHPesimista1.front().second) {

					if (puntosCHPesimistaInferior.back().first
							== auxCHPesimista1.front().first) {
						puntosCHPesimistaInferior.pop_back();
						//							std::cout << "WW" << std::endl;
					}

					puntosCHPesimistaInferior.push_back(auxCHPesimista1.front());

				}
				auxCHPesimista1.erase(auxCHPesimista1.begin());

			} else {

				if (auxCHPesimista1.front().first
						> auxCHPesimista2.front().first) {
					//						std::cout <<"ingrprobandoesando3 "<< auxCHPesimista1.back().first << "," << auxCHPesimista1.back().second << " - "
					//											<< puntosCHPesimista.back().first << "," << puntosCHPesimista.back().second<< std::endl;
					if (puntosCHPesimistaInferior.back().second
							> auxCHPesimista1.front().second) {

						if (puntosCHPesimistaInferior.back().first
								== auxCHPesimista1.front().first) {
							puntosCHPesimistaInferior.pop_back();
						}

						puntosCHPesimistaInferior.push_back(auxCHPesimista1.front());

					}
					auxCHPesimista1.erase(auxCHPesimista1.begin());

				} else {
					//						std::cout <<"ingrprobandoesando4 "<< auxCHPesimista2.back().first << "," << auxCHPesimista2.back().second << " - "
					//															<< puntosCHPesimista.back().first << "," << puntosCHPesimista.back().second<< std::endl;
					if (puntosCHPesimistaInferior.back().second
							> auxCHPesimista2.front().second) {

						if (puntosCHPesimistaInferior.back().first
								== auxCHPesimista2.front().first) {
							puntosCHPesimistaInferior.pop_back();
						}

						puntosCHPesimistaInferior.push_back(auxCHPesimista2.front());

					}

					auxCHPesimista2.erase(auxCHPesimista2.begin());

				}

			}
		}

		//verificar que sea el poligono convexo

		//FUNCIONA A LA PERFECCION, COMPROBAR EN EL ALGORITMO DE LOS AZULES SI FUNCIONA

		for (int k = puntosCHPesimistaInferior.size() - 1; k > 1; k--) {
			/*
			 * ecuacion de la recta
			 *  Y = m*X + n
			 *
			 *  con:
			 *  	m= (y2-y1)/(x2-x1)
			 *  	n= y1 - m*x1
			 *
			 */
			double x1 = puntosCHPesimistaInferior[k - 2].first;
			double y1 = puntosCHPesimistaInferior[k - 2].second;
			double x2 = puntosCHPesimistaInferior[k].first;
			double y2 = puntosCHPesimistaInferior[k].second;
			double m = (y2 - y1) / (x2 - x1);
			double n = y1 - m * x1;

			//compruebo que sea convexo
			if (puntosCHPesimistaInferior[k - 1].second
					> m * puntosCHPesimistaInferior[k - 1].first + n) {
				puntosCHPesimistaInferior.erase(puntosCHPesimistaInferior.begin() + k - 1);
			}

		}

	}

	////////////////////////////////////////////////////////////////
	//// Cuadrante superior
	////////////////////////////////////////////////////////////////

	std::vector<std::pair<double, double> > puntosCHPesimistaSuperior;

	//inserto el primer punto, esquina inferior izquierda
	//como no estoy alamcrnando los puntos, solo lo imprimo
	dgp2.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pLow[1]);
	//punto esquina superior derecha
	dgp2.drawPoint(root->m_nodeMBR.m_pHigh[0], root->m_nodeMBR.m_pHigh[1]);
	//punto esquina superior izquierda
	dgp2.drawPoint(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1]);

	//inserto el primer punto de las esquinas superirores derechas de los mbr.
	//puntosCHPesimistaSuperior.push_back(rectangulos[0]);

//	std::vector<std::pair<double, double> > auxCHPesimista1;
//	std::vector<std::pair<double, double> > auxCHPesimista2;

	for (unsigned int i = 0; i < nodes.size(); i++) {
		//esquina inferior izquierda
		auxCHPesimista1.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pLow[0],
						nodes[i]->m_nodeMBR.m_pLow[1]));

		//esquina superior derecha
		auxCHPesimista2.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
						nodes[i]->m_nodeMBR.m_pHigh[1]));
		//std::cout << "ingresando " << auxCHPesimista1.back().first << ","
		//	<< auxCHPesimista1.back().second << std::endl;
		//std::cout << "ingresando " << auxCHPesimista2.back().first << ","
		//	<< auxCHPesimista2.back().second << std::endl;

	}

	//ordenando
	std::sort(auxCHPesimista1.begin(), auxCHPesimista1.end(),
			comparacionParesXRojo);
	//ordenando
	std::sort(auxCHPesimista2.begin(), auxCHPesimista2.end(),
			comparacionParesXRojo);

	//		for (unsigned int i = 0; i < auxCHPesimista1.size(); i++) {
	//			std::cout << "a## " << auxCHPesimista1[i].first << ","
	//					<< auxCHPesimista1[i].second << std::endl;
	//
	//		}
	//		for (unsigned int i = 0; i < auxCHPesimista2.size(); i++) {
	//			std::cout << "b## " << auxCHPesimista2[i].first << ","
	//					<< auxCHPesimista2[i].second << std::endl;
	//
	//		}

	puntosCHPesimistaSuperior.push_back(auxCHPesimista2[0]);

	//insertando puntos
	for (int i = 0; auxCHPesimista1.size() > 0 || auxCHPesimista2.size() > 0;
			i++) {
		//std::cout << "$$ " <<  auxCHPesimista1.size() << "  " << auxCHPesimista2.size() << std::endl;
		if (auxCHPesimista1.size() <= 0) {
			//				std::cout <<"ingrprobandoesando1 "<< auxCHPesimista1.back().first << "," << auxCHPesimista1.back().second << " - "
			//						<< puntosCHPesimista.back().first << "," << puntosCHPesimistaSuperior.back().second<< std::endl;
			if (puntosCHPesimistaSuperior.back().second
					< auxCHPesimista2.front().second) {

				if (puntosCHPesimistaSuperior.back().first
						== auxCHPesimista2.front().first) {
					puntosCHPesimistaSuperior.pop_back();
				}

				puntosCHPesimistaSuperior.push_back(auxCHPesimista2.front());

			}
			auxCHPesimista2.erase(auxCHPesimista2.begin());

		} else {
			if (auxCHPesimista2.size() <= 0) {
				//					std::cout <<"ingrprobandoesando2 "<< auxCHPesimista2.back().first << "," << auxCHPesimista2.back().second << " - "
				//										<< puntosCHPesimistaSuperior.back().first << "," << puntosCHPesimistaSuperior.back().second<< std::endl;
				if (puntosCHPesimistaSuperior.back().second
						< auxCHPesimista1.front().second) {

					if (puntosCHPesimistaSuperior.back().first
							== auxCHPesimista1.front().first) {
						puntosCHPesimistaSuperior.pop_back();
						//							std::cout << "WW" << std::endl;
					}

					puntosCHPesimistaSuperior.push_back(auxCHPesimista1.front());

				}
				auxCHPesimista1.erase(auxCHPesimista1.begin());

			} else {

				if (auxCHPesimista1.front().first
						> auxCHPesimista2.front().first) {
					//						std::cout <<"ingrprobandoesando3 "<< auxCHPesimista1.back().first << "," << auxCHPesimista1.back().second << " - "
					//											<< puntosCHPesimistaSuperior.back().first << "," << puntosCHPesimistaSuperior.back().second<< std::endl;
					if (puntosCHPesimistaSuperior.back().second
							< auxCHPesimista1.front().second) {

						if (puntosCHPesimistaSuperior.back().first
								== auxCHPesimista1.front().first) {
							puntosCHPesimistaSuperior.pop_back();
						}

						puntosCHPesimistaSuperior.push_back(auxCHPesimista1.front());

					}
					auxCHPesimista1.erase(auxCHPesimista1.begin());

				} else {
					//						std::cout <<"ingrprobandoesando4 "<< auxCHPesimista2.back().first << "," << auxCHPesimista2.back().second << " - "
					//															<< puntosCHPesimistaSuperior.back().first << "," << puntosCHPesimistaSuperior.back().second<< std::endl;
					if (puntosCHPesimistaSuperior.back().second
							< auxCHPesimista2.front().second) {

						if (puntosCHPesimistaSuperior.back().first
								== auxCHPesimista2.front().first) {
							puntosCHPesimistaSuperior.pop_back();
						}

						puntosCHPesimistaSuperior.push_back(auxCHPesimista2.front());

					}

					auxCHPesimista2.erase(auxCHPesimista2.begin());

				}

			}
		}

		//verificar que sea el poligono convexo

		//FUNCIONA A LA PERFECCION, COMPROBAR EN EL ALGORITMO DE LOS AZULES SI FUNCIONA

		for (int k = puntosCHPesimistaSuperior.size() - 1; k > 1; k--) {
			/*
			 * ecuacion de la recta
			 *  Y = m*X + n
			 *
			 *  con:
			 *  	m= (y2-y1)/(x2-x1)
			 *  	n= y1 - m*x1
			 *
			 */
			double x1 = puntosCHPesimistaSuperior[k - 2].first;
			double y1 = puntosCHPesimistaSuperior[k - 2].second;
			double x2 = puntosCHPesimistaSuperior[k].first;
			double y2 = puntosCHPesimistaSuperior[k].second;
			double m = (y2 - y1) / (x2 - x1);
			double n = y1 - m * x1;

			//compruebo que sea convexo
			if (puntosCHPesimistaSuperior[k - 1].second
					< m * puntosCHPesimistaSuperior[k - 1].first + n) {
				puntosCHPesimistaSuperior.erase(puntosCHPesimistaSuperior.begin() + k - 1);
			}

		}

	}

	////////////////////////////////////////////////////////////////
	//// union de las CH
	///////////////////////////////////////////////////////////////
//	std::cout <<"aaa4  ::getCHPessimist()"<<std::endl;

	chPessimist.erase(chPessimist.begin(), chPessimist.end());

	//busco punto de interseccion de ambas convex hull pesimistas
	if(puntosCHPesimistaInferior[0].first > puntosCHPesimistaSuperior[0].first ){
		//si existe alguna interseccion entre ambas CH, busco el punto

		//por ahora voy a elminar el primer punto
		puntosCHPesimistaInferior.erase(puntosCHPesimistaInferior.begin());
		puntosCHPesimistaSuperior.erase(puntosCHPesimistaSuperior.begin());

	}

	for (int i = puntosCHPesimistaSuperior.size()-1 ; i >= 0; i--) {
		chPessimist.push_back(puntosCHPesimistaSuperior[i]);
	}

	for (unsigned int i = 0; i < puntosCHPesimistaInferior.size() ; i++) {
		chPessimist.push_back(puntosCHPesimistaInferior[i]);
	}

	//agrego bordes derecho del MBR de la raiz
	chPessimist.push_back(
			std::make_pair(root->m_nodeMBR.m_pLow[0],
					root->m_nodeMBR.m_pLow[1]));
	chPessimist.push_back(
					std::make_pair(root->m_nodeMBR.m_pLow[0],
							root->m_nodeMBR.m_pHigh[1]));


	//dibujo las lineas
	//dibujar lineas entre los puntos
	for (unsigned int i = 0; i < chPessimist.size(); i++) {
//		std::cout << "## " << chPessimist[i].first <<"," << chPessimist[i].second << std::endl;
		dgp2.drawPoint(chPessimist[i].first, chPessimist[i].second);
		dgp2.drawLine(chPessimist[i].first, chPessimist[i].second,
				chPessimist[(i + 1)%chPessimist.size()].first,
				chPessimist[(i + 1)%chPessimist.size()].second);
	}
//	std::cout << "puntos: "<< chPessimist.size() << std::endl;

	 return chPessimist;

}

void SpatialIndex::RTree::ConvexHullObjectRightSide::filter(){
	//		std::cout << "ConvexHullObjectRightSide::filter()" << std::endl;

	//DrawGnuPlot dgp0("imagen CH rojo 00");
	//		dgp0.setRange(-200, 5000, -200, 5000);
	if (this->madeOfPoints) {
		return;
	}

	std::vector<SpatialIndex::RTree::NodePtr> newNodes;

	std::stringstream ss;
	ss <<  id << " imagen ConvexHullObject " << nodes[0]->m_level;

	DrawGnuPlot dgp0(ss.str());
	dgp0.setRange(-200, 5000, -200, 5000);

	for (uint32_t i = 0; i < nodes.size(); i++) {

		std::vector<std::pair<double, double> > lineas;
		//ingreso una linea desde la esquina superior izquierda del mbr
		//al lado derecho del MBR superior
		lineas.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
						root->m_nodeMBR.m_pLow[1]));
		lineas.push_back(
				std::make_pair(nodes[i]->m_nodeMBR.m_pHigh[0],
						nodes[i]->m_nodeMBR.m_pLow[1]));

		//dgp0.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1],nodes[i]->m_nodeMBR.m_pLow[0], nodes[i]->m_nodeMBR.m_pHigh[1]);
		//std::cout << "node n° " << i << " total: " << nodes.size()<< std::endl;
		if (!Geometry::seIntersecan(this->chPessimist, lineas)) {
			//dgp0.drawLine(root->m_nodeMBR.m_pLow[0], root->m_nodeMBR.m_pHigh[1],nodes[i]->m_nodeMBR.m_pLow[0], nodes[i]->m_nodeMBR.m_pHigh[1]);
			for (uint32_t cChild = 0; cChild < nodes[i]->m_children; ++cChild) {
				nodosAccesados++;
				NodePtr child = tree->readNode(nodes[i]->m_pIdentifier[cChild]);
				std::vector<std::pair<double, double> > lineas2;
				lineas2.push_back(
						std::make_pair(root->m_nodeMBR.m_pHigh[0],
								root->m_nodeMBR.m_pLow[1]));
				lineas2.push_back(
						std::make_pair(child->m_nodeMBR.m_pHigh[0],
								child->m_nodeMBR.m_pLow[1]));
				if (!Geometry::seIntersecan(this->chPessimist, lineas2)) {
					newNodes.push_back(child);
					dgp0.drawRectangle(child->m_nodeMBR.m_pLow,
							child->m_nodeMBR.m_pHigh, "#00FF00");
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
	std::sort(nodes.begin(), nodes.end(), comparacionXRojo);

	this->madeOfPoints = nodes[0]->isLeaf();
}
