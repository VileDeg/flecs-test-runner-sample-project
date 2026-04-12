include(FetchContent)

FetchContent_Declare(
    test_runner
    GIT_REPOSITORY https://github.com/VileDeg/flecs-test-runner
)

FetchContent_Declare(
    modules
    GIT_REPOSITORY https://github.com/VileDeg/flecs-test-runner-modules
)

FetchContent_MakeAvailable(
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

target_link_libraries(
  ${EXE_NAME}
  PRIVATE
    ${TEST_RUNNER_LIB_NAME}
    ${MODULES_LIB_NAME}
)