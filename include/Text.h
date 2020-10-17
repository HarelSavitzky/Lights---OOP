#pragma once
//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Const.h"

//--------------------Text Class definition --------------------
class Text
{
public:
	//--------constructor&destructor------------
	Text() {};
	virtual ~Text() = default;

	//--------class functions------------
	void drawMessage(sf::RenderWindow& window, int message);
	void buildMessages(sf::RenderWindow& window);

private:
	//--------class members------------
	std::vector<sf::Text> m_messages;//saves the messages
	sf::Font m_font; //saves the font
};