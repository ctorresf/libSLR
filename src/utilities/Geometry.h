/*
 * Geometry.h
 *
 *  Created on: 15-09-2015
 *      Author: claudio
 *
 *      This code is based in "Computational Geometry in C" (Second Edition),
Chapter 7.  It is not written to be comprehensible without the
explanation in that book. Written by Joseph O'Rourke.
 */

#ifndef UTILITIES_GEOMETRY_H_
#define UTILITIES_GEOMETRY_H_

#include <vector>
#include <iostream>
#include        <math.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define X       0
#define Y       1
//typedef enum { FALSE, TRUE } bool;
typedef enum { Pin, Qin, Unknown } tInFlag;

#define DIM     2               /* Dimension of points */
typedef int     tPointi[DIM];   /* type integer point */
typedef double  tPointd[DIM];   /* type double point */
#define PMAX    1000            /* Max # of pts in polygon */

typedef tPointi tPolygoni[PMAX];/* type integer polygon */

class Geometry {
public:
	Geometry();
	virtual ~Geometry();
	//O(n*m)
	static bool seIntersecan2(std::vector <std::pair<double, double> > poligono1,std::vector <std::pair<double, double> > poligono2);
	//O(m+n)
	static bool seIntersecan(std::vector <std::pair<double, double> > P,std::vector <std::pair<double, double> > Q);
	static double *ecuacionRecta(double x1, double y1, double x2, double y2);
	static unsigned int tipoInterseccion(double* aLow, double* aHigh, double* bLow, double* bHigh);


	//CONSTANTES PARA INTERSECCIÓN
	static const unsigned int DISJOINT=1;
	static const unsigned int CORNER=1;
	static const unsigned int SIDE=1;
	static const unsigned int CONTAINMENT=1;
	static const unsigned int PIERCING=1;

private:
	/*---------------------------------------------------------------------
	Function prototypes.
	---------------------------------------------------------------------*/
	static void    ClosePostscript( void );
	static void	PrintSharedSeg( tPointd p, tPointd q );
	static double  Dot( tPointi a, tPointi b );
	static int	AreaSign( tPointi a, tPointi b, tPointi c );
	static char    SegSegInt( tPointi a, tPointi b, tPointi c, tPointi d, tPointd p, tPointd q );
	static char    ParallelInt( tPointi a, tPointi b, tPointi c, tPointi d, tPointd p, tPointd q );
	static bool    Between( tPointi a, tPointi b, tPointi c );
	static void    Assigndi( tPointd p, tPointi a );
	static void    SubVec( tPointi a, tPointi b, tPointi c );
	static bool    LeftOn( tPointi a, tPointi b, tPointi c );
	static bool    Left( tPointi a, tPointi b, tPointi c );
	static tInFlag InOut( tPointd p, tInFlag inflag, int aHB, int bHA );
	static int     Advance( int a, int *aa, int n, bool inside, tPointi v );
	static void	OutputPolygons( void );
	static bool Collinear( tPointi a, tPointi b, tPointi c );
	/*-------------------------------------------------------------------*/
};


#endif /* UTILITIES_GEOMETRY_H_ */
