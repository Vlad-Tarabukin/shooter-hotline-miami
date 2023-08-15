//
// Created by Vlad on 15.08.2023.
//

#ifndef SHOOTER_FLAME_H
#define SHOOTER_FLAME_H

#include <World.h>
#include "../ShooterConsts.h"
#include "utils/EventHandler.h"

class Flame final : public RigidBody {
private:
    double _damage = ShooterConsts::FLAME_DAMAGE;

    void collisionWithObject(const ObjectNameTag &tag, std::shared_ptr<RigidBody> obj) {
        if (tag.str().find("Enemy") != std::string::npos) {
            sf::Uint16 targetId = std::stoi(tag.str().substr(6));
            EventHandler::call<void(sf::Uint16, double)>(Event("damage_player"), targetId, _damage);
        }
    }
public:
    explicit Flame() : RigidBody(ObjectNameTag("flame_" + std::to_string(rand()))) {

        double s = 2 * (1.5 - 0.5 * static_cast<double>(rand()) / RAND_MAX);

        loadObj(ShooterConsts::FLAME_OBJ, Vec3D{s, s, s});
        setAcceleration(Vec3D{0, -ShooterConsts::GRAVITY, 0});
        setCollision(true);
        setCollider(false);

        setCollisionCallBack([this](const ObjectNameTag &tag, std::shared_ptr<RigidBody> obj) { collisionWithObject(tag, obj); });
    }

    void setDamage (double damage) { _damage = damage;}
};

#endif //SHOOTER_FLAME_H
