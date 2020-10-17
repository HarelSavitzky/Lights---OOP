//--------------------include Section --------------------
#include "Board.h"

//---------------------buildBoard function --------------------------
/*when the file is readed, this file will build the board using the vertices angles
vector, in the loop it will build the stage according to the task, where each row
gets bigger untill the center and than gets smaller*/
std::vector< std::unique_ptr <Point>> Board::buildBoard(int levelNumber)
{	
	auto location = sf::Vector2f(BOARDER_GAP, BOARDER_GAP);
	std::vector< std::unique_ptr <Point>> points;	//variables definition
	auto colCount = 0;
	auto rowCount = 0;
	auto centerRow = levelNumber; 
	auto countUntillCenter = centerRow - MIN_ROW_LENGTH;
	auto startingGap = (EDGE_LENGTH + POINT_SIZE) * countUntillCenter;
	auto firstJump = MIN_ROW_LENGTH;
	auto jumpSum = firstJump;
	auto jumpCount = 1;
	auto sumOfVertices = verticesSummary(centerRow);

	for (int i = 0; i < sumOfVertices; i++)	//will run on the amount of vertices the level contains
	{
		if (i == jumpSum && countUntillCenter > 0)//this 'if' will initiate in every change between
		{											//rows - untill the last placement of a vertex in the 
			startingGap -= EDGE_LENGTH + POINT_SIZE;	//middle (and biggest) row
			colCount = 0;						
			rowCount += 1;
			jumpSum += firstJump + jumpCount;
			jumpCount++;
			countUntillCenter--;
		}
		if (countUntillCenter == 0)	//this will have to happen only once,
		{						//after the center row - when the rows starts to get smaller
			jumpCount--;
			countUntillCenter--;
		}
		if (i == jumpSum && countUntillCenter < 0)//this 'if' will initiate in every change between
		{											//rows - after the last placement of a vertex in the
			startingGap += EDGE_LENGTH + POINT_SIZE;	//middle (and biggest) row
			colCount = 0;
			rowCount += 1;
			jumpCount--;
			jumpSum += firstJump + jumpCount;
			countUntillCenter--;
		}
		location = sf::Vector2f((BOARDER_GAP)+startingGap +	//summary of the location of each vertex
			(COL_GAP * colCount), (BOARDER_GAP)+(ROW_GAP * rowCount));
		colCount += 1;

		if (i == (sumOfVertices / 2))	// this 'if' is to know if this is the core vertex
			points.emplace_back(std::make_unique <Point>(location, m_verticesEdgeAngles[i], true));
		else
			points.emplace_back(std::make_unique <Point>(location, m_verticesEdgeAngles[i], false));
	}
	return points;	//return the complete stage, ready to draw
}
//---------------------readStagesFromFile function --------------------------
/*the function reads stage after stage, in each call it reads one stage and ofcourse
it validates all the data on the file and throw exception if needed*/
void Board::readStagesFromFile(std::ifstream& inputFile)
{
	std::string currentLine;
	std::istringstream iss;		//function veriables
	int numOfEdges;
	int temp;
	int numOfVertex = 0;
	m_verticesEdgeAngles.clear();	//clear data with each level read
	auto firstIteration = true;
	int sumOfVertices;

	while (!inputFile.eof())
	{
		std::getline(inputFile, currentLine);	//read the line

		if (inputFile.eof())
			m_isEof = true;			//check if eof + check if "next"level
		if (currentLine == "next")
			break;

		iss.str(currentLine);	//insert line to istringstream

		if (firstIteration == true)			//first iteration operation
		{									//read the middle row number and varify in all needed ways
			inputVerification(iss, m_centerRowSize, inputFile, firstIteration);//if not valid throw exception
			sumOfVertices = verticesSummary(m_centerRowSize);
			if(m_centerRowSize % 2 == 0)
				throw std::invalid_argument(INVALID_CENTER); //------------------
			firstIteration = false;
			iss.clear();
			continue;
		}
				//(more conditions and throws inside 'inputVerification')
		inputVerification(iss, numOfEdges, inputFile, firstIteration);//read the numOfEdges of a vertex
		if(numOfEdges > MAX_EDGES 									//and varify->if not valid, throw
			|| numOfEdges <= 0)
			throw std::out_of_range(INVALID_INPUT);

		std::vector<int> tempVec;	//creat vector for angles of each row
		m_verticesEdgeAngles.push_back(tempVec);

		for (int i = 0; i < numOfEdges; i++)
		{
			if (!(iss >> temp) && !inputFile.eof())	//read the angles of all the row and insert
				throw std::out_of_range(SHORT_OF_ANGLES);//them to a vector how saves all the angles
			if (!angleValidation(temp))						//of all the vertices, check input validation in
				throw std::invalid_argument(INVALID_ANGLE);	//any possible way
			m_verticesEdgeAngles[numOfVertex].push_back(temp);
		}
		if(iss.rdbuf()->in_avail())			//another check if there are too much arguments...
			throw std::out_of_range(ANGLES_OVERLOAD);

		numOfVertex++;	//after implacement - move on to next vertex
		iss.clear();	//clear stream for next line
	}
 	if (sumOfVertices != m_verticesEdgeAngles.size() && (!inputFile.eof()))	
		throw std::out_of_range(CENTER_LINE_SIZE_AND_NUMBER_OF_VERTEX_DONT_FIT);
}													//if there are not enaugh vertices comparing
													//to summary of them (using the middle row size) - throw
//---------------------inputVerification function --------------------------
void Board::inputVerification(std::istringstream& iss, int& value ,
 std::ifstream& inputFile, bool firstIteration)
{
	if (!(iss >> value) && !inputFile.eof())		//in the cases that we can check for simmilar exceptions
		throw std::out_of_range(INVALID_INPUT);		//this function will read the input from the stream and
	if (firstIteration)								//validate it, if not valid, it will throw exception
	{
		if (iss.rdbuf()->in_avail())
			throw std::out_of_range(ARGUMENTS_OVERLOAD);
	}
}

//---------------------angleValidation function --------------------------
bool Board::angleValidation(int angle)
{
	if (angle != 30 && angle != 90 &&		//function to check the validation of the angles input
		angle != 150 && angle != 210 &&
		angle != 270 && angle != 330)
		return false;
	else
		return true;
}

//---------------------verticesSummary function --------------------------
int Board::verticesSummary(int centerRow)
{
	auto summary = centerRow;				//function that returns the number of vertices that there will
	auto iterations = centerRow - MIN_ROW_LENGTH;//be in the stage - according to the middle row
	auto firstJump = MIN_ROW_LENGTH;
	auto jumpCount = iterations;

	for (int i = 0; i < iterations; i++)
	{
		summary += (centerRow - jumpCount) * 2;
		jumpCount--;
	}
	return summary;
}