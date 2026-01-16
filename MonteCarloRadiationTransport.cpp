// MonteCarloRadiationTransport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Simulator.h"
#include "Material.h"

int main()
{
    // Number of particles and step size
    int numParticles = 10000;
    double stepSize = 0.1;      // cm

    // Create the simulator
    Simulator sim(numParticles, stepSize);

    // Add materials
    Material lead("Lead", 2.0, 0.05);   //thickness 2cm, absorption probability 5% per step
    Material water("Water", 5.0, 0.01); //thickness 5cm, absorption probability 1% per step

    sim.addMaterial(lead);
    sim.addMaterial(water);
    
    // Run sim
    sim.run();

    // Print results
    sim.report();

    return 0;
}

