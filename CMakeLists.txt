##
## EPITECH PROJECT, 2022
## R-TYPE
## File description:
## Main CMakeLists
##

cmake_minimum_required(VERSION 3.17)

cmake_policy(VERSION 3.17)

set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_BUILD_TYPE Release)

project(RTYPE VERSION 1.0
        DESCRIPTION "r-type with Pada game engine"
        LANGUAGES CXX)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG "main"
)

set(CLIENT_NAME "rtype_client")
set(SERVER_NAME "rtype_server")


set(CMAKE_CXX_STANDARD 17)

set(DIRECTORY_ENCAPSULATION "Libs/Encapsulation/Raylib")

set(SRC_ENCAPSULATION
        ${DIRECTORY_ENCAPSULATION}/src/Lib.cpp
        ${DIRECTORY_ENCAPSULATION}/src/Element/Element.cpp
        ${DIRECTORY_ENCAPSULATION}/src/Interaction/Interaction.cpp
        ${DIRECTORY_ENCAPSULATION}/src/Sound/Sound.cpp
        ${DIRECTORY_ENCAPSULATION}/src/Text/Text.cpp
        )

set(SRC_ENGINE
        Engine/Error/ErrorLoader.cpp
        Engine/Loader/ClassLoader.cpp
        Engine/Utils/CSV.cpp
        Engine/Utils/Time.cpp
        Engine/Utils/Collision.cpp
        Engine/ComponentManagement/RegisterComponents.cpp
        Engine/Systems/ESystems.cpp
        Engine/GameCore.cpp
        Engine/Entity/EntityCache.cpp

        Engine/Network/NetworkUtils/DataTransfer.cpp
        Engine/Network/NetworkUtils/tools.cpp
        )

set(SRC_SERVER
        Server/Core/main.cpp
        Server/Core/startServer.cpp

        Engine/Network/Server/ServerTCP.cpp
        Engine/Network/Server/ServerTCPHandler.cpp
        Engine/Network/Server/ServerUDP.cpp
        
        Server/Systems/EntityGeneration/Missile.cpp
        Server/Systems/EntityGeneration/Auxiliaries.cpp
        
        Server/Systems/Physique/Collision.cpp
        Server/Systems/Physique/Movement.cpp
        Server/Systems/Physique/PhysiqueSystems.cpp
        Server/Systems/Network/SendDataSystems.cpp
        Server/Systems/EnemySystem/EnemySystems.cpp
        Server/Systems/VisualEffect/VisualEffectSystems.cpp

        src/Entity/Obstacle.cpp
        src/Entity/Player.cpp
        src/Entity/Button.cpp
        src/Entity/Powerup.cpp
        src/Entity/Missile.cpp
        src/Entity/Enemy.cpp
        src/Entity/Auxiliaries.cpp

        Server/TCPGame/tcpServerGameLogic.cpp
        Server/TCPGame/ServerMenu.cpp
        Server/UDPGame/ServerGame.cpp
        Server/UDPGame/logicGameServer.cpp
)

set(SRC_CLIENT
        Client/Core/main.cpp
        Client/Core/startClient.cpp
        
        Client/Systems/Draw/DrawSystems.cpp
        Client/Systems/Background/BackgroundSystems.cpp
        Client/Systems/Button/ButtonSystem.cpp
        Client/Systems/Physique/Collision.cpp
        Client/Systems/Physique/Movement.cpp
        Client/Systems/Physique/PhysiqueSystems.cpp
        Client/Systems/VisualEffect/VisualEffectSystems.cpp
        Client/Systems/Rendering/RenderingSystems.cpp

        src/Entity/Background.cpp
        src/Entity/Button.cpp
        src/Entity/VisualEffect.cpp
        src/Entity/Fonts.cpp

        Engine/Network/Client/ClientTCP.cpp
        Engine/Network/Client/ClientUDP.cpp

        Client/TCPGame/tcpClientGameLogic.cpp
        Client/TCPGame/ClientMenu.cpp
        Client/TCPGame/Layers.cpp
        Client/UDPGame/ClientGame.cpp
        Client/UDPGame/logicGameClient.cpp
        Client/UDPGame/InputControl.cpp
)

set(SRCS
        src/ComponentManagement/RegisterComponents.cpp
        src/Systems/Text/TextSystems.cpp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Libs/Encapsulation/Raylib/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Libs/JSONcpp)

FIND_PACKAGE(raylib REQUIRED)
FIND_PACKAGE(jsoncpp REQUIRED)

