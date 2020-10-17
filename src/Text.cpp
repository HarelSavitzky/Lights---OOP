//--------------------include Section --------------------
#include "Text.h"

//---------------------buildMessages function --------------------------
/*function to build the messages of the end of a level or of the end of the game*/
void Text::buildMessages(sf::RenderWindow& window)
{
	m_font.loadFromFile("fontn.TTF");//load the font

	for (int i = 0; i < NUM_OF_MESSAGES; i++)			
	{
		sf::Text temp;
		temp.setFont(m_font);				//create both of the messages
		temp.setColor(sf::Color::Yellow);
		temp.setCharacterSize(60);
		temp.setOutlineThickness(10);
		if (i == NEXT_LEVEL_MESSSAGE)
			temp.setString("Level Complete");
		if (i == END_GAME_MESSSAGE)
			temp.setString("Game Over");
		temp.setPosition(sf::Vector2f(10, 10));
		m_messages.push_back(temp);
	}
}
//---------------------drawMessage function --------------------------
void Text::drawMessage(sf::RenderWindow& window, int message)
{
	window.draw(m_messages[message]);//print one of the messages according to the number of "message"
}