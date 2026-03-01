#include <iostream>
#include <unordered_set>

#include <flecs.h>

#include <test_runner/test_runner.h>
//#include <modules/movement.h>
#include <modules/time.h>
#include <modules/test.h>

using mass = flecs::units::mass;

struct Mass {
  double value;
};

struct Count {
  int count;
};


int remote(int argc, char* argv[]) {
  // Passing in the command line arguments will allow the explorer to display
  // the application name.
  flecs::world world(argc, argv);

  world.set_threads(4); // TODO: remove?

  TestRunner::setLogLevel(TestRunner::LogLevel::INFO);
  TestRunner::initialize<
		movement::module, 
		modules::time
	>(world);
  //TestRunner::registerModule<modules::time>(world);

	TestRunner::registerTypes<movement::Vector2D>(world); // world

  /*TestRunner::initialize(world, [](flecs::world& world) {
    world.import<modules::movement>();
    world.import<modules::time>();
  });*/


#if 0

  world.import<flecs::units>();
  world.import<flecs::stats>(); // Collect statistics periodically


  // Mass component
  world.component<Mass>()
    .member<double, mass::KiloGrams>("value");



  // Simple hierarchy
  flecs::entity Sun = world.entity("Sun")
    .set<Mass>({ 1.988500e31 });

  flecs::entity Earth = world.scope(Sun).entity("Earth")
    .set<Mass>({ 5.9722e24 });

  world.scope(Earth).entity("Moon")
    .set<Mass>({ 7.34767309e22 });


   
  std::cout << "All entities: \n";


  // Use the C API to get the highest issued id, then test each id
  ecs_entity_t max_id = ecs_get_max_id(ecs.c_ptr());

  for(ecs_entity_t e = 1; e <= max_id; ++e) {
  if(!ecs.is_alive(e)) continue;   // skip dead / unused ids

  // Get the name (returns nullptr if not named)
  const char* name = ecs_get_name(ecs.c_ptr(), e);
  if(name && name[0] != '\0') {
    std::cout << "Entity " << e << " : " << name << '\n';
  } else {
    std::cout << "Entity " << e << " : (unnamed)\n";
  }
  }
#endif


#if 0
	flecs::entity e1 = world.entity()
		.add<movement::Position>();


	flecs::entity e2 = world.entity("test_entity")
		.add<movement::Position>()
		.add<movement::Velocity>();

	auto entity_ser = e2.to_json();

	auto entt_ser = "{\"name\":\"test_entity\", \"components\":{\"movement.module.Vector2D\":{\"x\":\"0\", \"y\":0}, \"movement.module.Velocity\":{\"linearSpeed\":\"-.13444722548e39\", \"direction\":{\"x\":0, \"y\":0}}}}";

	e2.from_json(entity_ser);


	e2.from_json(entt_ser);
	entity_ser = e2.to_json();

#endif

  std::cout << "Running HTTP server on port 27750 ...\n";
  // Run application with REST interface. When the application is running,
  // navigate to https://flecs.dev/explorer to inspect it!
  //
  // See docs/FlecsRemoteApi.md#explorer for more information.
  return world.app()
    .enable_rest()
    .enable_stats()
    .run();
}


int main(int argc, char *argv[]) {
  int ret = remote(argc, argv);

  return ret;
}
