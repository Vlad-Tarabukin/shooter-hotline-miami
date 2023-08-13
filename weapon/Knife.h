//
// Created by Vlad on 13.08.2023.
//

#ifndef SHOOTER_KNIFE_H
#define SHOOTER_KNIFE_H

#include "Weapon.h"
#include "../ShooterConsts.h"

class Knife final : public Weapon {
public:
    explicit Knife() : Weapon(0.2, 100, true,
                              ShooterConsts::MELEE_FIRE_SOUND,
                              ObjectNameTag("knife"), ShooterConsts::KNIFE_OBJ,
                              Vec3D{3.7, 3.7, 3.7}, Vec3D{-2.3, 1.5, 1.9},Vec3D{0, 0, 0}) {}
};


#endif //SHOOTER_KNIFE_H
