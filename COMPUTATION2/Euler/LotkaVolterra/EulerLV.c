/*==============================================================*/
/* Euler method for Lotka-Volterra (prey-predator) model        */
/*    x'(t) = x(t) - x(t)*y(t)                                  */
/*    y'(t) = -y(t) + x(t)*y(t)                                 */
/*    x(0) = 1, y(0) = 2                                        */
/*==============================================================*/
#include <stdio.h>
#include <math.h>


/*--- The initial and final times ---*/
#define T0   0.0
#define T1   10.0

/*--- The initial data ---*/
#define X0   1.0
#define Y0   2.0

/*--- Division number ---*/
#define N    1000

/*--- Right-hand sides of the equations: f(t,x,y), g(t,x,y) ---*/
double f(double x, double y) { return x - x * y; }
double g(double x, double y) { return -y + x * y; }

/*--- Euler scheme ---*/
double eulerX(double dt, double x, double y) {
  return x + dt * f(x, y);
}

double eulerY(double dt, double x, double y) {
  return y + dt * g(x, y);
}

/*--- main ---*/
int main(void) {
  int i;         
  double dt;     // Step size
  double x, y;   // Approx. solutions
  double tmpX;   // Temporal variable for x
  double t;      // Time

  dt = (T1 - T0) / N;

  /* Set the initial condition */
  x = X0;
  y = Y0;

  printf("%6.4f %16.14f %16.14f\n", 0.0, x, y);

  for (i = 1; i <= N; i++) {
    t = T0 + i * dt;

    /* Calculate from (X_n, Y_n) to (X_{n+1}, Y_{n+1}) */
    tmpX = x;
    x = eulerX(dt, tmpX, y);
    y = eulerY(dt, tmpX, y);

    /* Display a time t_n, X_n, and Y_n for each step */
    printf("%6.4f %16.14f %16.14f\n", t, x, y);
  }

  return 0;
}
