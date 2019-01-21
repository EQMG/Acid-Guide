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
set(GAME_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Sources/")

add_executable(Game ${GAME_SOURCES})
add_dependencies(Game Acid)

target_compile_features(Game PUBLIC cxx_std_17)
set_target_properties(Game PROPERTIES
	POSITION_INDEPENDENT_CODE ON
	FOLDER "Acid"
	)

target_include_directories(Game PRIVATE ${ACID_INCLUDE_DIR} ${GAME_INCLUDE_DIR})
target_link_libraries(Game PRIVATE Acid)

if(MSVC AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set_target_properties(Game PROPERTIES LINK_FLAGS "/subsystem:windows /ENTRY:mainCRTStartup")
elseif(UNIX AND APPLE)
	set_target_properties(Game PROPERTIES
		MACOSX_BUNDLE_BUNDLE_NAME "Game"
		MACOSX_BUNDLE_SHORT_VERSION_STRING ${ACID_VERSION}
		MACOSX_BUNDLE_LONG_VERSION_STRING ${ACID_VERSION}
		MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/Scripts/MacOSXBundleInfo.plist.in"
		)
endif()

add_test(NAME "Game" COMMAND "Game")

if(ACID_INSTALL_EXAMPLES)
	install(TARGETS Game
			RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
			ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
			)
endif()
