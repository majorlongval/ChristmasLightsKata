#include "gtest.h"
#include "LightArray.h"

using namespace std;

using namespace ChristmasLightsKata;

namespace  {


class ChristmasLightsKataTester : public ::testing::Test
{
protected:
    ChristmasLightsKataTester(){}
    virtual ~ChristmasLightsKataTester(){}
    Lights lights;
    vector<int> p00 = {0, 0};//     HOW THE LIGHTS ARE DISPLAYED
    vector<int> p44 = {4, 4};//
    vector<int> p45 = {4, 5};//     *p00
    vector<int> p46 = {4, 6};//
    vector<int> p54 = {5, 4};//               *p44 *p45 *p46
    vector<int> p55 = {5, 5};//               *p54 *p55 *p56
    vector<int> p56 = {5, 6};//               *p64 *p65 *p66
    vector<int> p64 = {6, 4};//
    vector<int> p65 = {6, 5};//
    vector<int> p66 = {6, 6};//


    void setValueOfPointGroup(vector<vector<int>> pointGroup, int value)
    {

        for (vector<int> point: pointGroup)
        {
            if (value>0)
            {
                lights.turnOn(point);
            }
            else
            {
                lights.turnOff(point);
            }

        }
    }

    bool PointGroupAreSame(vector<vector<int>> pointGroup, bool state)
    {
        bool areAllSame = true;
        for (auto& point: pointGroup)
        {
            if(lights.isOn(point) != state)
            {
                areAllSame = false;

            }
        }
        return areAllSame;
    }
};

TEST_F(ChristmasLightsKataTester, canTurnOnOneLight)
{
    ASSERT_FALSE(lights.isOn(p00));
    lights.turnOn(p00);
    ASSERT_TRUE(lights.isOn(p00));
    lights.turnOn(p00);
    ASSERT_TRUE(lights.isOn(p00));
}

TEST_F(ChristmasLightsKataTester, canTurnOffOneLight)
{
    lights.turnOn(p00);
    lights.turnOff(p00);
    ASSERT_FALSE(lights.isOn(p00));
}

TEST_F(ChristmasLightsKataTester, turningOnALight_ShouldOnlyTurnThisOneOn)
{
    lights.turnOn(p55);
    vector<vector<int>> pointGroup = {p44, p45, p46,
                                      p54,      p56,
                                      p64, p65, p66};
    ASSERT_TRUE(lights.isOn(p55));
    ASSERT_TRUE(PointGroupAreSame(pointGroup, false));
}

TEST_F(ChristmasLightsKataTester, turningOffALight_ShouldOnlyTurnThisOneOff)
{
    vector<vector<int>> pointGroup =  {p44, p45, p46,
                                       p54, p55, p56,
                                       p64, p65, p66};
    vector<vector<int>> pointGroup2 = {p44, p45, p46,
                                       p54,      p56,
                                       p64, p65, p66};
    setValueOfPointGroup(pointGroup, 1);
    lights.turnOff(p55);
    ASSERT_FALSE(lights.isOn(p55));
    ASSERT_TRUE(PointGroupAreSame(pointGroup2, true));
}

TEST_F(ChristmasLightsKataTester, canCheckManyLightsAtOnce)
{

    vector<vector<int>> pointGroup =  {p44, p45, p46,
                                       p54, p55, p56,
                                       p64, p65, p66};
    ASSERT_TRUE(PointGroupAreSame(pointGroup, false));
    setValueOfPointGroup(pointGroup, 1);
    ASSERT_TRUE(lights.areOn(p44, p66));
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

TEST_F(ChristmasLightsKataTester, canToggleOneLight)
{
    lights.toggle(p00);
    ASSERT_TRUE(lights.isOn(p00));
    lights.turnOff(p00);
    ASSERT_TRUE(lights.isOn(p00));
    lights.turnOff(p00);
    ASSERT_FALSE(lights.isOn(p00));
}

TEST_F(ChristmasLightsKataTester, brightnessCantBeLowerThanZero)
{
    lights.turnOff(p00);
    lights.turnOff(p00);
    lights.turnOn(p00);
    ASSERT_TRUE(lights.isOn(p00));
}

TEST_F(ChristmasLightsKataTester, canGetTheTotalBrightness)
{
    lights.turnOn(p00);
    ASSERT_EQ(lights.getTotalBrightness(), 1);
    lights.turnOn({5, 5}, {9, 9});
    ASSERT_EQ(lights.getTotalBrightness(), 26);
    lights.turnOff({5, 5}, {9, 9});
    lights.turnOn({0, 0}, {999, 999});
    ASSERT_EQ(lights.getTotalBrightness(), 1000001);
    lights.turnOff({0, 0}, {999, 999});
    lights.toggle({0, 0}, {999, 999});
    ASSERT_EQ(lights.getTotalBrightness(), 2000001);
}

TEST_F(ChristmasLightsKataTester, totalBrightnessFromSantasInstructions)
{
    lights.turnOn({887,9}, {959, 629});
    lights.turnOn({454, 398}, {844, 448});
    lights.turnOff({539, 243}, {559, 965});
    lights.turnOff({370, 819}, {676, 868});
    lights.turnOff({145, 40}, {370, 997});
    lights.turnOff({301, 3}, {808, 453});
    lights.turnOn({351, 678}, {951, 908});
    lights.toggle({720, 196}, {897, 994});
    lights.toggle({831, 394}, {904, 860});
    ASSERT_EQ(lights.getTotalBrightness(), 539560);
}
}
