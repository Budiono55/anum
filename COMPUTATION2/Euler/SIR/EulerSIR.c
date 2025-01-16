/*========================================================*/
/* Euler method for SIR model                             */
/*    S'(t) = -β*S(t)*I(t)                                */
/*    I'(t) = β*S(t)*I(t) - γ*I(t)                        */
/*    R'(t) = γ*I(t)                                      */
/*    S(0) = S0, I(0) = I0, R(0) = R0                     */
/*========================================================*/
#include <stdio.h>

/*--- The initial and final times ---*/
#define T0   0.0
#define T1   10.0

/*--- The initial data ---*/
#define S0   1.0
#define I0   1.0
#define R0   0.0

/*--- Parameters ---*/
#define BETA  0.3  // Infection rate
#define GAMMA 0.1  // Recovery rate

/*--- Division number ---*/
#define N    100

/*--- Right-hand sides of the equations: f(t,S,I,R), g(t,S,I,R), h(t,S,I,R) ---*/
double f(double S, double I) { return -BETA * S * I; }
double g(double S, double I) { return BETA * S * I - GAMMA * I; }
double h(double I) { return GAMMA * I; }

/*--- Euler scheme ---*/
/* In this source, we set the function of the Euler scheme for each component.
   Of course, you can make 1 function by using arrays and pointers. */
double eulerS(double dt, double S, double I) {
  return S + dt * f(S, I);
}

double eulerI(double dt, double S, double I) {
  return I + dt * g(S, I);
}

double eulerR(double dt, double I) {
  return R0 + dt * h(I);
}

/*--- main ---*/
int main(void) {
  int i;         
  double dt;     // Step size
  double S, I, R; // Approx. solutions
  double t;      // Time

  dt = (T1 - T0) / N;

  /* Set the initial condition */
  S = S0;
  I = I0;
  R = R0;

  printf("%6.4f %16.14f %16.14f %16.14f\n", 0.0, S, I, R);

  for (i = 1; i <= N; i++) {
    t = T0 + i * dt;

    /* Calculate from (S_n, I_n, R_n) to (S_{n+1}, I_{n+1}, R_{n+1}) */
    double tmpS = S;  // Temporarily store S
    double tmpI = I;  // Temporarily store I
    S = eulerS(dt, tmpS, tmpI);
    I = eulerI(dt, tmpS, tmpI);
    R = eulerR(dt, tmpI);

    /* Display time t_n, S_n, I_n, R_n for each step */
    printf("%6.4f %16.14f %16.14f %16.14f\n", t, S, I, R);
  }

  return 0;
}
