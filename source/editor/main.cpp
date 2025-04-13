#include <filesystem>
#include <iostream>
#include <string>
#include "runtime/engine.h"
#include "editor.h"


int main(int argc, char** argv)
{
	std::filesystem::path executable_path(argv[0]);
	std::filesystem::path config_file_path = executable_path.parent_path().parent_path() / "configs/ToonEditor.ini";

	Toon::ToonEngine* engine = new Toon::ToonEngine();
	engine->initialize();
	engine->startEngine(config_file_path.generic_string());

	Toon::ToonEditor* editor = new Toon::ToonEditor();
	editor->initialize(engine);
	editor->run();
	editor->clear();

	engine->clear();
	engine->shutdownEngine();

	return 0;
}