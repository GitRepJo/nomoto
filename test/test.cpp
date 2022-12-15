#include <catch2/catch_test_macros.hpp>

#include <nomoto_sim.hpp>


TEST_CASE( "Test the Nomoto model")
{
    
    NomotoSim exampleSim;

    NomotoSim::varSim varS;
    constNomoto constN;

    NomotoSim::resultNomoto resN;
    

    SECTION("read values should match expectation")
    {   
     
        // Read in values from file
        constN = exampleSim.readNomoto("./test_config.yaml");
        varS = exampleSim.readSimulation("./test_config.yaml");
    
        REQUIRE( constN.delta == 512332123.3212321);
        REQUIRE( varS.initX == 12312.123342123) ;
    }
    
    // Use Figure 3 of K.Nomoto 1956 On the steering qualities of ships in International shipbuilding progress
    // Small deviations because delta rudder angle is set directly to 15 degree instead of rising as described
    SECTION("Compare model with figure 3 K= 0.065 & T = 30")
    {   
        // Set back struct to values in definition
        constN = {};
        varS = {};

        constN.delta = 15.0;
        constN.K = 0.065;
        constN.T = 30; 
        varS.time = 100;
        varS.step = 0.1;
        varS.terminal_output = false;
        
        resN = exampleSim.runNomoto(constN,varS);
        
        int s_result = resN.yaw_rate.size();
        double end_yaw_rate = resN.yaw_rate.at(s_result-1);
        
        REQUIRE( (end_yaw_rate < 1.0) & (end_yaw_rate > 0.90) );
    }
    
    // Use Figure 3 of K.Nomoto 1956 On the steering qualities of ships in International shipbuilding progress 
    // Small deviations because delta rudder angle is set directly to 15 degree instead of rising as described
     SECTION("Compare model with figure 3 K= 0.005 & T = 50")
    {   
        // Set back struct to values in definition
        constN = {};
        varS = {};

        constN.delta = 15.0;
        constN.K = 0.05;
        constN.T = 50; 
        varS.time = 100;
        varS.step = 0.1;
        varS.terminal_output = false;
        
        resN = exampleSim.runNomoto(constN,varS);
        
        int s_result = resN.yaw_rate.size();
        double end_yaw_rate = resN.yaw_rate.at(s_result-1);
        
        REQUIRE( (end_yaw_rate < 0.7) & (end_yaw_rate > 0.60) );
    }

}
