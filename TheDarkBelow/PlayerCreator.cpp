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
    Entity& PlayerCreator::CreatePlayerEntity(const std::array<sf::Texture, 4>& playerTextures) {
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
        playerSpriteIdle.setTexture(playerTextures[0]);
        AnimationData idleAnimation{
            10,
            12,
            Constants::AnimationType::IDLE,
            { sf::IntRect(0, 40, 108, 40) }
        };
        sf::Sprite playerSpriteRun;
        playerSpriteRun.setTexture(playerTextures[1]);
        AnimationData runAnimation{
            10,
            12,
            Constants::AnimationType::RUN,
            { sf::IntRect(0, 40, 108, 40) }
        };

        gCoordinator.AddComponent(
            Player,
            ECS::Sprite{
                {
                    { idleAnimation.type, playerSpriteIdle },
                    { runAnimation.type, playerSpriteRun }
                },
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
