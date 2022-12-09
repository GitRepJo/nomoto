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

#ifndef NOMOTO_SIM_HPP
#define NOMOTO_SIM_HPP

#include <nomoto_ode.hpp>

#include <eigen3/Eigen/Dense>
#include <boost/numeric/odeint.hpp>
#include<tuple>
#include<string>
#include <vector>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <boost/math/interpolators/cubic_b_spline.hpp>
#include <boost/math/differentiation/finite_difference.hpp>


/* Read model and simulation parameters and run a Nomoto ship model simulation*/ 
class NomotoSim {
public:

    /**
    * @brief Constructor
    * @param -
    */
    NomotoSim();
    /**
    * @brief Deconstructor
    * @param -
    */
    ~NomotoSim();

    /* Constants used for the simulation of Nomotos ship model*/
    struct varSim
    {
        double yawRate; // Initial yaw rate
        double step; // Stepsize for integration
        double time; // Time to end of integration
    };

    /**
    * @brief Run the Nomoto ship model simulation by using a predefined ordinary differential equation
    * @param cN
    * @param vS
    */
    void runNomoto(constNomoto cN,varSim vS);
    
    /**
    * @brief Read constants for the Nomoto ship model
    * @param nomotoFile .yaml file that matches variables in constNomoto struct
    * @return constNomoto struct with constants for Nomoto
    * @details The constants will be used to set up the Nomoto ship model functor
    */
    constNomoto readNomoto(std::string nomotoFile);
    
    /**
    * @brief Read variables for the simulation of Nomotos ship model
    * @param simFile -yanl file that matches variables in varSim struct
    * @return varSim struct with variables for specific simulation
    * @details The variables will be used by boost integration function to set up the simulation
    */
    varSim readSimulation(std::string simFile);
};

#endif //NOMOTO_SIM_HPP