add_executable(Game)

# This file is quite big, so for readability we include instead...
# This uses target_sources(Game) to define its headers & source files
include(CMakeSources.cmake)

target_compile_features(Game PUBLIC cxx_std_17)
target_include_directories(Game PRIVATE 
		# Project source includes
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		# Generated headers
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		)
target_link_libraries(Game PRIVATE Acid::Acid)

if(MSVC AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set_target_properties(Game PROPERTIES 
			LINK_FLAGS "/subsystem:windows /ENTRY:mainCRTStartup"
			)
elseif(UNIX AND APPLE)
	set_target_properties(Game PROPERTIES
		MACOSX_BUNDLE_BUNDLE_NAME "Game"
		MACOSX_BUNDLE_SHORT_VERSION_STRING ${GAME_VERSION}
		MACOSX_BUNDLE_LONG_VERSION_STRING ${GAME_VERSION}
		MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/External/Acid/CMake/Info.plist.in"
		)
endif()

install(TARGETS Game
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		)