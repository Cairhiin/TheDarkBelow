#include "AnimationSystem.h"
#include "../Components/Sprite.h"
#include "../Components/Animation.h"

namespace DarkBelow {
	namespace ECS {
		void AnimationSystem::update(float dt) {
			for (auto& entity : mEntities) {
				auto& spriteComponent = gCoordinator.GetComponent<Sprite>(entity);
				auto const& animationComponent = gCoordinator.GetComponent<Animation>(entity);
				
				spriteComponent.srcRect.left = spriteComponent.srcRect.width *
					static_cast<size_t>(dt / animationComponent.speed) % animationComponent.frames;
			}
		}
	}
}