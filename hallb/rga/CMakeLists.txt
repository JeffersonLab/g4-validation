#----------------------------------------------------------------------------
# Setup the project.
#
cmake_minimum_required(VERSION 3.16...3.27)
project(rga)

# Find Geant4 package, activating all available UI and Vis drivers by default
find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
# Assuming common headers and sources are 2 directories up
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../../include)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# Assuming common headers and sources are 2 directories up
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/../../src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/../../include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(rga rga.cc ${sources} ${headers})
target_link_libraries(rga PRIVATE ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build this example. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(FILES_TO_COPY
        init_vis.mac
        vis.mac
        target_kapton_wall.stl
        target_torlon_base.stl
)

foreach (_script ${FILES_TO_COPY})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach ()


#----------------------------------------------------------------------------
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Geant4 include dirs: ${Geant4_INCLUDE_DIRS}")
message(STATUS "Geant4 libraries: ${Geant4_LIBRARIES}")
message(STATUS "Geant4 definitions: ${Geant4_DEFINITIONS}")
message(STATUS "Geant4 use file: ${Geant4_USE_FILE}")
message(STATUS "Qt6_DIR: $ENV{Qt6_DIR}")