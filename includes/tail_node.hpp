#ifndef SNAKE_TAIL_NODE_H
#define SNAKE_TAIL_NODE_H

#include "game_obj.hpp"
#include "point.hpp"
#include <memory>
#include <queue>

class TailNode : public GameObj {
public:
    static const double MAX_DIST;

    TailNode() = default;

    ~TailNode() = default;

    void addTo(GameObj *parent);

    void addPath(Point *point);

    bool collidesWith(GameObj *other, int nodeNumber);

    double moveTo(Point *target);

    void update() override;

    TailNode *nextNode_ = nullptr;
    std::queue<Point *> path;
    double speedDelta_ = 0;
    bool inMotion_ = false;
};

#endif
