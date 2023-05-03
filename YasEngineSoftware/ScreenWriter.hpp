#ifndef YASENGINESOFTWARE_SCREENWRITER_HPP
#define YASENGINESOFTWARE_SCREENWRITER_HPP
#include<string>
#include<vector>
#include<SDL2/SDL_surface.h>
#include"Vector2D.hpp"
#include"ViewPort.hpp"
#include "FontObject.hpp"
#include "FontSurface.hpp"

class ScreenWriter final : public ViewPort
{
    public:
        struct Font {
            FontObject* vertisecBaseData;
            FontSurface* surface;
        };
        std::vector<Font*> fonts;
        char charactersTable[37];
        ScreenWriter();
        void initialize();
        void write(int x, int y, const char * text, SDL_Surface *na_czym);
        void write(int x, int y, std::string text, SDL_Surface *na_czym);
        void write(int x, int y, short integers, SDL_Surface *na_czym);
        void initialize(int characterWidth, int characterHeight, const char* plik_znakow);
        void writeNew(int x, int y, std::string text, SDL_Surface *na_czym, int width, int height);
};

#endif //YASENGINESOFTWARE_SCREENWRITER_HPP
