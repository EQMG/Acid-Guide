#include <iostream>
#include <Devices/Mouse.hpp>
#include <Files/Files.hpp>
#include <Files/FileSystem.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>

using namespace acid;

int main(int argc, char **argv)
{
	// Creates the engine.
	auto engine{std::make_unique<Engine>(argv[0])};

	// Registers file search paths.
	Files::Get()->AddSearchPath("Resources/Game");
	Files::Get()->AddSearchPath("Resources/Engine");

	printf("Working Directory: %s\n", FileSystem::GetWorkingDirectory().c_str());

	// Registers modules.

	// Registers components.

	// Initializes modules.
	Window::Get()->SetTitle("Game");
	Window::Get()->SetIcons({"Icons/Icon-16.png", "Icons/Icon-24.png", "Icons/Icon-32.png", "Icons/Icon-48.png",
		"Icons/Icon-64.png", "Icons/Icon-96.png", "Icons/Icon-128.png", "Icons/Icon-192.png", "Icons/Icon-256.png"});
//	Mouse::Get()->SetCursor("Guis/Cursor.png");
//	Renderer::Get()->SetManager(std::make_unique<MainRenderer>());
//	Scenes::Get()->SetScene(std::make_unique<Scene1>());

	// Runs the game loop.
	auto exitCode{engine->Run()};

	// Pauses the console.
//	std::cin.get();
	return exitCode;
}
