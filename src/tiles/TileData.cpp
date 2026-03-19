#include "tiles/TileData.h"

namespace {
    constexpr TileType F = TileType::Field;
    constexpr TileType C = TileType::City;
    constexpr TileType R = TileType::Road;
    constexpr TileType M = TileType::Monastery;
}

const std::vector<TileData> ALL_TILES = {
    {
        "StartTile",
        { C, F, R, F },
        {  1, 0,  3,
           1, 2,  3,
           1, 2,  3 }
       },
       {
           "StraightRoad",
           { R, F, F },
           {  1, 0, 2,
              1, 0, 2,
              1, 0, 2 }
       },
       {
           "CurvedRoad",
           { R, F, F },
           {  1, 1, 1,
              0, 0, 1,
              2, 0, 1 }
       },
       {
           "Monastery",
           { F, M },
           {  0, 0, 0,
              0, 1, 0,
              0, 0, 0 }
       },
       {
           "CityOne",
           { C, F },
           {  0, 0, 0,
              1, 1, 1,
              1, 1, 1 }
       },
       {
           "CityTwo",
           { C, C, F, F },
           {  0, 0, 0,
              2, 2, 3,
              1, 1, 1 }
       },
       {
           "CityCorner",
           { C, F, F },
           {  0, 0, 0,
              1, 0, 0,
              1, 1, 2 }
       },
       {
           "FullCity",
           { C },
           {  0, 0, 0,
              0, 0, 0,
              0, 0, 0 }
       },
};