#pragma once

#include "raylib.h"

class Truck
{
public:
    void Init(Texture2D texture, Vector2 position, float speed);
    void Update(float deltaTime);
    void Draw() const;

    void SetPosition(Vector2 position);
    
    Vector2 GetPosition() const;
    float GetSpeed() const;
    Rectangle GetBounds() const;

private:
    Texture2D texture_;
    Vector2 position_;
    float speed_ = 0.0f;
};