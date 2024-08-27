#include "yas_engine.hpp"
#define SDL_MAIN_HANDLED

int main(int argc, char* argv[]) {
  YasEngine* yas_engine = YasEngine::GetInstance();
  yas_engine->initialize();
  yas_engine->YasEngineStart();
  return 0;
}
