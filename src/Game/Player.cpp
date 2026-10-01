#include "Player.h"

void Player::Init()
{
    textureUp_ = LoadTexture("resources/Game/Player_F.png");
    textureDown_ = LoadTexture("resources/Game/Player_D.png");
    textureLeft_ = LoadTexture("resources/Game/Player_L.png");
    textureRight_ = LoadTexture("resources/Game/Player_R.png");
}

void Player::Unload()
{
    UnloadTexture(textureUp_);
    UnloadTexture(textureDown_);
    UnloadTexture(textureLeft_);
    UnloadTexture(textureRight_);
}

void Player::Update(const ScreenLayout& layout)
{
    if (IsKeyPressed(KEY_W)) 
    {
        m_direction = Direction::Up;
        Move(-1, 0, layout);
    } 
    else if (IsKeyPressed(KEY_S))
    {
        m_direction = Direction::Down;
        Move(1, 0, layout);
    } 
    else if (IsKeyPressed(KEY_A))
    {
        m_direction = Direction::Left;
        Move(0, -1, layout);
    }
    else if (IsKeyPressed(KEY_D))
    {
        m_direction = Direction::Right;
        Move(0, 1, layout);
    }
}

void Player::Move(int rowOffset, int columnOffset, const ScreenLayout& layout)
{
    const int newRow = row_ + rowOffset;
    const int newColumn = column_ + columnOffset;
    if (!layout.IsValidCell(newRow, newColumn)) { return; }

    row_ = newRow;
    column_ = newColumn;
}

void Player::Draw(const ScreenLayout& layout) const
{
    const Vector2 center = layout.GetCellCenter(row_, column_);
    const Texture2D* texture = &textureUp_;

    switch (m_direction)
    {
    case Direction::Up:
        texture = &textureUp_;
        break;

    case Direction::Down:
        texture = &textureDown_;
        break;

    case Direction::Left:
        texture = &textureLeft_;
        break;

    case Direction::Right:
        texture = &textureRight_;
        break;
    }

    // Place texture center exactly on cell center
    const Vector2 position {
        center.x - texture->width / 2.0f,
        center.y - texture->height / 2.0f
    };

    DrawTextureV(*texture, position, WHITE);
}