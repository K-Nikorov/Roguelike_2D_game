#ifndef GAME_STRUCTURE_H
#define GAME_STRUCTURE_H

#include <vector>

#include "game_level.h"

class GameStructure
{
public:
    std::vector<std::vector<GameLevel>> GameStruct;
    std::pair<unsigned int, unsigned int> curLevel;
    std::pair<int, int> nextLevelDir;


    GameStructure() { }

    glm::vec2 Load(const char *file, unsigned int gameWidth, unsigned int gameHeight);

    GameLevel& GetCurLevel();

    GameLevel& SwitchNextLevel();

private:
    glm::vec2 init(std::vector<std::vector<char>> gameData, unsigned int gamelWidth, unsigned int gameHeight);

    glm::vec2 LoadLevel(char levelType, unsigned int gamelWidth, unsigned int gameHeight, GameLevel level);

};

#endif // GAME_STRUCTURE_H
