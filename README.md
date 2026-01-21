## Monte Carlo Radiation Transport Simulator

A C++ Monte Carlo simulation that models particle attenuation through shielding materials.
This project highlights **C++ Programming**, **probabilistic modeling**, and **statistical analysis** skills.

--

## Overview

This simulation estimates the transmission and absorbtion of particles through a material slab using a probabilistic approach:

Each particle is tracked indivdually as it propagates through a stack of materials. Absorption is modeled probabilitistically, allowing the simulation to approximate the exponential attenuation law:

\[
I(x) - I_0 e^{-\mu x}
\]

where: 

- \(I(x)\) = particle intensity after traveling distance \(x\)
- \(I_0\)  = initial intensity 
- \(\mu\)  = material's macroscopic absorption coefficient

The simulator also computes statistical uncertainty allowing results to be interpreted rigorously. 

--

## Key Features

- Modular C++ code structure
- Clear separation of **Particle**, **Material**, and **Simulator**
- Monte Carlo simulation loop
- Comparison of simulation results against theoretical predictions
- Pre-material statistic tracking
- Statiscal uncertainty estimation
- Runtime measurement using std::chrono
- Scaled to billions of particles

--

## Interactive Simulation

The simulator now allows the user to:

1. Input the **number of particles** to simulate
2. Input the **step size** in cm
3. Input the **number of materials**
4. For each material, input:
	- Names
	- Thickness (cm)
	- Absorption probability per step (0-1)
	
This allows the user to simulate realistic shielding scenarios with multiple materials.
Each particle is simulate individually and propagated sequentially through all materials in order.

For each particle:
1. The particle enters the first material.
2. At each step inside the material, a Bernoulli trial determines whether the particle is absorbed.
3. If absorbed, the particle is terminated and does not enter any subsequent materials.
4. If the particle survives the entire thickness of a meterial, it proceeds to the next material. 
5. The particle survives the simulation only if it passes through all materials.

This approach ensures that downstream materials only recieve particles that physically survive upstream attenuation.

---

## Monte Carlo Convergence Demonstration

Monte Carlo radiation transport relies on statisical sampling. As the number of simulated particles increases, the numerical result should converge toward the analytical solution predicted by the exponential attenuation theory.

To demonstrate correct Monte Carlo behavior, the simulator was run with increasing particle counts using the same material configuration.

For a simulation with N amount of particles and multiple shielding materials (Lead, Concrete, Polyethylene, etc.), the following statistics can be retrieved:

- Surival fraction: N_survived / N
- Standard deviation: sqrt(survivalFraction(1 - survivalFraction))
- Standard error: sigma / sqrt(N)
- 95% confidence interval: [(sigma - stdError), (sigma + stdError)]

The reported confidence interval demonstates converge as athe number of simulated particles increases. The Monte Carlo survival fraction is expected to be lower than the analytical solution for a single material due to additional attenuation from multiple shielding layers. 

---

## Example Realistic Run

To demonstrate statistical convergence, the simulation was run with 500,000,000

Enter number of particles to simulate: 1000000000
Enter step size in cm: .1
Enter number of materials: 3
Material 1 name: Lead
Thickness in cm: 5
Absorption probability per step (0-1): .00995
Material 2 name: Concrete
Thickness in cm: 50
Absorption probability per step (0-1): .001
Material 3 name: Polyethylene
Thickness in cm: 30
Absorption probability per step (0-1): .0005
Particles simulated: 1000000000
Particles survived: 316558334
Fraction survived: 0.316558
Standard deviation: 0.465133
Standard error: 1.47088e-05
95% confidence interval: [0.31653, 0.316587]

Material survival fractions and statistics:
Lead
Entered: 1000000000
Survived: 0.606547
Fraction Survived: 0.606547
Standard deviation: 0.488516
Standard error: 1.54482e-05
95% confidence interval: [0.316528, 0.316589]
Concrete
Entered: 606546925
Survived: 0.60636
Fraction Survived: 0.60636
Standard deviation: 0.488557
Standard error: 1.98373e-05
95% confidence interval: [0.316519, 0.316597]
Polyethylene
Entered: 367786000
Survived: 0.860713
Fraction Survived: 0.860713
Standard deviation: 0.346245
Standard error: 1.80545e-05
95% confidence interval: [0.316523, 0.316594]
Theoretical fraction (first material only): 0.606536
Simulation runtime: 10214.3seconds

	Although different material may exhibit similar survival fractions, their statistical uncertainties may differ. 
	
	Materials later in the stack recieve fewer particles due to attentuation in previous layers. Since standard error scaled as 1/ sqrt(N), materials with fewer entering particles naturally exhibit larger statistical uncertainty.

	This behavior is expected and reflects correct physical and statistical modeling of particle transport. 
	

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

- Include optional plotting and simulated vs theoretical results
- include parallelization, show scaling from 2, 4 and 8 cores 
