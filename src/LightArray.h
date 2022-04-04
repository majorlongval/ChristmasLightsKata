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

    void turnOn(std::vector<int> lightPosition);
    void turnOn(std::vector<int> fromLightPosition, 
                std::vector<int> toLightPosition);
    void turnOff(std::vector<int> lightPosition);
    void turnOff(std::vector<int> fromLightPosition, 
                 std::vector<int> toLightPosition);
    void toggle(std::vector<int> lightposition);
    void toggle(std::vector<int> fromLightPosition, 
                std::vector<int> toLightPosition);
    bool isOn(std::vector<int> lightPosition);
    bool areOn(std::vector<int> fromLightPosition, std::vector<int> toLightPosition);
    uint32_t nbOn();

private:
    std::vector<uint32_t> lights;
    void setValue(std::vector<int> lightPosition, uint32_t value);
    void setValue(std::vector<int> fromLightPosition, std::vector<int> toLightPosition, uint32_t value);
    uint32_t getValue(std::vector<int> lightPosition);
    uint32_t nbLightsOn;
};

}
