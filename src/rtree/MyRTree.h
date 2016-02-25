/******************************************************************************
 * Project:  libspatialindex - A C++ library for spatial indexing
 * Author:   Marios Hadjieleftheriou, mhadji@gmail.com
 ******************************************************************************
 * Copyright (c) 2002, Marios Hadjieleftheriou
 *
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

#include "Statistics.h"
#include "Node.h"
#include "PointerPoolNode.h"
#include <spatialindex/SpatialIndex.h>
#include "../utilities/DrawGnuPlot.h"
//#include "ConvexHullObjectLeftUpperCorner.h"
//#include "ConvexHullObject.h"

namespace SpatialIndex
{
	namespace RTree
	{
		class MyRTree : public ISpatialIndex
		{
                  //class NNEntry;
			class ConvexHullObject;
			class ConvexHullObjectLeftUpperCorner;

		public:
			MyRTree(IStorageManager&, Tools::PropertySet&);
				// String                   Value     Description
				// ----------------------------------------------
				// IndexIndentifier         VT_LONG   If specified an existing index will be openened from the supplied
				//                          storage manager with the given index id. Behaviour is unspecified
				//                          if the index id or the storage manager are incorrect.
				// Dimension                VT_ULONG  Dimensionality of the data that will be inserted.
				// IndexCapacity            VT_ULONG  The index node capacity. Default is 100.
				// LeafCapactiy             VT_ULONG  The leaf node capacity. Default is 100.
				// FillFactor               VT_DOUBLE The fill factor. Default is 70%
				// TreeVariant              VT_LONG   Can be one of Linear, Quadratic or Rstar. Default is Rstar
				// NearMinimumOverlapFactor VT_ULONG  Default is 32.
				// SplitDistributionFactor  VT_DOUBLE Default is 0.4
				// ReinsertFactor           VT_DOUBLE Default is 0.3
				// EnsureTightMBRs          VT_BOOL   Default is true
				// IndexPoolCapacity        VT_LONG   Default is 100
				// LeafPoolCapacity         VT_LONG   Default is 100
				// RegionPoolCapacity       VT_LONG   Default is 1000
				// PointPoolCapacity        VT_LONG   Default is 500

			virtual ~MyRTree();



			//
			// ISpatialIndex interface
			//
			virtual void insertData(uint32_t len, const byte* pData, const IShape& shape, id_type shapeIdentifier);
			virtual bool deleteData(const IShape& shape, id_type id);
			virtual void containsWhatQuery(const IShape& query, IVisitor& v);
			virtual void intersectsWithQuery(const IShape& query, IVisitor& v);
			virtual void pointLocationQuery(const Point& query, IVisitor& v);
			virtual void nearestNeighborQuery(uint32_t k, const IShape& query, IVisitor& v, INearestNeighborComparator&);
			virtual void nearestNeighborQuery(uint32_t k, const IShape& query, IVisitor& v);
			virtual void selfJoinQuery(const IShape& s, IVisitor& v);
			virtual void queryStrategy(IQueryStrategy& qs);
			virtual void getIndexProperties(Tools::PropertySet& out) const;
			virtual void addCommand(ICommand* pCommand, CommandType ct);
			virtual bool isIndexValid();
			virtual void getStatistics(IStatistics** out) const;
			virtual void flush();
			void miFuncion();
			std::vector<std::pair<double, double> >  intentoAlgoritmo1RojosArriba();
			std::vector<std::pair<double, double> >  intentoAlgoritmo1AzulesAbajo();
			void intentoAlgoritmo1RojosArribaRecursivo(Node* nodo,std::vector<std::pair<double, double> > puntosSolucion);
			void intentoAlgoritmo1AzulesAbajoRecursivo(Node* nodo,std::vector<std::pair<double, double> > puntosSolucion);
			std::vector<std::pair<double, double> > intentoAlgoritmo1RojosIzquierda();
			std::vector<std::pair<double, double> >  intentoAlgoritmo1AzulesDerecha();
			//SpatialIndex::RTree::ConvexHullObject *intentoConvexHullAzul();
			NodePtr obtenerRaiz();
			void intentoConvexHullAzul2(DrawGnuPlot* dgp);
			void intentoConvexHullRojo2(DrawGnuPlot* dgp);
			//mod
			NodePtr readNode(id_type page);
		private:
			void initNew(Tools::PropertySet&);
			void initOld(Tools::PropertySet& ps);
			void storeHeader();
			void loadHeader();

			void insertData_impl(uint32_t dataLength, byte* pData, Region& mbr, id_type id);
			void insertData_impl(uint32_t dataLength, byte* pData, Region& mbr, id_type id, uint32_t level, byte* overflowTable);
			bool deleteData_impl(const Region& mbr, id_type id);

			id_type writeNode(Node*);
//			NodePtr readNode(id_type page);
			void deleteNode(Node*);

			void rangeQuery(RangeQueryType type, const IShape& query, IVisitor& v);
			void selfJoinQuery(id_type id1, id_type id2, const Region& r, IVisitor& vis);
            void visitSubTree(NodePtr subTree, IVisitor& v);
            
            //fuciones propias
            static bool comparacionX (NodePtr i,NodePtr j);
            static bool comparacionXRojo (NodePtr i,NodePtr j);

            //fin funciones propias

			IStorageManager* m_pStorageManager;

			id_type m_rootID, m_headerID;

			RTreeVariant m_treeVariant;

			double m_fillFactor;

			uint32_t m_indexCapacity;

			uint32_t m_leafCapacity;

			uint32_t m_nearMinimumOverlapFactor;
				// The R*-Tree 'p' constant, for calculating nearly minimum overlap cost.
				// [Beckmann, Kriegel, Schneider, Seeger 'The R*-tree: An efficient and Robust Access Method
				// for Points and Rectangles', Section 4.1]

			double m_splitDistributionFactor;
				// The R*-Tree 'm' constant, for calculating spliting distributions.
				// [Beckmann, Kriegel, Schneider, Seeger 'The R*-tree: An efficient and Robust Access Method
				// for Points and Rectangles', Section 4.2]

			double m_reinsertFactor;
				// The R*-Tree 'p' constant, for removing entries at reinserts.
				// [Beckmann, Kriegel, Schneider, Seeger 'The R*-tree: An efficient and Robust Access Method
				//  for Points and Rectangles', Section 4.3]

			uint32_t m_dimension;

			Region m_infiniteRegion;

			Statistics m_stats;

			bool m_bTightMBRs;

			Tools::PointerPool<Point> m_pointPool;
			Tools::PointerPool<Region> m_regionPool;
			Tools::PointerPool<Node> m_indexPool;
			Tools::PointerPool<Node> m_leafPool;

			std::vector<Tools::SmartPointer<ICommand> > m_writeNodeCommands;
			std::vector<Tools::SmartPointer<ICommand> > m_readNodeCommands;
			std::vector<Tools::SmartPointer<ICommand> > m_deleteNodeCommands;

#ifdef HAVE_PTHREAD_H
			pthread_mutex_t m_lock;
#endif

			class NNEntry
			{
			public:
				id_type m_id;
				IEntry* m_pEntry;
				double m_minDist;

				NNEntry(id_type id, IEntry* e, double f) : m_id(id), m_pEntry(e), m_minDist(f) {}
				~NNEntry() {}

				struct ascending : public std::binary_function<NNEntry*, NNEntry*, bool>
				{
					bool operator()(const NNEntry* __x, const NNEntry* __y) const { return __x->m_minDist > __y->m_minDist; }
				};
			}; // NNEntry

			class NNComparator : public INearestNeighborComparator
			{
			public:
				double getMinimumDistance(const IShape& query, const IShape& entry)
				{
					return query.getMinimumDistance(entry);
				}

				double getMinimumDistance(const IShape& query, const IData& data)
				{
					IShape* pS;
					data.getShape(&pS);
					double ret = query.getMinimumDistance(*pS);
					delete pS;
					return ret;
				}
			}; // NNComparator

			class ValidateEntry
			{
			public:
				ValidateEntry(Region& r, NodePtr& pNode) : m_parentMBR(r), m_pNode(pNode) {}

				Region m_parentMBR;
				NodePtr m_pNode;
			}; // ValidateEntry

			friend class Node;
			friend class Leaf;
			friend class Index;
			friend class BulkLoader;
//			friend class ConvexHullObject;
//			friend class ConvexHullObjectLeftUpperCorner;

			friend std::ostream& operator<<(std::ostream& os, const MyRTree& t);
		}; // RTree

		std::ostream& operator<<(std::ostream& os, const MyRTree& t);

		//visitadores auxiliares
		class Visitador1: public SpatialIndex::IVisitor {
		public:
			double nodosVisitados=0;
			Visitador1(double y){
				this->yMenor = y;
			}
			virtual ~Visitador1(){}
			void visitData(const IData& d){
				//std::cout << "punto en borde " << std::endl;
				IShape* pS;
				d.getShape(&pS);
				// do something.
				Region r;
				pS->getMBR(r);
//				std::cout << "punto " << ": " << r.m_pHigh[0] << " - " << r.m_pHigh[1] << std::endl;

				if( r.m_pHigh[1] < yMenor){
					yMenor = r.m_pHigh[1];
				}

			}
			void visitNode(const INode& n){
				nodosVisitados++;
				//std::cout << "visitador 1 node level " << n.getLevel() << std::endl;
			}
			void visitData(std::vector<const IData*>& v){}

			double yMenor;
		private:
			std::vector<std::pair<double, double> > xy_pts_B;

		};
		class Visitador2: public SpatialIndex::IVisitor {
		public:
			double nodosVisitados=0;
			Visitador2(double x) {
				this->xMayor = x;
			}
			virtual ~Visitador2() {}
			void visitData(const IData& d) {
				//std::cout << "punto en borde " << std::endl;
				IShape* pS;
				d.getShape(&pS);
				// do something.
				Region r;
				pS->getMBR(r);
//				std::cout << "punto " << ": " << r.m_pHigh[0] << " - " << r.m_pHigh[1]
//						<< std::endl;

				if( r.m_pHigh[0] > xMayor){
					xMayor = r.m_pHigh[0];
				}
			}
			void visitNode(const INode& n) {
				nodosVisitados++;
			}
			void visitData(std::vector<const IData*>& v) {
			}

			double xMayor;

		private:
			std::vector<std::pair<double, double> > xy_pts_B;

		};
		class Visitador3: public SpatialIndex::IVisitor {
				public:
			double nodosVisitados=0;
					Visitador3(double y){
						this->yMayor = y;
					}
					virtual ~Visitador3(){}
					void visitData(const IData& d){
						//std::cout << "punto en borde " << std::endl;
						IShape* pS;
						d.getShape(&pS);
						// do something.
						Region r;
						pS->getMBR(r);
		//				std::cout << "punto " << ": " << r.m_pHigh[0] << " - " << r.m_pHigh[1] << std::endl;

						if( r.m_pHigh[1] > yMayor){
							yMayor = r.m_pHigh[1];
						}

					}
					void visitNode(const INode& n){
						nodosVisitados++;
						//std::cout << "visitador 1 node level " << n.getLevel() << std::endl;
					}
					void visitData(std::vector<const IData*>& v){}

					double yMayor;
				private:
					std::vector<std::pair<double, double> > xy_pts_B;

				};
				class Visitador4: public SpatialIndex::IVisitor {
				public:
					double nodosVisitados=0;
					Visitador4(double x) {
						this->xMenor = x;
					}
					virtual ~Visitador4() {}
					void visitData(const IData& d) {
						//std::cout << "punto en borde " << std::endl;
						IShape* pS;
						d.getShape(&pS);
						// do something.
						Region r;
						pS->getMBR(r);
//						std::cout << "punto " << ": " << r.m_pHigh[0] << " - " << r.m_pHigh[1]
//								<< std::endl;

						if( r.m_pHigh[0] < xMenor){
							xMenor = r.m_pHigh[0];
						}
					}
					void visitNode(const INode& n) {
						nodosVisitados++;
					}
					void visitData(std::vector<const IData*>& v) {
					}

					double xMenor;

				private:
					std::vector<std::pair<double, double> > xy_pts_B;

				};
				class NodoListaX{
								public:
									double xMin;
									double xMax;
									id_type id;
									NodoListaX(double xMin, double xMax, id_type id){
										this->id=id;
										this->xMax=xMax;
										this->xMin=xMin;
									}
								};
				class Query1: public SpatialIndex::IQueryStrategy {
					//obtengo el x mayor
				public:
					Query1(double x, Region r){
						xMayor=x;
						nodosVisitados=0;
						this->r = r;
					}
					virtual ~Query1(){

					}
					void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext){

						nodosVisitados++;
						const INode* n = dynamic_cast<const INode*>(&entry);
						//NodePtr n = dynamic_cast<NodePtr>(&entry);

						if( n->isLeaf() ){ //es hoja
							//recorro sus hijos
							for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
								//Region r2;
								IShape* ps;
								//((r2 = *(n->m_ptrMBR[cChild]);
								n->getChildShape(cChild, &ps);
								Region* pr = dynamic_cast<Region*>(ps);
//								std::cout <<"aa: "<< pr->m_pLow[0]<<" "<< pr->m_pLow[0] << std::endl;
								if( pr->m_pHigh[0] > xMayor){
									xMayor = pr->m_pHigh[0];
								}

							}
						}else{ //nodo interno
							//recorro sus hijos
							for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
								IShape* ps;
								n->getChildShape(cChild, &ps);
								Region* pr = dynamic_cast<Region*>(ps);
//								std::cout << "info y nodo: " << pr->m_pLow[1] << std::endl;
								if(r.intersectsRegion(*pr)){
								//if ( pr->m_pLow[1] == y || pr->m_pHigh[1]==y ) {
									NodoListaX nodo(pr->m_pLow[0], pr->m_pHigh[0],n->getChildIdentifier(cChild));
								//	lista.push_back(nodo);
									if(lista.empty()){
										lista.push_back(nodo);
									}else{
										NodoListaX nn=lista.front();
										if(pr->m_pHigh[0] > nn.xMax){
											if(pr->m_pLow[0] > nn.xMax){
												lista.erase(lista.begin(), lista.end());
												lista.push_back(nodo);
											}else{
												lista.push_front(nodo);
											}
										}else{
											if(pr->m_pHigh[0] > nn.xMin){
												lista.push_back(nodo);
											}
										}
									}

									//ids.push(n->getChildIdentifier(cChild));
								}
							}
						}

						if (!lista.empty()/*!ids.empty()*/) {
							//nextEntry = ids.front();
							nextEntry = lista.front().id;
							lista.pop_front();
							//ids.pop();
							hasNext = true;
						} else {
							hasNext = false;
						}
					}

					std::queue<id_type> ids;
					std::list<NodoListaX> lista;
					double xMayor;
					double nodosVisitados;
					Region r;
				};
				class Query2: public SpatialIndex::IQueryStrategy {
									//obtengo el x menor
								public:
									Query2(double x, Region r){
										xMenor=x;
										nodosVisitados=0;
										this->r = r;
									}
									virtual ~Query2(){

									}
									void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext){

										nodosVisitados++;
										const INode* n = dynamic_cast<const INode*>(&entry);
										//NodePtr n = dynamic_cast<NodePtr>(&entry);

										if( n->isLeaf() ){ //es hoja
											//recorro sus hijos
											for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
												//Region r2;
												IShape* ps;
												//((r2 = *(n->m_ptrMBR[cChild]);
												n->getChildShape(cChild, &ps);
												Region* pr = dynamic_cast<Region*>(ps);
				//								std::cout <<"aa: "<< pr->m_pLow[0]<<" "<< pr->m_pLow[0] << std::endl;
												if( pr->m_pLow[0] < xMenor){
													xMenor = pr->m_pHigh[0];
												}

											}
										}else{ //nodo interno
											//recorro sus hijos
											for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
												IShape* ps;
												n->getChildShape(cChild, &ps);
												Region* pr = dynamic_cast<Region*>(ps);
												//std::cout << "info y nodo: " << pr->m_pLow[1] << std::endl;
												if(r.intersectsRegion(*pr)){
												//if ((pr->m_pLow[1] == y || pr->m_pHigh[1]==y) ) {
													NodoListaX nodo(pr->m_pLow[0], pr->m_pHigh[0],n->getChildIdentifier(cChild));
													if(lista.empty()){
														lista.push_back(nodo);
													}else{
														NodoListaX nn=lista.front();
														if(pr->m_pLow[0] < nn.xMin){
															if(pr->m_pHigh[0] < nn.xMin){
																lista.erase(lista.begin(), lista.end());
																lista.push_back(nodo);
															}else{
																lista.push_front(nodo);
															}
														}else{
															if(pr->m_pHigh[0] < nn.xMin){
																lista.push_back(nodo);
															}
														}
													}

													//ids.push(n->getChildIdentifier(cChild));
												}
											}
										}

										if (!lista.empty()/*!ids.empty()*/) {
											//nextEntry = ids.front();
											nextEntry = lista.front().id;
											lista.pop_front();
											//ids.pop();
											hasNext = true;
										} else {
											hasNext = false;
										}
									}

									std::queue<id_type> ids;
									std::list<NodoListaX> lista;
									double xMenor;
									double nodosVisitados;
									Region r;
								};
				class Query3: public SpatialIndex::IQueryStrategy {
									//obtengo el y mayor
								public:
									Query3(double y, Region r){
										yMayor=y;
										nodosVisitados=0;
										this->r = r;
									}
									virtual ~Query3(){

									}
									void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext){

										nodosVisitados++;
										const INode* n = dynamic_cast<const INode*>(&entry);
										//NodePtr n = dynamic_cast<NodePtr>(&entry);

										if( n->isLeaf() ){ //es hoja
											//recorro sus hijos
											for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
												//Region r2;
												IShape* ps;
												//((r2 = *(n->m_ptrMBR[cChild]);
												n->getChildShape(cChild, &ps);
												Region* pr = dynamic_cast<Region*>(ps);
				//								std::cout <<"aa: "<< pr->m_pLow[0]<<" "<< pr->m_pLow[0] << std::endl;
												if( pr->m_pHigh[1] > yMayor){
													yMayor = pr->m_pHigh[1];
												}

											}
										}else{ //nodo interno
											//recorro sus hijos
											for (uint32_t cChild = 0; cChild < n->getChildrenCount(); ++cChild) {
												IShape* ps;
												n->getChildShape(cChild, &ps);
												Region* pr = dynamic_cast<Region*>(ps);
												//std::cout << "info y nodo: " << pr->m_pLow[1] << std::endl;
												if(r.intersectsRegion(*pr)){
												//if ((pr->m_pLow[0] == x || pr->m_pHigh[0]==x) ) {
													NodoListaX nodo(pr->m_pLow[1], pr->m_pHigh[1],n->getChildIdentifier(cChild));
													if(lista.empty()){
														lista.push_back(nodo);
													}else{
														NodoListaX nn=lista.front();
														if(pr->m_pHigh[1] > nn.xMax){
															if(pr->m_pLow[1] > nn.xMax){
																lista.erase(lista.begin(), lista.end());
																lista.push_back(nodo);
															}else{
																lista.push_front(nodo);
															}
														}else{
															if(pr->m_pHigh[1] > nn.xMin){
																lista.push_back(nodo);
															}
														}
													}

													//ids.push(n->getChildIdentifier(cChild));
												}
											}
										}

										if (!lista.empty()/*!ids.empty()*/) {
											//nextEntry = ids.front();
											nextEntry = lista.front().id;
											lista.pop_front();
											//ids.pop();
											hasNext = true;
										} else {
											hasNext = false;
										}
									}

									std::queue<id_type> ids;
									std::list<NodoListaX> lista;
									double yMayor;
									double nodosVisitados;
									Region r;
								};
