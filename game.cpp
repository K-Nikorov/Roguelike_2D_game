#include "game.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

#include <iostream>

using namespace std;

const glm::vec2 PLAYER_SIZE(40.0f, 44.0f);

const float PLAYER_VELOCITY(100.0f);

const float PLAYER_ANIMATION_CHANGE_TIME(0.07f);


SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height, unsigned int panel_width)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), PanelWidth(panel_width), time_gap(0), tree_pos(0), cut_gap(0) { }

Game::~Game() { }


void Game::Init()
{
    ResourceManager::LoadShader("./Shaders/vShader.txt", "./Shaders/fShader.txt", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width+this->PanelWidth), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));


    ResourceManager::LoadTexture("./resources/exit_down.png", true, "exit_down");
    ResourceManager::LoadTexture("./resources/exit_up.png", true, "exit_up");
    ResourceManager::LoadTexture("./resources/exit_left.png", true, "exit_left");
    ResourceManager::LoadTexture("./resources/exit_right.png", true, "exit_right");
    ResourceManager::LoadTexture("./resources/floor.png", true, "floor");
    ResourceManager::LoadTexture("./resources/grass.png", true, "grass");
    ResourceManager::LoadTexture("./resources/wall.png", true, "wall");
    ResourceManager::LoadTexture("./resources/space.png", true, "space");
    ResourceManager::LoadTexture("./resources/glob_exit.png", true, "glob_exit");
    ResourceManager::LoadTexture("./resources/key.png", true, "key");
    ResourceManager::LoadTexture("./resources/lock.png", true, "lock");
    ResourceManager::LoadTexture("./resources/messages/death_message.png", false, "death");
    ResourceManager::LoadTexture("./resources/messages/win_message.png", false, "win");
    ResourceManager::LoadTexture("./resources/background.png", true, "background");


    for (int i = 0; i < 4; ++i)
    {
        std::string path = "./resources/lives/lives_" + std::to_string(i) + ".png";
        ResourceManager::LoadTexture(path.c_str(), true, std::string("lives_") + std::to_string(i));
    }

    for (int i = 0; i < 4; ++i)
    {
        std::string path = "./resources/inventory/inventory_" + std::to_string(i) + ".png";
        ResourceManager::LoadTexture(path.c_str(), true, std::string("inventory_") + std::to_string(i));
    }

    std::vector<std::string> acts = {"go", "stand"};
    std::vector<std::string> dirs = {"down", "up", "left", "right"};

    AnimatedGameObject::LoadAnimation("hero_sprites", "player", acts, dirs, 10);
    AnimatedGameObject::LoadAnimation("wolf_sprites", "wolf", acts, dirs, 5);

    this->GameStruct.Load("./Game_Structures/struc1.txt", this->Width, this->Height);
    this->StartState = this->GameStruct;

    this->Level = this->GameStruct.GetCurLevel();

    this->Player = new PlayerObject("player");
    this->Player->SetParams("player", this->Level.startPosition, PLAYER_SIZE, ResourceManager::GetTexture("player_stand_up_1"), glm::vec4(1.0f), glm::vec2(0.0f));
    this->Player->init();

    this->fadeInFlag = this->fadeOutFlag = this->finishFade = false;
}


void Game::PanelDraw()
{
    float proposion = 1.0f * (this->Height - 2) / (this->PanelWidth - 2);
    unsigned int width = 10, height = width * proposion;
    float unit_width = (this->PanelWidth-2) / static_cast<float>(width), unit_height = (this->Height-2) / static_cast<float>(height);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            (*Renderer).DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(this->Width + 1 + j*unit_width, 1 + i*unit_height),
                                   glm::vec2(unit_width, unit_height), 0.0f, glm::vec4(0.0f, 0.30f, 0.22f, 1.0f));
        }
    }

    (*Renderer).DrawSprite(this->Player->healthPanel[this->Player->lives], glm::vec2(this->Width + unit_width, unit_height),
                           glm::vec2(4*unit_width, unit_height), 0.0f, glm::vec4(1.0f));

    for (int i = 0; i < this->Player->inventory.size(); ++i)
    {
        PlayerObject::InventoryObject tool = this->Player->inventory[i];
        std::string invName = "inventory_" + std::to_string(tool.num);
        (*Renderer).DrawSprite(ResourceManager::GetTexture(invName), glm::vec2(this->Width + 2*i*unit_width, 8*unit_height),
                               glm::vec2(2*unit_width, 2*unit_height), 0.0f, glm::vec4(1.0f));
        (*Renderer).DrawSprite(tool.objTex, glm::vec2(this->Width + 2*i*unit_width, 8*unit_height),
                               glm::vec2(2*unit_width, 2*unit_height), 0.0f, glm::vec4(1.0f));
    }
}


