#include "player.hpp"

Player::Player(int x, int y) {
  GameObj::load("snake_head", x, y);
}

void Player::update() {
  GameObj::update();
  auto delta = speed_ * timeDelta_;
  nextNode_->speedDelta_ = delta;
  switch (direction) {
    case Left:
      x_ -= delta;
      break;
    case Right:
      x_ += delta;
      break;
    case Up:
      y_ -= delta;
      break;
    case Down:
      y_ += delta;
      break;
  }

  if (nextNode_->collidesWith(this, 0)) {
    reset();
  }

  if (!nextNode_->path.empty()) {
    auto lastPath = nextNode_->path.back();
    if (distanceTo(lastPath->x(), lastPath->y()) > delta) {
      nextNode_->addPath(new Point(getX(), getY()));
    }
  } else if (distanceTo(nextNode_->getX(), nextNode_->getY()) > delta) {
    nextNode_->addPath(new Point(getX(), getY()));
  }
}

bool Player::perpendicularTo(Direction d) const {
  switch (direction) {
    case Left:
    case Right: {
      switch (d) {
        case Up:
        case Down:
          return true;
        default:
          break;
      }
      break;
    }

    case Up:
    case Down: {
      switch (d) {
        case Left:
        case Right:
          return true;
        default:
          break;
      }
      break;
    }
  }
  return false;
}

void Player::setDirection(Direction d) {
  if (perpendicularTo(d)) {
    direction = d;
    nextNode_->addPath(new Point(getX(), getY()));
  }
}

void Player::grow() {
  auto node = new TailNode();
  if (nextNode_ == nullptr) {
    node->addTo(this);
    nextNode_ = node;
  } else {
    node->addTo(lastNode_);
    lastNode_->nextNode_ = node;
  }
  lastNode_ = node;
}

void Player::reset() {
  speed_ = 0;
}

Player::~Player() = default;
