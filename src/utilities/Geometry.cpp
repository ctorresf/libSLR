/*
 * Geometry.cpp
 *
 *  Created on: 15-09-2015
 *      Author: claudio
 */

#include "Geometry.h"


Geometry::Geometry() {
	// TODO Auto-generated constructor stub

}

Geometry::~Geometry() {
	// TODO Auto-generated destructor stub
}

bool Geometry::seIntersecan2(std::vector<std::pair<double, double> > poligono1,
		std::vector<std::pair<double, double> > poligono2){
	//std::cout << "p "<< poligono1.size()<< "  __  "<< poligono2.size()<< std::endl;
	for (unsigned int i = 0; i < poligono1.size(); i++) {
		double x1 = poligono1[i].first;
		double y1 = poligono1[i].second;
		double x2 = poligono1[(i + 1) % poligono1.size()].first;
		double y2 = poligono1[(i + 1) % poligono1.size()].second;
		double m1 = (y2 - y1) / (x2 - x1);
		double n1 = y1 - m1 * x1;

		for (unsigned int j = 0; j < poligono2.size(); j++) {
			x1 = poligono2[j].first;
			y1 = poligono2[j].second;
			x2 = poligono2[(j + 1) % poligono2.size()].first;
			y2 = poligono2[(j + 1) % poligono2.size()].second;
			double m2 = (y2 - y1) / (x2 - x1);
			double n2 = y1 - m2 * x1;

			double x = (n2 - n1) / (m1 - m2);

//veo si las lienas se intersectan
//dejo solo 2 decimales, por temas de precision
			if (((int) ((m1 * x + n1) * 100)) / 100.0 	== ((int) ((m2 * x + n2) * 100)) / 100.0
					&& ((x >= poligono1[i].first && x <= poligono1[(i + 1) % poligono1.size()].first)
							|| (x <= poligono1[i].first	&& x >= poligono1[(i + 1) % poligono1.size()].first))
					&& ((x >= poligono2[j].first && x <= poligono2[(j + 1) % poligono2.size()].first)
							|| (x <= poligono2[j].first && x >= poligono2[(j + 1) % poligono2.size()].first))) {
				//std::cout << "#### se intersecan " << std::endl;
				return true;

			}

		}

	}
	return false;

}

