#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

namespace ecs {
	using EntityId			= std::uint32_t;	// 0 - 2.147.483.647
	using ComponentId		= std::uint16_t;	// 0 - 65.535
	using ArchetypeId		= std::uint16_t;	// 0 - 65.535

	// Unsure about this atm...
	// It's used for  type erasure
	struct Column {
		void*			elements;
		std::size_t		elementSize;
		std::size_t		elementCount;
	};

	// Used to store each  unique component list  only once
	struct Archetype {
		ecs::ArchetypeId			id;
		std::vector<ComponentId>	componentList;
		std::vector<Column>			components;
	};
}

#endif