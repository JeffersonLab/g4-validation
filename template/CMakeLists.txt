
#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.21)
project(project_name)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
# Assuming common headers and sources are 2 directories up
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../../include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# Assuming common headers and sources are 2 directories up
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc     ${PROJECT_SOURCE_DIR}/../../src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/../../include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(project_name project_name.cc ${sources} ${headers})
target_link_libraries(project_name ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build this example. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(FILES_TO_COPY
  run.mac
  init_vis.mac
  vis.mac
  )

foreach(_script ${FILES_TO_COPY})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

# for some reason this is not added to the cflags
# but in the examples it it. Investigate more.
set(G4CONFIG "$ENV{G4INSTALL}/bin/geant4-config")
execute_process (
    COMMAND ${G4CONFIG} --cflags
    OUTPUT_VARIABLE G4CFLAGS
)
string(STRIP ${G4CFLAGS} G4CFLAGS)
set(CMAKE_CXX_FLAGS " ${G4CFLAGS} ${CMAKE_CXX_FLAGS}")

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
message(STATUS "")
message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
message(STATUS "CMAKE_CXX_FLAGS: "  ${CMAKE_CXX_FLAGS})
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "")


install(TARGETS project_name DESTINATION bin)
