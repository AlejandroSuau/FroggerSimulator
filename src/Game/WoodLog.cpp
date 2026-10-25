#include "WoodLog.h"

void WoodLog::Init(
    Texture2D texture,
    Vector2 position,
    float speed)
{
    texture_ = texture;
    position_ = position;
    speed_ = speed;
}

void WoodLog::Update(float deltaTime)
{
    // Logs: izquierda -> derecha
    position_.x += speed_ * deltaTime;
}

void WoodLog::Draw() const
{
    DrawTextureV(texture_, position_, WHITE);
}

Rectangle WoodLog::GetBounds() const
{
    // We substract player width from log so it doesn't push it
    // from its boundaries.
    return {
        position_.x,
        position_.y,
        static_cast<float>(texture_.width) - 48,
        static_cast<float>(texture_.height)
    };
}

Vector2 WoodLog::GetPosition() const
{
    return position_;
}

void WoodLog::SetPosition(Vector2 position)
{
    position_ = position;
}

float WoodLog::GetSpeed() const
{
    return speed_;
}