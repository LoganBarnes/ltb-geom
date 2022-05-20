# ##############################################################################
# Copyright (c) 2022 Logan Barnes - All Rights Reserved
# ##############################################################################

# ##############################################################################
# External Packages
# ##############################################################################
cpmaddpackage(NAME
              LtbApp
              GITHUB_REPOSITORY
              LoganBarnes/ltb-app
              GIT_TAG
              main
              )

# ##############################################################################
# Apps
# ##############################################################################
ltb_create_app(ltb_geom_meshes_app ${CMAKE_CURRENT_LIST_DIR}/meshes/main.cpp)
target_link_libraries(ltb_geom_meshes_app PRIVATE LtbGeom::LtbGeom)
