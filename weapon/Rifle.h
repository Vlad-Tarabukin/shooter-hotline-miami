//
// Created by Иван Ильин on 06.06.2021.
//

#ifndef SHOOTER_RIFLE_H
#define SHOOTER_RIFLE_H

#include "Weapon.h"
#include "../ShooterConsts.h"

class Rifle final : public Weapon {
public:
    explicit Rifle() : Weapon(5, 5, 1.0, 1.0, 10000, 0.5,
                              ShooterConsts::RIFLE_FIRE_SOUND, false, ShooterConsts::RELOAD_SOUND,
                              ObjectNameTag("rifle"), ShooterConsts::RIFLE_OBJ, Vec3D{3, 3, 3},
                              Vec3D{-2.6, 1, 1.5},Vec3D{0, 0, 0}) {}
};


#endif //SHOOTER_3DZAVR_RIFLE_H
