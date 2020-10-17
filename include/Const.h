#pragma once
//--------------------include Section --------------------
#include <SFML/Graphics.hpp>

//--------------------const Section --------------------
const int  MAX_DEVIATION = 30;
const int  LEVEL_ONE = 5;
const int  MAX_EDGES = 6;
const int  NEXT_LEVEL = 1;
const int  GAME_OVER = 0;
const int  BOARDER_GAP = 150;
const int  MIN_ROW_LENGTH = 3;
const int POINT_SIZE = 6;
const int EDGE_WIDTH = POINT_SIZE / 2;
const int EDGE_LENGTH = POINT_SIZE * 3;
const int  COL_GAP = (EDGE_LENGTH * 2) + POINT_SIZE * 1.9;
const int  ROW_GAP = (EDGE_LENGTH * 2) + EDGE_WIDTH * 1.8;
const int NUM_OF_MESSAGES = 2;
const int END_GAME_MESSSAGE = 1;
const int NEXT_LEVEL_MESSSAGE = 0;
const float STARTING_ANGLE = 180.f;
const float RIGHT_ROTATION = 60.f;
const float LEFT_ROTATION = -60.f;
const sf::Color LIGHTS_OFF = sf::Color::Red;
const sf::Color LIGHTS_ON = sf::Color::Yellow;
const sf::Color EDGE_COLOR = sf::Color::White;
const std::string CENTER_LINE_SIZE_AND_NUMBER_OF_VERTEX_DONT_FIT =
					"\nException throwed:\n total number of vertices"
					"for a level with a middle row as entered,\n"
					"dosent fit with the number of vertices counted";
const std::string INVALID_INPUT = "\nException throwed:\n invalid input\n";
const std::string ARGUMENTS_OVERLOAD = "\nException throwed:\n too much arguments\n";
const std::string ANGLES_OVERLOAD = "\nException throwed:\n too much angles\n";
const std::string SHORT_OF_ANGLES = "\nException throwed:\n not enaugh angles\n";
const std::string INVALID_ANGLE = "\nException throwed:\invalid angle\n";
const std::string INVALID_CENTER = "\nException throwed:\ninvalid center line size\n";
const std::string FILE_ERROR = "\nException throwed:\nCant open file\n";