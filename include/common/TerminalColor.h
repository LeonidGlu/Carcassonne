#pragma once
#include <string>


//namespace TerminalColor {
//    constexpr const char* RESET = "\033[0m";
//    constexpr const char* BOLD = "\033[1m";
//    constexpr const char* COLORS[] = {
//        "\033[91m", "\033[92m", "\033[93m",
//        "\033[94m", "\033[95m", "\033[96m"
//    };
//
//    inline std::string getPlayerColor(int playerIndex) {
//        return COLORS[playerIndex % 6];
//    }
//}

namespace TerminalColor {
	inline const std::string RESET = "\033[0m";
	inline const std::string BOLD = "\033[1m";
	inline const std::string COLORS[] = {
		"\033[91m", //0red city
		"\033[92m", //1green field
		"\033[93m", //2yellow road
		"\033[94m", //3blue monastery
		"\033[90m" //4gray crossroad
	};

	inline std::string getPlayerColor(int playerIndex) {
		return COLORS[playerIndex % 6];
	}

	inline std::string getSegmentColor(const Segment& seg) {
		switch (seg.type) {
		case TileType::City: return COLORS[0];
		case TileType::Field: return COLORS[1];
		case TileType::Road: return COLORS[2];
		case TileType::Monastery: return COLORS[3];
		case TileType::Crossroad: return COLORS[4];
		default: return RESET;
		}
	}
}