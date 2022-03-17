#include "LightArray.h"

using namespace std;

using namespace  ChristmasLightsKata;


Lights::Lights():lights(NB_ROWS*NB_COLUMNS, 0), nbLightsOn(0)
{}

bool Lights::isOn(vector<int> p)
{
    return (getValue(p) > 0);
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
    setValue(p, 1);
}

void Lights::turnOn(vector<int> p0, vector<int> p1)
{
    setValue(p0, p1, 1);
}

void Lights::turnOff(vector<int> p)
{
    setValue(p, 0);
}

void Lights::turnOff(vector<int> p0, vector<int> p1)
{
    setValue(p0, p1, 0);
}

void Lights::toggle(vector<int> p)
{
    if (this->getValue(p) > 0)
    {
        this->setValue(p, 0);
    }
    else
    {
        this->setValue(p, 1);
    }
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

uint32_t Lights::nbOn()
{
    return nbLightsOn;
}

void Lights::setValue(vector<int> p, uint32_t value)
{
    if (value != this->getValue(p))
    {
        lights[p[0] + NB_ROWS*p[1]] = value;
        if (value == 0)
        {
            nbLightsOn --;
        }
        else 
        {
        nbLightsOn += value;
        }
        
    }
    
}

void Lights::setValue(vector<int> p0, vector<int> p1, uint32_t value)
{
    //Considering p0 is always smaller (both components) than p1

    for (auto i = p0[0];i <= p1[0]; i++)
    {
        for (auto j = p0[1];j <= p1[1]; j++)
        {
            setValue({i, j}, value);
        }
    }
}

uint32_t Lights::getValue(vector<int> p)
{
    return lights[p[0] + NB_ROWS*p[1]];
}

