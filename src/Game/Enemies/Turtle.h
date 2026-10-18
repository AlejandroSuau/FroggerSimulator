#pragma once

#include "raylib.h"

class Turtle
{
public:
    void Init(Texture2D texture, Vector2 position, float speed);

    void Update(float deltaTime);
    void Draw() const;

    Rectangle GetBounds() const;

    Vector2 GetPosition() const;
    void SetPosition(Vector2 position);

private:
    Texture2D texture_;
    Vector2 position_;
    float speed_ = 0.0f;
};