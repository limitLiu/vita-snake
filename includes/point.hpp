#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H

struct Point {
    Point(double x, double y) {
      x_ = x;
      y_ = y;
    }

    ~Point() = default;

    [[nodiscard]] double x() const { return x_; }

    [[nodiscard]] double y() const { return y_; }

    double x_;
    double y_;
};

#endif
