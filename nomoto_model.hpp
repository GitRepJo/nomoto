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

/**
    @name nomoto_model.hpp
	@brief Calculates the Nomoto shipmodel as specified in a configuration file.
	@author Jonas Mahler
	@date 10.2022
*/

#ifndef NOMOTO_MODEL_HPP
#define NOMOTO_MODEL_HPP

#include <eigen3/Eigen/Dense>
#include<tuple>
#include<string>
#include<vector>
#include <iostream>

using namespace Eigen;
/**
* @brief Print a std::vector entry by entry
* @param -
*/
static inline void print (std::string const desc, std::vector<double> const &input)
{
    std::cout << desc << ' ';
    for (double i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}
/**
* @class Nomoto
* @brief Sets up, simulates and saves the results of a Nomoto model of a ship
*/
class Nomoto {
public:
    /**
     * @brief Constructor, initialize matrices of Nomoto with zero
     * @param -
     */
    Nomoto();
    
    /**
    * @brief Overloaded Constructor, initialize matrices of Nomoto as specified
    * @param MatrixXd Specifies Nomotos model 
    */
    Nomoto(MatrixXd Amatrix, MatrixXd Bmatrix, MatrixXd Cmatrix, MatrixXd initialState, MatrixXd inputSequenceMatrix);
    
    /**
    * @brief Deconstructor
    * @param -
    */
    ~Nomoto();
    
    /**
    * @brief Reads the config file and write variables as specified
    * @param config_file File that contains simulation variables for Nomotos model
    */
    void read(std::string config_file);
    
    /**
    * @brief Run all simulation steps after each other as fast as possible
    * @param -
    */
    void runSequence();
    
    /**
    * @brief Run one step of the simulation. That allows for realtime simulation if steps are run accordingly
    * @param -
    */
    void runStep();
    
    /**
    * @brief Save simulation results to file
    * @param inputSimulationConfiguration The configuration with which the simulation is run
    * @param inputSequenceRudderAngle The input rudder angle for each simulation step
    * @param outputSequenceYawRate The output yaw angle for each simulation step
    */
    void save(std::string inputSimulationConfiguration , std::string inputSequenceRudderAngle , std::string outputSequenceYawRate);

private:
    // MatrixXd is an Eigen typdef for Matrix<double, Dynamic, Dynamic>
    MatrixXd A,B,C,D; // A,B,C matrices
    MatrixXd x0;     // initial state
    MatrixXd steps;  // input sequnce, dimensions: m\times  timeSamples
    MatrixXd angle;
    MatrixXd simulatedStateSequence; //simulated state sequence, dimensions: n\times  timeSamples
    MatrixXd simulatedOutputSequence; //simulated output sequence, dimensions: r\times  timeSamples
    MatrixXd timeRowVector;           // time row vector [0,1,2,3,\ldots, timeSamples-1]
    int m, n, r, timeSamples; //m - input dimension, n- state dimension, r-output dimension, timeSamples- number of time samples 
};
#endif //NOMOTO_MODEL_HPP