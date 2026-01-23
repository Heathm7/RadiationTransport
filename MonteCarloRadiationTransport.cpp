// MonteCarloRadiationTransport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "Simulator.h"
#include "Material.h"
#include "ConsoleViewer.h"


int main()
{
    // Number of threads on users system
    unsigned int maxThreads = std::thread::hardware_concurrency();
    if (maxThreads == 0)
        maxThreads = 1;

    unsigned int numThreads;
    std::cout << "Detected " << maxThreads << " logical cores." << '\n';
    std::cout << "Enter number of threads to use (1-" << maxThreads << "): " << '\n';
    std::cin >> numThreads;

    if (numThreads < 1)
        numThreads = 1;
    
    if (numThreads > maxThreads) 
        numThreads = maxThreads;

    // Number of particles and step size
    int numParticles;
    std::cout << "Enter number of particles to simulate: ";
    std::cin >> numParticles;

    double stepSize;
    std::cout << "Enter step size in cm: ";
    std::cin >> stepSize;


    // Create the simulator
    Simulator sim(numParticles, stepSize, numThreads);

    // Add materials
    int numMaterials;
    std::cout << "Enter number of materials: ";
    std::cin >> numMaterials;

    for (int i = 0; i < numMaterials; i++) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        std::string name;
        std::cout << "Material " << i + 1 << " name: ";
        std::getline(std::cin, name);

        double thickness;
        std::cout << "Thickness in cm: ";
        std::cin >> thickness;

        double absorptionProb;
        std::cout << "Absorption probability per step (0-1): ";
        std::cin >> absorptionProb;

        sim.addMaterial(Material(name, thickness, absorptionProb));

    } 

    // Timing start
    auto start = std::chrono::high_resolution_clock::now();

    // Run sim
    sim.run();

    auto end = std::chrono::high_resolution_clock::now();
    // Timing end

    // Print results
    ConsoleViewer::report(sim.getStats()); 

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Simulation runtime: " << elapsed.count() << "seconds" << "\n";

    return 0;
}

