#ifndef VARIOUSTOOLS_HPP
#define VARIOUSTOOLS_HPP
#include<vector>
#include<SDL.h>


void listRenderersInformation()
{
    int renderDriversNumber = SDL_GetNumRenderDrivers();
    std::vector<SDL_RendererInfo*> renderersDriversInformations;

    for (int i = 0; i < renderDriversNumber; i++)
    {
        renderersDriversInformations.push_back(new SDL_RendererInfo);
        SDL_GetRenderDriverInfo(i, renderersDriversInformations.at(i));
    }

    for (int i = 0; i < renderDriversNumber; i++)
    {
        std::cout << renderersDriversInformations[i]->name << std::endl;
        for (int j = 0; j < renderersDriversInformations[i]->num_texture_formats; j++)
        {
            std::cout << SDL_GetPixelFormatName(renderersDriversInformations[i]->texture_formats[j]) << std::endl;
        }
    }

    for (int i = 0; i < renderDriversNumber; i++)
    {
        delete renderersDriversInformations.at(i);
    }

}

#endif
