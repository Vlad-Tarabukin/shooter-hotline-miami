//
// Created by Иван Ильин on 22.09.2021.
//

#ifndef SHOOTER_SHOOTER_H
#define SHOOTER_SHOOTER_H

#include <Engine.h>
#include <gui/Window.h>

#include "player/Player.h"
#include "player/PlayerController.h"
#include "player/PlayerController.h"
#include "network/ShooterClient.h"
#include "network/ShooterServer.h"

class Shooter final : public Engine {
private:
    std::shared_ptr<Player> player = std::make_shared<Player>(ObjectNameTag("Player"),
                                                              ShooterConsts::CUBE_OBJ,
                                                              Vec3D{1.5, 1.8, 1.5});
    std::shared_ptr<PlayerController> playerController = std::make_shared<PlayerController>(player, keyboard, mouse);

    Window mainMenu;

    std::shared_ptr<ShooterServer> server = std::make_shared<ShooterServer>();
    std::shared_ptr<ShooterClient> client = std::make_shared<ShooterClient>(player);
    std::shared_ptr<ChatManager> chat = std::make_shared<ChatManager>();
    bool isTypingMessage = false;
    std::string message;

    bool inGame = false;
    int fireTraces = 0;
    std::string current_map = ShooterConsts::BIG_MAP_OBJ;

    void start() override;
    void update() override;
    void gui() override;
    void drawChat();
    void play();
    void drawPlayerStats();
    void drawStatsTable();

    void initNetwork();

    void spawnPlayer(sf::Uint16 id);
    void removePlayer(sf::Uint16 id);
    void addFireTrace(const Vec3D &from, const Vec3D &to);
    void removeFireTrace(const ObjectNameTag &traceName);
    void addBonus(const std::string &bonusName, const Vec3D &position);
    void removeBonus(const ObjectNameTag &bonusName);
    void addWeapon(std::shared_ptr<Weapon> weapon);
    void removeWeapon(std::shared_ptr<Weapon> weapon);
    void changeEnemyWeapon(const std::string &weaponName, sf::Uint16 enemyId);
    void addFlame(const Vec3D &position, const Vec3D &direction, bool isEnemy);
    void removeFlame(ObjectNameTag tag);

public:
    Shooter() : mainMenu(screen, mouse) {};
};


#endif //SHOOTER_SHOOTER_H
