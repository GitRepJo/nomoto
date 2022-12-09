
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

#include <nomoto_sim.hpp>

NomotoSim::NomotoSim()
{}

NomotoSim::~NomotoSim()
{}

void NomotoSim::runNomoto(constNomoto cN,NomotoSim::varSim vS)
{
    typedef boost::numeric::odeint::runge_kutta_dopri5< std::array< double, 1 >  > stepper_type;
    
    std::array<double,1> start_state1 = {vS.yawRate};
    
    NomotoOde sim(cN);
    
    boost::numeric::odeint::integrate_adaptive( make_controlled( 1E-12 , 1E-12 , stepper_type() ),
                        sim , start_state1 , 0.0 , vS.time , vS.step , write_nomoto );
}

NomotoSim::varSim NomotoSim::readSimulation(std::string simFile)
{
    NomotoSim::varSim var;

    YAML::Node config = YAML::LoadFile(simFile);

    var.step    = config["step"].as<double>(); 
    var.time    = config["time"].as<double>(); 
    var.yawRate = config["yawRate"].as<double>(); 
    
    return var;
}

constNomoto NomotoSim::readNomoto(std::string nomotoFile)
{
    constNomoto con;
    
    YAML::Node config = YAML::LoadFile(nomotoFile);

    con.K = config["K"].as<double>();
    con.T = config["T"].as<double>();
    con.delta = config["delta"].as<double>();

    return con;
}