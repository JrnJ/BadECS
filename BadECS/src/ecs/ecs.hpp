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
			for (ecs::EntityId i = 0; i < entities.size(); ++i) {
				if (entities[i] == entityId) {
					entities.erase(entities.begin() + i);
					entityComponents.erase(i);
					break;
				}
			}
		}

		template<typename T>
		void RegisterComponent() {
			// assert that component isn't already registered
			componentTypes[typeid(T).hash_code()] = componentTypeCounter++;
		}

		template<typename System, typename... Components>
		void RegisterSystem() {
			std::cout << "RegisterSystem called with " << sizeof...(Components) << " parameters." << std::endl;
			((std::cout << "Parameter type: " << typeid(Components).name() << std::endl), ...);
		}

		//template<typename T>
		//void AddComponent(ecs::EntityId entityId, T&& component) {
		//	// assert component doesn't exist
		//	// entityComponents[entityId].push_back(componentTypes[typeid(T).hash_code()]);
		//	entityComponents[entityId][componentTypes[typeid(T).hash_code()]] = new T(std::forward<T>(component));
		//}
		
		template<typename T>
		void AddComponent(ecs::EntityId entityId, T& component) {
			// assert component doesn't exist
			// entityComponents[entityId].push_back(componentTypes[typeid(T).hash_code()]);

			// entity.components[std::type_index(typeid(Component))] = component;
			// entity.components[std::type_index(typeid(Component))] = std::forward<Component>(component);
			// entity.components[std::type_index(typeid(Component))] = new Component(std::forward<Component>(component));
			// entityComponents[entityId][componentTypes[typeid(T).hash_code()]] = std::forward<T>(component);
			entityComponents[entityId][componentTypes[typeid(T).hash_code()]] = std::move(&component);
		}

		template<typename T>
		void RemoveComponent(ecs::EntityId entityId) {
			// assert component exists
			//entityComponents[entityId].erase();
			entityComponents[entityId].erase(componentTypes[typeid(T).hash_code()]);
			/*for (ecs::EntityId i = 0; i < entityComponents[entityId].size(); ++i) {
				if (entityComponents[entityId][i] == componentTypes[typeid(T).hash_code()]) {
					entityComponents[entityId].erase(entityComponents[entityId].begin() + i);
					break;
				}
			}*/
		}

		template<typename T>
		bool HasComponent(ecs::EntityId entityId) {
			return entityComponents[entityId].contains(componentTypes[typeid(T).hash_code()]);
		}

		template<typename T>
		T& GetComponent(ecs::EntityId entityId) {
			// assert
			return *static_cast<T*>(entityComponents[entityId][componentTypes[typeid(T).hash_code()]]);
		}

	private:
		// Registered Components
		std::unordered_map<std::size_t, ecs::ComponentId> componentTypes{};
		static inline ecs::ComponentId componentTypeCounter{ 0 };

		// Entities
		std::vector<ecs::EntityId> entities{};
		static inline ecs::EntityId entityCounter{ 0 };

		// Components
		std::unordered_map<ecs::EntityId, std::unordered_map<ecs::ComponentId, void*>> entityComponents{};

		// Systems
		std::unordered_map<std::size_t, void*> systems{};
	};
}

#endif