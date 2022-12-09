// Copyright (c) 2022 Jonas Mahler
	
// This file is part of ode.

// ode is free software: you can redistribute it and/or modify it under the terms 
// of the GNU General Public License as published by the Free Software Foundation, 
// either version 3 of the License, or (at your option) any later version.

// ode is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along 
// with ode. If not, see <https://www.gnu.org/licenses/>. 

#ifndef NOMOTO_ODE_HPP
#define NOMOTO_ODE_HPP

#include <eigen3/Eigen/Dense>
#include <iostream>

/* Constants used for Nomoto ship model*/
struct constNomoto
    {
        double K; // Hydrodynamic constant dependent on vessel
        double T; // Time constant dependent on vessel
        double delta; // Rudder angle of the vessel
    };

/**
* @brief Write output of boost integration function to terminal
* @param x Pointer to the array that contains the states of the ordinary differential equation
* @param t Time that belongs to state x 
*/
inline void write_nomoto( const std::array<double,1> &x , const double t )
{
std::cout << "This is x[0]" << t << '\t' << x[0] << std::endl;
}

/* Functor Ordinary Differential Equation for Nomoto ship model

----Variables/Constants 
delta : Rudder angle
phi   : Yaw
d_phi : Yaw velocity
r     : Yaw velocity (equals d_phi)
d_r   : Yaw acceleration
K     : Hydrodynamic constant dependent on vessel
T     : Time constant dependent on vessel
a     : -1/T
b     : K/T

Equation
----
d_phi = r
d_r   = a * r + b *delta 
*/
class NomotoOde {

public:

    const constNomoto &nomCoeff;
    NomotoOde( constNomoto &coeff) :  nomCoeff(coeff) { };

    void operator() ( const std::array<double,1> &x , std::array<double,1> &dxdt , const double t )
    {
        double a = - 1/nomCoeff.T;
        double b = nomCoeff.K/nomCoeff.T;
        
        dxdt[0] = a * x[0] + b * nomCoeff.delta; 
    }
};
#endif //NOMOTO_ODE_HPP