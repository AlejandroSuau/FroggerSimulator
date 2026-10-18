#include "Turtle.h"

void Turtle::Init(Texture2D texture, Vector2 position, float speed)
{
    texture_ = texture;
    position_ = position;
    speed_ = speed;
}

void Turtle::Update(float deltaTime)
{
    position_.x += speed_ * deltaTime;
}

void Turtle::Draw() const
{
    DrawTextureV(texture_, position_, WHITE);
}

Rectangle Turtle::GetBounds() const
{
    return {
        position_.x,
        position_.y,
        static_cast<float>(texture_.width),
        static_cast<float>(texture_.height)
    };
}

Vector2 Turtle::GetPosition() const
{
    return position_;
}

void Turtle::SetPosition(Vector2 position)
{
    position_ = position;
}