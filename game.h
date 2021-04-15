#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sprite_renderer.h"
#include "resource_manager.h"
#include "game_object.h"
#include "game_level.h"
#include "game_structure.h"

#include <vector>
#include <queue>
#include <map>
#include <string>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_DEATH,
    GAME_LEVEL_CHANGE,
    GAME_MESSAGE
};


class Game
{
public:


    GameState State;
    bool Keys[1024];
    unsigned int Width, Height, PanelWidth;
    float time_gap;
    float cut_gap;
    glm::vec2 tree_poses[4];
    unsigned tree_pos;

    GameStructure StartState;
    GameStructure GameStruct;
    GameLevel CurrentLevel;

    GameLevel Level;
    PlayerObject *Player;

    unsigned int textGap;

    std::queue<GameObject> collisionBuffer;

    bool fadeOutFlag;
    bool fadeInFlag;
    bool finishFade;


    Game(unsigned int game_width, unsigned int game_height, unsigned int panel_width);


    ~Game();


    void Init();


    void PanelDraw();
    // Игровой цикл
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    void DoCollisions();
    void ReactCollisions();

private:
    void RestartGame();

    bool CheckCollisions(GameObject &player, GameObject &tile);

    void exitReaction();
    void wallReaction(GameObject wallTile);
    void spaceReaction();
    void keyReaction();
    void lockReaction(GameObject lockTile);
    void wolfReaction();
    void globExitReaction();

};


#endif // GAME_H
