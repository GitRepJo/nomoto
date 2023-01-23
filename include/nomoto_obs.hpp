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

#ifndef NOMOTO_OBS_HPP
#define NOMOTO_OBS_HPP

#include <eigen3/Eigen/Dense>
#include <vector>

/**
* @brief Functor to save the result of an integration with boost e.g. adaptive integration
* @param states std::vector<std::vector<double>> intermediate and result state(s) of integration
* @param times std::vector<double> Time that corresponds to according state
*/
class SaveNomoto
{   
public:
     /**
    * @brief Set parameters for observations
    * @param states vector of states (yaw rate)
    * @param times vector of integration steps
    * @return -
    * @details -
    */
    void set (std::vector<std::array<double,1>> &states, std::vector<double> &times) 
    {
        m_states = &states;
        m_times = &times;
    };
    
    /**
    * @brief Observe intermediate steps of odeint
    * @param x vector of arrays to save state vector derivative (which is in this case one (yaw rate)) 
    * @param t double time of integration step 
    * @return -
    * @details Pass by reference to allows observing the states outside of this function
    * Use vector of arrays to extend state vector of observer if required
    */
    void operator()( const std::array<double,1> &x, const double t )
    {    
        m_states->push_back(x);
        m_times->push_back(t);
    }
private:

    std::vector<std::array<double,1>> * m_states;
    std::vector<double> * m_times;
};

#endif //NOMOTO_OBS_HPP