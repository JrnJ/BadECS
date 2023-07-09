#include <iostream>
#include <string>
#include <cstdlib>

#include "ecs/ecs.hpp"
#include "ecs/systems/PhysicsSystem.hpp"


int main() {
	//int value{ 10 };
	//int& valueRef{ value };
	//int* valuePtr{ &value };

	//int valuePtrToValue{ *valuePtr };

	//void* valueVoidPtr{ &value };
	//int valueIdk = *static_cast<int*>(valueVoidPtr);

	//return 0;

	int frame = 1;
	
	// Setup some data
	ecs::Registry reg;

	// Register Components
	reg.RegisterComponent<Transform>();
	reg.RegisterComponent<Rigidbody>();
	reg.RegisterComponent<Renderable>();

	// Create Entities
	ecs::EntityId player	= reg.CreateEntity();
	Transform playerTransform{ 1.0f, 1.0f };
	Rigidbody playerRigidbody{ 1.0f, 1.0f };
	reg.AddComponent<Transform>(player, playerTransform);
	reg.AddComponent<Rigidbody>(player, playerRigidbody);
	//reg.AddComponent<Transform>(player, { 1.0f, 1.0f });
	//reg.AddComponent<Rigidbody>(player, { 1.0f, 1.0f });

	ecs::EntityId enemy		= reg.CreateEntity();
	Transform enemyTransform{ 2.0f, 2.0f };
	Rigidbody enemyRigidbody{ 2.0f, 2.0f };
	reg.AddComponent<Transform>(enemy, enemyTransform);
	reg.AddComponent<Rigidbody>(enemy, enemyRigidbody);

	// Create Blocks
	ecs::EntityId block1	= reg.CreateEntity();
	Transform block1Transform{ 1.0f, 1.0f };
	reg.AddComponent<Transform>(block1, block1Transform);

	ecs::EntityId block2	= reg.CreateEntity();
	Transform block2Transform{ 2.0f, 2.0f };
	reg.AddComponent<Transform>(block2, block2Transform);

	ecs::EntityId block3	= reg.CreateEntity();
	Transform block3Transform{ 3.0f, 3.0f };
	Rigidbody block3Rigidbody{ 0.3f, 0.3f };
	reg.AddComponent<Transform>(block3, block3Transform);
	reg.AddComponent<Rigidbody>(block3, block3Rigidbody);

	reg.DestroyEntity(block2);
	reg.RemoveComponent<Rigidbody>(block3);

	if (reg.HasComponent<Transform>(player)) {
		Transform& tf = reg.GetComponent<Transform>(player);
	}

	if (reg.HasComponent<Rigidbody>(block3)) {
		Rigidbody& rb = reg.GetComponent<Rigidbody>(block3);
	}
	
	reg.RegisterSystem<PhysicsSystem>();
	reg.RegisterSystem<PhysicsSystem, Transform, Rigidbody>();
	reg.RegisterSystem<PhysicsSystem, Transform, Rigidbody, Renderable>();

	while (true) {
		std::cout << "===[ ECS | Frame: " << frame << " ]===" << std::endl;



		// Get action
		std::string input{};
		std::cin >> input;

		// 
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear"); 
#endif
		frame++;
	}

	return 0;
}