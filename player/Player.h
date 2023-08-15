//
// Created by Иван Ильин on 14.03.2021.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H

#include <utility>

#include <SFML/Audio/Sound.hpp>

#include <utils/ResourceManager.h>
#include <Camera.h>
#include <World.h>

#include "../weapon/Ak47.h"
#include "../weapon/Shotgun.h"
#include "../weapon/Gun.h"
#include "../weapon/Gold_Ak47.h"
#include "../weapon/Rifle.h"
#include "../weapon/Mac10.h"
#include "../weapon/Silencer.h"
#include "../weapon/Bat.h"
#include "../weapon/Knife.h"
#include "../weapon/Katana.h"
#include "../weapon/Flamethrower.h"
#include "../ShooterConsts.h"


class Player final : public RigidBody {
private:
    double _health = ShooterConsts::HEALTH_MAX;
    double _ability = ShooterConsts::ABILITY_MAX;

    double _headAngle = 0;

    int _kills = 0;
    int _deaths = 0;

    std::vector<std::shared_ptr<Weapon>> _weapons;
    size_t _selectedWeapon = 0;

    bool _isPickingUp = false;

    std::string _nickName = ShooterConsts::PLAYER_NAME;

    std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> _rayCastFunction;

    void collisionWithObject(const ObjectNameTag &tag, std::shared_ptr<RigidBody> obj);

public:
    explicit Player(ObjectNameTag name, const std::string &filename = ShooterConsts::CUBE_OBJ, const Vec3D &scale = Vec3D{1, 1, 1});

    void setHealth(double h) { _health = h; }

    void setAbility(double a) { _ability = a; }

    void setPickingUp(bool p) { _isPickingUp = p; }

    [[nodiscard]] double health() const { return _health; }

    [[nodiscard]] double ability() const { return _ability; }

    void setFullHealth();

    void setFullAbility();

    void reInitWeapons();

    void addWeapon(std::shared_ptr<Weapon> weapon);

    void selectWeapon(int index);

    bool fire();

    void reload();

    [[nodiscard]] std::shared_ptr<Weapon> weapon() const { return _weapons[_selectedWeapon]; }

    void rotateWeaponsRelativePoint(const Vec3D &point, const Vec3D &v, double val);

    [[nodiscard]] int kills() const { return _kills; }

    [[nodiscard]] int deaths() const { return _deaths; }

    void addKill() { _kills++; }

    void addDeath() { _deaths++; }

    void setKills(int kills) { _kills = kills; }

    void setDeaths(int deaths) { _deaths = deaths; }

    void setRayCastFunction(std::function<IntersectionInformation(const Vec3D &, const Vec3D &)> rayCastFunction) {
        _rayCastFunction = std::move(rayCastFunction);
    }

    // This is for situation when you want to store the position of the head but you dont have attached camera
    void setHeadAngle(double a) { _headAngle = a; }

    [[nodiscard]] double headAngle() const { return _headAngle; };

    [[nodiscard]] std::string playerNickName() const { return _nickName; }

    void setPlayerNickName(const std::string &name) { _nickName = name; }

    void selectWeaponAnimation();

    void fireWeaponAnimation();

    void meleeFireWeaponAnimation();

    void reloadWeaponAnimation();

    void throwWeapon();
};


#endif //MINECRAFT_3DZAVR_PLAYER_H
