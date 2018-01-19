cmake_minimum_required(VERSION 3.0)

#REPLACE ALL 'DUMMY' OCCURENCES BY YOUR PLUGIN NAME
#AND ADAPT THE CODE BELOW TO YOUR OWN NEEDS!

option( INSTALL_Q3D2D_PLUGIN "Check to install q3D2D plugin" OFF )

# CloudCompare 'MYPLUGIN' plugin
if (INSTALL_Q3D2D_PLUGIN)
    project( Q3D2D_PLUGIN )

	#As we are going to re-use several components of the main qCC project
	#we define its sources path relatively to the plugin's dir
	set(CloudCompare_QCC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../qCC)
	
	#include the whole CC directory (easier)
	include_directories( ${CloudCompare_QCC_DIR} )
    
    #load necessary libraries (see qPCV for an example)
    #add_subdirectory (LIB1)
    
    #if the plugin is an 'OpenGL filter', uncomment the line below
    #set( CC_OPENGL_FILTER ON BOOL)
    include( ../CMakePluginTpl.cmake )

	#we also need picking hub classes
	list( APPEND  CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_QCC_DIR}/ccPickingListener.h )
	list( APPEND  CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_QCC_DIR}/ccPickingHub.h )	
	list( APPEND  CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_QCC_DIR}/ccPickingHub.cpp )
    
    #set dependencies to necessary libraries (see qPCV for an example)
    #target_link_libraries( ${PROJECT_NAME} LIB1 )
    #include_directories( ${LIB1_INCLUDE_DIR} )
endif()
