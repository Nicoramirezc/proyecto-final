#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Vehicle.h"
#include "Passenger.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

struct LevelData {
    int width = 0, height = 0;
    int numZones = 0;
    vector<shared_ptr<Vehicle>> vehicles;
    vector<Passenger> passengers;
};

class LevelLoader
{
public:
    static bool load(const string& filename, LevelData& data);
};

#endif