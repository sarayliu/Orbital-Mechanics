//
// Sara Liu, 28 October 2019
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
//Moon
#define MM 7.349e+22 // kg
#define RM 1.7374e+6 // m
#define V 1023.157  // m/s

#define PI 3.14159265
    
double r = 3.844e8 ; // distance from Earth
//
// parameters
//
#define DT 180     // s
// #define DT 25    // s
//
double  t[14160] ; //initializing outside of main to solve memory issue
double  x[14160] ;
double  y[14160] ;
double vx[14160] ;
double vy[14160] ;
double  d[14160] ;
double  v[14160] ;
//
int main()
{
	//
	// time intervals - duration is 90 minutes
	//
   int n = (int)( 0.5 + ( 24 * 29.5 * 60 * 60 ) / DT ) ;
//    int n = (int)( 0.5 + ( 24 * 3 * 60 * 60 ) / DT ) ;
	//
   printf( "%d\n", n ) ;
	//////////////////////////////////////////////////
	//
   //
	//////////////////////////////////////////////////
	//
   FILE*  fout  ;
	//
   int    j     ;
	//
   // double r , a ;
   //Apollo
   double a, aAE, aAM;
   double tA[n];
   tA[0]  = 96302.0          ; // 26 h, 45 m, 2 s
   double rA     = R + 202751774.4 ;
   double vmagA  = 1527.048         ;
   double xA[n], yA[n], vxA[n], vyA[n], dAE[n], dAM[n], vA[n];
   int timeIndex = 0;
   double dAM_at_return[n];
   double tAngle[n], xAngle[n], yAngle[n], tAAngle[n], xAAngle[n], yAAngle[n], vAAngle[n];
   double stopLoop;
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
   //Moon
   t[0]  =          0.0 ;
   x[0]  =            r ;
   y[0]  =          0.0 ;
   vx[0] =          0.0 ;
   vy[0] =            V ;
   d[0]  =            r ;
   v[0]  =            V ; 
	//
	//////////////////////////////////////////////////
	//
   for(int ang = 1; ang < 90; ang++)
   {
   //       printf("Angle: %f\n", ang);
      timeIndex = 0;
      double angle = ang*PI/180;
      xA[0] = rA * cos(angle);
      yA[0] = rA * sin(angle);
      vxA[0] = vmagA * cos(angle);
      vyA[0] = vmagA * sin(angle);
      dAE[0] = pow(pow(xA[0], 2) + pow(yA[0], 2), 0.5); 
      dAM[0] = pow(pow(xA[0] - x[0], 2) + pow(yA[0] - y[0], 2), 0.5);
      for( j = 1 ; j < n ; j ++ )
      {
         t[j] = t[j-1] + DT           ;
      //moon
         x[j] = x[j-1] + DT * vx[j-1] ;
         y[j] = y[j-1] + DT * vy[j-1] ;
         d[j] = pow(pow(x[j], 2) + pow(y[j], 2), 0.5);
      //calculate a
      //
         a = -G*M/pow(d[j], 2);
         double ax = a*x[j]/d[j];
         double ay = a*y[j]/d[j];
      // update vx
         vx[j] = vx[j - 1] + ax*DT;
      // update vy
         vy[j] = vy[j - 1] + ay*DT;
         v[j] = pow(pow(vx[j], 2) + pow(vy[j], 2), 0.5);
      //
      //Apollo
         if(tA[0] <= j * DT)
         {
            // printf("%i\n", j);
            timeIndex++;
            tA[timeIndex] = tA[timeIndex-1] + DT;
            xA[timeIndex] = xA[timeIndex-1] + DT * vxA[timeIndex-1];
            yA[timeIndex] = yA[timeIndex-1] + DT * vyA[timeIndex-1];
            dAE[timeIndex] = pow(pow(xA[timeIndex], 2) + pow(yA[timeIndex], 2), 0.5);
            dAM[timeIndex] = pow(pow(xA[timeIndex] - x[j], 2) + pow(yA[timeIndex] - y[j], 2), 0.5); 
            if(dAE[timeIndex - 1] > dAE[timeIndex])
            {
               // printf("%f, %f\n", dAE[timeIndex - 1], dAE[timeIndex]);
            //                printf("THETA: %f\n", angle*180/PI);
            //                printf("%i\n", timeIndex);
               dAM_at_return[ang] = dAM[timeIndex];
               if(ang == 42)
               {
                  for(int k = 0; k < j; k++)
                  {
                     tAngle[k] = t[k];
                     xAngle[k] = x[k];
                     yAngle[k] = y[k];
                     tAAngle[k] = tA[k];
                     xAAngle[k] = xA[k];
                     yAAngle[k] = yA[k];
                     vAAngle[k] = vA[k];
                     stopLoop = j;
                  }
               }
               break;
            }
            aAE = -G*M/pow(dAE[timeIndex], 2);
            double aAEx = aAE*xA[timeIndex]/dAE[timeIndex];
            double aAEy = aAE*yA[timeIndex]/dAE[timeIndex]; 
            aAM = -G*MM/pow(dAM[timeIndex], 2);
            double aAMx = aAM*xA[timeIndex]/dAM[timeIndex];
            double aAMy = aAM*yA[timeIndex]/dAM[timeIndex];
            double aAx = aAEx + aAMx;
            double aAy = aAEy + aAMy;
            vxA[timeIndex] = vxA[timeIndex-1] + aAx*DT;
            vyA[timeIndex] = vyA[timeIndex-1] + aAy*DT;
            vA[timeIndex] = pow(pow(vxA[timeIndex], 2) + pow(vyA[timeIndex], 2), 0.5);
         }
      }
   }
   double minDFromMoon = dAM_at_return[1];
   int theta = 1;
   for(int ang = 2; ang < 90; ang++)
   {
      if(dAM_at_return[ang] < minDFromMoon)
      {
         minDFromMoon = dAM_at_return[ang]; 
         theta = ang;
      }
   }
   printf("Minimum distance from moon: %f\n", minDFromMoon);
   printf("THETA for free return trajectory: %i\n", theta); 
	//
	//////////////////////////////////////////////////
	//
   fout = fopen( "orbitMoon.txt" , "w" ) ;
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
   fout = fopen( "freeReturn.txt", "w");
   for(j = 0; j < stopLoop; j++)
   {
      fprintf(fout, "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n", j, tAngle[j], xAngle[j], yAngle[j], tAAngle[j], xAAngle[j], yAAngle[j], vAAngle[j]);
   }
   fclose(fout);
   return 0 ;
}
//
// end of file
//