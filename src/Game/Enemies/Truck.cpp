#include "Truck.h"

void Truck::Init(Texture2D texture, Vector2 position, float speed)
{
    texture_ = texture;
    position_ = position;
    speed_ = speed;
}

void Truck::Update(float deltaTime)
{
    position_.x += speed_ * deltaTime;
}

void Truck::Draw() const
{
    DrawTextureV(texture_, position_, WHITE);
}

Rectangle Truck::GetBounds() const
{
    return {
        static_cast<float>(position_.x),
        static_cast<float>(position_.y),
        static_cast<float>(texture_.width),
        static_cast<float>(texture_.height)
    };
}

void Truck::SetPosition(Vector2 position)
{
    position_ = position;
}

Vector2 Truck::GetPosition() const
{
    return position_;
}

float Truck::GetSpeed() const
{
    return speed_;
}