#include "Player.h"

void Player::Init()
{
    ResetPosition();
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

bool Player::Update(const ScreenLayout& layout)
{
    if (IsKeyPressed(KEY_W)) 
    {
        direction_ = Direction::Up;
        Move(-1, 0, layout);
        return true;
    } 
    else if (IsKeyPressed(KEY_S))
    {
        direction_ = Direction::Down;
        Move(1, 0, layout);
        return true;
    } 
    else if (IsKeyPressed(KEY_A))
    {
        direction_ = Direction::Left;
        Move(0, -1, layout);
        return true;
    }
    else if (IsKeyPressed(KEY_D))
    {
        direction_ = Direction::Right;
        Move(0, 1, layout);
        return true;
    }

    return false;
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
    Vector2 center = layout.GetCellCenter(row_, column_);
    center.x += horizontalOffset_;

    const Texture2D* texture = &textureUp_;

    switch (direction_)
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

void Player::AddHorizontalOffset(float amount, const ScreenLayout& layout)
{
    horizontalOffset_ += amount;

    // Mantener sincronizada la posición lógica con la visual
    while (horizontalOffset_ >= ScreenLayout::CELL_SIZE &&
        column_ < ScreenLayout::COLUMNS - 1)
    {
        ++column_;
        horizontalOffset_ -= ScreenLayout::CELL_SIZE;
    }

    while (horizontalOffset_ <= -ScreenLayout::CELL_SIZE &&
        column_ > 0)
    {
        --column_;
        horizontalOffset_ += ScreenLayout::CELL_SIZE;
    }

    // Evitar que la rana salga del layout
    Rectangle bounds = GetBounds(layout);

    const float rightOverflow =
        bounds.x + bounds.width - layout.GetRight();

    if (rightOverflow > 0.0f)
    {
        horizontalOffset_ -= rightOverflow;
    }
}

Rectangle Player::GetBounds(const ScreenLayout& layout) const
{
    // All textures have same bounds
    const Texture2D* texture = &textureUp_;
    
    Vector2 center = layout.GetCellCenter(row_, column_);
    center.x += horizontalOffset_;

    return {
        static_cast<float>(center.x - texture->width / 2),
        static_cast<float>(center.y - texture->height / 2),
        static_cast<float>(texture->width),
        static_cast<float>(texture->height)
    };
}

void Player::ResetPosition()
{
    row_ = startingRow_;
    column_ = startingCol_;
    direction_ = Direction::Up;
    horizontalOffset_ = 0.f;
}

std::pair<int, int> Player::GetColumnRow() const
{
    return { column_, row_ };
}