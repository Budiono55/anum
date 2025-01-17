/*=======================================*/
/* Euler method for SIR model (IVP)      */
/*    S' = -beta*S*I                     */
/*    I' = beta*S*I - gamma*I            */
/*    S(T0)=S0, I(T0)=I0                 */
/*=======================================*/
#include <stdio.h>
#include <math.h>

/*--- The initial and final times ---*/
#define T0   0.0
#define T1   100.0  // Simulation up to 100 units of time 

/*--- The initial data ---*/
#define S0   1.0   // Initial susceptible fraction 
#define I0   0.1   // Initial infected fraction 
#define R0   0    // Initial recovered fraction 

/*--- Parameters of the model ---*/
#define BETA  0.1   // Transmission rate 
#define GAMMA 0.2   // Recovery rate 

/*--- Division number ---*/
#define N    1000   /* Number of steps */

/*--- Right-hand sides of the equations: f(t,S,I), g(t,S,I) ---*/
double f(double t, double S, double I) { return -BETA * S * I; }
double g(double t, double S, double I) { return BETA * S * I - GAMMA * I; }

/*--- Euler scheme ---*/
/* In this source, we set the function of the Euler scheme for each component.
   Of course, you can make 1 function by using arrays and pointers. */

double eulerS(double dt, double t, double S, double I)
{
    return (S + dt * f(t, S, I));
}

double eulerI(double dt, double t, double S, double I)
{
    return (I + dt * g(t, S, I));
}

double eulerR(double dt, double t, double I, double R)
{
    return (R + dt * GAMMA * I);
}

/*--- main ---*/
int main(void)
{
    int i;
    double dt;       // step size
    double S, I, R;  // (approx.) solutions
    double tmpS;     // temporal data of S
    double t;        // time

    dt = (T1 - T0) / N;

    /* Set the initial condition */
    S = S0;
    I = I0;
    R = R0;

    printf("Time       S(t)           I(t)           R(t)\n");
    printf("%6.4f %16.14f %16.14f %16.14f \n", T0, S, I, R);

    for (i = 1; i <= N; i++)
    {
        t = T0 + i * dt;

        /* Calculate from (S_n, I_n, R_n) to (S_{n+1}, I_{n+1}, R_{n+1}) */
        tmpS = S;
        S = eulerS(dt, t, S, I);
        I = eulerI(dt, t, tmpS, I);
        R = eulerR(dt, t, I, R);

        /* Display the time t_n, S_n, I_n, and R_n for each step */
        printf("%6.4f %16.14f %16.14f %16.14f \n", t, S, I, R);
    }

    return 0;
}
