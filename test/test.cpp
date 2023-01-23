#include <catch2/catch_test_macros.hpp>

#include <nomoto_sim.hpp>


TEST_CASE( "Test the Nomoto model")
{
    
    NomotoSim exampleSim("./test_config.yaml","./test_config.yaml");

    NomotoSim::resultNomoto resN;
    

    SECTION("read values should match expectation")
    {      
        REQUIRE( exampleSim.cN.delta == 512332123.3212321);
        REQUIRE( exampleSim.vS.initX == 12312.123342123) ;
    }
    
    // Use Figure 3 of K.Nomoto 1956 On the steering qualities of ships in International shipbuilding progress
    // Small deviations because delta rudder angle is set directly to 15 degree instead of rising as described
    SECTION("Compare model with figure 3 K= 0.065 & T = 30")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = 15.0;
        exampleSim.cN.K = 0.065;
        exampleSim.cN.T = 30; 
        exampleSim.vS.time = 100;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.terminal_output = false;
        
        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.yaw_rate.size();
        double end_yaw_rate = resN.yaw_rate.at(s_result-1);
        
        REQUIRE( (end_yaw_rate < 1.0) & (end_yaw_rate > 0.90) );
    }
    
    // Use Figure 3 of K.Nomoto 1956 On the steering qualities of ships in International shipbuilding progress 
    // Small deviations because delta rudder angle is set directly to 15 degree instead of rising as described
     SECTION("Compare model with figure 3 K= 0.005 & T = 50")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = 15.0;
        exampleSim.cN.K = 0.05;
        exampleSim.cN.T = 50; 
        exampleSim.vS.time = 100;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.terminal_output = false;
        
        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.yaw_rate.size();
        double end_yaw_rate = resN.yaw_rate.at(s_result-1); 
        
        REQUIRE( (end_yaw_rate < 0.7) & (end_yaw_rate > 0.60) );
    }
    

    SECTION("position after 1 second and rudder angle 0 with constant velocity")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = 0.0;
        exampleSim.cN.K = 0.5;
        exampleSim.cN.T = 50; 
        exampleSim.vS.time = 1;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.velocity = 15;
        exampleSim.vS.terminal_output = false;

        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.x_pos.size();

        // Round because of floating point errors
        double end_pos_x = round( resN.x_pos.at(s_result-1) * 100 ) / 100; 
        double end_pos_y = round( resN.y_pos.at(s_result-1) * 100 ) / 100; 
        
        REQUIRE(end_pos_x == 15);
        REQUIRE(end_pos_y == 0.0);
    }

       SECTION("position after 1 second and rudder angle 0 with constant velocity and initial heading to 90 degree ")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = 0.0;
        exampleSim.cN.K = 0.5;
        exampleSim.cN.T = 50.0; 
        exampleSim.vS.time = 1.0;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.velocity = 15.0;
        exampleSim.vS.initYaw = 90.0;
        exampleSim.vS.terminal_output = false;

        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.x_pos.size();

        // Round because of floating point errors
        double end_pos_x = round( resN.x_pos.at(s_result-1) * 100 ) / 100; 
        double end_pos_y = round( resN.y_pos.at(s_result-1) * 100 ) / 100; 
        
        REQUIRE(end_pos_x == 0.0);
        REQUIRE(end_pos_y == 15.0);
    }

    SECTION("yaw angle has to be in positive x,y section for positive rudder deflection")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = 30.0;
        exampleSim.cN.K = 0.5;
        exampleSim.cN.T = 50.0; 
        exampleSim.vS.time = 1.0;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.velocity = 15.0;
        exampleSim.vS.initYaw = 0.0;
        exampleSim.vS.terminal_output = false;

        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.x_pos.size();

        // Round because of floating point errors
        double yaw = round( resN.yaw.at(s_result-1) * 100 ) / 100; 
    
        REQUIRE((yaw > 0) & (yaw < 90 ));
    }

    SECTION("yaw angle has to be in negative x,y section for negative rudder deflection")
    {   
        // Set back struct to values in definition
        exampleSim.cN = {};
        exampleSim.vS = {};

        exampleSim.cN.delta = -30.0;
        exampleSim.cN.K = 0.5;
        exampleSim.cN.T = 50.0; 
        exampleSim.vS.time = 1.0;
        exampleSim.vS.step = 0.1;
        exampleSim.vS.velocity = 15.0;
        exampleSim.vS.initYaw = 0.0;
        exampleSim.vS.terminal_output = false;

        exampleSim.sim.set(exampleSim.cN);
        
        resN = exampleSim.runNomoto();
        
        int s_result = resN.x_pos.size();

        // Round because of floating point errors
        double yaw = round( resN.yaw.at(s_result-1) * 100 ) / 100; 
    
        REQUIRE((yaw < 0) & (yaw > -90 ));
    }


}

