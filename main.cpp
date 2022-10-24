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