

# Explicit source file list (no GLOB_RECURSE)
set(SRC_FILES
    main.cpp
)


include(FetchContent)
#include(../Functions.cmake)

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

## Inside RepoA/build
#cmake .. -DFETCHCONTENT_SOURCE_DIR_REPO_B=../../RepoB
# cmake -S . -B build -DFETCHCONTENT_SOURCE_DIR_MODULES=../flecs-test-runner-modules -DFETCHCONTENT_SOURCE_DIR_TEST_RUNNER=../flecs-test-runner
#target_include_directories(repo_b_lib PUBLIC include)


set(TEST_RUNNER_DIR "test-runner")
set(TEST_RUNNER_LIB_NAME "TestRunner")

set(MODULES_DIR "modules")
set(MODULES_LIB_NAME "Modules")



set(EXE_NAME ${PROJECT_NAME})
set(SRC_DIR "./")


#include(../Functions.cmake)
discover_sources(${SRC_DIR} SRC_FILES)

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
    # ../../${TEST_RUNNER_DIR}/src/core/include
    # ../../${MODULES_DIR}/src/include
)

target_link_libraries(
  ${EXE_NAME}
  PRIVATE
    flecs::flecs_static
    #${CMAKE_SOURCE_DIR}/../../${TEST_RUNNER_LIB_NAME}
    ${TEST_RUNNER_LIB_NAME}
    ${MODULES_LIB_NAME}
)