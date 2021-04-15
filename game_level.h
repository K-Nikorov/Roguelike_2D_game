#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
    std::vector<GameObject> Tiles;
    std::vector<WolfObject> AnimObj;

    glm::vec2 startPosition;
    glm::vec2 leftExitPos, upExitPos, rightExitPos, downExitPos;
    std::vector<unsigned int> keyIndexes;
    std::vector<unsigned int> lockIndexes;


    GameLevel() { }


    glm::vec2 Load(const char *file, unsigned int levelWidth, unsigned int levelHeight, std::vector<bool> necExits);


    void UpdateAnimations(float dt);


    void Draw(SpriteRenderer &renderer);

private:

    glm::vec2 init(std::vector<std::vector<char>> tileData, unsigned int levelWidth, unsigned int levelHeight, std::vector<bool> necExits);
};

#endif
