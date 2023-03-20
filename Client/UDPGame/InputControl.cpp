/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputControl
*/

#include <iostream>
#include "ClientGame.hpp"
#include "ClientUDPSingletons.hpp"
#include "Serialization.hpp"

/**
 * @brief 
 * Move the player according to it's position and direction
 * 
 * @param r 
 * @param singletons 
 * @param playerID 
 * @param movement 
 */
void updatePlayerDirection(Registry &r, EngineComponent::Singletons &singletons, std::size_t &playerID, std::pair<float, float> &&movement)
{
    auto &velocities = r.getComponents<EngineComponent::Direction>();
    auto &animations = r.getComponents<EngineComponent::SpriteSheet>();

    if (playerID < velocities.size()) {
        auto &velocity = velocities[playerID];
        auto &animation = animations[playerID];

        if (velocity) {
            velocity->xDirection = movement.first;
            velocity->yDirection = movement.second;
            if (!animation)
                return;
            if (velocity->xDirection == 0 && velocity->yDirection == 0) // static animation
                animation->rec.x = animation->xStartPoint + (animation->xFrameSpeed * EngineClient::UDP::MovementAnimation::STATIC);
            else if (velocity->yDirection != 0) { // UP DOWN MOVEMENT
                if (velocity->yDirection < 0) {// Up animation
                    animation->rec.x = animation->xStartPoint + (animation->xFrameSpeed * EngineClient::UDP::MovementAnimation::UP);
                }
                if (velocity->yDirection > 0) // Down animation
                    animation->rec.x = animation->xStartPoint + (animation->xFrameSpeed * EngineClient::UDP::MovementAnimation::DOWN);
            } else { // LEFT RIGHT MOVEMENT
                if (velocity->xDirection > 0) // Right animation
                    animation->rec.x = animation->xStartPoint + (animation->xFrameSpeed * EngineClient::UDP::MovementAnimation::RIGHT);
                if (velocity->xDirection < 0) // Left animation
                    animation->rec.x = animation->xStartPoint + (animation->xFrameSpeed * EngineClient::UDP::MovementAnimation::LEFT);
            }
        }
    }
}

/**
 * @brief 
 * Change the direction of the player with key pressed
 * 
 * @param r 
 * @param singletons 
 * @param interaction 
 * @param client 
 */
