//
// Created by mason on 1/14/2025.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "engine/engine.hpp"
#include "game/physics/object.hpp"



struct VerletObject {
    Vec2 position_current;
    Vec2 position_old;
    Vec2 acceleration;

    void updatePosition(float dt) {
      // Compute velocity
      const Vec2 velocity = position_current - position_old;
      // Save current position
      position_old = position_current;
      // Perform verlet integration
      position_current = position_current + velocity + acceleration * dt * dt;
      // Reset acceleration
      acceleration = {};
    }

    void accelerate(Vec2 acc) {
        acceleration += acc;
    }
};

struct Solver {
  Vec2 gravity = {0.0f, 1000.0f};

  void update(float dt)
  {
    applyGravity();
    applyConstraint();
    updatePositions(dt);
  }

  void updatePositions(float dt)
  {
    core::foreach<VerletObject>([](VerletObject& obj) {
      obj.updatePosition(dt);
    });
  }

  void applyGravity()
  {
    core::foreach<VerletObject>([this](VerletObject& obj) {
      obj.accelerate(gravity);
    });
  }

  void applyConstraint()
  {
    const Vec2 position{800.0f, 450.0f};
    const float radius = 400.0f;
    core::foreach<VerletObject>([&](VerletObject& obj) {
      const Vec2 to_obj = obj.position_current - position;
      const float dist = MathVec2::length(to_obj);
      // 50 is the default radius
      if (dist > radius - 50.0f) {
        const Vec2 n = to_obj / dist;
        obj.position_current = position + n * (dist - 50.0f);
      }
    });
  }

};



#endif //SOLVER_H
