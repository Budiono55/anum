/*=======================================*/
/* Euler method for system of ODEs (IVP) */
/*    x' = f(t,x,y)                      */
/*    y' = g(t,x,y)                      */
/*    x(T0)=X0,  y(T0)=Y0                */
/*=======================================*/
#include <stdio.h>
#include <math.h>

/*--- The initial and final times ---*/
#define T0   0.0
#define T1   1.0

/*--- The initial data ---*/
#define X0   10.0
#define Y0   11.0

/*--- division number ---*/
#define N    100

/*--- Right-hand sides of the equations: f(t,x,y), g(t,x,y) ---*/
double f(double t, double x, double y) { return x-3*y; }
double g(double t, double x, double y) { return -3*x+y; }

/*--- Euler scheme ---*/
/* In this source, we set the function of the Euler scheme for each component.
   Of course, you can make 1 function by using arrays and pointers. */

double eulerx(double dt, double t, double x, double y)
{
 return(x+dt*f(t,x,y));
}

double eulery(double dt, double t, double x, double y)
{
 return(y+dt*g(t,x,y));
}

/*--- main ---*/
int main(void)
{
  int i;         
  double dt;     //  step size 
  double x,y;    //  (approx.) solutons
  double tempx;   //  temporal data of x
  double t;      //  time
  
  dt=(T1-T0)/N;

  /*  Set the initial condition */
  x=X0;
  y=Y0;
  
  printf("%6.4f %16.14f %16.14f \n", 0.0, x, y);

  for(i=1; i<=N; i++) 
  {
    t=T0+i*dt;

   /* Calculate from (X_n, Y_n) to (X_{n+1}, Y_{n+1}) */
    tempx=x;
    x=eulerx(dt,t,x,y); 
    y=eulery(dt,t,tempx,y); 

   /* display a time t_n, X_n and Y_n for each step */

    printf("%6.4f %16.14f %16.14f \n", t, x, y);
  }
}
