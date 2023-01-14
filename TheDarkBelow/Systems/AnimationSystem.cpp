#include "AnimationSystem.h"
#include "../Components/Sprite.h"
#include "../Components/Animation.h"

namespace DarkBelow {
	namespace ECS {
		void AnimationSystem::update(float dt) {
			this->timer += dt * 1000;
			for (auto& entity : mEntities) {
				auto& spriteComponent = gCoordinator.GetComponent<Sprite>(entity);
				auto& animationComponent = gCoordinator.GetComponent<Animation>(entity);
				bool hasPriority = animationComponent.animation.isPriorityAnimation;
				bool hasChanged = spriteComponent.currentSpriteName != animationComponent.animation.type;
				bool hasFinished = spriteComponent.srcRect.left >=
					animationComponent.animation.frames * spriteComponent.srcRect.width;

				if ((hasChanged && !hasPriority) || (hasChanged && hasFinished)) {
					spriteComponent.currentSpriteName = animationComponent.animation.type;
					animationComponent.animation = this->getAnimation(animationComponent.animation.type);
					spriteComponent.srcRect.left = 0;
				}
				
				if (
					hasFinished &&
					animationComponent.animation.playsContinuously == true
				) {
					spriteComponent.srcRect.left = 0;
				}
				else if (hasFinished &&
					animationComponent.animation.playsContinuously == false
				) {
					animationComponent.animation.type = AnimationType::IDLE;
				}
				
				if (this->timer >= animationComponent.speed) {
					spriteComponent.srcRect.left +=
						(spriteComponent.srcRect.width + animationComponent.animation.offset);
					this->timer -= animationComponent.speed;
				}
			}		
		}

		const AnimationData& AnimationSystem::getAnimation(AnimationType type) const {
			switch (type) {
			case AnimationType::IDLE:
				return Constants::Player::idleAnimation;
			case AnimationType::RUN:
				return Constants::Player::runAnimation;
			case AnimationType::ATTACK_1:
				return Constants::Player::attack_1_Animation;
			default:
				return Constants::Player::idleAnimation;
			}
		}
	}
}