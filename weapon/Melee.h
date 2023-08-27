//
// Created by Vlad on 27.08.2023.
//

#ifndef SHOOTER_MELEE_H
#define SHOOTER_MELEE_H

#include <string>

#include <SFML/Audio/Sound.hpp>

#include <io/SoundController.h>
#include <geometry/Mesh.h>
#include <utils/Time.h>
#include <Camera.h>
#include <Consts.h>
#include <World.h>
#include "Weapon.h"

class Melee : public Weapon {
private:
    const double _fireDelay = 1; // time delay between fires
    const double _damage = 100;

    const std::string _fireSound;
    const bool _keepPlaying = false;

    double _lastFireTime = std::numeric_limits<double>::min();
public:
    explicit Melee(double fireDelay, double damage, std::string fireSound, bool keepPlaying, ObjectNameTag weaponName,
          const std::string &objFileName, const Vec3D &s, const Vec3D &t, const Vec3D &r);

    FireInformation
    fire(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction, const Vec3D &position,
         const Vec3D &direction) override;

    std::map<ObjectNameTag, double>
    attack(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction,
                const Vec3D &cameraPosition, const Vec3D &direction) const;

    [[nodiscard]] double fireDelay() const { return _fireDelay; }
};


#endif //SHOOTER_MELEE_H
