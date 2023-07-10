#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

namespace ecs {
	using EntityId			= std::uint32_t;	// 0 - 2.147.483.647
	using ComponentId		= std::uint16_t;	// 0 - 65.535
	using ArchetypeId		= std::uint16_t;	// 0 - 65.535

	using TypeId			= std::size_t;		// std::size_t
}

#endif