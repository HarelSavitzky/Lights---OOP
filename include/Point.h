#pragma once
//--------------------include Section --------------------
#include "Const.h"
#include <vector>
#include <SFML/Graphics.hpp>

//--------------------Point Class definition --------------------
class Point
{
public:
    //--------constructor&destructor------------
    Point() {};
    virtual ~Point() = default;
    Point(sf::Vector2f location, std::vector<int> angles, bool light);

    //--------class functions------------
    void draw(sf::RenderTarget& target) const;
    void click(sf::Vector2f location, float key);
    void rotate(float key);
    void setLight(bool light);

    //--------short functions------------
    void setPointStatus(bool value) { m_isPointChecked = value; };
    void newNeighbor(Point* newNeighbor){ m_neighbors.push_back(newNeighbor); };

    //--------get functions------------
    std::vector < std::unique_ptr <sf::RectangleShape>>& getEdges() { return m_edges; };
    std::unique_ptr<sf::CircleShape>& getPoint() { return m_point; }; //not all are const, because they cant be
    std::vector<Point*> getNeighbors() const { return m_neighbors; };
    bool getIfChecked() const { return m_isPointChecked; };
    bool isLight() const { return m_lightOn; };
    bool isCore() const { return m_isCore; };

private:
    //--------class members------------
    std::vector<Point*> m_neighbors;   //pointers to all the neighbors of a vertex
    std::unique_ptr<sf::CircleShape> m_point;   //a circle, in the point shape
    std::vector < std::unique_ptr <sf::RectangleShape>> m_edges;    //all the edges of a point
    int m_numOfEdges;   //number of edges of a point
    bool m_lightOn; //boolians to check if vertex is lightOn/isCore/ifChecked(in bfs)
    bool m_isCore;
    bool m_isPointChecked;

};
