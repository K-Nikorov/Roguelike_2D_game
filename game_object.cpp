#include "game_object.h"
#include <iostream>

#include <vector>
#include <map>
#include <string>


GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0), Sprite() { }

GameObject::GameObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity)
    : ObjectName(name), Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0), Sprite(sprite){ }


AnimatedGameObject::AnimatedGameObject()
    : GameObject::GameObject(), time_gap(0) { }

AnimatedGameObject::AnimatedGameObject(std::string objName)
    : GameObject()
{
    this->ObjectName = objName;
}

AnimatedGameObject::AnimatedGameObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity)
    : GameObject::GameObject(name, pos, size, sprite, color, velocity), time_gap(0) { }


PlayerObject::PlayerObject()
    : AnimatedGameObject::AnimatedGameObject(), lives(3), hasKey(0), lockCollision(false)
{
    for (int i = 0; i < 4; ++i)
    {
        this->healthPanel.push_back(ResourceManager::GetTexture(std::string("lives_") + std::to_string(i)));
    }

}

PlayerObject::PlayerObject(std::string objName)
    : AnimatedGameObject(objName), lives(3), hasKey(0), lockCollision(false)
{
    for (int i = 0; i < 4; ++i)
    {
        this->healthPanel.push_back(ResourceManager::GetTexture(std::string("lives_") + std::to_string(i)));
    }

}
PlayerObject::PlayerObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity, unsigned int keys)
    : AnimatedGameObject::AnimatedGameObject(name, pos, size, sprite, color, velocity), lives(3), hasKey(keys), lockCollision(false)
{
    for (int i = 0; i < 4; ++i)
    {
        this->healthPanel.push_back(ResourceManager::GetTexture(std::string("lives_") + std::to_string(i)));
    }

}


WolfObject::WolfObject()
    : AnimatedGameObject::AnimatedGameObject(){ }

WolfObject::WolfObject(std::string objName)
    : AnimatedGameObject(objName) { }

WolfObject::WolfObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity)
    : AnimatedGameObject::AnimatedGameObject(name, pos, size, sprite, color, velocity) { }




void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}


void GameObject::SetTexture(Texture2D sprite)
{
    this->Sprite = sprite;
}


void GameObject::SetParams(std::string objName, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f))
{
    this->ObjectName = objName;
    this->Position = pos;
    this->Size = size;
    this->Sprite = sprite;
    this->Color = color;
    this->Velocity = velocity;
}


void GameObject::SetRotation(float r)
{
    this->Rotation = r;
}



std::map<std::string, std::vector<std::string>>  AnimatedGameObject::AnimatedObjectsTexNames;

std::pair <std::vector<Texture2D>, int> & AnimatedGameObject::operator[](std::string name)
{
    return this->animations[name];
}


void AnimatedGameObject::LoadAnimation(std::string folder, std::string objName, std::vector<std::string> acts, std::vector<std::string> dirs, unsigned int frames)
{
    for (auto act: acts)
    {
        for (auto dir: dirs)
        {
            for (int i = 1; i <= frames; ++i)
            {
                std::string path;
                std::string name;
                name = objName + "_" + act + "_" + dir + "_" + std::to_string(i);
                path = "./resources/" + folder + "/" + act + "_" + dir + "/" + std::to_string(i) + ".png";
                ResourceManager::LoadTexture(path.c_str(), true, name.c_str());

                AnimatedGameObject::PushObjectsTexNames(objName, objName + "_" + act + "_" + dir + "_" +  std::to_string(i));
            }
        }
    }
}


void AnimatedGameObject::init()
{
    for (std:: string texName: AnimatedGameObject::AnimatedObjectsTexNames[this->ObjectName])
    {
        unsigned ind = texName.rfind("_");
        std::string name = texName.substr(0, ind);
        this->PushTexture(name, ResourceManager::GetTexture(texName));
    }
}


void AnimatedGameObject::PushTexture(std::string name, Texture2D tex)
{
    if (this->animations.find(name) == this->animations.end())
    {
        std::vector<Texture2D> vec(1, tex);
        this->animations[name] = make_pair(vec, 0);
    }
    else
    {
        this->animations[name].first.push_back(tex);
    }
}


