#include <test_runner/test_runner.h>

#include <modules/time.h>
#include <modules/movement.h>
#include <modules/structural.h>
#include <modules/modifiers.h>

int main(int argc, char *argv[]) {
	TestRunner::setLogLevel(TestRunner::LogLevel::TRACE);
#if 0 
	return TestRunner::main<
		movement::module,
		waiting::module
	>(argc, argv);
#else
	flecs::world world(argc, argv);
	TestRunner::initialize<
		movement::module,
		waiting::module,	
		structural::module,
		modifiers::module
	>(world);
	// Single:
	// TestRunner::registerOperatorsForComponent<movement::Velocity>(world);
	// Multiple:
	TestRunner::registerOperators<
		movement::Velocity,
		movement::Speed
	>(world);
	return TestRunner::run(world);
#endif
}
