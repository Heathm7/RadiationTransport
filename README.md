## Monte Carlo Radiation Transport Simulator

A C++ Monte Carlo simulation that models particle attenuation through shielding materials.
This project highlights both **C++ Programming** and **Mathematical Modeling** skills.

--

## Overview

This simulation estimates the transmission and absorbtion of particles through a material slab using a probabilistic approach:

- Each particle moves in discrete steps through the material.
- At each step, the particle has a probability of being absorbed. 
- The simulation approximates the **Exponential Attenuation Law**

\[
I(x) - I_0 e^{-\mu x}
\]

where: 

- \(I(x)\) = particle intensity after traveling distance \(x\)
- \(I_0\)  = initial intensity 
- \(\mu\)  = material's macroscopic absorption coefficient

--

## Current Implementation

- Particle.h - defines particles with position, energy, and alive status
- Material.h - defines shielding materials with thickness and absorption probability
- Simulator.h / Simulator.cpp - Monte Carlo loop that moves particles through materials and records absorptions
- MonteCarloRadiationTransport.cpp - example fun of the simulator

--

## Example Output

Running the simulator with 10,000 particles, Lead (2cm, 5% absorption per step) and Water (5cm, 1% absorption per step):

Particles simulated: 10000
Particles survived: 2142
Fraction survived: 0.2142
Theoretical fraction (first material only): 0.358486

*> Monte Carlo simulation is stochastic, so results vary slightly.
*> Increasing particle count or decreasing step size improves accuracy.


## Key Features

- Modular C++ code structure
- Clear separation of **Particle**, **Material**, and **Simulator**
- Monte Carlo simulation loop
- Comparison of simulation results against theoretical predictions
- Statiscal uncertainty estimation

--

## File Structure

/Header Files
Particle.h
Material.h
Simulator.h
/Source Files
simulator.cpp
MonteCarloRadiationTransport.cpp
.gitignore
README.md
MonteCarloRadiationTransport.sln

--

## Technologies

- C++17
- Visual Studio 2022 (MSVC)
- Git + Github for version control

--

## Next Steps

- Implement statistical analysis of surviving particles
- Add multi-material attenuation comparision
- Include optional plotting and simulated vs theoretical results
- Allow user to input materials and particle count. 
