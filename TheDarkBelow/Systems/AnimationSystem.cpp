#include "AnimationSystem.h"
#include "../Components/Sprite.h"
#include "../Components/Animation.h"

namespace DarkBelow {
	namespace ECS {
		void AnimationSystem::update(float dt) {
			this->timer += dt * 1000;
			for (auto& entity : mEntities) {
				auto& spriteComponent = gCoordinator.GetComponent<Sprite>(entity);
				auto const& animationComponent = gCoordinator.GetComponent<Animation>(entity);
				
				if (spriteComponent.currentSpriteName != animationComponent.animation.type) {
					spriteComponent.currentSpriteName = animationComponent.animation.type;
					spriteComponent.srcRect.left = 0;
				}
				
				if (
					spriteComponent.srcRect.left >=
					animationComponent.animation.frames * spriteComponent.srcRect.width
					) {
					spriteComponent.srcRect.left = 0;
				}
				
				if (this->timer >= animationComponent.speed) {
					spriteComponent.srcRect.left +=
						(spriteComponent.srcRect.width + animationComponent.animation.offset);
					this->timer -= animationComponent.speed;
				}
			}		
		}
	}
}