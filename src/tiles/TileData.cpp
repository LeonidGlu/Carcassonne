#include "tiles/TileData.h"

namespace {
    constexpr TileType F = TileType::Field;
    constexpr TileType C = TileType::City;
    constexpr TileType R = TileType::Road;
    constexpr TileType M = TileType::Monastery;
    constexpr TileType X = TileType::Crossroad;
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
           { C, C, F },
           {  0, 0, 0,
              2, 2, 2,
              1, 1, 1 }
       },
       {
           "CityCorner",
           { C, F},
           {  0, 0, 0,
              1, 0, 0,
              1, 1, 0 }
       },
       {
           "FullCity",
           { C },
           {  0, 0, 0,
              0, 0, 0,
              0, 0, 0 }
       },
       {
           "Crossroad4",
           { R, R, R, R, F, F, F, F, X },
           {  4, 0, 5,
              3, 8, 1,
              7, 2, 6 }

       },
       {
           "Crossroad3",
           { R, R, R, F, F, F, X },
           { 3, 0, 4,
             1, 6, 2,
             5, 5, 5 }
       },
       {
           "Crossroad2",
           { R, R, F, F, X },
           { 2, 0, 3,
             1, 4, 3,
             3, 3, 3 }
       },
};