//
// Created by mason on 1/14/2025.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "engine/engine.hpp"



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



#endif //SOLVER_H
