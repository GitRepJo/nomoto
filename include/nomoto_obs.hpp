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

    void set (std::vector<std::array<double,1>> &states, std::vector<double> &times) 
    {
        m_states = &states;
        m_times = &times;
    };
    
    // Use vector of arrays to extend state vector of observer if required
    //SaveNomoto(std::vector<std::array<double,1>> &states, std::vector< double > &times ) : m_states( states ), m_times( times ) { }
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