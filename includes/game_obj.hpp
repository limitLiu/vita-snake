#ifndef SNAKE_GAME_OBJ_H
#define SNAKE_GAME_OBJ_H

#include <string>
#include <vector>

enum Direction {
    Up, Right, Down, Left
};

class GameObj {
public:
    GameObj() = default;

    ~GameObj();

    void load(std::string texture, double x, double y);

    virtual void render();

    virtual void update();

    virtual void add(GameObj *child);

    virtual double distanceTo(GameObj *other);

    virtual double distanceTo(double x, double y);

    GameObj *parent = nullptr;
    std::vector<GameObj *> children;

    [[nodiscard]] double getX() const { return x_; }

    [[nodiscard]] double getY() const { return y_; }

protected:
    double x_ = 0;
    double y_ = 0;
    std::string texture_;
    int lastUpdate_ = 0;
    double timeDelta_{};
};

#endif
