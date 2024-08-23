#include <SDL.h>
#include <iostream>

int  main(int  argc,  char*  argv[])
{
        bool  quit  =  false;
        SDL_Event  event;
        if  (SDL_Init(SDL_INIT_VIDEO)  !=  0)  {
                std::cout  <<  "SDL_Init  Error:  "  <<  SDL_GetError()  <<  std::endl;
                return  1;
        }

        SDL_Window*  win  =  SDL_CreateWindow("Hello  SDL3",  640,  480,  NULL);
        if  (win  ==  nullptr)  {
                std::cout  <<  "SDL_CreateWindow  Error:  "  <<  SDL_GetError()  <<  std::endl;
                SDL_Quit();
                return  1;
        }

        while  (!quit)
        {
                while  (SDL_PollEvent(&event))
                {
                        if  (event.type  ==  SDL_EVENT_QUIT)
                        {
                                quit  =  true;
                        }
                        else
                        {
                                if  (event.type  ==  SDL_EVENT_KEY_DOWN)
                                {
                                        switch  (event.key.key)
                                        {
                                        case  SDLK_ESCAPE:
                                                quit  =  true;
                                                break;
                                        case  SDLK_SPACE:
                                                quit  =  true;
                                                break;
                                        default:
                                                ;
                                        }
                                }
                        }
                }
        }

        //SDL_Delay(9000);

        SDL_DestroyWindow(win);
        SDL_Quit();
        return  0;
}