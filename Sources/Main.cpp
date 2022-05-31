#include <iostream>
#include <Devices/Windows.hpp>
#include <Files/Files.hpp>
#include <Graphics/Renderer.hpp>
#include <Scenes/Scenes.hpp>
#include "Config.hpp"

using namespace acid;

int main(int argc, char **argv) {
	// Creates the engine.
	auto engine = std::make_unique<Engine>(argv[0]);

	// TODO: Only when not installed. 
	if (std::filesystem::exists(GAME_RESOURCES_DEV)) {
		Files::Get()->AddSearchPath(std::string(GAME_RESOURCES_DEV));
	}
	
	// Registers file search paths.
	Files::Get()->AddSearchPath("Resources/Game");
	Files::Get()->AddSearchPath("Resources/Engine");

	Log::Out("Working Directory: %ls\n", std::filesystem::current_path());

	// Registers modules.

	// Registers components.

	// Initializes modules.
	auto window0 = Windows::Get()->AddWindow();
	window0->SetTitle("Game");
	window0->SetIcons({"Icons/Icon-16.png", "Icons/Icon-24.png", "Icons/Icon-32.png", "Icons/Icon-48.png",
		"Icons/Icon-64.png", "Icons/Icon-96.png", "Icons/Icon-128.png", "Icons/Icon-192.png", "Icons/Icon-256.png"});
	
	window0->OnClose().connect([]() {
		Engine::Get()->RequestClose();
	});

	//Graphics::Get()->SetManager(std::make_unique<MainRenderer>());
	//Scenes::Get()->SetScene(std::make_unique<Scene1>());

	// Runs the game loop.
	auto exitCode = engine->Run();

	// Pauses the console.
	//std::cout << "Press enter to continue...";
	//std::cin.get();
	return exitCode;
}
