//python
#include <fstream> // For file operations

int main() {
    // Open a file for writing position data
    std::ofstream outfile("output.dat");

   const double rotationSpeed = 1.0e-6;
const double dt = 1.0;                   // time step in seconds
    const double rotationSpeed = 1.0e-6; 

//initial conditions for the spacecraft
Spacecraft spacecraft(1e6, 0, 1e4, 0, 2e4, 0);  // Placed at (x=1e6, y=0, z=1e4) with initial velocity in y-direction

//performing simulation
for (double t = 0; t <= simulationTime; t += dt) {
        integrate(spacecraft, rotationSpeed, dt);

    spacecraft.position = newmanJanis(spacecraft.position, rotationSpeed);
                  }
