Jonas Mahler 11.2022

# Description
This .cpp program is a 1 Degree of Freedom model of a ship after Nomoto.    
It is most commonly used to design a autopilot for course correction e.g. a sliding mode controller. 

For more information look into 

- K.Nomoto 1956 " On the steering qualities of ships"     
in International shipbuilding progress
 
- Muhammad Ejaz and Mou Chen 2017 " Sliding mode control design of a ship    
steering autopilot with input saturation" in International Journal of Advanced    
Robotic Systems

The program my also serve as a template for ship models with a higher degree of freedom, e.g. 3DoF.  

Odeint is used for integration, which is included in boost.     
The differential equation as well as the observer to the function has to be passed to the odeint integrator function.    
Odeint does not allow member functions to be passed to the integrator function.    
Thus the ode and the observer are functors.    
They can be found in nomoto_ode.hpp and nomoto_obs.hpp respectively.  

# TODO
Add test

# Bug report
None

# Build the code

Cmake is used to create the build files.
Clone the code
```
git clone 
```
Create a build directory in the new git directory
```
cd /home/$USER/git/nomoto 
mkdir -p build 
```
Create the build files with cmake and build the code
```
cmake -DCMAKE_BUILD_TYPE=Releases -S . -B build && cmake --build build
```

# Run the code 
An example simulation run with the program can be found in main.cpp.    
Parameters for the simulation and the differential equation can be read from a .yaml file or specified directly in the main function.    
This is shown in main.cpp that may serve as an example to run the code.     

Run the code
```
cd /home/$USER/git/nomoto 
./nomoto
```
 
