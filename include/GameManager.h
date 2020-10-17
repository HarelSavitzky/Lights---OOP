#pragma once
//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <queue>
#include "Text.h"

//--------------------GameManager Class definition --------------------
class GameManager
{
public:	
	//--------constructor&destructor------------
	GameManager(){};
	virtual ~GameManager() = default;

	//--------class functions------------
	void runGame();
	void openFile(std::ifstream& inputFile);
	void checkForCollision();
	void buildLevel(std::ifstream& inputFile);
	void updateDisplay(sf::RenderWindow& window);
	void handleEvents(sf::Event& event, sf::RenderWindow& window);
	void findNeighbors();
	void isComplete(sf::RenderWindow& window);

private:
	//--------class members------------
	Board m_currentLevel;	//board class member to operate board class
	std::vector<std::unique_ptr<Point>> m_points;	//saves all the vertices each level at a time
	Text m_text;	//Text class member to operate text class
	bool m_levelComplete = false;	//boolians to tell us if stage/game completed
	bool m_isLastStage = false;

};