#include <iostream>
#include <Files/Files.hpp>
#include <Files/Json/FileJson.hpp>
#include <Helpers/FileSystem.hpp>
#include <Inputs/Mouse.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>

using namespace acid;

int main(int argc, char **argv)
{
	// Registers file search paths.
	Files::SetBaseDirectory(argv[0]);
	Files::AddSearchPath("Resources/Game");
	Files::AddSearchPath("Resources/Engine");

	// Creates the engine.
	auto engine = std::make_unique<Engine>();

	printf("Working Directory: %s\n", FileSystem::GetWorkingDirectory().c_str());

	// Registers modules.

	// Registers components.

	// Initializes modules.
	Display::Get()->SetTitle("Game");
	Display::Get()->SetIcon("Logos/Flask.png");
//	Mouse::Get()->SetCustomMouse("Guis/Cursor.png");
//	Renderer::Get()->SetManager(new MainRenderer());
//	Scenes::Get()->SetScene(new Scene1());

	// Runs the game loop.
	int32_t exitCode = engine->Run();

	// Pauses the console.
//	std::cin.get();
	return exitCode;
}
