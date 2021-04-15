#include "game_level.h"
#include <map>
#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>


glm::vec2 GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight, std::vector<bool> necExits)
{
    this->Tiles.clear();

    char tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<char>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<char> row;
            while (sstream >> std::noskipws >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            return this->init(tileData, levelWidth, levelHeight, necExits);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : this->Tiles)
    {
        tile.Draw(renderer);
    }
    for (WolfObject &wolf: this->AnimObj)
    {
        wolf.Draw(renderer);
    }
}


glm::vec2 GameLevel::init(std::vector<std::vector<char>> tileData, unsigned int levelWidth, unsigned int levelHeight, std::vector<bool> necExits)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
    std::map<char, std::string> tex_map;
    tex_map['.'] = "floor";
    tex_map['@'] = "player";
    tex_map[' '] = "space";

    glm::vec2 playerPos = glm::vec2(0.0f);
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            glm::vec2 pos(unit_width * x, unit_height * y);
            glm::vec2 size(unit_width, unit_height);
            GameObject floor("floor", pos, size, ResourceManager::GetTexture("floor"), glm::vec4(1.0f));
            this->Tiles.push_back(floor);
        }
    }
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            glm::vec2 pos(unit_width * x, unit_height * y);
            glm::vec2 size(unit_width, unit_height);
            std::string tex_name;
            if (tileData[y][x] == '#')
            {
                float angle = 0.0f;
                tex_name = "wall";
                GameObject wall("wall", pos, size, ResourceManager::GetTexture(tex_name.c_str()), glm::vec4(1.0f));
                wall.SetRotation(angle);
                this->Tiles.push_back(wall);
            }
            else if (tileData[y][x] == 'x') // exit
            {
                std::string tex_name;
                if ((y == 0) && necExits[1])
                {
                    tex_name = "exit_up";
                    this->upExitPos = pos;
                }
                else if ((x == width - 1) && (necExits[2]))
                {
                    tex_name = "exit_right";
                    this->rightExitPos = pos;
                }
                else if ((y == height-1) && (necExits[3]))
                {
                    tex_name = "exit_down";
                    this->downExitPos = pos;
                }
                else if ((x == 0) && (necExits[0]))
                {
                    tex_name = "exit_left";
                    this->leftExitPos = pos;
                }
                else
                    tex_name = "NO_EXIT";

                if (tex_name == "NO_EXIT")
                {
                    GameObject exit_wall("wall", pos, size, ResourceManager::GetTexture("wall"), glm::vec4(1.0f));
                    this->Tiles.push_back(exit_wall);
                }
                else
                {
                    GameObject exit_wall("exit", pos, size, ResourceManager::GetTexture(tex_name.c_str()), glm::vec4(1.0f));
                    this->Tiles.push_back(exit_wall);
                }
            }
            else if (tileData[y][x] == 'Q')
            {
                GameObject glob_exit("glob_exit", pos, size, ResourceManager::GetTexture("glob_exit"), glm::vec4(1.0f));
                this->Tiles.push_back(glob_exit);
            }
            else if (tileData[y][x] == '@')
            {
                playerPos = pos;
                this->startPosition = pos;
            }
            else if (tileData[y][x] == 'K')
            {
                pos.x += size.x/4; pos.y += size.y/4;
                size.x /= 2; size.y /= 2;
                GameObject key("key", pos, size, ResourceManager::GetTexture("key"), glm::vec4(1.0f));
                this->Tiles.push_back(key);
                this->keyIndexes.push_back(this->Tiles.size() - 1);
            }
            else if (tileData[y][x] == 'L')
            {
                pos.x -= size.x/2; pos.y -= size.y/1.3;
                size.x *= 2; size.y *= 2;
                GameObject lock("lock", pos, size, ResourceManager::GetTexture("lock"), glm::vec4(1.0f));
                this->Tiles.push_back(lock);
                this->lockIndexes.push_back(this->Tiles.size()-1);
            }
            else if (tileData[y][x] == 'W')
            {
                size.y *= 1.2;
                size.x *= 0.8;

                WolfObject wolf("wolf", pos, size, ResourceManager::GetTexture("wolf_go_up_1"), glm::vec4(1.0f), glm::vec2(100.0f, 100.0f));
                wolf.init();
                wolf.currentActDir = "wolf_go_up";
                this->AnimObj.push_back(wolf);
            }
            else if (tileData[y][x] == 'S')
            {
                size.y *= 1.2;
                size.x *= 0.8;

                WolfObject wolf("wolf", pos, size, ResourceManager::GetTexture("wolf_go_down_1"), glm::vec4(1.0f), glm::vec2(100.0f, 100.0f));
                wolf.init();
                wolf.currentActDir = "wolf_go_down";
                this->AnimObj.push_back(wolf);
            }
            else if (tileData[y][x] == 'D')
            {
                size.x *= 1.2;
                size.y *= 0.8;

                WolfObject wolf("wolf", pos, size, ResourceManager::GetTexture("wolf_go_right_1"), glm::vec4(1.0f), glm::vec2(100.0f, 100.0f));
                wolf.init();
                wolf.currentActDir = "wolf_go_right";
                this->AnimObj.push_back(wolf);
            }
            else if (tileData[y][x] == 'A')
            {
                size.x *= 1.2;
                size.y *= 0.8;

                WolfObject wolf("wolf", pos, size, ResourceManager::GetTexture("wolf_go_left_1"), glm::vec4(1.0f), glm::vec2(100.0f, 100.0f));
                wolf.init();
                wolf.currentActDir = "wolf_go_left";
                this->AnimObj.push_back(wolf);
            }
            else if (tileData[y][x] != '.')
            {
                GameObject obj(tex_map[tileData[y][x]], pos, size, ResourceManager::GetTexture(tex_map[tileData[y][x]].c_str()), glm::vec4(1.0f));
                this->Tiles.push_back(obj);
            }
        }
    }
    return playerPos;
}


void GameLevel::UpdateAnimations(float dt)
{
    for (int i = 0; i < this->AnimObj.size(); ++i)
    {
        this->AnimObj[i].UpdatePosition(dt);
        this->AnimObj[i].ActDirDetermination("");
        this->AnimObj[i].SwitchAnimation(dt);
    }
}



