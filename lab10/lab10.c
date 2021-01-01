//
// Sara Liu, 18 December 2019
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
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
#include "mpi.h"
    
double r = 3.844e8 ; // distance from Earth
//
// parameters
//
#define DT 180     // s
// #define DT 5    // s
//
double  t[3541] ; //initializing outside of main to solve memory issue
double  x[3541] ;
double  y[3541] ;
double vx[3541] ;
double vy[3541] ;
double  d[3541] ;
double  v[3541] ;
//
int main( int argc , char* argv[] )
{
//
   // MPI variables
   //
   int        size    ; // same
   int        rank    ; // different
   //
   MPI_Status status  ;
   int        tag = 0 ; // same!
   //
   // other variables
   //
   int        iter ;
   double     result[3] ;
   long double t1     ;
   long double t2     ;
   //
   // boilerplate
   //
   MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ;
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ;
   //
   srand( rank ) ; // different!
   
   if( rank == 0 )
   {
      t1 = time(NULL);
      printf( "waiting...\n" ) ;
      //
   //      for(double deltaP = 0; deltaP < 1.01; deltaP += 0.01)
      {
         double speeds[7], angles[7], exitSpds[7];
         for( int k = 1 ; k < size; k++ )
         {
            MPI_Recv( result , 3 , MPI_DOUBLE , k , tag , MPI_COMM_WORLD , &status ) ;
         //
         // printf("*** %d\n",k); 
         // printf( "%d %20.16f\n" , size , result ) ;
            speeds[k-1] = result[0];
            angles[k-1] = result[1];
            exitSpds[k-1] = result[2];
         }
      //
         double bestInitialSpeed = speeds[0];
         double fastestAngle = angles[0];
         double maxExitSpeed = exitSpds[0];
         int bestWorker = 1;
         for(int i = 1; i < 7; i++)
         {
         //             printf("%f %f\n", maxExitSpeed, exitSpds[i]);
            if(exitSpds[i] > maxExitSpeed)
            {
               bestInitialSpeed = speeds[i];
               fastestAngle = angles[i];
               maxExitSpeed = exitSpds[i];
               bestWorker = i + 1; 
            }
         }
         printf("Initial Speed: %f m/s\n", bestInitialSpeed);
         printf("Initial Angle: %f degrees\n", fastestAngle);
         printf("Max exit speed: %f m/s\n", maxExitSpeed);
         printf("Worker with max exit speed: %i\n", bestWorker);
      }
      t2 = time(NULL);
   //       printf("t1 = %Lf s\n", t1);
   //       printf("t2 = %Lf s\n", t2);
      printf("Time: %Lf s\n", t2 - t1);
   }
   // workers have rank > 0
   else
   {
   printf("Rank: %i\n", rank);
      //
   // time intervals
   //
      int n = (int)( 0.5 + ( 24 * 7.375 * 60 * 60 ) / DT ) ;
   //    int n = (int)( 0.5 + ( 24 * 3 * 60 * 60 ) / DT ) ;
   //
   //////////////////////////////////////////////////
   //
   //
   //////////////////////////////////////////////////
   //
   //       FILE*  fout  ;
   //
      int    j     ;
   //
   // double r , a ;
   //Probe
      double a, aAE, aAM;
      double tA[n];
      tA[0]  = 0 ;
      double rA     = 2 * RM;
      double xA[n], yA[n], vxA[n], vyA[n], dAE[n], dAM[n], vA[n];
      double bestISpeed = 0;
      int bestAngle = 181 + 13 * rank;
      double bestSpeed = 0;
      double tAngle[n], xAngle[n], yAngle[n], xAAngle[n], yAAngle[n], vAAngle[n], dAMAngle[n];
      double result[3];
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
      for(double vmagA = 1000; vmagA < 2000; vmagA += 10)
      {
         for(int ang = 181 + 13 * rank; ang < 194 + 13 * rank; ang++)
         {
         // printf("Angle: %f\n", ang);
            double angle = ang*PI/180;
            xA[0] = r + rA * cos(angle);
            yA[0] = rA * sin(angle);
            vxA[0] = vmagA * cos(angle);
            vyA[0] = vmagA * sin(angle);
            dAE[0] = pow(pow(xA[0], 2) + pow(yA[0], 2), 0.5); 
            dAM[0] = pow(pow(xA[0] - x[0], 2) + pow(yA[0] - y[0], 2), 0.5);
            int returning = 0;
            for( j = 1 ; j < n ; j ++ )
            {
               t[j] = t[j-1] + DT           ;
            //moon
               x[j] = x[j-1] + DT * vx[j-1] ;
               y[j] = y[j-1] + DT * vy[j-1] ;
               d[j] = pow(pow(x[j], 2) + pow(y[j], 2), 0.5);
            //calculate a
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
               tA[j] = tA[j-1] + DT;
               xA[j] = xA[j-1] + DT * vxA[j-1];
               yA[j] = yA[j-1] + DT * vyA[j-1];
               dAE[j] = pow(pow(xA[j], 2) + pow(yA[j], 2), 0.5);
               dAM[j] = pow(pow(xA[j] - x[j], 2) + pow(yA[j] - y[j], 2), 0.5); 
               aAE = -G*M/pow(dAE[j], 2);
               double aAEx = aAE*xA[j]/dAE[j];
               double aAEy = aAE*yA[j]/dAE[j]; 
               aAM = -G*MM/pow(dAM[j], 2);
               double aAMx = aAM*(xA[j] - x[j])/dAM[j];
               double aAMy = aAM*(yA[j] - y[j])/dAM[j];
               double aAx = aAEx + aAMx;
               double aAy = aAEy + aAMy;
               vxA[j] = vxA[j-1] + aAx*DT;
               vyA[j] = vyA[j-1] + aAy*DT;
               vA[j] = pow(pow(vxA[j], 2) + pow(vyA[j], 2), 0.5);
            }
         
            double wentAroundEarth = 0;
            for(int vIter = 0; vIter < n; vIter++)
            {
               if(vA[vIter] > pow(2 * G * M/dAE[vIter], 0.5) && vA[vIter] > bestSpeed && dAM[vIter] < 4000000 && yA[vIter] > 0) // && vxA[vIter] > 0)
               {
                  for(int k = 0; k < n; k++)
                  {
                     tAngle[k] = t[k];
                     xAngle[k] = x[k];
                     yAngle[k] = y[k];
                     xAAngle[k] = xA[k];
                     yAAngle[k] = yA[k];
                     if(wentAroundEarth == 0 && xAAngle[k] < 0 && yAAngle[k] < 0 && xAAngle[k] < - R * cos(yAAngle[k]/xAAngle[k]) && yAAngle[k] < - R * sin(yAAngle[k]/xAAngle[k]))
                     {
                        wentAroundEarth = 1;
                     }
                     vAAngle[k] = vA[k];
                     dAMAngle[k] = dAM[k];
                  }
                  if(wentAroundEarth == 0)
                  {
                     break;
                  }
                  bestISpeed = vmagA;
                  bestAngle = ang;
                  bestSpeed = vA[vIter];
                  // printf("Distance from probe to Moon: %f\n", dAM[vIter]);
               //                   printf("Coordinates of probe at exit: (%f, %f)\n", xA[vIter], yA[vIter]);
               //                   printf("Initial speed of probe: %f\n", vmagA);
               //                   printf("Initial angle of probe: %i\n", bestAngle);
               //                   printf("Exit speed of probe: %f\n", bestSpeed);
                  break; //exit speed found, do not take speed after it has gone beyond the system
               }
            }
         }
      }
      if(bestSpeed == 0)
      {
         printf("Worker %i's probes did not exit the Earth-Moon system\n", rank);
      }
      else
      {
         printf("Worker %i's probe had a max exit speed of %f\n", rank, bestSpeed);
      }
      result[0] = bestISpeed;
      result[1] = bestAngle;
      result[2] = bestSpeed;
            
      FILE*  fout  ;
      fout = fopen( "orbitMoonLab10.txt" , "w" ) ;
      //
      for( j = 0 ; j < n ; j ++ )   
      {
         fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f\n" , j , t[j] , x[j] , y[j], d[j], v[j] ) ;
      }
      //
      fclose( fout ) ;
      //
      char fname[50];
      sprintf(fname, "hyperbolicProbeMPI%i.txt", rank);
      fout = fopen(fname, "w");
      // char str[] rankCh = (char)rank;
   //       fout = fopen( strcat(strcat("hyperbolicProbeMPI", rankCh), ".txt"), "w");
      for(j = 0; j < n; j++)
      {
         fprintf(fout, "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n", j, tAngle[j], xAngle[j], yAngle[j], xAAngle[j], yAAngle[j], vAAngle[j], dAMAngle[j]);
         // fprintf(fout, "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n", j, tA[j], x[j], y[j], xA[j], yA[j], vA[j], dAM[j]);
      }
      fclose(fout);
         // return 0 ;
   
      // printf("*** %d %d\n",counter,rank);
      MPI_Send( result , 3 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
   //
   }
   // boilerplate
   //
   MPI_Finalize() ;
   //
   return 0;
} 
//////////////////////////////////////////////////
	//
   // end of file
//