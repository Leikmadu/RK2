cd ~/Desktop/Leikmadur/workspace/RK2

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.14)
project(monster_flyweight)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_executable(monster_demo src/monster.cpp)
target_include_directories(monster_demo PRIVATE include)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
    
    add_executable(monster_tests
        tests/test_monster.cpp
        src/monster.cpp
    )
    
    target_include_directories(monster_tests PRIVATE include)
    target_link_libraries(monster_tests gtest_main)
    
    add_test(NAME monster_tests COMMAND monster_tests)
endif()

# CPack для deb-пакета
set(CPACK_PACKAGE_NAME "monster-flyweight")
set(CPACK_PACKAGE_VERSION "1.0.8")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Monster Flyweight Pattern Demo")
set(CPACK_PACKAGE_CONTACT "leikmadu@users.noreply.github.com")

set(CPACK_DEBIAN_PACKAGE_NAME "monster-flyweight")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Monster Flyweight Pattern Demo")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})

install(TARGETS monster_demo RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB;TGZ")
include(CPack)
EOF
