#pragma once
//--------------------include Section --------------------
#include <vector>
#include <Point.h>
#include <fstream>
#include <sstream>

//--------------------Board Class definition --------------------
class Board
{
public:
	//--------constructor&destructor------------
	Board() {};
	virtual ~Board() = default;

	//--------class functions------------
	std::vector< std::unique_ptr <Point>> buildBoard(int levelNumber);
	int verticesSummary(int centerRow);
	void readStagesFromFile(std::ifstream& inputFile);
	void inputVerification(std::istringstream & iss, int& value, std::ifstream& inputFile, bool firstIteration);
	bool angleValidation(int angle);

	//--------get functions------------
	bool isEof() const { return m_isEof; };
	int getRowSize() const {return m_centerRowSize;};

private:
	//--------class members------------
	std::vector<std::vector<int>> m_verticesEdgeAngles;//saves all the angles of all the vertices,
	int m_centerRowSize;//saves the center row size							//each level at a time
	bool m_isEof = false;//tells us if end of file

};