cmake_minimum_required(VERSION 3.29)
project(untitled46)

# Použijeme C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Nepoužívat rozšíření kompilátoru

# Výstupní složka pro spustitelné soubory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Přidání SFML přes FetchContent
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Přidání spustitelného souboru
add_executable(untitled46 main.cpp
        Managers/EntityManager.cpp
        Managers/EntityManager.h
        Managers/SpriteManager.cpp
        Managers/SpriteManager.h
        Insetors/InsertEntity.cpp
        Insetors/InsertEntity.h
        Entitys/Entity.h
        Entitys/Entity.cpp
        Entitys/Player.cpp
        Entitys/Player.h
)

# Linkování SFML
target_link_libraries(untitled46 PRIVATE sfml-graphics sfml-window sfml-system)
