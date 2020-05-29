# All of these will be set as PUBLIC sources to Game
set(_temp_game_headers
		)
set(_temp_game_sources
		Main.cpp
		)
		
get_filename_component(CURRENT_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
if(ACID_LINK_RESOURCES)
    # Directory that Tycoon resources can be found.
    set(GAME_RESOURCES_DIR "${CURRENT_PARENT_DIR}/Resources")
endif()
if(ACID_INSTALL_RESOURCES)
	# Install resources for end-user usage because many source files use these
	install(DIRECTORY "${CURRENT_PARENT_DIR}/Resources"
			# Example: this will install the Resources dir to /usr/share/Tycoon/Resources on Linux
			DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}"
			)
endif()

# Adds a CMake generated config file
configure_file(Config.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp" @ONLY)

# Sets all headers as PRIVATE sources for Game
# The BUILD/INSTALL interface generator expressions are for the EXPORT command
# Otherwise it wouldn't know where to look for them
foreach(_game_header IN LISTS _temp_game_headers)
	target_sources(Game PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_game_header}>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${_game_header}>
			)
endforeach()
# Sets all sources (cpp) as PRIVATE sources for Game
# An INSTALL_INTERFACE isn't needed, as cpp files aren't installed
foreach(_game_source IN LISTS _temp_game_sources)
	target_sources(Game PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_game_source}>
			)
endforeach()

# Changes how sources appear in IDE virtual file structures.
include(AcidGroupSources)
acid_group_sources("${CMAKE_CURRENT_SOURCE_DIR}" "/" "" "${_temp_game_headers}")
acid_group_sources("${CMAKE_CURRENT_SOURCE_DIR}" "/" "" "${_temp_game_sources}")

# Include this file in our project view.
target_sources(Game PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CMakeSources.cmake>
        )
