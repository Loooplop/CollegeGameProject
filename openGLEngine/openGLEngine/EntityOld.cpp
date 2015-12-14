#include "Entity.h"


Entity::Entity()
{
	pos = rot = vec3f(0, 0, 0);
	model = new Model();
}


Entity::~Entity()
{
}
