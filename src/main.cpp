#include "gtest.h"
#include <string>
#include <sstream>

#include "LightArray.h"
#include "gtest/gtest.h"

using namespace std;

using namespace ChristmasLightsKata;

namespace  {

class ChristmasLightsKataTester : public ::testing::Test
{
protected:

    ChristmasLightsKataTester(){}
    virtual ~ChristmasLightsKataTester(){}
    Lights lights;
    vector<vector<int>> testLightsPositions =
    {
            {1, 1}, {1, 2},
            {2, 1}, {2, 2}
    };
    vector<vector<int>> aroundTestLightsPositions = 
    {
    {0, 0}, {0, 1}, {0, 2}, {0, 3},
    {1, 0},                 {1, 3},
    {2, 0},                 {2, 3},
    {3, 0}, {3, 1}, {3, 2}, {3, 3}
    };
    const bool TURNED_OFF = false;
    const bool TURNED_ON = true;

    void setLights(vector<vector<int>> lightPositionGrid, bool state)
    {
        if (state)
        {
            for (auto& lightPosition: lightPositionGrid)
            {
                lights.turnOn(lightPosition);
            }
        }
        else
        {
            for (auto& lightPosition: lightPositionGrid)
            {
                lights.turnOff(lightPosition);
            }
        }

    }
    
    testing::AssertionResult isInExpectedState(vector<int> lightPosition, bool state)
    {
        if (lights.isOn(lightPosition) == state)
        {
            return testing::AssertionSuccess();
        }
        else
        {
            return testing::AssertionFailure()<< "light at coordinate " << 
                                              vecOfInt2String(lightPosition) <<
                                              " was not in state " << state;
        } 
    }

    testing::AssertionResult lightsAreInExpectedState(vector<vector<int>>lightPositionGrid, bool state) //LightsAreInTheExpectedState
    {
        vector<vector<int>> lightsInInvalidState;
        for (auto& lightPosition: lightPositionGrid)
        {
            if (! isInExpectedState(lightPosition, state))
            {
                lightsInInvalidState.push_back(lightPosition);
            }
            
        }
        if (lightsInInvalidState.empty())
        {
            return testing::AssertionSuccess();
        }
        else 
        {
            ostringstream oss;
            oss << "lights are invalid at coordinates:";
            for (auto& lightPosition: lightsInInvalidState)
            {
                oss << " " << vecOfInt2String(lightPosition);
            }
            return testing::AssertionFailure() << oss.str();
        }
        
    }
    

