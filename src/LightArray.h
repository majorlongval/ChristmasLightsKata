#pragma once

#include <cstdint>
#include <vector>


namespace ChristmasLightsKata {


class Lights
{
    static const int NB_ROWS = 1000;
    static const int NB_COLUMNS = 1000;
public:
    Lights();
    virtual ~Lights() = default;

    bool isOn(std::vector<int> p);
    bool areOn(std::vector<int> p0, std::vector<int> p1);//fromPoint toPoint
    void turnOn(std::vector<int> p);
    void turnOn(std::vector<int> p0, std::vector<int> p1);
    void turnOff(std::vector<int> p);
    void turnOff(std::vector<int> p0, std::vector<int> p1);
    void toggle(std::vector<int> p);
    void toggle(std::vector<int> p0, std::vector<int> p1);
    uint32_t nbOn();

private:
    std::vector<uint32_t> lights;
    void setValue(std::vector<int> p, uint32_t value);
    void setValue(std::vector<int> p0, std::vector<int> p1, uint32_t value);
    uint32_t getValue(std::vector<int> p);
    uint32_t nbLightsOn;
};

}
