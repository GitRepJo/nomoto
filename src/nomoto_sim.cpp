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


#include <nomoto_sim.hpp>
#include <nomoto_obs.hpp>

NomotoSim::NomotoSim()
{}

NomotoSim::~NomotoSim()
{}

NomotoSim::resultNomoto NomotoSim::runNomoto(constNomoto cN,NomotoSim::varSim vS)
{
    typedef boost::numeric::odeint::runge_kutta_dopri5< std::array< double, 1 >  > stepper_type;
    
    std::array<double,1> start_state1 = {vS.initYawRate};
    
    NomotoOde sim(cN);
    
    std::vector<std::array<double,1>> m_states;
    std::vector<double> m_times;
    
    SaveNomoto sav(m_states, m_times);
    
    boost::numeric::odeint::integrate_adaptive( make_controlled( 1E-12 , 1E-12 , stepper_type() ),
                        sim , start_state1 , 0.0 , vS.time , vS.step , sav );

    resultNomoto res;
    res = calcResult(vS,m_states,m_times);

    if (vS.terminal_output == true)
    {
        for (std::vector<double>::size_type i = 0; i < res.time.size(); i++)
        {
            double t = round(res.time.at(i)  *100)/100;
            double x = round(res.x_pos.at(i) *100)/100;
            double y = round(res.y_pos.at(i) *100)/100;
            double yaw = round(res.yaw.at(i) *100)/100;
            
            std::cout <<"t[sec]: "<< t <<" x[m]: "<< x <<" y[m]: "<< y <<" yaw[deg]: " << yaw << '\n' << "\n";
        } 
    }  

    return res;
}

NomotoSim::resultNomoto NomotoSim::calcResult(varSim vS, std::vector<std::array<double,1>> &states , std::vector< double > &times)
{
    NomotoSim::resultNomoto res;
    
    res.x_pos.push_back(vS.initX);
    res.y_pos.push_back(vS.initY);
    res.yaw.push_back(vS.initYaw);
    res.yaw_rate.push_back(vS.initYawRate);
    res.time.push_back(0);
    res.yaw_acc.push_back(0);

    double pi = 2*acos(0.0);
    std::vector<double> delta_time;

    for (std::vector<double>::size_type i = 1; i < states.size(); i++)
    {
        // Access first array element of vector of arrays "states" at position i. In this implementation, the 
        // array is of size 1 because the state array is of size 1 (only yaw rate).
        res.yaw_rate.push_back(states.at(i)[0]);

        res.time.push_back(times.at(i));

        double delta_time = res.time.at(i) - res.time.at(i-1);
        
        // yaw = (yaw rate of step * time of step) + previous yaw
        double yaw = res.yaw_rate.at(i) * delta_time + res.yaw.at(i-1);
        res.yaw.push_back(yaw);

         // yaw acceleration = (yaw rate of step - yaw rate of previous step) * time of step
        double yaw_acc = (res.yaw_rate.at(i) - res.yaw_rate.at(i-1)) * delta_time;
        res.yaw_acc.push_back(yaw_acc);

        double yaw_rad = yaw * pi / 180;
        
        // Position in x = cos(yaw in radians) * time of step * fixed velocity + previous positon
        double x_pos = cos(yaw_rad) * delta_time * vS.velocity; 
        res.x_pos.push_back(x_pos + res.x_pos.at(i-1)); 

        // Position in y = sin(yaw in radians) * time of step * fixed velocity + previous positon
        double y_pos = sin(yaw_rad) * delta_time * vS.velocity; 
        res.y_pos.push_back(y_pos+ res.y_pos.at(i-1)); 
    }

    return res;
}

NomotoSim::varSim NomotoSim::readSimulation(std::string simFile)
{
    NomotoSim::varSim var;

    YAML::Node config = YAML::LoadFile(simFile);

    var.step    = config["step"].as<double>(); 
    var.time    = config["time"].as<double>(); 
    var.initYaw = config["initYaw"].as<double>(); 
    var.initYawRate = config["initYawRate"].as<double>(); 
    var.initX = config["initX"].as<double>(); 
    var.initY = config["initY"].as<double>(); 
    var.velocity= config["velocity"].as<double>();
    var.terminal_output = config["terminal_output"].as<bool>();

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