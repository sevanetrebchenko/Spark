#include "world.h"

namespace Spark {
    World* World::_world = nullptr;

    ECS::Entities::EntityManager *World::GetEntityManager() {
        return &_entityManager;
    }

    World &World::GetInstance() {
        if (!_world) {
            _world = new World();
        }

        return *_world;
    }
}
