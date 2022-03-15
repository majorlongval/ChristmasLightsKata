#include "LightArray.h"

using namespace std;

using namespace  ChristmasLightsKata;


Lights::Lights():lights(NB_ROWS*NB_COLUMNS, 0){}

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
            vector<int> tmpPoint = {i, j};
            isOn = isOn & (this->getValue(tmpPoint) > 0);
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
            vector<int> tmpPoint = {i, j};
            toggle(tmpPoint);
        }
    }
}

uint32_t Lights::nbOn()
{
    uint32_t nbOn= 0;
    for (int i=0; i<NB_ROWS; i++)
    {
        for (int j=0; j<NB_COLUMNS; j++)
        {
            vector<int> tmpPoint = {i, j};
            if (this->isOn(tmpPoint))
            {
                nbOn++;
            }
        }
    }
    return nbOn;
}

void Lights::setValue(vector<int> p, uint32_t value)
{
    lights[p[0] + NB_ROWS*p[1]] = value;
}

void Lights::setValue(vector<int> p0, vector<int> p1, uint32_t value)
{
    //Considering p0 is always smaller (both components) than p1
    for (auto i = p0[0];i <= p1[0]; i++)
    {
        for (auto j = p0[1];j <= p1[1]; j++)
        {
            vector<int> tmp_point = {i, j};
            setValue(tmp_point, value);
        }
    }
}

uint32_t Lights::getValue(vector<int> p)
{
    return lights[p[0] + NB_ROWS*p[1]];
}