class Query4: public SpatialIndex::IQueryStrategy {
	//obtengo el y menor
public:
	Query4(double y, Region r) {
		yMenor = y;
		nodosVisitados = 0;
		this->r = r;
	}
	virtual ~Query4() {

	}
	void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext) {

		nodosVisitados++;
		const INode* n = dynamic_cast<const INode*>(&entry);
		//NodePtr n = dynamic_cast<NodePtr>(&entry);

		if (n->isLeaf()) { //es hoja
			//recorro sus hijos
			for (uint32_t cChild = 0; cChild < n->getChildrenCount();
					++cChild) {
				//Region r2;
				IShape* ps;
				//((r2 = *(n->m_ptrMBR[cChild]);
				n->getChildShape(cChild, &ps);
				Region* pr = dynamic_cast<Region*>(ps);
				//								std::cout <<"aa: "<< pr->m_pLow[0]<<" "<< pr->m_pLow[0] << std::endl;
				if (pr->m_pLow[1] < yMenor) {//los low y high son iguales en las hojas
					yMenor = pr->m_pLow[1];
				}

			}
		} else { //nodo interno
				 //recorro sus hijos
			for (uint32_t cChild = 0; cChild < n->getChildrenCount();
					++cChild) {
				IShape* ps;
				n->getChildShape(cChild, &ps);
				Region* pr = dynamic_cast<Region*>(ps);
				//std::cout << "info y nodo: " << pr->m_pLow[1] << std::endl;
				if(r.intersectsRegion(*pr)){
				//if ((pr->m_pLow[0] == x || pr->m_pHigh[0] == x)) {
					NodoListaX nodo(pr->m_pLow[1], pr->m_pHigh[1],
							n->getChildIdentifier(cChild));
					if (lista.empty()) {
						lista.push_back(nodo);
					} else {
						NodoListaX nn = lista.front();
						if (pr->m_pLow[1] < nn.xMin) {
							if (pr->m_pHigh[1] < nn.xMin) {
								lista.erase(lista.begin(), lista.end());
								lista.push_back(nodo);
							} else {
								lista.push_front(nodo);
							}
						} else {
							if (pr->m_pLow[1] < nn.xMax) {
								lista.push_back(nodo);
							}
						}
					}

					//ids.push(n->getChildIdentifier(cChild));
				}
			}
		}

		if (!lista.empty()/*!ids.empty()*/) {
			//nextEntry = ids.front();
			nextEntry = lista.front().id;
			lista.pop_front();
			//ids.pop();
			hasNext = true;
		} else {
			hasNext = false;
		}
	}

	std::queue<id_type> ids;
	std::list<NodoListaX> lista;
	double yMenor;
	double nodosVisitados;
	Region r;
};

	}
}
