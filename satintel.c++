from Spacecraft import Spacecraft as SC
from planetary_data import earth

package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"github.com/ANG13T/SatIntel/cli"
)
func setEnvironmentalVariable(envKey string) string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("%s: ", envKey)
	input, err := reader.ReadString('\n')

	if err != nil {
		fmt.Println("Error reading input:", err)
		os.Exit(1)
	}
	input = strings.TrimSuffix(input, "\n")

	if err := os.Setenv(envKey, input); err != nil {
		fmt.Printf("Error setting environment variable %s: %v\n", envKey, err)
		os.Exit(1)
	}
	return input
}
func checkEnvironmentalVariable(envKey string) {
	_, found := os.LookupEnv(envKey)
	if !found {
		setEnvironmentalVariable(envKey)
	}
}


/*
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Define initial conditions
double x1_0 = 0.0;
double x2_0 = 0.0;
double x3_0 = 0.0;
double x4_0 = 0.0;
//initial time ('t0') are defined
double t0 = 0.0;

// Define time span

//Time Span for Ordinary Differential Equations (ODEs) VECTORS
double tf = 10.0;
vector<double> tspan = {t0, tf};

// Define options for ODE solver

//relative & absoulute tolerances

double RelTol = 1e-12;
double AbsTol = 1e-12;

// Define function to solve ODE
//placeholder function for defining the differential equations of the perturbed two-body problem
void perturbed_two_body(double t, double x[], double dxdt[]) {
    // Define differential equations for perturbed two-body problem
    // ...
// defining gravitational constant
	double G = 6.67430e-11;

	//defined the constant masses
	double m1 = 1.0; // Mass of body 1
    	double m2 = 1.0; // Mass of body 2


//positions & velocities
	double x1 = x[0];
    double x2 = x[1];
    double x3 = x[2];
    double x4 = x[3];
}

// Define Runge-Kutta method
//the implementation details are also not provided in the code snippet.

//The perturbed two-body problem involves the motion of two celestial bodies under the influence of gravitational forces from other bodies, causing perturbations in their orbits.

void RK4(double h, double x[], double t) {
    // ...
}

int main() {
    // Define initial conditions
    double x[] = {x1_0, x2_0, x3_0, x4_0};

    // Define options for ODE solver
    double options[] = {RelTol, AbsTol};

    // Solve ODE
    double t = t0;
    while (t < tf) {
        RK4(h, x, t); // Call the RK4 method
        t += h;
    }

    // Print results
    // ...
//adding the resukts to print in effective motion........PRINT
	for (int i = 0; i < 4; ++i) {
        cout << "x[" << i << "] at t=" << t << ": " << x[i] << endl;
    }
    return 0;
}
*?
