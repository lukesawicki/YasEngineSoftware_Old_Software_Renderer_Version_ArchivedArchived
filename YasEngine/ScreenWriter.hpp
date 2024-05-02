#ifndef SCREENWRITER_HPP
#define SCREENWRITER_HPP
#include<string>
#include<vector>
#include<SDL_surface.h>
#include"Vector2D.hpp"
#include"ViewPort.hpp"
#include "FontObject.hpp"
#include "FontSurface.hpp"

class ScreenWriter final
{
    public:
        static const int NUMBER_OF_CHARACTERS = 37;
        static const int FONT_WIDTH = 17;
        static const int FONT_HEIGHT = 17;

        struct Font {
            Font()
            {
                verticesBaseData = new FontObject();
                surface = new FontSurface();
            }
            FontObject* verticesBaseData;
            FontSurface* surface;
        };
        std::vector<Font*> fonts;
        char charactersTable[NUMBER_OF_CHARACTERS];
        ScreenWriter();
        void initialize();
        void initializeFontObjects();
        void initializeFontSurfaces();
        void prepareFontVertices();
        void write(int x, int y, std::string text, const Vector4D<Uint8>& color, PixelsTable& pixelsTable);
        void initialize(int characterWidth, int characterHeight, const char* plik_znakow);
        void writeNew(int x, int y, std::string text, SDL_Surface *na_czym, int width, int height);
};

#endif //SCREENWRITER_HPP
