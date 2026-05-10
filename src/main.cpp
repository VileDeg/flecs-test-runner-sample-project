#include <test_runner/test_runner.h>

#include <modules/time.h>
#include <modules/movement.h>
#include <modules/structural.h>
#include <modules/modifiers.h>

#define PROFILE_ARG_SHORT "-p"
#define PROFILE_ARG_LONG_PREF "--"
#define PROFILE_ARG_LONG_POST "profile"
#define PROFILE_ARG_LONG PROFILE_ARG_LONG_PREF PROFILE_ARG_LONG_POST

#define PROFILE_BATCH_SIZE_PLCHLD "<profile_batch_size>"

#define HELP_MESSAGE \
	"... .exe [-p, --profile] " PROFILE_BATCH_SIZE_PLCHLD

// ================================================================================================
struct CliArguments {
	int profileBatchSize = -1;

	friend std::ostream& operator<<(std::ostream& os, const CliArguments& args) {
		os << "(" << "\n\t"
			<< PROFILE_BATCH_SIZE_PLCHLD " = " << args.profileBatchSize << "\n"
		<< ")";
		return os;
	}
};

template <typename T>
using FlagParser = std::function<T(char*)>;

// ================================================================================================
template <typename Parser>
static auto parseFlag(
	int argc, char** argv, 
	int argIndex, 
	const char* argShort,
	const char* argLong,
	const char* argPlaceholderName,
	Parser parser
) -> std::optional<decltype(parser(argv[0]))> {
	int index = 1 + argIndex;
	if (argc <= index) {
		return std::nullopt;
	}

	auto profileFlag = std::string(argv[index]);
	if (
		profileFlag == argShort ||
		profileFlag == argLong
	) {
		if (argc > index + 1) {
			return parser(argv[index + 1]);
		} else {
			std::ostringstream ss;
			ss << "Invalid argument " << index + 1 << ", expected " << argPlaceholderName;
			throw std::runtime_error(ss.str());
		}
	} else {
		std::ostringstream ss;
		ss << "Invalid argument " << index << ", expected " << argShort << " or " << argLong;
		throw std::runtime_error(ss.str());
	}
}

// ================================================================================================
static CliArguments parseCliArguments(int argc, char* argv[]) {
	CliArguments parsed;
	parsed.profileBatchSize = parseFlag(
		argc, argv,
		0, 
		PROFILE_ARG_SHORT, PROFILE_ARG_LONG, 
		PROFILE_BATCH_SIZE_PLCHLD,
		[](char* arg) {
			return std::stoi(arg);
		}
	).value_or(-1);
	return parsed;
}

// ================================================================================================
int main(int argc, char *argv[]) {
	auto logLevel = TestRunner::LogLevel::TRACE;
	CliArguments parsed;
	try {
		parsed = parseCliArguments(argc, argv);
	} catch (const std::runtime_error& error) {
		std::cerr << "Failed to parse CLI arguments: " << error.what() << "\n";
		std::cout << HELP_MESSAGE << "\n";
		return 1;
	}
	if (logLevel == TestRunner::LogLevel::TRACE) {
		std::cout << "Parsed arguments: " << parsed << "\n";
	}
	TestRunner::setLogLevel(logLevel);
#if 1
	return TestRunner::main<
		movement::module,
		waiting::module,
		structural::module,
		modifiers::module
	>(
		8,
		parsed.profileBatchSize > 0
			? std::optional<int>{parsed.profileBatchSize}
			: std::nullopt,
		argc, 
		argv
	);
#else
	flecs::world world(argc, argv);
	TestRunner::initialize<
		movement::module,
		waiting::module,
		structural::module,
		modifiers::module
	>(
		world, 
		8, 
		parsed.profileBatchSize > 0 
			? std::optional<int>{parsed.profileBatchSize} 
			: std::nullopt
	);
	/* Single / multiple */
	/*/
	TestRunner::registerOperatorsForComponent<movement::Velocity>(world);
	/*/
	TestRunner::registerOperators<
		movement::Velocity,
		movement::Speed
	>(world);
	//*/
	return TestRunner::run(world);
#endif
}
