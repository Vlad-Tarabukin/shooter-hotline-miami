//
// Created by Vlad on 11.08.2023.
//

#ifndef SHOOTER_SILENCER_H
#define SHOOTER_SILENCER_H

#include "Weapon.h"
#include "../ShooterConsts.h"

class Silencer final : public Weapon {
public:
    explicit Silencer() : Weapon(60, 12, 2.0, 0.2, 100, 1.0,
                              ShooterConsts::SILENCER_FIRE_SOUND, false, ShooterConsts::RELOAD_SOUND,
                              ObjectNameTag("silencer"), ShooterConsts::SILENCER_OBJ, Vec3D{4, 4, 4},
                              Vec3D{-2.6, 1, 2.7},Vec3D{0, 0, 0}) {}
};


#endif //SHOOTER_SILENCER_H