void movementControl(Registry &r, EngineComponent::Singletons &singletons, std::unique_ptr<PadaEngine::Iinteraction> &interaction, std::unique_ptr<EngineNetwork::INetwork> &client)
{
    std::size_t &playerID = singletons.getSingleton<std::size_t>(EngineClient::UDP::SingletonsEnum::ID);
    auto &lastMove = singletons.getSingleton<std::pair<float, float>>(EngineClient::UDP::SingletonsEnum::LAST_MOVE);
    float moveX = 0;
    float moveY = 0;

    if (interaction.get()->isKeyDowned(EngineComponent::KEY_VALUE::ARROW_LEFT))
        moveX = -10;
    if (interaction.get()->isKeyDowned(EngineComponent::KEY_VALUE::ARROW_RIGHT))
        moveX = 10;
    if (interaction.get()->isKeyDowned(EngineComponent::KEY_VALUE::ARROW_UP))
        moveY = -5;
    if (interaction.get()->isKeyDowned(EngineComponent::KEY_VALUE::ARROW_DOWN))
        moveY = 5;

    // If moved send it to the server
    // If movement is the same as the last movement don't send, so the server receive only movement change
    if ((moveX != 0 || moveY != 0) && (lastMove.first != moveX || lastMove.second != moveY)) {
        EngineUtils::DeltaTime &deltaTime = singletons.getSingleton<EngineUtils::DeltaTime>(EngineClient::UDP::DELTA_TIME);
        lastMove.first = moveX; // update last move
        lastMove.second = moveY;
        moveX *= 60;
        moveY *= 60;
        updatePlayerDirection(r, singletons, playerID, {moveX, moveY});
        try {
            EngineNetwork::UDPDataStructure::PlayerMove movement = EngineNetwork::UDPDataStructure::convertToPlayerMove(playerID - 100, moveX, moveY);
            auto message = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::PlayerMove>({EngineNetwork::UDPDataStructure::MOVE_PLAYER},
            movement);
            std::cout << "Sending to server movement [" << movement.moveX << ", " << movement.moveY << "] from player " << playerID - 100<< "\n";
            client.get()->writeToAll(message);
        } catch (std::bad_cast const &error) {
        }
    }

    // If release move key set movement to 0
    if (interaction.get()->isKeyReleased(EngineComponent::KEY_VALUE::ARROW_LEFT)
     || interaction.get()->isKeyReleased(EngineComponent::KEY_VALUE::ARROW_RIGHT)
     || interaction.get()->isKeyReleased(EngineComponent::KEY_VALUE::ARROW_UP)
     || interaction.get()->isKeyReleased(EngineComponent::KEY_VALUE::ARROW_DOWN)) {
        try {
            lastMove.first = 0; // update last move
            lastMove.second = 0;
            updatePlayerDirection(r, singletons, playerID, {moveX, moveY});
            EngineNetwork::UDPDataStructure::PlayerMove movement = EngineNetwork::UDPDataStructure::convertToPlayerMove(playerID - 100, 0, 0);
            auto message = EngineNetwork::Serialisation::pack<EngineNetwork::UDPDataStructure::PlayerMove>({EngineNetwork::UDPDataStructure::MOVE_PLAYER},
            movement);
            std::cout << "Sending to server movement [" << movement.moveX << ", " << movement.moveY << "] from player " << playerID - 100 << "\n";

            client.get()->writeToAll(message);
        } catch (std::bad_cast const &error) {
        }
    }
}

/**
 * @brief 
 * Create a normal or strong missile of Ally faction when Key Space is released
 * 
 * @param singletons 
 * @param interaction 
 * @param client 
 */
void missileControl(EngineComponent::Singletons &singletons, std::unique_ptr<PadaEngine::Iinteraction> &interaction, std::unique_ptr<EngineNetwork::INetwork> &client)
{
    std::size_t playerID = singletons.getSingleton<std::size_t>(EngineClient::UDP::SingletonsEnum::ID) - 100;
    auto &deltaTime = singletons.getSingleton<EngineUtils::DeltaTime>(EngineClient::UDP::SingletonsEnum::DELTA_TIME);
    auto &bullet_timer = singletons.getSingleton<EngineUtils::Timer>(EngineClient::UDP::SingletonsEnum::BULLET_TIMER);
    // If space send to server
    if (interaction.get()->isKeyDowned(EngineComponent::KEY_VALUE::SPACE)) {
        bullet_timer.UpdateTimer(deltaTime.getDeltaTime());
    } else if (interaction.get()->isKeyReleased(EngineComponent::KEY_VALUE::SPACE)) {
        try {
            EngineNetwork::DataStructure::IDStatus fire = {playerID, false}; // normal shoot
            if (bullet_timer.TimerDone())
                fire.isOk = true; // big shoot
            auto message = EngineNetwork::Serialisation::pack<EngineNetwork::DataStructure::IDStatus>({EngineNetwork::UDPDataStructure::PLAYER_FIRE}, fire);
            client.get()->writeToAll(message);
            std::cout << "Sending missile request release\n";
            if (fire.isOk)
                singletons.getSingleton<std::string>(EngineClient::UDP::EFFECT_NAME) = "fire_two";
            else
                singletons.getSingleton<std::string>(EngineClient::UDP::EFFECT_NAME) = "fire_one";
            bullet_timer.RestartTimer();
        } catch(std::bad_cast const &error) {
            return;
        }
    }
}

/**
 * @brief 
 * Handle all the events/key pressedfrom the player
 * 
 */
void EngineClient::ClientGame::inputControl()
{
    movementControl(_register, _singletons, _inter, _client);
    missileControl(_singletons, _inter, _client);
}