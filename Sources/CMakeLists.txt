file(GLOB_RECURSE GAME_HEADER_FILES
	"*.h"
	"*.hpp"
	)
file(GLOB_RECURSE GAME_SOURCE_FILES
	"*.c"
	"*.cpp"
	"*.rc"
	)
set(GAME_SOURCES
	${GAME_HEADER_FILES}
	${GAME_SOURCE_FILES}
	)

add_executable(Game ${GAME_SOURCES})

target_compile_features(Game PUBLIC cxx_std_17)
target_include_directories(Game PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
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
		MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/CMake/MacOSXBundleInfo.plist.in"
		)
endif()

# Creates a symbolic link from Resources to Resources/Game in the binary folder
if(GAME_LINK_RESOURCES)
	get_filename_component(CURRENT_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
	add_custom_command(TARGET Game POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/Resources
			COMMAND ${CMAKE_COMMAND} -E create_symlink ${CURRENT_PARENT_DIR}/Resources ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/Resources/Game 
			)
endif()

install(TARGETS Game
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		)