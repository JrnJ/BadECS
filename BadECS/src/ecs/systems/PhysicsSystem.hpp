#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "System.hpp"

class PhysicsSystem : System
{
public:
	void Update(ecs::Registry& reg) override;
};

#endif