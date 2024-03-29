#include <iostream>
#include <cmath>
#include <vector>

#include <fstream> //operations for this file

// constants
const double G = 6.674e-11;    // gravitational constant
const double c = 299792458;   // LIGHT SPEED

// structure to represent a 3D point
struct Point {
    double x, y, z;

    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Point operator-(const Point& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Point operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }




    Point operator/(double scalar) const {




        // making sure scalar is not zero to avoid division by zero
        if (scalar != 0.0) {
            return {x / scalar, y / scalar, z / scalar};
        } else {
            // handle division by zero gracefully (we'll probably need to adjust as needed)
            std::cerr << "Error: Division by zero.\n";
            return *this;  // Return original value
        }
    }
};

// spacecraft or satellite structure
struct Spacecraft {
    Point position;
    Point velocity;

    Spacecraft(double x, double y, double z, double vx, double vy, double vz): position(x, y, z), velocity(vx, vy, vz) {}
};

//i have to make these coordinates real-life. so x,y, and z is more efficient and believeable.

// function to calculate gravitational force from a rotating black hole using the Kerr metric
Point gravitationalForce(const Point& position, double rotationSpeed) {
    // assuming a Kerr black hole with mass M and rotation parameter a
    const double M = 1e30;
    const double a = 0.9;  // Example rotation parameter

    // calculate the Boyer-Lindquist radial coordinate
    double r = std::sqrt(position.x * position.x + position.y * position.y + position.z * position.z);

    // calculate the gravitational force using the Kerr metric
    double forceMagnitude = -G * M * (1.0 - 2.0 * G * M / (r * c * c)) / (r * r);

    // including effect of black hole rotation
    double r_perp = std::sqrt(position.x * position.x + position.y * position.y);
    double phi_bh = std::atan2(position.y, position.x) + rotationSpeed * r_perp / (r * c);

    Point forceVector(forceMagnitude * std::cos(phi_bh), forceMagnitude * std::sin(phi_bh), 0.0);

    return forceVector;
}

// function to perform numerical integration using runge-kutta method
void integrate(Spacecraft& spacecraft, double rotationSpeed, double dt) {
    
//adding info abt Runga coefficients
    const double k1 = dt;
    const double k2 = dt / 2.0;
    const double k3 = dt / 2.0;
    const double k4 = dt;

//gravitational force
    Point force1 = gravitationalForce(spacecraft.position, rotationSpeed);
    Point force2 = gravitationalForce(spacecraft.position + spacecraft.velocity * (k2 / 2.0), rotationSpeed);
    Point force3 = gravitationalForce(spacecraft.position + spacecraft.velocity * (k3 / 2.0), rotationSpeed);
    Point force4 = gravitationalForce(spacecraft.position + spacecraft.velocity * k4, rotationSpeed);

    // update velocity and position using Runge-Kutta method
    //spacecraft.velocity += (k1 + k2.5 / force4 * force1 + 2.0 * k2 * force2 + 2.0 * k3 * force3 + k4 * force4) / 6.0;
    spacecraft.velocity = spacecraft.velocity + (force1 * k1 + force2 * (2.0 * k2) + force3 * (2.0 * k3) + force4 * k4) / 6.0;

    spacecraft.position = spacecraft.position + (spacecraft.velocity * dt);

    //spacecraft.position.x += spacecraft.velocity.x * dt;
    //spacecraft.position.y += spacecraft.velocity.y * dt;
    //spacecraft.position.z += spacecraft.velocity.z * dt;
}

// function to apply a simple form of the newman-janis algorithm for rotating black hole
Point newmanJanis(const Point& position, double rotationSpeed) {
    // apply a simplified form of the Newman-Janis algorithm
    double r_perp = std::sqrt(position.x * position.x + position.y * position.y);
//arc tangent is a trigonometric function that returns the angle whose tangent is the given ratio. 
    double phi_bh = std::atan2(position.y, position.x) + rotationSpeed * r_perp / (position.z * c);
// rotate the position. changing the position of something by rotating it around a point. 
    double x_rotated = position.x * std::cos(phi_bh) - position.y * std::sin(phi_bh);
//now for the y
    double y_rotated = position.x * std::sin(phi_bh) + position.y * std::cos(phi_bh);
return {x_rotated, y_rotated, position.z};
}


int main() {
//execute the plan idiot
// Open a file for writing position data
    std::ofstream outfile("output.dat");

// Simulation parameters
    const double simulationTime = 1000.0;   // in seconds
    const double dt = 1.0;                   // time step in seconds
const double rotationSpeed = 1.0e-6;    // Rotation speed of the black hole in rad/s (example value)

    // Initial conditions for the spacecraft
    Spacecraft spacecraft(1e6, 0, 1e4, 0, 2e4, 0); // Placed at (x=1e6, y=0, z=1e4) with initial velocity in y-direction
// Perform the simulation
    for (double t = 0; t <= simulationTime; t += dt) {
        integrate(spacecraft, rotationSpeed, dt);
        spacecraft.position = newmanJanis(spacecraft.position, rotationSpeed);
// Write position data to file
        outfile << t << " " << spacecraft.position.x << " " << spacecraft.position.y << " " << spacecraft.position.z << "\n";
    

// Close the file
    outfile.close();

    return 0;
    }
}