void AnimatedGameObject::SwitchAnimation(float dt)
{
    this->time_gap += dt;
    if (this->time_gap > OBJECT_ANIMATION_CHANGE_TIME)
    {
        unsigned int frames = this->animations[this->currentActDir].first.size();
        this->time_gap = 0;
        ++this->animations[this->currentActDir].second;
        this->animations[this->currentActDir].second %= frames;
        unsigned int ind = this->animations[this->currentActDir].second;
        this->SetTexture(this->animations[this->currentActDir].first[ind]);
    }
}


void AnimatedGameObject::PushObjectsTexNames(std::string objName, std::string texName)
{
    if (AnimatedGameObject::AnimatedObjectsTexNames.find(objName) == AnimatedGameObject::AnimatedObjectsTexNames.end())
    {
        std::vector<std::string> vec(1, texName);
        AnimatedGameObject::AnimatedObjectsTexNames[objName] = vec;
    }
    else
    {
        AnimatedGameObject::AnimatedObjectsTexNames[objName].push_back(texName);
    }
}


void PlayerObject::ActDirDetermination(std::string act_dir)
{
    this->currentActDir = this->ObjectName + "_" + act_dir;
}


PlayerObject::InventoryObject::InventoryObject(std::string objName)
{
    this->objName = objName;
    this->num = 1;
    this->objTex = ResourceManager::GetTexture(objName);
}


void PlayerObject::AddInventory(std::string objName)
{
    bool added = false;
    for (int i = 0; i < this->inventory.size(); ++i)
    {
        if ((this->inventory[i].objName == objName) && (this->inventory[i].num < 3))
        {
            added = true;
            ++this->inventory[i].num;
            break;
        }
    }
    if (!added)
    {
        this->inventory.push_back(objName);
        added = true;
    }
}

void PlayerObject::RemoveInventory(std::string objName)
{
    for (int i = this->inventory.size()-1; i >= 0; --i)
    {
        if (this->inventory[i].objName == objName)
        {
            --this->inventory[i].num;
            if (this->inventory[i].num == 0)
            {
                this->inventory.erase(this->inventory.begin() + i);
            }
            break;
        }
    }
}


constexpr unsigned int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

void WolfObject::ActDirDetermination(std::string act_dir)
{
    if (this->currentActDir == "wolf_go_up")
    {
        if (this->Position.y < this->Size.y)
        {
            this->currentActDir = "wolf_go_down";
        }
    }
    else if (this->currentActDir == "wolf_go_down")
    {
        if (this->Position.y + this->Size.y > WINDOW_HEIGHT - this->Size.y)
        {
            this->currentActDir = "wolf_go_up";
        }
    }
    else if (this->currentActDir == "wolf_go_left")
    {
        if (this->Position.x < this->Size.x)
        {
            this->currentActDir = "wolf_go_right";
        }
    }
    else if (this->currentActDir== "wolf_go_right")
    {
        if (this->Position.x + this->Size.x > WINDOW_WIDTH - this->Size.x)
        {
            this->currentActDir = "wolf_go_left";
        }
    }
}

void WolfObject::UpdatePosition(float dt)
{
    if (this->currentActDir == "wolf_go_left")
    {
        float velocity = this->Velocity.x * dt;
        if ((this->Position.x >= 0.0f))
            this->Position.x -= velocity;

    }
    if (this->currentActDir == "wolf_go_right")
    {
        float velocity = this->Velocity.x * dt;
        if ((this->Position.x < WINDOW_WIDTH - this->Size.x))
            this->Position.x += velocity;
    }
    if (this->currentActDir == "wolf_go_up")
    {
        float velocity = this->Velocity.y * dt;
        if ((this->Position.y >= 0.0f))
            this->Position.y -= velocity;
    }
    if (this->currentActDir == "wolf_go_down")
    {
        float velocity = this->Velocity.y * dt;
        if ((this->Position.y < WINDOW_HEIGHT - this->Size.y))
            this->Position.y += velocity;
    }
}


