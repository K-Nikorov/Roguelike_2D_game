#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"


class SpriteRenderer
{
public:
    SpriteRenderer(const Shader &shader);

    ~SpriteRenderer();

    void DrawSprite(const Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));

    bool decreaseAlpha();

    bool increaseAlpha();

private:
    Shader shader;
    unsigned int quadVAO;

    float globAlpha;

    void initRenderData();
};

#endif // SPRITE_RENDERER_H
