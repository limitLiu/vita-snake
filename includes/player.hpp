#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include "game_obj.hpp"
#include "tail_node.hpp"

class Player : public GameObj {
public:
    Player(int x, int y);

    void update() override;

    ~Player();

    void reset();

    void grow();

    [[nodiscard]] bool perpendicularTo(Direction d) const;

    void setDirection(Direction d);

    Direction direction = Down;

private:
    int speed_ = 128;

    TailNode *lastNode_ = nullptr;
    TailNode *nextNode_ = nullptr;
};

#endif
