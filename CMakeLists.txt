cmake_minimum_required(VERSION 3.5)

project(RemObj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets RemoteObjects)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets RemoteObjects)



# Server sources
set(SERVER_SOURCES
    main_srv.cpp
)

# Client sources
set(CLIENT_SOURCES
    main_cli.cpp
)

# Create the server target
add_executable(server
    ${SERVER_SOURCES}
)

# Create the client target
add_executable(client
    ${CLIENT_SOURCES}
)


qt6_add_repc_sources(server
    serverobject.rep
)

qt_add_repc_replicas(client
    serverobject.rep
)


# Link the necessary libraries for both targets
target_link_libraries(server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::RemoteObjects)
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::RemoteObjects)

# Set target properties for both server and client
set_target_properties(server PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.server
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_target_properties(client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install server and client targets
install(TARGETS server client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable if Qt6 is being used
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(server)
    qt_finalize_executable(client)
endif()