bool Geometry::seIntersecan(std::vector<std::pair<double, double> > P,
		std::vector<std::pair<double, double> > Q){
	/* P has n vertices, Q has m vertices. */
	int n= P.size();
	int m= Q.size();

	   int     a, b;           /* indices on P and Q (resp.) */
	   int     a1, b1;         /* a-1, b-1 (resp.) */
	   tPointi A, B;           /* directed edges on P and Q (resp.) */
	   int     cross;          /* sign of z-component of A x B */
	   int     bHA, aHB;       /* b in H(A); a in H(b). */
	   tPointi Origin = {0,0}; /* (0,0) */
	   tPointd p;              /* double point of intersection */
	   tPointd q;              /* second point of intersection */
	   tInFlag inflag;         /* {Pin, Qin, Unknown}: which inside */
	   int     aa, ba;         /* # advances on a & b indices (after 1st inter.) */
	   bool    FirstPoint;     /* Is this the first point? (used to initialize).*/
	   tPointd p0;             /* The first point. */
	   int     code;           /* SegSegInt return code. */

	   /* Initialize variables. */
	   a = 0; b = 0; aa = 0; ba = 0;
	   inflag = Unknown; FirstPoint = true;

	   do {
	      /*printf("%%Before Advances:a=%d, b=%d; aa=%d, ba=%d; inflag=%d\n", a, b, aa, ba, inflag);*/
	      /* Computations of key variables. */
	      a1 = (a + n - 1) % n;
	      b1 = (b + m - 1) % m;

	      tPointi aux1;
	      aux1[0] = P[a].first;
	      aux1[1] = P[a].second;
			tPointi aux2;
			aux2[0] = P[a1].first;
			aux2[1] = P[a1].second;
			tPointi qb;
			qb[0] = Q[b].first;
			qb[1] = Q[b].second;
			tPointi qb1;
			qb1[0] = Q[b1].first;
			qb1[1] = Q[b1].second;
	      SubVec( aux1, aux2, A );
	      SubVec( qb, qb1, B );

	      cross = AreaSign( Origin, A, B );
	      aHB   = AreaSign( qb, qb, aux1);
	      bHA   = AreaSign( aux2, aux1, qb );
	     // printf("%%cross=%d, aHB=%d, bHA=%d\n", cross, aHB, bHA );

	      /* If A & B intersect, update inflag. */
	      code = SegSegInt( aux2, aux1, qb1, qb, p, q );
	     // printf("%%SegSegInt: code = %c\n", code );
	      if ( code == '1' || code == 'v' ) {
	         if ( inflag == Unknown && FirstPoint ) {
	            aa = ba = 0;
	            FirstPoint = false;
	            p0[X] = p[X]; p0[Y] = p[Y];
	            //printf("%8.2lf %8.2lf moveto\n", p0[X], p0[Y] );
	         }
	         //AQUI SE ENCUENTRAN LAS INTERSECCIONES
	         return true;
	        // std::cout << "se intersectan en: "<< p[0] << ","<< p[1] << std::endl;
	        // dgp.drawPoint( p[0], p[1]);
	//         dgp.drawPoint( (double)P[a][0], (double)P[a][1]);
	//         dgp.drawPoint( (double)Q[b][0], (double)Q[b][1]);
	//         dgp.drawPoint( (double)P[a1][0], (double)P[a1][1]);
	//         dgp.drawPoint( (double)Q[b1][0], (double)Q[b1][1]);

	         //inflag = InOut( p, inflag, aHB, bHA );
	         //el compilador manda error
	         //pego el codigo de la funcion
	         if      ( aHB > 0)
	        	 inflag =  Pin;
	         else if ( bHA > 0)
	        	 inflag =  Qin;

	        // printf("%%InOut sets inflag=%d\n", inflag);
	      }

	      /*-----Advance rules-----*/

	    /*   Special case: A & B overlap and oppositely oriented.
	      if ( ( code == 'e' ) && (Dot( A, B ) < 0) )
	            PrintSharedSeg( p, q ), exit(EXIT_SUCCESS);

	       Special case: A & B parallel and separated.
	      if ( (cross == 0) && ( aHB < 0) && ( bHA < 0 ) )
	            printf("%%P and Q are disjoint.\n"), exit(EXIT_SUCCESS);*/

	      /* Special case: A & B collinear. */
	      else if ( (cross == 0) && ( aHB == 0) && ( bHA == 0 ) ) {
	            /* Advance but do not output point. */
	            if ( inflag == Pin )
	               b = Advance( b, &ba, m, inflag == Qin, qb );
	            else
	               a = Advance( a, &aa, n, inflag == Pin, aux1 );
	         }

	      /* Generic cases. */
	      else if ( cross >= 0 ) {
	         if ( bHA > 0)
	            a = Advance( a, &aa, n, inflag == Pin,aux1 );
	         else
	            b = Advance( b, &ba, m, inflag == Qin, qb );
	      }
	      else /* if ( cross < 0 ) */{
	         if ( aHB > 0)
	            b = Advance( b, &ba, m, inflag == Qin, qb );
	         else
	            a = Advance( a, &aa, n, inflag == Pin, aux1 );
	      }
	      //printf("%%After advances:a=%d, b=%d; aa=%d, ba=%d; inflag=%d\n", a, b, aa, ba, inflag);

	   /* Quit when both adv. indices have cycled, or one has cycled twice. */
	   } while ( ((aa < n) || (ba < m)) && (aa < 2*n) && (ba < 2*m) );

	//   if ( !FirstPoint ) /* If at least one point output, close up. */
	//            printf("%8.2lf %8.2lf lineto\n", p0[X], p0[Y] );
	//
	//   /* Deal with special cases: not implemented. */
	//   if ( inflag == Unknown)
	//      printf("%%The boundaries of P and Q do not cross.\n");
	   return false;
}

