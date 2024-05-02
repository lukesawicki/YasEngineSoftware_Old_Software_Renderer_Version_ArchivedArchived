#include"YasEngine.hpp"
#define SDL_MAIN_HANDLED

void TODO(const char* todo)
{
	std::cout << todo << "\n";
}

int main(int argc, char* argv[])
{
	YasEngine* yasEngine = YasEngine::GetInstance();
	yasEngine->initialize();
	yasEngine->YasEnginStart();
	return 0;
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
