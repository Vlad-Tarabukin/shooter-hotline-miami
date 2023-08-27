//
// Created by Vlad on 15.08.2023.
//

#ifndef SHOOTER_FLAMETHROWER_H
#define SHOOTER_FLAMETHROWER_H

#include "Weapon.h"
#include "../ShooterConsts.h"
#include "utils/EventHandler.h"

class Flamethrower final : public Weapon {
public:
    explicit Flamethrower() : Weapon(400, 100, 4.0, 0.01, 0, 0, ShooterConsts::FLAMETHROWER_FIRE_SOUND, true,
                                ShooterConsts::RELOAD_SOUND, ObjectNameTag("flamethrower"),
                                ShooterConsts::FLAMETHROWER_OBJ,
                                Vec3D{3, 3, 3}, Vec3D{-2.1, 0.8, 1.9}, Vec3D{0, 0, 0}) {}

    std::map<ObjectNameTag, double>
    processFire(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction,
                const Vec3D &position, const Vec3D &direction) const override {
        EventHandler::call<void(Vec3D, Vec3D, bool)>(Event("add_flame"), position, direction, false);
        EventHandler::call<void(Vec3D, Vec3D)>(Event("your_flame"), position, direction);
        return {};
    }
};

#endif //SHOOTER_FLAMETHROWER_H
