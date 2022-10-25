
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
	@name nomoto_model.cpp
	@brief Calculates the Nomoto shipmodel as specified in a configuration file.
	@author Jonas Mahler
	@date 10.2022
*/


#include "nomoto_model.hpp"
#include "yaml-cpp/yaml.h"
#include "eigen3/Eigen/Dense"
#include <iostream>

using namespace std;

Nomoto::Nomoto()
{
	m = 0; n = 0; r = 0;
	A.resize(1, 1); A.setZero();
	B.resize(1, 1); B.setZero();
	C.resize(1, 1); C.setZero();
	x0.resize(1, 1); x0.setZero();
	steps.resize(1, 1); steps.setZero();
	angle.resize(1, 1); angle.setZero();
	
	simulatedStateSequence.resize(1, 1); simulatedStateSequence.setZero();
	simulatedOutputSequence.resize(1, 1); simulatedOutputSequence.setZero();
	timeRowVector.resize(1, 1); timeRowVector.setZero();
}
Nomoto::~Nomoto()
{}

void Nomoto::read(std::string config_file)
{
    YAML::Node config = YAML::LoadFile(config_file);

    const vector<double> eigenVecA = config["matrix_A"].as<vector<double>>();
    Eigen::Matrix<double,2,2,Eigen::RowMajor> A(eigenVecA.data());
    cout << "Matrix  A: " << A << endl;

	const vector<double> eigenVecB = config["matrix_A"].as<vector<double>>();
    Eigen::Matrix<double,2,1> B(eigenVecB.data());
    cout << "Matrix  B: " << B << endl;

	const vector<double> eigenVecC = config["matrix_C"].as<vector<double>>();
    Eigen::Matrix<double,1,2> C(eigenVecA.data());
    cout << "Matrix  C: " << C << endl;

	const vector<double> eigenVecD = config["matrix_D"].as<vector<double>>();
    Eigen::Matrix<double,1,1> D(eigenVecD.data());
    cout << "Matrix  D: " << D << endl;

	const vector<double> eigenVecInit = config["init_state_x"].as<vector<double>>();
    Eigen::Matrix<double,2,1> initState(eigenVecInit.data());
    cout << "Matrix initState: " << initState << endl;

	// Sum of all entires in vector results in total simulation steps (e.g. 10.0,10.0,10.0 = 30 steps)
	const vector<double> eigenVecSteps = config["simulation_steps"].as<vector<double>>();
	print("Simulation steps:",eigenVecSteps);	
	
	// This is the angle of each simulation sequence (e.g. 10.0 steps x 45.0 degree ,10.0 steps x 45.0 degree ,... , 10.0 steps x 0.0 degree )
	const vector<double> eigenVecAngle = config["simulation_rudder_angle"].as<vector<double>>();
	print("Rudder angle for simulation steps:",eigenVecAngle);
	
	// Calculate the input sequence of rudder angles with simulation steps and angles
	vector<double> inputSeqRudAngle;
	for (int i = 0; i < sizeof(eigenVecSteps); i++)
	{	
		vector<double> stepsPerAngle(eigenVecSteps[i],eigenVecAngle[i]);
		//print("steps per angle:", stepsPerAngle);
		inputSeqRudAngle.insert(inputSeqRudAngle.end(),stepsPerAngle.begin(),stepsPerAngle.end());
	}
	print("Input sequence of rudder angles for simulation:",inputSeqRudAngle);
}

void Nomoto::runSequence()
{	
	// Calculate the sequence for rudder angle. One rudder angle resembles one timestep
	

	for (int j = 0; j < timeSamples; j++)
	{
		if (j == 0)
		{
			simulatedStateSequence.col(j) = x0;
			simulatedOutputSequence.col(j) = C * x0;
		}
		else
		{
			//simulatedStateSequence.col(j) = A * simulatedStateSequence.col(j - 1) + B * inputSequence.col(j - 1);
			//simulatedOutputSequence.col(j) = C * simulatedStateSequence.col(j);
		}
		
	}
}
void Nomoto::save(std::string inputSimulationConfiguration , std::string inputSequenceRudderAngle , std::string outputSequenceYawRate)
{
        
}