double *Geometry::ecuacionRecta(double x1, double y1, double x2, double y2){

	double* ec;
	ec = new double[2];
	ec[0] = (y2 - y1) / (x2 - x1);
	ec[1] = y1 - ec[0] * x1;

	return ec;

}

unsigned int Geometry::tipoInterseccion(double* aLow, double* aHigh, double* bLow, double* bHigh){
	/*
	 * cada array esta formado por dos elemento (x,y)
	 * low es el punto de la esquina inferior izquierda del rectangulo
	 * high es el punto de la esquina superiro derecha del rectangulo
	 */


}


/*---------------------------------------------------------------------
Prints out the double point of intersection, and toggles in/out flag.
---------------------------------------------------------------------*/
tInFlag Geometry::InOut( tPointd p, tInFlag inflag, int aHB, int bHA )
{
  // printf("%8.2lf %8.2lf lineto\n", p[X], p[Y] );

   /* Update inflag. */
   if      ( aHB > 0)
      return Pin;
   else if ( bHA > 0)
      return Qin;
   else    /* Keep status quo. */
      return inflag;
}
/*---------------------------------------------------------------------
   Advances and prints out an inside vertex if appropriate.
---------------------------------------------------------------------*/
int     Geometry::Advance( int a, int *aa, int n, bool inside, tPointi v )
{
//   if ( inside )
//      printf("%5d    %5d    lineto\n", v[X], v[Y] );
   (*aa)++;
   return  (a+1) % n;
}



/*
   Returns true iff c is strictly to the left of the directed
   line through a to b.
*/
bool    Geometry::Left( tPointi a, tPointi b, tPointi c )
{
        return  AreaSign( a, b, c ) > 0;
}

bool    Geometry::LeftOn( tPointi a, tPointi b, tPointi c )
{
        return  AreaSign( a, b, c ) >= 0;
}

bool    Geometry::Collinear( tPointi a, tPointi b, tPointi c )
{
        return  AreaSign( a, b, c ) == 0;
}
/*---------------------------------------------------------------------
a - b ==> c.
---------------------------------------------------------------------*/
void    Geometry::SubVec( tPointi a, tPointi b, tPointi c )
{
   int i;

   for( i = 0; i < DIM; i++ )
      c[i] = a[i] - b[i];
}


int	Geometry::AreaSign( tPointi a, tPointi b, tPointi c )
{
    double area2;

    area2 = ( b[0] - a[0] ) * (double)( c[1] - a[1] ) -
            ( c[0] - a[0] ) * (double)( b[1] - a[1] );

    /* The area should be an integer. */
    if      ( area2 >  0.5 ) return  1;
    else if ( area2 < -0.5 ) return -1;
    else                     return  0;
}

