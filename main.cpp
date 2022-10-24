/**
	Copyright (c) 2022 Jonas Mahler
	
    @name main.cpp
	@brief An example of how to use nomoto_model.hpp and run Nomotos model
	@author Jonas Mahler
	@date 10.2022
*/

#include "nomoto_model.hpp"

int main()
{
    Nomoto Simulation1;
    
	Simulation1.read("../configuration.yaml");
	
	Simulation1.runSequence();

	//Simulation1.save("inputSimulationConfiguration","inputSequenceRudderAngle.csv", "outputSequenceYawRate.csv");
}