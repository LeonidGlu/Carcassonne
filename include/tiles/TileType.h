#pragma once
#include <iostream>

enum class TileType {
	Road,
	City,
	Monastery,
	Field,
};

inline std::ostream& operator<<(std::ostream& os, const TileType& type) {
    switch (type) {
    case TileType::Road:      os << "Road"; break;
    case TileType::City:      os << "City"; break;
    case TileType::Monastery: os << "Monastery"; break;
    case TileType::Field:     os << "Field"; break;
    default:                  os << "Unknown";
    }
    return os;
}