#include <stdio.h>
#include <math.h>

/*--- Calculate from t=0 to t=T ---*/
#define T   5.0

/*--- Initial data ---*/
#define X0   2.0

/*--- parameter(s) ---*/
#define A  1.0

/*--- division number ---*/
#define N    1000

/*---  f(t,x)  ---*/
double f(double t, double x) { return x - x * x; }

/*--- Exact solution ---*/
double ExactSol(double t) { return exp(A*t); }

/*--- main ---*/
/*
     h: mesh size
     x=X_n: approx. sol.
     t: time
     en=|e_n|: error
     maxen=max_n |e_n|
*/
int main(void)
{
  int n;
  double h=T/N;  
  double x=X0;  
  double t=0.0;  
  double maxen=0.0, en;

  printf("# Time t_n, Numerical sol. X_n, Exact sol. x(t_n), Error e_n\n"); 

  for(n=0; n<N; n++) 
  {
	t=n*h;                     // "t" : t_n 
    en=fabs(x-ExactSol(t));    // "x" : X_n 
    maxen=maxen > en ? maxen: en ;  // maxen = max(maxen, en)
                                  // ?: conditional operator

    /* display t_n, X_n, x(t_n) and |e_n| */
    printf("%6.4f      %16.14f   %16.14f  %16.10e\n",
           t, x, ExactSol(t), en); 

    /* 4th Order Runge-Kutta Method */
    double k1 = h * f(t, x);
    double k2 = h * f(t + h / 2, x + k1 / 2);
    double k3 = h * f(t + h / 2, x + k2 / 2);
    double k4 = h * f(t + h, x + k3);

    x = x + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;  // Update x using RK4 formula
  }

    /* display t_N, X_N, x(t_N) and |e_N| */
	t=N*h;
    en=fabs(x-ExactSol(t));
    maxen=maxen > en ? maxen: en ;  
    printf("%6.4f      %16.14f   %16.14f  %16.10e\n",
           t, x, ExactSol(t), en); 

  /* max of |e_n| */
  printf("###  max_n |e_n|=%16.10e\n",maxen);
}
