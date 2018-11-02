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

if(ACID_BUILD_RELEASE AND WIN32)
	add_executable(Game WIN32 ${GAME_SOURCES})
else()
	add_executable(Game ${GAME_SOURCES})
endif()

set_target_properties(Game PROPERTIES
	POSITION_INDEPENDENT_CODE ON
	FOLDER "Game"
)

add_dependencies(Game Acid)

target_include_directories(Game PUBLIC ${ACID_INCLUDE_DIR} ${GAME_INCLUDE_DIR})
target_link_libraries(Game PUBLIC Acid)

if(MSVC)
	set_target_properties(Game PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
elseif(UNIX AND APPLE)
	set_target_properties(Game PROPERTIES
		MACOSX_BUNDLE_BUNDLE_NAME "Game"
		MACOSX_BUNDLE_SHORT_VERSION_STRING ${GAME_VERSION}
		MACOSX_BUNDLE_LONG_VERSION_STRING ${GAME_VERSION}
		MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/Libraries/Acid/Scripts/MacOSXBundleInfo.plist.in"
	)
endif()

# Install
if(GAME_INSTALL)
	install(DIRECTORY .
		DESTINATION include
		FILES_MATCHING PATTERN "*.h"
		PATTERN "Private" EXCLUDE
	)

	install(TARGETS Game
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
endif()
