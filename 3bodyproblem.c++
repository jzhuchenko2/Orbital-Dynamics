#include <iostream>
#include <cmath>
#include <vector>

using namesapce std;

//gravitational constants
const double G = 6.67430e-11;
const double M1 = 5.972e24; //Earth mass HUGE
const double M2 = 7.342e22; // Moon mass
const double R1 = 3.844e8;  // Earth-Moon distance

class Spacecraft {
public:
    double mass;
    double x, y; // Position in 2D space
    double vx, vy; Velocity Componenents

    //this is a constructor for a Satellite class in C++. it initializes a new instance of the Satellite class with the provided parameters.
    Spacecraft(double m, double initialX, double initialY, double initialVx, double initialVy)
        : mass(m), x(initialX), y(initialY), vx(initialVx), vy(initialVy) {}

    void calculateGravity(double& fx, double& fy) {
        double r1 = sqrt((x + R1) * (x + R1) + y * y);
        double r2 = sqrt((x - (1.0 - R1)) * (x - (1.0 - R1)) + y * y);

        // Gravitational forces from Earth and Moon
        double force1 = G * M1 * mass / (r1 * r1);
        double force2 = G * M2 * mass / (r2 * r2);

        // Components of forces along x and y axes
        fx = force1 * (-(x + R1) / r1) + force2 * ((x - (1.0 - R1)) / r2);
        fy = force1 * (-y / r1) + force2 * (y / r2);

The forces are calculated by considering the inverse square law for gravity and the positions of the object relative to Earth and Moon.
The components are determined by multiplying the gravitational forces with the corresponding unit vectors along the x and y axes.
//now using the RKF45 method to update position and velocity 
    void update(double& dt) {
        double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y, k5x, k5y, k6x, k6y;
        double fx, fy;

        calculateGravity (fx, fy);
        k1x = dt * vx;
        k1y = dt * vy;

        calculateGravity(fx, fy);
        k2x = dt * (vx + 0.25 * k1x);
        k2y = dt * (vy + 0.25 * k1y);

        calculateGravity(fx, fy);
        k3x = dt * (vx + 3.0 / 32.0 * k1x + 9.0 / 32.0 * k2x);
        k3y = dt * (vy + 3.0 / 32.0 * k1y + 9.0 / 32.0 * k2y);

        calculateGravity(fx, fy);
        k4x = dt * (vx + 1932.0 / 2197.0 * k1x - 7200.0 / 2197.0 * k2x + 7296.0 / 2197.0 * k3x);
        k4y = dt * (vy + 1932.0 / 2197.0 * k1y - 7200.0 / 2197.0 * k2y + 7296.0 / 2197.0 * k3y);

        calculateGravity(fx, fy);
        k5x = dt * (vx + 439.0 / 216.0 * k1x - 8.0 * k2x + 3680.0 / 513.0 * k3x - 845.0 / 4104.0 * k4x);
        k5y = dt * (vy + 439.0 / 216.0 * k1y - 8.0 * k2y + 3680.0 / 513.0 * k3y - 845.0 / 4104.0 * k4y);

        calculateGravity(fx, fy);
        k6x = dt * (vx - 8.0 / 27.0 * k1x + 2.0 * k2x - 3544.0 / 2565.0 * k3x + 1859.0 / 4104.0 * k4x - 11.0 / 40.0 * k5x);
        k6y = dt * (vy - 8.0 / 27.0 * k1y + 2.0 * k2y - 3544.0 / 2565.0 * k3y + 1859.0 / 4104.0 * k4y - 11.0 / 40.0 * k5y);

        x += 25.0 / 216.0 * k1x + 1408.0 / 2565.0 * k3x + 2197.0 / 4104.0 * k4x - 1.0 / 5.0 * k5x;
        y += 25.0 / 216.0 * k1y + 1408.0 / 2565.0 * k3y + 2197.0 / 4104.0 * k4y - 1.0 / 5.0 * k5y;

        vx += 16.0 / 135.0 * k1x + 6656.0 / 12825.0 * k3x + 28561.0 / 56430.0 * k4x - 9.0 / 50.0 * k5x + 2.0 / 55.0 * k6x;
        vy += 16.0 / 135.0 * k1y + 6656.0 / 12825.0 * k3y + 28561.0 / 56430.0 * k4y - 9.0 / 50.0 * k5y + 2.0 / 55.0 * k6y;

        dt = calculateNewStepSize(dt);
    }
private:

    double calculateNewStepSize(double dt) {
        double error = calculateError();
        double safetyFactor = 0.9;
        double newDt = dt * safetyFactor * pow(1.0 / error, 0.2);

        // Limit the maximum increase in step size
        if (newDt > 2.0 * dt) {
            newDt = 2.0 * dt;
        }

        return newDt;
    }

    double calculateError() {
        // Implement your error calculation method based on the problem characteristics
            return 1.0e-8;
    }
};
    void simulateDeepSpaceExploration(Spacecraft& spacecraft, double simulationTime, double& dt) {
    for (double t = 0; t < simulationTime; t += dt) {
        spacecraft.update(dt);

        // Print spacecraft position at each time step
        cout << "Time: " << t << " - Position (x, y): (" << spacecraft.x << ", " << spacecraft.y << ")" << endl;
    }
}
    int main() {
    //define spacecraft
    Spacecraft spacecraft(1000.0, -R1, 0.0, 0.0, -1.0);
        // Simulation parameters
            double simulationTime = 500000.0; // Adjust simulation time based on the desired duration
            double dt = 1000.0;   //initial time step

        simulateDeepSpaceExploration(spacecraft, simulationTime, dt);

        return 0;
}

//now for Kepler's equation that everyone speaks about
M=E−e⋅sin(E)

where:

�
M is the mean anomaly,
�
E is the eccentric anomaly,
�
e is the eccentricity of the orbit.

// Example usage
    double meanAnomaly = 2.5;     // Example mean anomaly
    double eccentricity = 0.1;   // Example eccentricity


   double eccentricAnomaly = solveKeplersEquation(meanAnomaly, eccentricity);
cout << "Mean Anomaly: " << meanAnomaly << endl;
    cout << "Eccentricity: " << eccentricity << endl;
    cout << "Eccentric Anomaly: " << eccentricAnomaly << endl;

return 0;
}
