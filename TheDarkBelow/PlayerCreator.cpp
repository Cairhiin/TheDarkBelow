#include "PlayerCreator.h"
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/RigidBody.h"
#include "Components/Gravity.h"
#include "Components/Collision.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "TextureLoader.h"

extern DarkBelow::ECS::Coordinator gCoordinator;
extern DarkBelow::TextureLoader gTextureLoader;

namespace DarkBelow {
    using namespace ECS;
    Entity& PlayerCreator::CreatePlayerEntity(
        /* Will be turned into an array in the future
           when there's more animation texture sheets 
        */
        const sf::Texture& playerTextureIdle
    ) {
        auto Player = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(
            Player,
            Transform{
                sf::Vector2f(650.f, 150.f),
                sf::Vector2f(0.f, 0.f),
                Constants::Player::SCALE
            });
        gCoordinator.AddComponent(
            Player,
            RigidBody{
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(0.f, 0.f)
            });
        gCoordinator.AddComponent(
            Player,
            Gravity{
                Constants::Game::GRAVITY
            });
        gCoordinator.AddComponent(
            Player,
            Collision{
                Constants::Level::PLAYER,
                { 650.f, 150.f, 48.f, 86.f }
            });   
        
        sf::Sprite playerSpriteIdle;
        playerSpriteIdle.setTexture(playerTextureIdle);
        AnimationData idleAnimation{
            10,
            12,
            Constants::AnimationType::IDLE,
            { sf::IntRect(0, 40, 108, 40) }
        };

        gCoordinator.AddComponent(
            Player,
            ECS::Sprite{
                {{ idleAnimation.type, playerSpriteIdle }},
                { 0, 40, 108, 40 }
            });
        gCoordinator.AddComponent(
            Player,
            ECS::Animation{
                idleAnimation,
                10
            });
        gCoordinator.GetComponent<ECS::Sprite>(Player).init();

        return Player;
    }
}
