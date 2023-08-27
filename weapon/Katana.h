//
// Created by Vlad on 13.08.2023.
//

#ifndef SHOOTER_KATANA_H
#define SHOOTER_KATANA_H

#include "Melee.h"
#include "../ShooterConsts.h"

class Katana final : public Melee {
public:
    explicit Katana() : Melee(1.2, 1000,ShooterConsts::MELEE_FIRE_SOUND, false,
                              ObjectNameTag("katana"), ShooterConsts::KATANA_OBJ,
                              Vec3D{3.7, 5, 3.7}, Vec3D{-2.3, 0.8, 1.9},Vec3D{0, 0, 0}) {}
};


#endif //SHOOTER_KATANA_H
