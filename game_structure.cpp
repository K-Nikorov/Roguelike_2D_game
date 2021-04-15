#include "game_structure.h"
#include <map>
#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>

glm::vec2 GameStructure::Load(const char *file, unsigned int gameWidth, unsigned int gameHeight)
{
    char gameCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<char>> gameData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<char> row;
            while (sstream >> std::noskipws >> gameCode)
                row.push_back(gameCode);
            gameData.push_back(row);
        }
        if (gameData.size() > 0)
            return this->init(gameData, gameWidth, gameHeight);
    }
}

glm::vec2 GameStructure::init(std::vector<std::vector<char>> gameData, unsigned int gameWidth, unsigned int gameHeight)
{
    unsigned int height = gameData.size();
    unsigned int width = gameData[0].size();

    glm::vec2 playerPos;
    for (unsigned int y = 0; y < height; ++y)
    {
        std::vector<GameLevel> levelRow;
        for (unsigned int x = 0; x < width; ++x)
        {
            GameLevel level;
            std::string levelPath;
            std::vector<bool> necExits(4, false);

            if ((x > 0) && (gameData[y][x-1] != ' '))
                necExits[0] = true;
            if ((y > 0) && (gameData[y-1][x] != ' '))
                necExits[1] = true;
            if ((x < width - 1) && (gameData[y][x+1] != ' '))
                necExits[2] = true;
            if ((y < height-1) && (gameData[y+1][x] != ' '))
            {
                necExits[3] = true;
            }

            levelPath = std::string("./Levels/") + gameData[y][x] + ".txt";
            if (gameData[y][x] == 'O')
            {
                playerPos = level.Load(levelPath.c_str(), gameWidth, gameHeight, necExits);
                this->curLevel = std::make_pair(y, x);
            }
            else
            {
                level.Load(levelPath.c_str(), gameWidth, gameHeight, necExits);
            }
            levelRow.push_back(level);
        }
        this->GameStruct.push_back(levelRow);
    }
    return playerPos;
}


GameLevel& GameStructure::GetCurLevel()
{
    int i = this->curLevel.first, j = this->curLevel.second;
    return this->GameStruct[i][j];
}


GameLevel& GameStructure::SwitchNextLevel()
{
    int i = this->curLevel.first + this->nextLevelDir.first;
    int j = this->curLevel.second + this->nextLevelDir.second;
    this->curLevel = std::make_pair(i, j);
    if (this->nextLevelDir == std::make_pair(0, -1))
    {
        this->GameStruct[i][j].startPosition = this->GameStruct[i][j].rightExitPos;
        this->GameStruct[i][j].startPosition.x -= this->GameStruct[i][j].Tiles[0].Size.x;
    }
    else if (this->nextLevelDir == std::make_pair(0, 1))
    {
        this->GameStruct[i][j].startPosition = this->GameStruct[i][j].leftExitPos;
        this->GameStruct[i][j].startPosition.x += this->GameStruct[i][j].Tiles[0].Size.x;
    }
    else if (this->nextLevelDir == std::make_pair(-1, 0))
    {
        this->GameStruct[i][j].startPosition = this->GameStruct[i][j].downExitPos;
        this->GameStruct[i][j].startPosition.y -= this->GameStruct[i][j].Tiles[0].Size.y;
    }
    else if (this->nextLevelDir == std::make_pair(1, 0))
    {
        this->GameStruct[i][j].startPosition = this->GameStruct[i][j].upExitPos;
        this->GameStruct[i][j].startPosition.y += this->GameStruct[i][j].Tiles[0].Size.y;
    }

    this->nextLevelDir = std::make_pair(0, 0);
    return this->GameStruct[i][j];
}
