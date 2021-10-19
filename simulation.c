#include <math.h>
#include <stdio.h>
#include <string.h>

#define real double

// Solar constant W / m ^ 2
#define S0 1370

// Stefan - Boltzmann constant W / m2 / K4
#define SIGMA 0.00000005670367

// Temperature inertia (in years)
#define THETA 100.0

// Albedo, in this simulation albedo is considered constant
// in reality albedo can become lower with increased temperatures
// due to ice cap melting
#define ALBEDO 0.33

// Initial values

// Simulation starts in 2007
static const real t0 = 2007.0;
// Temperaturature in 2007 in K
static const real T0 = 288.45;
// CO2 concentration in 2007 in ppm
static const real CO20 = 412.0;

// Greenhouse gaz fraction
static real G(real T, real co2) {
  return 3.35071874e-03 * T + 3.20986702e-05 * co2 - 0.561593690144655;
}

static real P_in(void) { return (1 - ALBEDO) * S0 / 4; }

static real P_out(real t, real T, real co2) {
  return (1 - G(T, co2)) * SIGMA * pow(T, 4);
}

static real F(real t, real T, real h, real co2) {
  return (P_in() - P_out(t, T, co2)) * h / THETA;
}

static real euler(real t_final, int steps) {

  FILE *f = fopen("output.dat", "w");
  double h = (t_final - t0) / steps;
  double t = t0;
  double T = T0;
  double co2 = CO20;

  while (t < t_final) {
    T += h * F(t, T, h, co2);
    t += h;
    co2 *= 1.01;
    fprintf(f, "%f %f\n", t, T - T0);
  }
  fclose(f);
  return T;
}

int main(int argc, char **argv) {

  euler(2107.0, 100);

  return 0;
}