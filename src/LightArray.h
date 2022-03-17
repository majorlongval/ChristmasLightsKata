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
    bool areOn(std::vector<int> p0, std::vector<int> p1);
    void turnOn(std::vector<int> p);
    void turnOn(std::vector<int> p0, std::vector<int> p1);
    void turnOff(std::vector<int> p);
    void turnOff(std::vector<int> p0, std::vector<int> p1);
    void toggle(std::vector<int> p);
    void toggle(std::vector<int> p0, std::vector<int> p1);
    uint32_t getTotalBrightness();

private:
    std::vector<uint32_t> lights;
    void changeBrightness(std::vector<int> p, uint32_t value);
    void changeBrightness(std::vector<int> p0, std::vector<int> p1, uint32_t value);
    uint32_t getBrightness(std::vector<int> p);
    uint32_t totalBrightness;
};

}
