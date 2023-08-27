//
// Created by Vlad on 13.08.2023.
//

#ifndef SHOOTER_BAT_H
#define SHOOTER_BAT_H

#include "Melee.h"
#include "../ShooterConsts.h"

class Bat final : public Melee {
public:
    explicit Bat() : Melee(0.8, 150, ShooterConsts::MELEE_FIRE_SOUND, false,
                              ObjectNameTag("bat"), ShooterConsts::BAT_OBJ,
                              Vec3D{3.7, 3.7, 3.7}, Vec3D{-2.3, 0.8, 1.9},Vec3D{0, 0, 0}) {}
};


#endif //SHOOTER_BAT_H