    string vecOfInt2String(vector<int> inputVector)
    {//Found in https://stackoverflow.com/questions/2518979/how-to-transform-a-vectorint-into-a-string
        stringstream tmpStringStream;
        copy( inputVector.begin(), inputVector.end(), ostream_iterator<int>(tmpStringStream, ","));

        string outputString = tmpStringStream.str();

        outputString = "{" +outputString.substr(0, outputString.length()-1) + "}";  // get rid of the trailing space
        return outputString;
    }

};

TEST_F(ChristmasLightsKataTester, canTurnOnOneLight)
{
    lights.turnOn({0, 0});

    EXPECT_TRUE(isInExpectedState({0, 0}, TURNED_ON));
}

TEST_F(ChristmasLightsKataTester, canTurnOffOneLight)
{
    
    lights.turnOn({0, 0});

    lights.turnOff({0, 0});

    ASSERT_FALSE(lights.isOn({0, 0}));
}

TEST_F(ChristmasLightsKataTester, canCheckIfLightIsOn)
{
    EXPECT_FALSE(lights.isOn({0, 0}));
    lights.turnOn({0, 0});
    EXPECT_TRUE(lights.isOn({0, 0}));
}

TEST_F(ChristmasLightsKataTester, canCheckManyLightsAtOnce)
{ 
    EXPECT_TRUE(lightsAreInExpectedState(testLightsPositions, TURNED_OFF));

    lights.turnOn({1, 1}, {2, 2});

    EXPECT_TRUE(lightsAreInExpectedState(testLightsPositions, TURNED_ON));    
}

TEST_F(ChristmasLightsKataTester, turningOnALight_ShouldOnlyTurnThisOneOn)
{
    vector<vector<int>> lightsAround = {{0, 0}, {0, 1}, {0, 2},
                                        {1, 0},         {1, 2},
                                        {2, 0}, {2, 1}, {2, 2}};
    
    lights.turnOn({1, 1});

    EXPECT_TRUE(lights.isOn({1, 1}));
    EXPECT_TRUE(lightsAreInExpectedState(lightsAround, TURNED_OFF));
}

TEST_F(ChristmasLightsKataTester, turningOffALight_ShouldOnlyTurnThisOneOff)
{
    vector<vector<int>> lightsAround = {{0, 0}, {0, 1}, {0, 2},
                                        {1, 0},         {1, 2},
                                        {2, 0}, {2, 1}, {2, 2}};
    lights.turnOn({0, 0}, {2, 2});

    lights.turnOff({1, 1});

    EXPECT_TRUE(isInExpectedState({1, 1}, TURNED_OFF));
    EXPECT_TRUE(lightsAreInExpectedState(lightsAround, TURNED_ON));
}

TEST_F(ChristmasLightsKataTester, canTurnOnManyLightsAtOnce)   
{
    vector<vector<int>> lightGrid = {{1, 1}, {1, 2},
                                     {2, 1}, {2, 2}};

    lights.turnOn({1, 1}, {2, 2});

    EXPECT_TRUE(lights.areOn({1, 1}, {2, 2}));
}

TEST_F(ChristmasLightsKataTester, turningOnSomeLights_ShouldOnlyTurnThoseOn)
{
    lights.turnOn({1, 1}, {2, 2});

    EXPECT_TRUE(lightsAreInExpectedState(aroundTestLightsPositions, TURNED_OFF));
}

TEST_F(ChristmasLightsKataTester, turningOffSomeLights_ShouldOnlyTurnThoseOff)
{
    lights.turnOn({0, 0}, {3, 3});

    lights.turnOff({1, 1}, {2, 2});

    EXPECT_TRUE(lightsAreInExpectedState(aroundTestLightsPositions, TURNED_ON));
}

TEST_F(ChristmasLightsKataTester, canToggleASingleLight)
{
    lights.toggle({1, 1});
    ASSERT_TRUE(isInExpectedState({1, 1}, TURNED_ON));
    
    lights.toggle({1, 1});
    ASSERT_TRUE(isInExpectedState({1, 1}, TURNED_OFF));
}

TEST_F(ChristmasLightsKataTester, canToggleManyLightsAtOnce)
{
    lights.toggle({1, 1}, {2, 2});
    ASSERT_TRUE(lightsAreInExpectedState({{1,1}, {1, 2}, {2, 1}, {2, 2}}, TURNED_ON));

    lights.toggle({1, 1}, {2, 2});
    ASSERT_TRUE(lightsAreInExpectedState({{1,1}, {1, 2}, {2, 1}, {2, 2}}, TURNED_OFF));

}

TEST_F(ChristmasLightsKataTester, togglingManyLights_ShouldOnlyToggleTheseLights)
{

    lights.toggle({1, 1}, {2, 2});

    ASSERT_TRUE(lightsAreInExpectedState({{1, 1}, {1, 2}, {2, 1}, {2, 2}}, TURNED_ON)); 
    ASSERT_TRUE(lightsAreInExpectedState(aroundTestLightsPositions, TURNED_OFF));

    lights.toggle({1, 1}, {2, 2});
    
    ASSERT_TRUE(lightsAreInExpectedState({{1,1}, {1, 2}, {2, 1}, {2, 2}}, TURNED_OFF));
    ASSERT_TRUE(lightsAreInExpectedState(aroundTestLightsPositions, TURNED_OFF));
}

TEST_F(ChristmasLightsKataTester, canCountHowManyAreOn)
{
    lights.turnOn({1, 1}, {2, 2}); 
    ASSERT_EQ(lights.nbOn(), 4);
    lights.turnOff({2, 2});
    ASSERT_EQ(lights.nbOn(), 3);
    lights.toggle({1, 1}, {2, 2});
    ASSERT_EQ(lights.nbOn(), 1);
}

TEST_F(ChristmasLightsKataTester, phase1TestValidation)
{
    lights.turnOn({887, 9}, {959,629});
    lights.turnOn({454,398}, {844,448});
    lights.turnOff({539,243}, {559,965});
    lights.turnOff({370,819}, {676,868});
    lights.turnOff({145,40}, {370,997});
    lights.turnOff({301,3}, {808,453});
    lights.turnOn({351,678}, {951,908});
    lights.toggle({720,196}, {897,994});
    lights.toggle({831,394}, {904,860});
    ASSERT_EQ(lights.nbOn(), 230022);
}

}
/*


*/

