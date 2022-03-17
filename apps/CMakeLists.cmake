##########################################################################################
# Copyright (c) 2022 Logan Barnes - All Rights Reserved
##########################################################################################

#########################
### External Packages ###
#########################
CPMAddPackage(
        NAME LtbApp
        GITHUB_REPOSITORY LoganBarnes/ltb-app
)

############
### Apps ###
############
ltb_create_app(
        meshes-app
        ${CMAKE_CURRENT_LIST_DIR}/meshes/main.cpp
)
target_link_libraries(
        meshes-app
        PRIVATE
        LtbGeom::ltb-geom
)