//
// Created by Иван Ильин on 14.03.2021.
//

#include <utility>

#include <animation/Animations.h>
#include <utils/EventHandler.h>
#include <utils/Log.h>
#include <io/Screen.h>

#include "Player.h"
#include "../weapon/Mac10.h"
#include "../weapon/Silencer.h"

Player::Player(ObjectNameTag name, const std::string &filename, const Vec3D &scale) : RigidBody(std::move(name), filename, scale) {
    setAcceleration(Vec3D{0, -ShooterConsts::GRAVITY, 0});
    setCollision(true);
    setVisible(false);
    setColor(sf::Color(0,0,0));

    setCollisionCallBack([this](const ObjectNameTag &tag, std::shared_ptr<RigidBody> obj) { collisionWithObject(tag, obj); });
}

void Player::rotateWeaponsRelativePoint(const Vec3D &point4D, const Vec3D &v, double val) {
    for (auto &weapon : _weapons) {
        weapon->rotateRelativePoint(point4D, v, val);
    }
}

void Player::collisionWithObject(const ObjectNameTag &tag, std::shared_ptr<RigidBody> obj) {
    if (tag.str().find("Bonus_gun") != std::string::npos) {
        addWeapon(std::make_shared<Gun>());
    }

    if (tag.str().find("Bonus_shotgun") != std::string::npos) {
        addWeapon(std::make_shared<Shotgun>());
    }

    if (tag.str().find("Bonus_ak47") != std::string::npos) {
        addWeapon(std::make_shared<Ak47>());
    }

    if (tag.str().find("Bonus_gold_ak47") != std::string::npos) {
        addWeapon(std::make_shared<Gold_Ak47>());
    }

    if (tag.str().find("Bonus_rifle") != std::string::npos) {
        addWeapon(std::make_shared<Rifle>());
    }

    if (tag.str().find("Bonus_mac10") != std::string::npos) {
        addWeapon(std::make_shared<Mac10>());
    }

    if (tag.str().find("Bonus_silencer") != std::string::npos) {
        addWeapon(std::make_shared<Silencer>());
    }

    if (tag.str().find("Bonus_hill") != std::string::npos) {
        setFullHealth();
    }

    if (tag.str().find("Bonus_ability") != std::string::npos) {
        setFullAbility();
    }

    if (tag.str().find("Bonus") != std::string::npos) {
        EventHandler::call<void(const std::string&)>(Event("take_bonus"), tag.str());
    }
}

void Player::addWeapon(std::shared_ptr<Weapon> weapon) {
    SoundController::loadAndPlay(SoundTag("changeWeapon"), ShooterConsts::CHANGE_WEAPON_SOUND);

    for (int i = 0; i < _weapons.size(); i++) {
        std::shared_ptr<Weapon> &w = _weapons[i];
        if (w->name() == weapon->name()) {
            w->refillAPack();
            if(_selectedWeapon != i){
                selectWeapon(i);
            }
            return;
        }
    }

    _weapons.push_back(weapon);
    attach(weapon);

    selectWeapon((_selectedWeapon + 1) % _weapons.size());

    _weapons.back()->translate(position());
    _weapons.back()->rotateRelativePoint(position() + Vec3D{0, 1.8, 0}, Vec3D{0, 1, 0}, angle().y());
    _weapons.back()->rotateRelativePoint(position() + Vec3D{0, 1.8, 0}, left(), headAngle());
}

void Player::reInitWeapons() {

    if (!_weapons.empty()) {
        for (auto weapon : _weapons) {
            unattach(ObjectNameTag(weapon->name()));
        }

        EventHandler::call<void(std::shared_ptr<Weapon>)>(Event("remove_weapon"),
                                                          _weapons[_selectedWeapon]);
        selectWeapon(0);
        _weapons.clear();
    }
    addWeapon(std::make_shared<Gun>());
    addWeapon(std::make_shared<Shotgun>());
    addWeapon(std::make_shared<Ak47>());
    addWeapon(std::make_shared<Gold_Ak47>());
    addWeapon(std::make_shared<Rifle>());
    addWeapon(std::make_shared<Mac10>());
    addWeapon(std::make_shared<Silencer>());
    selectWeapon(0);

    EventHandler::call<void(std::shared_ptr<Weapon>)>(Event("add_weapon"),
                                                      _weapons[_selectedWeapon]);
}

