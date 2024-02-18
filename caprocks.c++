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
