# ##############################################################################
# Copyright (c) 2022 Logan Barnes - All Rights Reserved
# ##############################################################################
cmake_minimum_required(VERSION 3.21)
project(LtbGeom VERSION 1.0.0)

# ##############################################################################
# Options
# ##############################################################################
option(LTB_GEOM_BUILD_APPS "Build the LTB Geom example applications" OFF)

option(LTB_ENABLE_TESTING "Enable LTB Testing" OFF)

if(LTB_ENABLE_TESTING AND NOT BUILD_TESTING)
    include(CTest)
endif()

# ##############################################################################
# CMake Package Manager
# ##############################################################################
include(cmake/CPM.cmake)

# ##############################################################################
# External Packages
# ##############################################################################
cpmaddpackage(NAME
              LtbUtil
              GITHUB_REPOSITORY
              LoganBarnes/ltb-util
              GIT_TAG
              main
              )
cpmaddpackage(NAME
              glm
              # None of the tagged versions have the fixes we need
              GIT_TAG
              6ad79aae3eb5bf809c30bf1168171e9e55857e45 # master
              GITHUB_REPOSITORY
              g-truc/glm
              # It's header only and the CMakeLists.txt file adds global flags
              # that break CUDA on windows
              DOWNLOAD_ONLY
              TRUE
              )
cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.6.0")

if(glm_ADDED)
    add_library(glm INTERFACE)
    add_library(glm::glm ALIAS glm)
    target_compile_definitions(glm
                               INTERFACE GLM_FORCE_RADIANS
                                         GLM_ENABLE_EXPERIMENTAL
                                         GLM_FORCE_EXPLICIT_CTOR
                               )
    target_include_directories(glm SYSTEM
                               INTERFACE $<BUILD_INTERFACE:${glm_SOURCE_DIR}>
                               )
endif()

# ##############################################################################
# LtbGeom::LtbGeom
# ##############################################################################
ltb_create_default_targets(LtbGeom
                           src/shapes/meshes/axes_mesh.cpp
                           src/shapes/meshes/cube_mesh.cpp
                           src/shapes/meshes/disc_mesh.cpp
                           src/shapes/meshes/icosphere_mesh.cpp
                           src/shapes/meshes/plane_mesh.cpp
                           src/shapes/ball.cpp
                           src/shapes/box.cpp
                           src/shapes/capsule.cpp
                           src/shapes/fwd.cpp
                           src/shapes/io.cpp
                           src/shapes/polygon.cpp
                           src/shapes/shape_info.cpp
                           src/comparison_utils.cpp
                           src/fwd.cpp
                           src/interpolator.cpp
                           src/interpolator_2d.cpp
                           src/interpolator_3d.cpp
                           src/mesh.cpp
                           src/ray.cpp
                           src/range.cpp
                           src/solvers.cpp
                           src/transform.cpp
                           src/vec.cpp
                           )

# Public
target_link_libraries(LtbGeom_deps INTERFACE LtbUtil::LtbUtil glm::glm)
target_include_directories(LtbGeom_deps
                           INTERFACE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                           )

# Private
target_link_libraries(LtbGeom_objs PRIVATE doctest::doctest)
target_include_directories(LtbGeom_objs
                           PRIVATE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
                           )

# Testing
if(TARGET test_LtbGeom)
    target_link_libraries(test_LtbGeom PRIVATE doctest_with_main)
endif()

# ##############################################################################
# Applications
# ##############################################################################
if(LTB_GEOM_BUILD_APPS OR LTB_BUILD_ALL_APPS)
    include(apps/CMakeLists.cmake)
endif()