void Player::selectWeapon(int index) {
    if (_weapons.size() > 1) {
        // change '_selectedWeapon'
        EventHandler::call<void(std::shared_ptr<Weapon>)>(Event("remove_weapon"),
                                                          _weapons[_selectedWeapon]);

        _selectedWeapon = index;

        EventHandler::call<void(std::shared_ptr<Weapon>)>(Event("add_weapon"),
                                                          _weapons[_selectedWeapon]);

        Log::log("selectedWeapon " + std::to_string(_selectedWeapon));
        SoundController::loadAndPlay(SoundTag("changeWeapon"), ShooterConsts::CHANGE_WEAPON_SOUND);
        selectWeaponAnimation();
    }

}

bool Player::fire() {
    auto camera = attached(ObjectNameTag("Camera"));
    if (camera != nullptr) {
        auto fireInfo = _weapons[_selectedWeapon]->fire(_rayCastFunction, camera->position(), camera->lookAt());
        for (auto&[damagedPlayerName, damage] : fireInfo.damagedPlayers) {
            sf::Uint16 targetId = std::stoi(damagedPlayerName.str().substr(6));
            EventHandler::call<void(sf::Uint16, double)>(Event("damage_player"), targetId, damage);
        }
        return fireInfo.shot;
    }
    return false;
}

void Player::reload() {
    _weapons[_selectedWeapon]->reload();
}

void Player::setFullHealth() {
    _health = ShooterConsts::HEALTH_MAX;
    SoundController::loadAndPlay(SoundTag("addHealth"), ShooterConsts::RESTORE_HEALTH_SOUND);
}

void Player::setFullAbility() {
    _ability = ShooterConsts::ABILITY_MAX;
    SoundController::loadAndPlay(SoundTag("addAbility"), ShooterConsts::RESTORE_ABILITY_SOUND);
}

void Player::selectWeaponAnimation() {
    Timeline::addAnimation<ARotateLeft>(AnimationListTag("select_weapon"),
                                        _weapons[_selectedWeapon],
                                        -2 * Consts::PI,
                                        0.3,
                                        Animation::LoopOut::None,
                                        Animation::InterpolationType::Cos);
}

void Player::fireWeaponAnimation() {
    Timeline::addAnimation<ARotateLeft>(AnimationListTag("fire_weapon"),
                                        _weapons[_selectedWeapon],
                                        -_weapons[_selectedWeapon]->fireDelay(),
                                        _weapons[_selectedWeapon]->fireDelay()/3,
                                        Animation::LoopOut::None,
                                        Animation::InterpolationType::Cos);
    Timeline::addAnimation<AWait>(AnimationListTag("fire_weapon"), 0);
    Timeline::addAnimation<ARotateLeft>(AnimationListTag("fire_weapon"),
                                        _weapons[_selectedWeapon],
                                        _weapons[_selectedWeapon]->fireDelay(),
                                        _weapons[_selectedWeapon]->fireDelay()/3,
                                        Animation::LoopOut::None,
                                        Animation::InterpolationType::Cos);
}

void Player::reloadWeaponAnimation() {
    Timeline::addAnimation<ARotateLeft>(AnimationListTag("reload_weapon"),
                                        _weapons[_selectedWeapon],
                                        -2 * Consts::PI,
                                        _weapons[_selectedWeapon]->reloadTime() / 2,
                                        Animation::LoopOut::None,
                                        Animation::InterpolationType::Cos);
}
