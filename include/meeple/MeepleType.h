#pragma once
#include "tiles/TileType.h"
#include <iostream>

enum class MeepleType {
	Knight,
	Monk,
	Rogue,
	Farmer
};

inline std::ostream& operator<<(std::ostream& os, const MeepleType& type) {
	switch (type) {
	case MeepleType::Knight: os << "Knight"; break;
	case MeepleType::Monk: os << " Monk"; break;
	case MeepleType::Rogue: os << "Rogue"; break;
	case MeepleType::Farmer: os << "Farmer"; break;
	default: os << "Unknown";
	}
	return os;
}

inline MeepleType tileTypeToMeepleType(TileType type) {
	switch (type) {
	case TileType::City:       return MeepleType::Knight;
	case TileType::Road:       return MeepleType::Rogue;
	case TileType::Field:      return MeepleType::Farmer;
	case TileType::Monastery:  return MeepleType::Monk;
	default: throw std::invalid_argument("Cannot convert TileType to MeepleType");
	}
}