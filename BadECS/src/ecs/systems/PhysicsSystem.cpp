#include "PhysicsSystem.hpp"

#include <iostream>

void PhysicsSystem::Update(ecs::Registry& reg)
{
	for (ecs::EntityId entity : entities) {
		Rigidbody& rb = reg.GetComponent<Rigidbody>(entity);
		std::cout << entity << " velocity: " << rb.dx << " : " << rb.dy << std::endl;
	}
}
