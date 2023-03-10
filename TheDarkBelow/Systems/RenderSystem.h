#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include "../ECS/System.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace DarkBelow {
	namespace ECS {
		class RenderSystem : public System {
		public:
			void init();
			void draw(sf::RenderWindow& window);

		private:
		};
	}
}

#endif

