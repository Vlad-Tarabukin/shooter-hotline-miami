//
// Created by Иван Ильин on 25.05.2021.
//

#ifndef SHOOTER_SERVER_H
#define SHOOTER_SERVER_H

#include "network/ServerUDP.h"
#include "Player.h"
#include "Bonus.h"

struct BonusInfo {
    Point4D position;
    double lastTake;
    bool onTheMap;
};

class Server : public ServerUDP {
private:
    std::map<sf::Uint16, std::shared_ptr<Player>> _players{};
    std::map<std::string, BonusInfo> _bonuses{};
    double _bonusRechargeTime = 60;

public:
    Server() = default;

    void broadcast() override;

    void processConnect(sf::Uint16 senderId) override;
    void processClientUpdate(sf::Uint16 senderId, sf::Packet& packet) override;
    void processDisconnect(sf::Uint16 senderId) override;

    void processCustomPacket(MsgType type, sf::Packet& packet, sf::Uint16 senderId) override;

    void processStop() override;

    void generateBonuses();

    void updateInfo() override;
};


#endif //MINECRAFT_3DZAVR_SERVER_H
