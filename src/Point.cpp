//--------------------include Section --------------------
#include "Point.h"

//---------------------Point Constructor --------------------------
Point::Point(sf::Vector2f location, std::vector<int> angles, bool isCore)
{
	m_point = std::make_unique <sf::CircleShape>(POINT_SIZE);	//create the point
	m_point->setOrigin(m_point->getRadius(), m_point->getRadius());
	m_point->setPosition(location);
	m_point->setFillColor(sf::Color::Red);						//initialize it
	m_lightOn = isCore;
	m_isCore = isCore;
	m_isPointChecked = false;
	if (isCore)				//if its the core
	{
		m_point->setFillColor(sf::Color::Yellow);
		m_isPointChecked = true;
	}
	for (auto i = 0; i < angles.size(); ++i)	//create all the edges of a point
	{
		m_edges.emplace_back(std::make_unique <sf::RectangleShape>());
		m_edges[i]->setSize({ EDGE_WIDTH, EDGE_LENGTH });
		m_edges[i]->setFillColor(sf::Color::White);
		m_edges[i]->setOrigin(m_edges[i]->getSize().x / 2, -m_point->getRadius());
		m_edges[i]->setPosition(m_point->getPosition());
		m_edges[i]->setRotation(STARTING_ANGLE + angles[i]);	//use the angles entered from file
	}
}

//---------------------setLight function --------------------------
void Point::setLight(bool light)
{
	if (light)			//function to set the light of a vertex on and off
	{
		m_lightOn = true;
		m_point->setFillColor(sf::Color::Yellow);
	}
	else if(!this->isCore())	//if its the core, never turn off
	{
		m_lightOn = false;
		m_point->setFillColor(sf::Color::Red);
	}
}

//---------------------draw function --------------------------
void Point::draw(sf::RenderTarget& target) const
{
	target.draw(*m_point);	//function to draw the point object - circle + rectangles
	for (const auto& e : m_edges)
		target.draw(*e);
}

//---------------------click function --------------------------
void Point::click(sf::Vector2f location, float key)
{										//if we clicked on a point, rotate it
	if (m_point->getGlobalBounds().contains(location))
		rotate(key);
}
//---------------------rotate function --------------------------
void Point::rotate(float key)
{
	auto ROTATION = key;	//function to rotate the edges
	for (auto& e : m_edges)	//according to key pressed
		e->rotate(ROTATION);
}