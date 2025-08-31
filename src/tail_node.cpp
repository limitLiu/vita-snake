#include "tail_node.hpp"

#include <memory>

const double TailNode::MAX_DIST = 4;

void TailNode::addTo(GameObj *parent) {
  GameObj::load("snake_body", parent->getX(), parent->getY());
  parent->add(this);
  x_ = parent->getX();
  y_ = parent->getY();
}

void TailNode::addPath(Point *point) {
  if (path.empty()) {
    if (distanceTo(point->x(), point->y()) > TailNode::MAX_DIST)
      path.push(point);
  }
}

bool TailNode::collidesWith(GameObj *other, int nodeNumber) {
  if (!inMotion_) {
    return false;
  }

  if (nodeNumber > 10 && distanceTo(other) < 16) {
    return true;
  }
  if (nextNode_ != nullptr) {
    return nextNode_->collidesWith(other, nodeNumber + 1);
  }

  return false;
}

void TailNode::update() {
  GameObj::update();
  if (nextNode_ != nullptr) {
    nextNode_->speedDelta_ = speedDelta_;
    if (!nextNode_->path.empty()) {
      auto lastPath = nextNode_->path.back();
      if (distanceTo(lastPath->x(), lastPath->y()) > TailNode::MAX_DIST) {
        nextNode_->addPath(new Point(getX(), getY()));
      }
    }
  }

  if (path.empty()) {
    return;
  }

  auto target = path.front();
  auto distance = moveTo(target);

  if (distance > MAX_DIST) {
    distance = moveTo(target);
  }

  if (distance < MAX_DIST) {
    path.pop();
    if (nextNode_ != nullptr) {
      nextNode_->addPath(target);
    } else {
      delete target;
    }
  }
}

double TailNode::moveTo(Point *target) {
  if (speedDelta_ > MAX_DIST) {
    speedDelta_ = MAX_DIST;
  }

  if (distanceTo(target->x(), target->y()) > speedDelta_) {
    if (x_ < target->x()) {
      x_ += speedDelta_;
    }

    if (x_ > target->x()) {
      x_ -= speedDelta_;
    }

    if (y_ < target->y()) {
      y_ += speedDelta_;
    }

    if (y_ > target->y()) {
      y_ -= speedDelta_;
    }
  }
  inMotion_ = true;
  return distanceTo(target->x(), target->y());
}
