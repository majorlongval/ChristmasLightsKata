#include "LightArray.h"

using namespace std;

using namespace  ChristmasLightsKata;


Lights::Lights():lights(NB_ROWS*NB_COLUMNS, 0)
{}

bool Lights::isOn(vector<int> p)
{
    return (getBrightness(p) > 0);
}

bool Lights::areOn(vector<int> p0, vector<int> p1)
{
    bool isOn = true;
    //Considering p0 is always smaller (both components) than p1
    for (auto i = p0[0];i <= p1[0]; i++)
    {
        for (auto j = p0[1];j <= p1[1]; j++)
        {
            isOn = isOn & this->isOn({i, j});
        }
    }
    return isOn;
}

void Lights::turnOn(vector<int> p)
{
    changeBrightness(p, 1);
}

void Lights::turnOn(vector<int> p0, vector<int> p1)
{
    changeBrightness(p0, p1, 1);
}

void Lights::turnOff(vector<int> p)
{
    changeBrightness(p, 0);
}

void Lights::turnOff(vector<int> p0, vector<int> p1)
{
    changeBrightness(p0, p1, 0);
}

void Lights::toggle(vector<int> p)
{
    this->changeBrightness(p, 2);
}

void Lights::toggle(vector<int> p0, vector<int> p1)
{
    for (auto i = p0[0];i <= p1[0]; i++)
    {
        for (auto j = p0[1];j <= p1[1]; j++)
        {
            toggle({i, j});
        }
    }
}

void Lights::changeBrightness(vector<int> p, uint32_t value)
{
    if (value == 0)
    {
        if (!this->isOn(p))
        {
            lights[p[0] + NB_ROWS*p[1]] --;
            totalBrightness --;
        }
    }
    else 
    {
        lights[p[0] + NB_ROWS*p[1]] += value;
        totalBrightness += value;
    }
    
}

void Lights::changeBrightness(vector<int> p0, vector<int> p1, uint32_t value)
{
    //Considering p0 is always smaller (both components) than p1

    for (auto i = p0[0];i <= p1[0]; i++)
    {
        for (auto j = p0[1];j <= p1[1]; j++)
        {
            changeBrightness({i, j}, value);
        }
    }
}

uint32_t Lights::getBrightness(vector<int> p)
{
    return lights[p[0] + NB_ROWS*p[1]];
}

