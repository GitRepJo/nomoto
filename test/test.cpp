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

        constN.delta =5.0;
        varS.initX == 0.0;
    }
    
    // Use Figure 3 of K.Nomoto 1956 On the steering qualities of ships in International shipbuilding progress 
    SECTION("Compare model with original publication approcimation in figure 3")
    {   
        // Set back struct to values in definition
        constN = {};
        varS = {};

        constN.delta = 15.0;
        constN.K = 0.065;
        constN.T = 50; 
        varS.time = 100;
        varS.step = 0.1;
        
        resN = exampleSim.runNomoto(constN,varS);
        
        int s_result = resN.yaw_rate.size();
        std::cout << "turn rate at last integration is:" << resN.yaw_rate.at(s_result-1);

    }
    
    

}