void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        this->Level.UpdateAnimations(dt);
        DoCollisions();
        ReactCollisions();
        this->cut_gap += dt;
    }
    else if (this->State == GAME_LEVEL_CHANGE)
    {
        if (!fadeOutFlag)
        {
            fadeOutFlag = (*Renderer).decreaseAlpha();
            if (fadeOutFlag)
            {
                this->Level = this->GameStruct.SwitchNextLevel();
                this->Player->SetParams("player", this->Level.startPosition, PLAYER_SIZE, ResourceManager::GetTexture("player_stand_up_1"), glm::vec4(1.0f), glm::vec2(0.0f));
            }
        }
        else if (!fadeInFlag)
        {
            fadeInFlag = (*Renderer).increaseAlpha();
        }
        else
        {
            this->State = GAME_ACTIVE;
            fadeInFlag = false;
            fadeOutFlag = false;
        }
    }
    else if (this->State == GAME_DEATH)
    {

    }
    else if (this->State == GAME_WIN)
    {

    }
}


void Game::RestartGame()
{
    this->GameStruct = this->StartState;
    this->Level = this->GameStruct.GetCurLevel();
    this->Player->SetParams("player", this->Level.startPosition, PLAYER_SIZE, ResourceManager::GetTexture("player_stand_up_1"), glm::vec4(1.0f), glm::vec2(0.0f));
    this->fadeInFlag = this->fadeOutFlag = this->finishFade = false;
    this->Player->lives = 3;
    this->Player->inventory.clear();
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        std::string dir;
        dir = "stand_up";

        if (this->Keys[GLFW_KEY_A])
        {
            if ((this->Player->Position.x >= 0.0f) && (!this->Player->leftBlocked))
                this->Player->Position.x -= velocity;

            dir = "go_left";
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if ((this->Player->Position.x < this->Width - this->Player->Size.x) && (!this->Player->rightBlocked))
                this->Player->Position.x += velocity;
            dir = "go_right";
        }
        if (this->Keys[GLFW_KEY_W])
        {
            if ((this->Player->Position.y >= 0.0f) && (!this->Player->upBlocked))
                this->Player->Position.y -= velocity;
            dir = "go_up";
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if ((this->Player->Position.y < this->Height - this->Player->Size.y) && (!this->Player->downBlocked))
                this->Player->Position.y += velocity;
            dir = "go_down";
        }
        if (this->Keys[GLFW_KEY_SPACE])
        {
            if ((this->Player->lockCollision) && (this->Player->hasKey) && (this->cut_gap > 0.5f))
            {
                this->cut_gap = 0;
                this->Player->hasKey -= 1;
                this->Player->RemoveInventory("key");

                int ind, minDist;
                ind = -1;
                minDist = 10000000;
                for (int i = 0; i < this->Level.lockIndexes.size(); ++i)
                {
                    int curDist;
                    GameObject curLock;
                    curLock = this->Level.Tiles[this->Level.lockIndexes[i]];
                    curDist = (abs((this->Player->Position.x + this->Player->Size.x/2) - (curLock.Position.x + curLock.Size.x/2))
                              + abs((this->Player->Position.y + this->Player->Size.y/2) - (curLock.Position.y + curLock.Size.y/2)));
                    if (curDist < minDist)
                    {
                        minDist = curDist;
                        ind = i;
                    }
                }

                for (int i = 0; i < this->Level.lockIndexes.size(); ++i)
                {
                    if (this->Level.lockIndexes[i] > this->Level.lockIndexes[ind])
                        --this->Level.lockIndexes[i];
                }
                for (int i = 0; i < this->Level.keyIndexes.size(); ++i)
                {
                    if (this->Level.keyIndexes[i] > this->Level.lockIndexes[ind])
                        --this->Level.keyIndexes[i];
                }

                int i = this->GameStruct.curLevel.first;
                int j = this->GameStruct.curLevel.second;
                this->Level.Tiles.erase(this->Level.Tiles.begin() + this->Level.lockIndexes[ind]);
                this->Level.lockIndexes.erase(this->Level.lockIndexes.begin() + ind);
                this->GameStruct.GameStruct[i][j] = this->Level;
            }
        }
        this->Player->ActDirDetermination(dir);
        this->Player->SwitchAnimation(dt);
    }
    else if (((this->State == GAME_DEATH) || (this->State == GAME_WIN)) && (this->finishFade))
    {
        if (this->Keys[GLFW_KEY_R])
        {
            RestartGame();
            this->State = GAME_ACTIVE;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        this->Level.Draw(*Renderer);
        this->Player->Draw(*Renderer);
        this->PanelDraw();
    }
    else if (this->State == GAME_LEVEL_CHANGE)
    {
        this->Level.Draw(*Renderer);
        this->Player->Draw(*Renderer);
        this->PanelDraw();
    }
    else if (this->State == GAME_DEATH)
    {
        if (!fadeOutFlag)
        {
            fadeOutFlag = (*Renderer).decreaseAlpha();
            this->Level.Draw(*Renderer);
            this->PanelDraw();
        }
        else if (!fadeInFlag)
        {
            (*Renderer).DrawSprite(ResourceManager::GetTexture("death"), glm::vec2(0.0f), glm::vec2(this->Width, this->Height),
                                        0.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            fadeInFlag = (*Renderer).increaseAlpha();
            this->finishFade = this->finishFade || fadeInFlag;
            fadeInFlag = false;
        }

    }
    else if (this->State == GAME_WIN)
    {
        if (!fadeOutFlag)
        {
            fadeOutFlag = (*Renderer).decreaseAlpha();
            this->Level.Draw(*Renderer);
            this->PanelDraw();
        }
        else if (!fadeInFlag)
        {
            (*Renderer).DrawSprite(ResourceManager::GetTexture("win"), glm::vec2(0.0f), glm::vec2(this->Width, this->Height),
                                        0.0f, glm::vec4(1.0f));
            fadeInFlag = (*Renderer).increaseAlpha();
            this->finishFade = this->finishFade || fadeInFlag;
            fadeInFlag = false;
        }
    }
}

bool Game::CheckCollisions(GameObject &player, GameObject &tile)
{
    bool collisionX = (player.Position.x + player.Size.x*7/10 >= tile.Position.x + tile.Size.x/10) &&
        (tile.Position.x + tile.Size.x*9/10 >= player.Position.x + player.Size.x*3/10);

    bool collisionY = (player.Position.y + player.Size.y*9/10 >= tile.Position.y + tile.Size.y/10) &&
        (tile.Position.y + tile.Size.y*9/10 >= player.Position.y + player.Size.y*8/10);

    return collisionX && collisionY;
}


void Game::DoCollisions()
{
    std::set<std::string> good;
    bool goodFlag = true;
    good.insert("floor"); good.insert("wall"); good.insert("exit");
    int cnt = 0;
    this->Player->upBlocked = false;
    this->Player->downBlocked = false;
    this->Player->rightBlocked = false;
    this->Player->leftBlocked = false;
    this->Player->lockCollision = false;
    for (GameObject &tile: this->Level.Tiles)
    {
        if (CheckCollisions(*Player, tile))
        {
            if (tile.ObjectName != "floor")
                this->collisionBuffer.push(tile);
        }
    }
    for (GameObject &tile: this->Level.AnimObj)
    {
        if (CheckCollisions(*Player, tile))
        {
            this->collisionBuffer.push(tile);
        }
    }
}


void Game::ReactCollisions()
{
    while (!this->collisionBuffer.empty())
    {
        GameObject colisTile = this->collisionBuffer.front();
        std::string objName = colisTile.ObjectName;
        this->collisionBuffer.pop();

        if (objName == "exit")
            exitReaction();
        else if (objName == "wall")
            wallReaction(colisTile);
        else if (objName == "space")
            spaceReaction();
        else if (objName == "glob_exit")
            globExitReaction();
        else if (objName == "key")
            keyReaction();
        else if (objName == "lock")
            lockReaction(colisTile);
        else if (objName == "wolf")
            wolfReaction();
    }
}

void Game::exitReaction()
{
    std::vector<std::pair<float, std::pair<int, int>>> edgeDist = {std::make_pair(this->Player->Position.x, std::make_pair(0, -1)),
                                                                      std::make_pair(this->Width - (this->Player->Position.x + this->Player->Size.x), std::make_pair(0, 1)),
                                                                      std::make_pair(this->Player->Position.y, std::make_pair(-1, 0)),
                                                                      std::make_pair(this->Height - (this->Player->Position.y + this->Player->Size.y), std::make_pair(1, 0))};

    sort(edgeDist.begin(), edgeDist.end());
    this->GameStruct.nextLevelDir = edgeDist[0].second;
    this->State = GAME_LEVEL_CHANGE;
}

void Game::wallReaction(GameObject wallTile)
{
    if (wallTile.Position.x > this->Player->Position.x)
        this->Player->rightBlocked = true;
    if (wallTile.Position.x <= this->Player->Position.x)
        this->Player->leftBlocked = true;

    if (wallTile.Position.y <= this->Player->Position.y)
        this->Player->upBlocked = true;
    if (wallTile.Position.y > this->Player->Position.y)
        this->Player->downBlocked = true;
}

void Game::spaceReaction()
{
    this->State = GAME_DEATH;
}

void Game::keyReaction()
{
    int ind, minDist;
    ind = -1;
    minDist = 10000000;
    for (int i = 0; i < this->Level.keyIndexes.size(); ++i)
    {
        int curDist;
        GameObject curKey;
        curKey = this->Level.Tiles[this->Level.keyIndexes[i]];
        curDist = (abs((this->Player->Position.x + this->Player->Size.x/2) - (curKey.Position.x + curKey.Size.x/2))
                  + abs((this->Player->Position.y + this->Player->Size.y/2) - (curKey.Position.y + curKey.Size.y/2)));
        if (curDist < minDist)
        {
            minDist = curDist;
            ind = i;
        }
    }

    for (int i = 0; i < this->Level.keyIndexes.size(); ++i)
    {
        if (this->Level.keyIndexes[i] > this->Level.keyIndexes[ind])
            --this->Level.keyIndexes[i];
    }
    for (int i = 0; i < this->Level.lockIndexes.size(); ++i)
    {
        if (this->Level.lockIndexes[i] > this->Level.keyIndexes[ind])
            --this->Level.lockIndexes[i];
    }

    int i = this->GameStruct.curLevel.first;
    int j = this->GameStruct.curLevel.second;
    //this->GameStruct.GameStruct[i][j].Tiles.erase(this->GameStruct.GameStruct[i][j].Tiles.begin() + this->Level.keyIndexes[ind]);
    this->Level.Tiles.erase(this->Level.Tiles.begin() + this->Level.keyIndexes[ind]);
    this->Level.keyIndexes.erase(this->Level.keyIndexes.begin() + ind);
    this->GameStruct.GameStruct[i][j] = this->Level;
    this->Player->hasKey += 1;
    this->Player->AddInventory("key");

}

void Game::lockReaction(GameObject lockTile)
{
    this->Player->lockCollision = true;
    wallReaction(lockTile);
}

void Game::wolfReaction()
{
    if (--this->Player->lives == 0)
    {
        this->State = GAME_DEATH;
    }
    else
    {
        int dx = 2 * (std::rand() % 2) - 1;
        int dy = 2 * (std::rand() % 2) - 1;
        this->Player->Position.x += this->Player->Size.x * dx;
        this->Player->Position.y += this->Player->Size.y * dy;
    }
}

void Game::globExitReaction()
{
    this->State = GAME_WIN;
}
