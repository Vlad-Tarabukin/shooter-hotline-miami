//
// Created by Vlad on 27.08.2023.
//

#include <utils/EventHandler.h>
#include <utils/Log.h>

#include "../ShooterConsts.h"
#include "Melee.h"


using namespace std;

Melee::Melee(double fireDelay, double damage, std::string fireSound, bool keepPlaying, ObjectNameTag weaponName,
             const string &objFileName, const Vec3D &s, const Vec3D &t, const Vec3D &r) : Weapon(std::move(weaponName), objFileName),
                                                                    _fireDelay(fireDelay), _damage(damage),
                                                                    _fireSound(std::move(fireSound)), _keepPlaying(keepPlaying) {

    loadObj(objFileName, s);
    setCollider(false);
    rotate(r);
    translate(t);
}

FireInformation Melee::fire(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction,
                             const Vec3D &position, const Vec3D &direction) {

    if (std::abs(Time::time() - _lastFireTime) < _fireDelay) {
        return FireInformation{std::map<ObjectNameTag, double>(), false};
    }

    _lastFireTime = Time::time();

    if(!_keepPlaying || SoundController::getStatus(SoundTag("fireSound_" + name().str())) != sf::Sound::Status::Playing) {
        SoundController::loadAndPlay(SoundTag("fireSound_" + name().str()), _fireSound);
        EventHandler::call<void(Vec3D, std::string)>(Event("your_fire_sound"), position, _fireSound);
    }
    Log::log("Melee::fire");

    EventHandler::call<void()>(Event("melee_fire"));
    return FireInformation{attack(std::move(rayCastFunction), position, direction), true};
}

std::map<ObjectNameTag, double>
Melee::attack(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction,
                    const Vec3D &cameraPosition, const Vec3D &direction) const {
    std::map<ObjectNameTag, double> damagedPlayers;

    // damage player
    auto rayCast = rayCastFunction(cameraPosition, cameraPosition + direction * ShooterConsts::MELEE_ATTACK_RANGE);
    if (rayCast.objectName.contains(ObjectNameTag("Enemy"))) {

        damagedPlayers[rayCast.objectName] += _damage / (1.0 + rayCast.distanceToObject);

        // If you hit the head the damage will be doubled
        if (rayCast.objectName.contains(ObjectNameTag("head"))) {
            damagedPlayers[rayCast.objectName] += _damage / (1.0 + rayCast.distanceToObject);
        }
        // If you hit the foot the damage will be divided by 2
        if (rayCast.objectName.contains(ObjectNameTag("foot"))) {
            damagedPlayers[rayCast.objectName] -= 0.5 * _damage / (1.0 + rayCast.distanceToObject);
        }
    }

    return damagedPlayers;
}
