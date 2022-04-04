#include "LightArray.h"

using namespace std;

using namespace  ChristmasLightsKata;


Lights::Lights():lights(NB_ROWS*NB_COLUMNS, 0), nbLightsOn(0)
{}

bool Lights::isOn(vector<int> p)
{
    return (getValue(p) > 0);
}

bool Lights::areOn(vector<int> fromLightPosition, vector<int> toLightPosition)
{
    bool isOn = true;
    //Considering p0 is always smaller (both components) than p1
    for (auto i = fromLightPosition[0];i <= toLightPosition[0]; i++)
    {
        for (auto j = fromLightPosition[1];j <= toLightPosition[1]; j++)
        {
            isOn = isOn & this->isOn({i, j});
        }
    }
    return isOn;
}

void Lights::turnOn(vector<int> lightPosition)
{
    setValue(lightPosition, 1);
}

void Lights::turnOn(vector<int> fromLightPosition, vector<int> toLightPosition)
{
    setValue(fromLightPosition, toLightPosition, 1);
}

void Lights::turnOff(vector<int> LightPosition)
{
    setValue(LightPosition, 0);
}

void Lights::turnOff(vector<int> fromLightPosition, vector<int> toLightPosition)
{
    setValue(fromLightPosition, toLightPosition, 0);
}

void Lights::toggle(vector<int> lightPosition)
{
    setValue(lightPosition,(int) !isOn(lightPosition));
}

void Lights::toggle(vector<int> fromLightPosition, vector<int> toLightPosition)
{
    for (auto i = fromLightPosition[0];i <= toLightPosition[0]; i++)
    {
        for (auto j = fromLightPosition[1];j <= toLightPosition[1]; j++)
        {
            toggle({i, j});
        }
    }
}

uint32_t Lights::nbOn()
{
    return nbLightsOn;
}

void Lights::setValue(vector<int> lightPosition, uint32_t value)
{
    if (value != this->getValue(lightPosition))
    {
        lights[lightPosition[0] + NB_ROWS*lightPosition[1]] = value;
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

void Lights::setValue(vector<int> fromLightPosition, vector<int> toLightPosition, uint32_t value)
{
    //Considering p0 is always smaller (both components) than p1

    for (auto i = fromLightPosition[0];i <= toLightPosition[0]; i++)
    {
        for (auto j = fromLightPosition[1];j <= toLightPosition[1]; j++)
        {
            setValue({i, j}, value);
        }
    }
}

uint32_t Lights::getValue(vector<int> lightPosition)
{
    return lights[lightPosition[0] + NB_ROWS*lightPosition[1]];
}

