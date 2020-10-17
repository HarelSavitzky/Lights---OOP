//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include <GameManager.h>

//--------------------prototype Section --------------------
void printExceptionToFile(std::exception& e);

//---------------------main function --------------------------
int main() try
{
	GameManager newGame;
	newGame.runGame();
}

//---------------------catch exceptions function --------------------------
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl; //(print the error to win32 window anyway)
    printExceptionToFile(e);    //call a function to print the error to file
    return EXIT_FAILURE;
}
//---------------------
catch (...)
{
    std::cerr << "Safety catch exception" << std::endl;
    return EXIT_FAILURE;
}
//---------------------

//---------------------printExceptionToFile function --------------------------
/*function to be called only from the exception and for printing the exception
error that throwd to a file called 'log.txt' that will be created in the output folder of the project*/
void printExceptionToFile(std::exception& e)
{
    std::ofstream logFile ("log.txt");  //creating the log.txt file
    logFile << e.what() << std::endl;   //print the exception to the file
    logFile.close();                    //close the file
}
//---------------------