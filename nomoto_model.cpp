/**
	Copyright (c) 2022 Jonas Mahler
	
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
	inputSequence.resize(1, 1); inputSequence.setZero();
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
}

void Nomoto::runSequence()
{
	for (int j = 0; j < timeSamples; j++)
	{
		if (j == 0)
		{
			simulatedStateSequence.col(j) = x0;
			simulatedOutputSequence.col(j) = C * x0;
		}
		else
		{
			simulatedStateSequence.col(j) = A * simulatedStateSequence.col(j - 1) + B * inputSequence.col(j - 1);
			simulatedOutputSequence.col(j) = C * simulatedStateSequence.col(j);
		}
		
	}
}
void Nomoto::save(std::string inputSimulationConfiguration , std::string inputSequenceRudderAngle , std::string outputSequenceYawRate)
{
        
}