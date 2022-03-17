##########################################################################################
# Copyright (c) 2022 Logan Barnes - All Rights Reserved
##########################################################################################
cmake_minimum_required(VERSION 3.21)
project(LtbGeom VERSION 1.0.0)

#############################
### CMake Package Manager ###
#############################
set(CPM_DOWNLOAD_VERSION 0.35.0)

if (CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif (DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else ()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif ()

if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
         https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
         ${CPM_DOWNLOAD_LOCATION}
         )
endif ()

include(${CPM_DOWNLOAD_LOCATION})

#########################
### External Packages ###
#########################
CPMAddPackage(
        NAME LtbUtil
        GITHUB_REPOSITORY LoganBarnes/ltb-util
)
CPMAddPackage(
        NAME glm
        # None of the tagged versions have the fixes we need
        GIT_TAG 6ad79aae3eb5bf809c30bf1168171e9e55857e45 # master
        GITHUB_REPOSITORY g-truc/glm
)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")

if (glm_ADDED)
    target_compile_definitions(glm
                               INTERFACE
                               GLM_FORCE_RADIANS
                               GLM_ENABLE_EXPERIMENTAL
                               GLM_FORCE_EXPLICIT_CTOR
                               )
endif ()

##########################
#### LtbGeom::ltb-geom ###
##########################
ltb_add_library(
        ltb-geom
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/meshes/axes_mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/meshes/cube_mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/meshes/disc_mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/meshes/icosphere_mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/meshes/plane_mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/ball.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/box.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/capsule.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/fwd.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/io.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/polygon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/shapes/shape_info.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/comparison_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/fwd.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/interpolator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/interpolator_2d.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/interpolator_3d.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/mesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/ray.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/range.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/solvers.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/transform.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ltb/geom/vec.cpp
)
add_library(
        LtbGeom::ltb-geom
        ALIAS
        ltb-geom
)
ltb_target_link_libraries(
        ltb-geom
        PUBLIC
        LtbUtil::ltb-util
        glm::glm
)
ltb_target_include_directories(
        ltb-geom
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
)
ltb_target_compile_features(
        ltb-geom
        PRIVATE
        cxx_std_17
)
set_target_properties(
        ltb-geom
        PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        WINDOWS_EXPORT_ALL_SYMBOLS ON
)

if (LTB_GEOM_BUILD_APPS OR LTB_BUILD_ALL_APPS)
    include(${CMAKE_CURRENT_LIST_DIR}/apps/CMakeLists.cmake)
endif ()