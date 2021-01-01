//
// Sara Liu, 18 October 2019
//
#include <stdio.h>
#include <math.h>
//
// https://physics.nist.gov/cgi-bin/cuu/Value?bg
//
#define G 6.674e-11 // (m^3)(kg^-1)(s^-2)
//
// https://ssd.jpl.nasa.gov/?planet_phys_par
//
#define M 5.972e+24 // kg
#define R 6.371e+6  // m
//
// parameters
//
#define DT 0.25     // s
//
int main()
{
	//
	// time intervals - duration is 90 minutes
	//
	int n = (int)( 0.5 + ( 1.5 * 60 * 60 ) / DT ) ;
	//
	//////////////////////////////////////////////////
	//
	double  t[n] ;
	double  x[n] ;
	double  y[n] ;
	double vx[n] ;
	double vy[n] ;
   double  d[n] ;
   double  v[n] ;
	//
	//////////////////////////////////////////////////
	//
	FILE*  fout  ;
	//
	int    j     ;
	//
	double r , a ;
	//
	//////////////////////////////////////////////////
	//
	// International Space Station
	//
	// https://www.nasa.gov/sites/default/files/atoms/files/np-2015-05-022-jsc-iss-guide-2015-update-111015-508c.pdf
	//
	// Page 54 - altitude : 370 km to 460 km
	// Page 54 - speed    : 28,000 km per hour
	//
	t[0]  =          0.0 ;
	x[0]  =          0.0 ;
	y[0]  = R + 400000.0 ;
	vx[0] =       7670.1 ;
	vy[0] =          0.0 ;
   d[0]  = R + 400000.0 ;
   v[0]  =       7670.1 ; 
	//
	//////////////////////////////////////////////////
	//
	for( j = 1 ; j < n ; j ++ )
	{
		t[j] = t[j-1] + DT           ;
		//
		x[j] = x[j-1] + DT * vx[j-1] ;
		y[j] = y[j-1] + DT * vy[j-1] ;
      d[j] = pow(pow(x[j], 2) + pow(y[j], 2), 0.5);
		//
		// calculate a
		//
      a = -G*M/pow(R + 400000.0, 2);
      double ax = a*x[j]/(R + 400000.0);
      double ay = a*y[j]/(R + 400000.0);
		// update vx
      vx[j] = vx[j - 1] + ax*DT;
		// update vy
      vy[j] = vy[j - 1] + ay*DT;
      v[j] = pow(pow(vx[j], 2) + pow(vy[j], 2), 0.5);
		//
	}
	//
	//////////////////////////////////////////////////
	//
	fout = fopen( "orbit.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f\n" , j , t[j] , x[j] , y[j], d[j], v[j] ) ;
		//
		// what else to print ?
		//
	}
	//
	fclose( fout ) ;
	//
	return 0 ;
}
//
// end of file
//