//--------------------include Section --------------------
#include <GameManager.h>

//---------------------runGame function --------------------------
void GameManager::runGame()
{
	auto window = sf::RenderWindow(sf::VideoMode(1000, 1000), "Lights - Harel_Savitzky");
	std::ifstream inputFile;

	m_text.buildMessages(window);	//build text messgaes

	openFile(inputFile);    //open levels file

	while (window.isOpen())
	{
		buildLevel(inputFile);  //read stages

		updateDisplay(window);  //display&update game
		if (m_isLastStage && m_levelComplete)
			break;		//check if we completed the game

		if (auto event = sf::Event{}; window.waitEvent(event))
			handleEvents(event, window);                //handle events (mouse clicks)

		checkForCollision(); //handle collision between edges
	}
	window.close();
	inputFile.close();  //close window&file
}

//---------------------isComplete function --------------------------
void GameManager::isComplete(sf::RenderWindow& window)
{
	for (auto& point : m_points) //if there is a light off - return
		if (!point->isLight())	//if not, the stage is completed
			return;				//keep on going in the function

	if(m_isLastStage)	//if the game is over display a message
		m_text.drawMessage(window, END_GAME_MESSSAGE);
	else                 //if the level is over display a message
		m_text.drawMessage(window, NEXT_LEVEL_MESSSAGE);

	window.display();
	_sleep(1500);	//give time for display
	m_levelComplete = true;//mark the level is completed
}

//---------------------updateDisplay function --------------------------
void GameManager::updateDisplay(sf::RenderWindow& window)
{
	window.clear(); //clear the window                         

	for (const auto& p : m_points)  //draw the graph
		p->draw(window);

	isComplete(window); //check if completed

	window.display();     
	window.clear();	//makes a better display in end of level			
}
//---------------------findNeighbors function --------------------------
/*function to calculate the neighbors of each point - on runtime.
we will run on the points, compare it to the others, and will see wich ones
fit to be the neighbors - using the positions of each one, and comparing the 
(x,y) values of them*/
void GameManager::findNeighbors()
{
	for (auto& point1 : m_points)	//take one point
	{
		auto point1Index = point1->getPoint()->getPosition();
		for (auto& point2 : m_points)	//take all the other points to compare with the first
		{
			auto point2Index = point2->getPoint()->getPosition();

			if (point1Index == point2Index)	//if its the same point, continue
				continue;

			if (point1Index.y == point2Index.y &&	//check horizpntal neighbors
				abs(point1Index.x - point2Index.x) == COL_GAP)
				point1->newNeighbor(point2.get());	//if its a neighbor, save him

			else if (abs(point1Index.y - point2Index.y) == ROW_GAP &&//check diagonal neighbors
				abs(point1Index.x - point2Index.x) < MAX_DEVIATION)
				point1->newNeighbor(point2.get()); //if its a neighbor, save him
		}
	}
}
//---------------------handleEvents function --------------------------
/*function to handle the game events - wich means mouse pressings on the vertices
or closing the game window*/
void GameManager::handleEvents(sf::Event& event, sf::RenderWindow& window)
{
	switch (event.type)
	{
	case sf::Event::Closed: //close the window button
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
		const auto location = window.mapPixelToCoords({ //mouse click handle
			event.mouseButton.x, event.mouseButton.y });//validate press location

		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Right:			//operate left click
			for (auto& p : m_points)
				p->click(location, LEFT_ROTATION);
			break;

		case sf::Mouse::Button::Left:			//operate right click
			for (auto& p : m_points)
				p->click(location, RIGHT_ROTATION);
			break;
		}
	}
}
//---------------------buildLevel function --------------------------
/*function to build the levels for  the game - building each level at a time
reading another one only after level complete!; this function is calling 
the read from file function, also calling to the build board function after that,
finding the neighbors and initialize relevant variables*/
void GameManager::buildLevel(std::ifstream& inputFile)
{
	static int levelNumber = LEVEL_ONE;
			//read only 'if' its the first level OR if a level is complete AND its not the last level
	if ((m_levelComplete || levelNumber == LEVEL_ONE) && (!m_isLastStage))
	{
		m_currentLevel.readStagesFromFile(inputFile);	//read stage from file
		if (m_currentLevel.isEof())
			m_isLastStage = true;	//if its eof, we are on the last stage
		m_points = m_currentLevel.buildBoard(m_currentLevel.getRowSize());	//build the board
		findNeighbors();			//find the neighbors
		levelNumber = NEXT_LEVEL; //have to change from first level
		m_levelComplete = false;  //also this, so we wont read a level without finishing one
	}
}
//---------------------checkForCollision function --------------------------
/*function to check for collision using BFS algorithm, the funciton will save in a queue
the vertices and will check them with their neighbors according to the algorithm, we will check
if the edges intersects using the intersect function of sfml and turn the lights on/off according to it*/
void GameManager::checkForCollision()
{
	std::queue<Point*> vertexQueue;
	for (auto& point : m_points)
		if (point->isCore())	//check if this is the core vertex, otherwise turn it off
		{
			Point* p = static_cast<Point*>(point.get());
			vertexQueue.push(p);	//start with the core vertex
		}
		else
		{
			point->setLight(false);
			point->setPointStatus(false);
		}
	auto currentElement = vertexQueue.front();	//each element to check
	while (!vertexQueue.empty())
	{
		currentElement = vertexQueue.front();
		for (int i = 0; i < currentElement->getEdges().size(); i++)	//run on the edges of the currentElement
		{
			auto endSearch = false;
			for (int j = 0; (j < currentElement->getNeighbors().size()) //run on the neighbors of the currentElement
				&& (!endSearch); j++)
			{
				if (currentElement->getNeighbors()[j]->getIfChecked())	//see if the vertex is checked, if so, skip on it
					continue;
				for (int z = 0; (z < currentElement->getNeighbors()[j]->getEdges().size())	//run on the edges of the current neighbor
					&& (!endSearch); z++)
				{
					if (currentElement->getEdges()[i]->getGlobalBounds().intersects(
						currentElement->getNeighbors()[j]->getEdges()[z]->getGlobalBounds()))
					{
						vertexQueue.push(currentElement->getNeighbors()[j]);//if edges intersect, put on queue, and light it
						currentElement->getNeighbors()[j]->setLight(true);
						currentElement->getNeighbors()[j]->setPointStatus(true);
						endSearch = true;
					}
				}
			}
		}
		vertexQueue.pop();
	}
}
//---------------------openFile function --------------------------
void GameManager::openFile(std::ifstream& inputFile)
{
	inputFile.open("levels.txt");				//openes the levels file, if error ->throws exception

	if (!inputFile.is_open())				//if the file dosent open throw exception
		throw std::runtime_error("\nException throwed:\nCant open file\n");
}