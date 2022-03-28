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
    vector<vector<int>> lightCoordinates = 
    {
    {0, 0}, {0, 1}, {0, 2}, {0, 3},
    {1, 0}, {1, 1}, {1, 2}, {1, 3},
    {2, 0}, {2, 1}, {2, 2}, {2, 3},
    {3, 0}, {3, 1}, {3, 2}, {3, 3}
    };
    const bool TURNED_OFF = false;
    const bool TURNED_ON = true;

    void setLights(vector<vector<int>> lightGrid, bool state)
    {
        if (state)
        {
            for (vector<int> light: lightGrid)
            {
                lights.turnOn(light);
            }
        }
        else
        {
            for (vector<int> light: lightGrid)
            {
                lights.turnOff(light);
            }
        }

    }
    
    testing::AssertionResult isInExpectedState(vector<int> light, bool state)
    {
        if (lights.isOn(light) == state)
        {
            return testing::AssertionSuccess();
        }
        else
        {
            return testing::AssertionFailure()<< "light at coordinate " << vecOfInt2String(light) <<" was not in state " << state;
        } 
    }

    testing::AssertionResult lightsAreInExpectedState(vector<vector<int>>lightGrid, bool state) //LightsAreInTheExpectedState
    {
        vector<vector<int>> lightsInInvalidState;
        for (auto& light: lightGrid)
        {
            if (! isInExpectedState(light, state))
            {
                lightsInInvalidState.push_back(light);
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
            for (auto& light: lightsInInvalidState)
            {
                oss << " " << vecOfInt2String(light);
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

TEST_F(ChristmasLightsKataTester, turningOnALight_ShouldOnlyTurnThisOneOn)
{
    vector<vector<int>> lightsAround = {{0, 0}, {0, 1}, {0, 2},
                                        {1, 0},         {1, 2},
                                        {2, 0}, {2, 1}, {2, 2}};
    
    lights.turnOn({1, 2});

    EXPECT_TRUE(lights.isOn({1, 1}));
    EXPECT_TRUE(lightsAreInExpectedState(lightsAround, TURNED_OFF));
}
/*
TEST_F(ChristmasLightsKataTester, turningOffALight_ShouldOnlyTurnThisOneOff)
{
    vector<vector<int>> allLights =  {p44, p45, p46,
                                      p54, p55, p56,
                                      p64, p65, p66};
    setLights(allLights, 1);
    vector<vector<int>> lightsAround = {p44, p45, p46,
                                        p54,      p56,
                                        p64, p65, p66};
    
    lights.turnOff(p55);

    ASSERT_FALSE(lights.isOn(p55));
    lightsAreInExpectedState(lightsAround, TURNED_ON);
}

TEST_F(ChristmasLightsKataTester, canCheckManyLightsAtOnce)// check if lights around the array are still off
{
    vector<vector<int>> pointGroup =  {p44, p45, p46,
                                       p54, p55, p56,
                                       p64, p65, p66};
    lightsAreInExpectedState(pointGroup, false);
    setLights(pointGroup, 1);
    ASSERT_TRUE(lights.areOn(p44, p66));//p44 to p55
}

TEST_F(ChristmasLightsKataTester, canTurnOnManyLightsAtOnce)
{
    ASSERT_FALSE(lights.areOn(p44, p66));
    lights.turnOn(p44, p66);
    ASSERT_TRUE(lights.areOn(p44, p66));
}

TEST_F(ChristmasLightsKataTester, canTurnOffManyLightsAtOnce)
{
    lights.turnOn(p44, p66);
    ASSERT_TRUE(lights.areOn(p44, p66));
    lights.turnOff(p44, p66);
    ASSERT_FALSE(lights.areOn(p44, p66));
}

TEST_F(ChristmasLightsKataTester, singleToggle_ShouldSwitchOnAndOffALight)
{
    lights.toggle(p44);
    ASSERT_TRUE(lights.isOn(p44));

    lights.toggle(p44);
    ASSERT_FALSE(lights.isOn(p44));
}

TEST_F(ChristmasLightsKataTester, singleToggle_ShouldOnlyAffectSpecifiedLight)
{
    vector<vector<int>> unaffectedLights =  {p44, p45, p46,
                                             p54,      p56,
                                             p64, p65, p66};
    
    lights.toggle(p55);

    lightsAreInExpectedState(unaffectedLights, TURNED_OFF);
}

TEST_F(ChristmasLightsKataTester, multiToggle_ShouldSwitchOnAndOffSpecifiedLights)
{
    lights.toggle(p44, p55);
    ASSERT_TRUE(lights.areOn(p44, p55));

    lights.toggle(p44);
    ASSERT_FALSE(lights.isOn(p44));
}

TEST_F(ChristmasLightsKataTester, canToggleManyLights)
{
    vector<vector<int>> pointGroup1 = {p44, p45,
                                       p54
                                                    };
    vector<vector<int>> pointGroup2 = {
                                                 p56,
                                            p65, p66};
    ASSERT_FALSE(lights.areOn(p44, p66));
    lights.toggle(p44, p55);
    ASSERT_TRUE(lights.areOn(p44, p55));
    lights.toggle(p55, p66);
    lightsAreInExpectedState(pointGroup1, true);
    lightsAreInExpectedState(pointGroup2, true);
    ASSERT_FALSE(lights.isOn(p55));
}

TEST_F(ChristmasLightsKataTester, canCountHowManyAreOn)
{
    lights.turnOn(p44, p66); 
    ASSERT_EQ(lights.nbOn(), 9);
    lights.turnOff(p44, p55);
    ASSERT_EQ(lights.nbOn(), 5);
    lights.toggle(p54, p66);
    ASSERT_EQ(lights.nbOn(), 3);
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
*/
}