add_executable(${SERVER_NAME} ${SRC_SERVER} ${SRCS} ${SRC_ENGINE} ${SRC_ENCAPSULATION})
TARGET_LINK_LIBRARIES(${SERVER_NAME} raylib asio::asio jsoncpp_object jsoncpp_static)

add_executable(${CLIENT_NAME} ${SRC_CLIENT} ${SRCS} ${SRC_ENGINE} ${SRC_ENCAPSULATION})
TARGET_LINK_LIBRARIES(${CLIENT_NAME} raylib asio::asio jsoncpp_object jsoncpp_static)

# LIBS
target_include_directories(${CLIENT_NAME} PUBLIC Libs/Encapsulation/include/)
target_include_directories(${CLIENT_NAME} PUBLIC Libs/Encapsulation/)
target_include_directories(${CLIENT_NAME} PUBLIC Libs/Encapsulation/Raylib/src)
# 
target_include_directories(${SERVER_NAME} PUBLIC Libs/Encapsulation/include/)
target_include_directories(${SERVER_NAME} PUBLIC Libs/Encapsulation/)
target_include_directories(${SERVER_NAME} PUBLIC Libs/Encapsulation/Raylib/src)

## ENGINE
target_include_directories(${CLIENT_NAME} PUBLIC Engine/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/ComponentManagement/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Components/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Utils/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Entity/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Loader)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Error/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Map/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Systems/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/CacheManagement/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Network/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Network/NetworkUtils/)
target_include_directories(${CLIENT_NAME} PUBLIC Engine/Network/Client/)

target_include_directories(${SERVER_NAME} PUBLIC Engine/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Network/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Network/NetworkUtils/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Network/Server/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/ComponentManagement/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Components/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Utils/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Entity/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Loader)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Error/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Map/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/Systems/)
target_include_directories(${SERVER_NAME} PUBLIC Engine/CacheManagement/)

## SRCS
target_include_directories(${CLIENT_NAME} PUBLIC src/ComponentManagement/)
target_include_directories(${CLIENT_NAME} PUBLIC src/Components/)
target_include_directories(${CLIENT_NAME} PUBLIC src/Entity/)
target_include_directories(${CLIENT_NAME} PUBLIC src/Systems/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/InputHandling/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Draw/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Background/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Button/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/VisualEffect/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Physique/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Text/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Systems/Rendering/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/UDPGame/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/TCPGame/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Component/)

# 
target_include_directories(${SERVER_NAME} PUBLIC src/ComponentManagement/)
target_include_directories(${SERVER_NAME} PUBLIC src/Components/)
target_include_directories(${SERVER_NAME} PUBLIC src/Entity/)
target_include_directories(${SERVER_NAME} PUBLIC src/Systems/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Systems/Physique/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Systems/EntityGeneration/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Systems/Network/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Systems/EnemySystem/)

target_include_directories(${SERVER_NAME} PUBLIC Server/UDPGame/)
target_include_directories(${SERVER_NAME} PUBLIC Server/TCPGame/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Component/)

target_include_directories(${CLIENT_NAME} PUBLIC RTYPE/GameLogic/UDP/Client/)
target_include_directories(${CLIENT_NAME} PUBLIC RTYPE/GameLogic/TCP/)
target_include_directories(${CLIENT_NAME} PUBLIC RTYPE/DataStructure/)
target_include_directories(${CLIENT_NAME} PUBLIC Client/Core)

target_include_directories(${SERVER_NAME} PUBLIC Network/Server/Systems/EntityGeneration/)
target_include_directories(${SERVER_NAME} PUBLIC Network/Server/Core/)
target_include_directories(${SERVER_NAME} PUBLIC Network/Server/Game/)
target_include_directories(${SERVER_NAME} PUBLIC RTYPE/GameLogic/UDP/Server/)
target_include_directories(${SERVER_NAME} PUBLIC RTYPE/GameLogic/TCP/)
target_include_directories(${SERVER_NAME} PUBLIC RTYPE/DataStructure/)
target_include_directories(${SERVER_NAME} PUBLIC Server/Core)
target_include_directories(${CLIENT_NAME} PUBLIC src/DataStructure/)
target_include_directories(${SERVER_NAME} PUBLIC src/DataStructure/)

set_target_properties(${SERVER_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set_target_properties(${CLIENT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_compile_options(-fPIC)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
install(TARGETS ${SERVER_NAME} RUNTIME DESTINATION bin)
install(TARGETS ${CLIENT_NAME} RUNTIME DESTINATION bin)
include(CPack)
