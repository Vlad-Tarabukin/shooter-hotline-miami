//
// Created by Иван Ильин on 02.06.2021.
//

#ifndef SHOOTER_MAC10_H
#define SHOOTER_MAC10_H

#include "Weapon.h"
#include "../ShooterConsts.h"

class Mac10 final : public Weapon {
public:
    explicit Mac10() : Weapon(125, 25, 2, 0.03, 20, 3.5,
                             ShooterConsts::MAC10_FIRE_SOUND, ShooterConsts::RELOAD_SOUND,
                             ObjectNameTag("mac10"), ShooterConsts::MAC10_OBJ,
                             Vec3D{3.7, 3.7, 3.7}, Vec3D{-2.3, 0.8, 1.9},Vec3D{0, 0, 0}) {}
};

#endif //SHOOTER_3DZAVR_MAC10_H
