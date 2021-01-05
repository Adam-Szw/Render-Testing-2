#include "Entity.h"
#include "Game.h"
#include "Renderer.h"

Entity::Entity()
{
	Game::currentScene->entities.push_back(this);
}
