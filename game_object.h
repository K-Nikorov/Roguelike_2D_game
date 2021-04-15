#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

#include <vector>
#include <map>
#include <string>

const float OBJECT_ANIMATION_CHANGE_TIME(0.07f);

class GameObject
{
public:
    std::string ObjectName;

    glm::vec2 Position, Size, Velocity;
    glm::vec4 Color;
    float Rotation;

    Texture2D Sprite;


    GameObject();
    GameObject(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));


    void SetParams(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity);

    void SetRotation(float r);

    void SetTexture(Texture2D sprite);


    virtual void Draw(SpriteRenderer &renderer);
};


class AnimatedGameObject: public GameObject
{
public:
    static std::map<std::string, std::vector<std::string>> AnimatedObjectsTexNames;

    std::map<std::string, std::pair <std::vector<Texture2D>, int>> animations;
    std::vector<std::string> acts;
    std::vector<std::string> dirs;
    std::string currentActDir;
    unsigned int frames;
    float time_gap;


    AnimatedGameObject();
    AnimatedGameObject(std::string objName);
    AnimatedGameObject(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));


    static void LoadAnimation(std::string folder, std::string objName, std::vector<std::string> acts, std::vector<std::string> dirs, unsigned int frames);
    static void PushObjectsTexNames(std::string objName, std::string texName);


    void init();

    void PushTexture(std::string name, Texture2D tex);

    void SwitchAnimation(float dt);

    std::pair <std::vector<Texture2D>, int> &  operator[](std::string name);

    virtual void ActDirDetermination(std::string act_dir) = 0;
};

class PlayerObject: public AnimatedGameObject
{
public:
    struct InventoryObject
    {
        std::string objName;
        Texture2D objTex;
        unsigned int num;

        InventoryObject(std::string objName);
    };

    bool upBlocked;
    bool downBlocked;
    bool leftBlocked;
    bool rightBlocked;

    unsigned int lives;
    unsigned int hasKey;
    bool lockCollision;

    std::vector<Texture2D> healthPanel;
    std::vector<InventoryObject> inventory;


    PlayerObject();
    PlayerObject(std::string objName);
    PlayerObject(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), unsigned int keys = 0);


    virtual void ActDirDetermination(std::string act_dir);


    void AddInventory(std::string objName);
    void RemoveInventory(std::string objName);
};


class WolfObject: public AnimatedGameObject
{
public:
    WolfObject();
    WolfObject(std::string objName);
    WolfObject(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    void UpdatePosition(float dt);

    virtual void ActDirDetermination(std::string act_dir);
};


#endif
