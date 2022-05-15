#include"YasEngine.hpp"
#define SDL_MAIN_HANDLED

// Free music used during development:
// Strange World by Darkroom (c) copyright 2022 Licensed under a Creative Commons Attribution Noncommercial  (3.0) license. http://dig.ccmixter.org/files/mactonite/64736 Ft: Martin Cee

int main(int argc, char* argv[])
{
	YasEngine* yasEngine = YasEngine::GetInstance();
	yasEngine->initialize();
	yasEngine->YasEnginStart();
	return 0;
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
