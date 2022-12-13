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
git clone git@github.com:GitRepJo/nomoto.git
```
Create a build directory in the new git directory
```
cd /home/$USER/nomoto 
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
cd /home/$USER/nomoto 
./nomoto
```

# Sample output
This is a terminal sample of the program running as specified in main.cpp and config.yaml
```
t[sec]: 0 x[m]: 0 y[m]: 0 yaw[deg]: 90

t[sec]: 0.1 x[m]: 0 y[m]: 0.14 yaw[deg]: 90

t[sec]: 0.21 x[m]: 0 y[m]: 0.29 yaw[deg]: 90

t[sec]: 0.32 x[m]: 0 y[m]: 0.45 yaw[deg]: 89.99

t[sec]: 0.43 x[m]: 0 y[m]: 0.6 yaw[deg]: 89.99

t[sec]: 0.54 x[m]: 0 y[m]: 0.75 yaw[deg]: 89.98

t[sec]: 0.65 x[m]: 0 y[m]: 0.91 yaw[deg]: 89.97

t[sec]: 0.76 x[m]: 0 y[m]: 1.06 yaw[deg]: 89.96

t[sec]: 0.87 x[m]: 0 y[m]: 1.21 yaw[deg]: 89.95

t[sec]: 0.98 x[m]: 0 y[m]: 1.37 yaw[deg]: 89.94

t[sec]: 1 x[m]: 0 y[m]: 1.4 yaw[deg]: 89.94

```
 
