#include "highScore.h"
using namespace std;
int highScore=0;

void LoadHighScore(){
    ifstream file("highscore.txt");

    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void SaveHighScore(int currentScore)
{
    if (currentScore > highScore)
    {
        highScore = currentScore;

        ofstream file("highscore.txt");

        if (file.is_open())
        {
            file << highScore;
            file.close();
        }
    }
}
