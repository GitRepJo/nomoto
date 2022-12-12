// Copyright (c) 2022 Jonas Mahler
	
// This file is part of nomoto.

// nomoto is free software: you can redistribute it and/or modify it under the terms 
// of the GNU General Public License as published by the Free Software Foundation, 
// either version 3 of the License, or (at your option) any later version.

// nomoto is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along 
// with nomoto. If not, see <https://www.gnu.org/licenses/>. 

#ifndef NOMOTO_ODE_HPP
#define NOMOTO_ODE_HPP

#include <eigen3/Eigen/Dense>
#include <iostream>

/* Constants used for Nomoto ship model*/
struct constNomoto
    {
        double K; // Hydrodynamic constant dependent on vessel
        double T; // Time constant dependent on vessel
        double delta; // Rudder angle of the vessel, positive value equals rudder deflection to the right [degree]
    };

/** 
* @brief Functor Ordinary Differential Equation for Nomoto ship model
* @param coeff struct of coefficients used by the nomto ordinary differential equation
* @details 
* ----Variables/Constants 
* delta : Rudder angle
* phi   : Yaw
* d_phi : Yaw velocity
* r     : Yaw velocity (equals d_phi)
* d_r   : Yaw acceleration
* K     : Hydrodynamic constant dependent on vessel
* T     : Time constant dependent on vessel
* a     : -1/T
* b     : K/T
* 
* Equation
* ----
* d_phi = r
* d_r   = a * r + b *delta 
*/
class NomotoOde {

public:

    const constNomoto &nomCoeff;
    
    NomotoOde( constNomoto &coeff) :  nomCoeff(coeff) { };

    // Use vector of arrays to extend state vector of ode if required
    void operator() ( const std::array<double,1> &x , std::array<double,1> &dxdt , double t )
    {
        // Boost integrator e.g. integrate_adaptive requires a variable t
        // t is not used by the ode
        // Create a dummy use case to avoid warnings
        t = 0.0;
        
        double a = - 1/nomCoeff.T + t;
        double b = nomCoeff.K/nomCoeff.T + t;
        
        dxdt[0] = a * x[0] + b * -nomCoeff.delta ; 
    }
};
#endif //NOMOTO_ODE_HPP