/*---------------------------------------------------------------------
SegSegInt: Finds the point of intersection p between two closed
segments ab and cd.  Returns p and a char with the following meaning:
   'e': The segments collinearly overlap, sharing a point.
   'v': An endpoint (vertex) of one segment is on the other segment,
        but 'e' doesn't hold.
   '1': The segments intersect properly (i.e., they share a point and
        neither 'v' nor 'e' holds).
   '0': The segments do not intersect (i.e., they share no points).
Note that two collinear segments that share just one point, an endpoint
of each, returns 'e' rather than 'v' as one might expect.
---------------------------------------------------------------------*/
char	Geometry::SegSegInt( tPointi a, tPointi b, tPointi c, tPointi d, tPointd p, tPointd q )
{
   double  s, t;       /* The two parameters of the parametric eqns. */
   double num, denom;  /* Numerator and denoninator of equations. */
   char code = '?';    /* Return char characterizing intersection. */

   /*printf("%%SegSegInt: a,b,c,d: (%d,%d), (%d,%d), (%d,%d), (%d,%d)\n",
	a[X],a[Y], b[X],b[Y], c[X],c[Y], d[X],d[Y]);*/

   denom = a[X] * (double)( d[Y] - c[Y] ) +
           b[X] * (double)( c[Y] - d[Y] ) +
           d[X] * (double)( b[Y] - a[Y] ) +
           c[X] * (double)( a[Y] - b[Y] );

   /* If denom is zero, then segments are parallel: handle separately. */
   if (denom == 0.0)
      return  ParallelInt(a, b, c, d, p, q);

   num =    a[X] * (double)( d[Y] - c[Y] ) +
            c[X] * (double)( a[Y] - d[Y] ) +
            d[X] * (double)( c[Y] - a[Y] );
   if ( (num == 0.0) || (num == denom) ) code = 'v';
   s = num / denom;
   /*printf("num=%lf, denom=%lf, s=%lf\n", num, denom, s);*/

   num = -( a[X] * (double)( c[Y] - b[Y] ) +
            b[X] * (double)( a[Y] - c[Y] ) +
            c[X] * (double)( b[Y] - a[Y] ) );
   if ( (num == 0.0) || (num == denom) ) code = 'v';
   t = num / denom;
   /*printf("num=%lf, denom=%lf, t=%lf\n", num, denom, t);*/

   if      ( (0.0 < s) && (s < 1.0) &&
             (0.0 < t) && (t < 1.0) )
     code = '1';
   else if ( (0.0 > s) || (s > 1.0) ||
             (0.0 > t) || (t > 1.0) )
     code = '0';

   p[X] = a[X] + s * ( b[X] - a[X] );
   p[Y] = a[Y] + s * ( b[Y] - a[Y] );

   return code;
}
char   Geometry::ParallelInt( tPointi a, tPointi b, tPointi c, tPointi d, tPointd p, tPointd q )
{
/*
   printf("ParallelInt: a,b,c,d: (%d,%d), (%d,%d), (%d,%d), (%d,%d)\n",
	a[X],a[Y], b[X],b[Y], c[X],c[Y], d[X],d[Y]);
*/

   if ( !Collinear( a, b, c) )
      return '0';

   if ( Between( a, b, c ) && Between( a, b, d ) ) {
      Assigndi( p, c );
      Assigndi( q, d );
      return 'e';
   }
   if ( Between( c, d, a ) && Between( c, d, b ) ) {
      Assigndi( p, a );
      Assigndi( q, b );
      return 'e';
   }
   if ( Between( a, b, c ) && Between( c, d, b ) ) {
      Assigndi( p, c );
      Assigndi( q, b );
      return 'e';
   }
   if ( Between( a, b, c ) && Between( c, d, a ) ) {
      Assigndi( p, c );
      Assigndi( q, a );
      return 'e';
   }
   if ( Between( a, b, d ) && Between( c, d, b ) ) {
      Assigndi( p, d );
      Assigndi( q, b );
      return 'e';
   }
   if ( Between( a, b, d ) && Between( c, d, a ) ) {
      Assigndi( p, d );
      Assigndi( q, a );
      return 'e';
   }
   return '0';
}
void	Geometry::Assigndi( tPointd p, tPointi a )
{
   int i;
   for ( i = 0; i < DIM; i++ )
      p[i] = a[i];
}
/*---------------------------------------------------------------------
Returns TRUE iff point c lies on the closed segement ab.
Assumes it is already known that abc are collinear.
---------------------------------------------------------------------*/
bool    Geometry::Between( tPointi a, tPointi b, tPointi c )
{
   tPointi      ba, ca;

   /* If ab not vertical, check betweenness on x; else on y. */
   if ( a[X] != b[X] )
      return ((a[X] <= c[X]) && (c[X] <= b[X])) ||
             ((a[X] >= c[X]) && (c[X] >= b[X]));
   else
      return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) ||
             ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}


/*---------------------------------------------------------------------
Returns the dot product of the two input vectors.
---------------------------------------------------------------------*/
double  Geometry::Dot( tPointi a, tPointi b )
{
    int i;
    double sum = 0.0;

    for( i = 0; i < DIM; i++ )
       sum += a[i] * b[i];

    return  sum;
}
