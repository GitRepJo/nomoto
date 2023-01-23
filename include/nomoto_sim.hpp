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

#ifndef NOMOTO_SIM_HPP
#define NOMOTO_SIM_HPP

#include <nomoto_ode.hpp>
#include <nomoto_obs.hpp>

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
        double velocity = 0.0; // Total velocity of the vessel
        double initYaw = 0.0; // Initial yaw in degree
        double initYawRate = 0.0; // Initial yaw rate in degree/s
        double initX = 0.0; // Initial position of x in meter
        double initY = 0.0; // Initial position of y in meter
        double step = 0.0; // Stepsize for integration
        double time = 0.0; // Time to end of integration
        bool terminal_output = true ; // Write result struct to terminal if true
    };
    
    /* Save the results of the simulation of Nomotos ship model*/
    struct resultNomoto
    {
        std::vector<double> x_pos; // Position x in m two dimensional carthesian global coordinates
        std::vector<double> y_pos; // Position y in m two dimensional carthesian global coordinates
        std::vector<double> time; // Time corresponding to the state
        std::vector<double> yaw; // Orientation in global coordinates relative to north in degree
        std::vector<double> yaw_rate; // Yaw rate in degree/s
        std::vector<double> yaw_acc;  // yaw rate acceleration in degree/s*s
    };

    /**
    * @brief Run the Nomoto ship model simulation by using a predefined ordinary differential equation
    * @param cN constNomoto struct to save constants for the Nomoto ODE
    * @param vS varSim struct to save constants variables specific to the simulation
    * @return resultNomoto struct with the results (actual yaw angle, position ...)
    */
    NomotoSim::resultNomoto runNomoto(constNomoto cN,varSim vS);
    
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

    SaveNomoto sav;
    NomotoOde sim;
    

private:
    /**
    * @brief Calculate the yaw angle based on the simulation parameters and the position
    * @param cN constNomoto struct to save constants for the Nomoto ODE
    * @param vS varSim struct to save constants variables specific to the simulation
    * @param states yaw rate result of the simulation, in this case only a one dimensional state vector
    * @param times Corresponding time for the yaw rate (no constant delta t with adaptive intregration)
    * @return resultNomoto struct with the results (actual yaw angle, position ...)
    */
    resultNomoto calcResult(varSim vS, std::vector<std::array<double,1>> &states , std::vector< double > &times);

    /**
    * @brief Write the result of the simulation to the terminal 
    * @param res struct that contains the result of the simulation
    * @details The values will be rounded to 2 digits after the comma
    */
    void writeTerminal(NomotoSim::resultNomoto res);

};

#endif //NOMOTO_SIM_HPP