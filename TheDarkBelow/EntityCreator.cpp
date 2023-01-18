#include "EntityCreator.h"
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/RigidBody.h"
#include "Components/Gravity.h"
#include "Components/Collision.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/Name.h"
#include "Components/Level.h"
#include "TextureLoader.h"

extern DarkBelow::ECS::Coordinator gCoordinator;
extern DarkBelow::TextureLoader gTextureLoader;

namespace DarkBelow {
    using namespace ECS;
    Entity& EntityCreator::CreatePlayerEntity() {
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
                { 650.f, 150.f, 48.f, 40.f }
            });   
        
        sf::Sprite playerSpriteIdle;      
        playerSpriteIdle.setTexture(*gTextureLoader.getTexture("playerCharIdle"));
        playerSpriteIdle.setOrigin(54, 20);

        sf::Sprite playerSpriteRun;
        playerSpriteRun.setTexture(*gTextureLoader.getTexture("playerCharRun"));
        playerSpriteRun.setOrigin(54, 20);

        sf::Sprite playerSpriteAttack_1;
        playerSpriteAttack_1.setTexture(*gTextureLoader.getTexture("playerCharAttack_1"));
        playerSpriteAttack_1.setOrigin(52, 20);

        gCoordinator.AddComponent(
            Player,
            ECS::Sprite{
                {
                    { Constants::Player::idleAnimation.type, playerSpriteIdle },
                    { Constants::Player::runAnimation.type, playerSpriteRun },
                    { Constants::Player::attack_1_Animation.type, playerSpriteAttack_1 }
                },
                { 0, 20, 120, 60 }
            });
        gCoordinator.AddComponent(
            Player,
            ECS::Animation{
                Constants::Player::idleAnimation,
                100
            });
        gCoordinator.GetComponent<ECS::Sprite>(Player).init();

        return Player;
    }

    Entity& EntityCreator::CreateMonsterEntity(
        Constants::Monster::MonsterType type, size_t level, bool isBoss
    ) {
        auto Monster = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(
            Monster,
            Level{ level }
        );
        gCoordinator.AddComponent(Monster,
            Transform{
                sf::Vector2f(250.f, 250.f),
                sf::Vector2f(0.f, 0.f),
                Constants::Monster::SCALE
            });
        gCoordinator.AddComponent(
            Monster,
            RigidBody{
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(0.f, 0.f)
            });
        gCoordinator.AddComponent(
            Monster,
            Gravity{
                Constants::Game::GRAVITY
            });
        gCoordinator.AddComponent(
            Monster,
            Collision{
                Constants::Level::MONSTER,
                { 250.f, 250.f, 48.f, 40.f }
            });
        return Monster;
    }
}
