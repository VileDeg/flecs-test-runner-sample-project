include(FetchContent)

# Fetch the Flecs repository
FetchContent_Declare(
    flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    #GIT_TAG master # Use the latest version; replace with a specific tag if needed
)

FetchContent_Declare(
    test_runner
    GIT_REPOSITORY https://github.com/VileDeg/flecs-test-runner
    #GIT_TAG master # Use the latest version; replace with a specific tag if needed
)

FetchContent_Declare(
    modules
    GIT_REPOSITORY https://github.com/VileDeg/flecs-test-runner-modules
    #GIT_TAG master # Use the latest version; replace with a specific tag if needed
)

FetchContent_MakeAvailable(
    flecs
    test_runner
    modules
)

set(TEST_RUNNER_LIB_NAME "TestRunner")
set(MODULES_LIB_NAME "Modules")

set(EXE_NAME ${PROJECT_NAME})
set(SRC_DIR "./")

set(SRC_FILES
    main.cpp
)

# Add the test executable
add_executable(
  ${EXE_NAME} 
  ${SRC_FILES}
)

# Add src directory to include path so headers can be found
target_include_directories(
  ${EXE_NAME} 
  PRIVATE 
    ${SRC_DIR}
)

# TODO: in newer version should not be needed
# currently needed to retrive reflection info about component's members
target_compile_definitions(
    flecs_static 
    PRIVATE 
        FLECS_CREATE_MEMBER_ENTITIES
)

target_link_libraries(
  ${EXE_NAME}
  PRIVATE
    flecs::flecs_static
    ${TEST_RUNNER_LIB_NAME}
    ${MODULES_LIB_NAME}
)