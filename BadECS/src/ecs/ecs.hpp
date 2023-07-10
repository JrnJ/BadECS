#ifndef ECSMANAGER_HPP
#define ECSMANAGER_HPP

#include <vector>
#include <iostream>
#include <unordered_map>
#include <type_traits>
#include <typeinfo>

#include "components/Rigidbody.hpp"
#include "components/Transform.hpp"
#include "components/Renderable.hpp"

#include "Types.hpp"

namespace ecs {
	class Registry {
	public:
		ecs::EntityId CreateEntity() {
			entities.push_back(++entityCounter);
			entityComponents.insert(std::make_pair(entityCounter, std::unordered_map<ecs::ComponentId, void*>()));
			return entityCounter;
		}

		void DestroyEntity(ecs::EntityId entityId) {
			for (ecs::EntityId entity = 0; entity < entities.size(); ++entity) {
				if (entities[entity] == entityId) {
					// System
					// Loop over systems and check if entity is there
					/*for (auto pair : systemComponents) {
						for (ecs::ComponentId component : pair.second) {
							if () {

							}
						}
					}*/
					/*for (auto pair : systems) {
						System& system = *static_cast<System*>(pair.second);
						for (ecs::EntityId systemEntity : system.entities) {
							if (systemEntity == entityId) {
								system.entities.
								break;
							}
						}
					}*/

					entities.erase(entities.begin() + entity);
					entityComponents.erase(entity);

					break;
				}
			}
		}

		template<typename Component>
		void RegisterComponent() {
			// assert that component isn't already registered
			componentTypes[typeid(Component).hash_code()] = componentTypeCounter++;
		}

		template<typename System, typename... Components>
		System& RegisterSystem() {
			// Make System
			System system{};
			systems.insert(std::make_pair(typeid(System).hash_code(), &system));

			// Set Components
			std::vector<ComponentId> components{};
			((components.push_back(typeid(Components).hash_code())), ...);
			systemComponents.insert(std::make_pair(typeid(system).hash_code(), components));

			// Return System
			return system;
		}

		//template<typename T>
		//void AddComponent(ecs::EntityId entityId, T&& component) {
		//	// assert component doesn't exist
		//	// entityComponents[entityId].push_back(componentTypes[typeid(T).hash_code()]);
		//	entityComponents[entityId][componentTypes[typeid(T).hash_code()]] = new T(std::forward<T>(component));
		//}
		
		template<typename Component>
		void AddComponent(ecs::EntityId entityId, Component& component) {
			// assert component doesn't exist
			// entityComponents[entityId].push_back(componentTypes[typeid(T).hash_code()]);

			// entity.components[std::type_index(typeid(Component))] = component;
			// entity.components[std::type_index(typeid(Component))] = std::forward<Component>(component);
			// entity.components[std::type_index(typeid(Component))] = new Component(std::forward<Component>(component));
			// entityComponents[entityId][componentTypes[typeid(T).hash_code()]] = std::forward<T>(component);
			entityComponents[entityId][componentTypes[typeid(Component).hash_code()]] = std::move(&component);
		}

		template<typename Component>
		void RemoveComponent(ecs::EntityId entityId) {
			// assert component exists
			//entityComponents[entityId].erase();
			entityComponents[entityId].erase(componentTypes[typeid(Component).hash_code()]);
			/*for (ecs::EntityId i = 0; i < entityComponents[entityId].size(); ++i) {
				if (entityComponents[entityId][i] == componentTypes[typeid(T).hash_code()]) {
					entityComponents[entityId].erase(entityComponents[entityId].begin() + i);
					break;
				}
			}*/
		}

		template<typename Component>
		bool HasComponent(ecs::EntityId entityId) {
			return entityComponents[entityId].contains(componentTypes[typeid(Component).hash_code()]);
		}

		template<typename Component>
		Component& GetComponent(ecs::EntityId entityId) {
			// assert
			return *static_cast<Component*>(entityComponents[entityId][componentTypes[typeid(Component).hash_code()]]);
		}

	private:
		// Registered Components
		std::unordered_map<ecs::TypeId, ecs::ComponentId> componentTypes{};
		static inline ecs::ComponentId componentTypeCounter{ 0 };

		// Entities
		std::vector<ecs::EntityId> entities{};
		static inline ecs::EntityId entityCounter{ 0 };

		// Components
		std::unordered_map<ecs::EntityId, std::unordered_map<ecs::ComponentId, void*>> entityComponents{};

		// Systems
		std::unordered_map<ecs::TypeId, void*> systems{};
		std::unordered_map<ecs::TypeId, std::vector<ecs::ComponentId>> systemComponents{};
	};
}

#endif