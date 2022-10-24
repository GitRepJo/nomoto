/**
	Copyright (c) 2022 Jonas Mahler
	
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

using namespace Eigen;

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
    MatrixXd inputSequence;  // input sequnce, dimensions: m\times  timeSamples
    MatrixXd simulatedStateSequence; //simulated state sequence, dimensions: n\times  timeSamples
    MatrixXd simulatedOutputSequence; //simulated output sequence, dimensions: r\times  timeSamples
    MatrixXd timeRowVector;           // time row vector [0,1,2,3,\ldots, timeSamples-1]
    int m, n, r, timeSamples; //m - input dimension, n- state dimension, r-output dimension, timeSamples- number of time samples 
};
#endif //NOMOTO_MODEL_HPP