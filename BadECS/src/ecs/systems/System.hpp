#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <set>
#include "../ecs.hpp"

class System {
public:
	virtual void Update(ecs::Registry& reg) = 0;
	std::set<ecs::EntityId> entities{};
};

#endif
