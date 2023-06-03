#include"ScreenWriter.hpp"
#include<iostream>
#include<sstream>
#include"YasGraphicsLibrary.hpp"
using namespace std;
ScreenWriter::ScreenWriter()
{
    int step;
    step=65;//Capital letters
    for(int i=0; i<26; i++)
    {
        charactersTable[i]=static_cast<char>(step++);
    }
    step=48;//Digits
    for(int i=26; i<36; i++)
    {
        charactersTable[i]=static_cast<char>(step++);
    }
    charactersTable[36]=' ';
    //Tablica znakow jest w celu wymowania z znakow z pliku graficznego na podstawie indeksu w tablicy znakow

    for(int i=0; i<NUMBER_OF_CHARACTERS; i++)
    {
        fonts.push_back(new Font());
    }
}
void ScreenWriter::initialize()
{
    initializeFontSurfaces();
    initializeFontObjects();
    prepareFontVertices();
}
void ScreenWriter::initialize(int szerokosc_znaku, int wysokosc_znaku, const char* plik_znakow)
{

}
void ScreenWriter::writeNew(int x, int y, string text, SDL_Surface *na_czym, int width, int height)
{
    SDL_Rect docelowe;
    int pom_w=0, pom_h=0;
    docelowe.x=x;
    docelowe.y=y;
    docelowe.w=width;
    docelowe.h=height;
    for(int i=0; i<static_cast<int>(text.size()); i++)
    {
        for(int j=0; j<63; j++)
        {
            if(text.at(i) == charactersTable[j])
            {
                //position.x=docelowe.w*j;
                docelowe.x=x+i*docelowe.w;
//                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
            }

        }
    }
}
//void ScreenWriter::write(int x, int y, const char * text, SDL_Surface *na_czym)
//{
//
//    string napis = text;
//    SDL_Rect docelowe;
//    docelowe.x=x;
//    docelowe.y=y;
////    docelowe.w=this->pozycja.w;
////    docelowe.h=this->pozycja.h;
//    for(int i=0; i<static_cast<int>(napis.size()); i++)
//    {
//        for(int j=0; j<63; j++)
//        {
//            if(napis.at(i) == charactersTable[j])
//            {
//                //position.x=docelowe.w*j;
//                docelowe.x=x+i*docelowe.w;
////                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
//            }
//
//        }
//    }
//}

void ScreenWriter::write(int x, int y, string text, const Vector4D<Uint8>& color, PixelsTable& pixelsTable)
{
    for(int i=0; i<static_cast<int>(text.size()); i++)
    {
        for(int j=0; j<NUMBER_OF_CHARACTERS; j++)
        {
            if(text.at(i) == charactersTable[j])
            {
                fonts.at(j)->verticesBaseData->setPosition(static_cast<float>(x + i*FONT_WIDTH), static_cast<float>(y));
                fonts.at(j)->verticesBaseData->generate();
                drawNumbersAsGroupOfLines(fonts.at(j)->verticesBaseData->worldVertices, fonts.at(j)->verticesBaseData->numberOfVertices, color, false, pixelsTable);
            }

        }
    }
}

//void ScreenWriter::write(int x, int y, short integers, SDL_Surface *na_czym)
//{
//    ostringstream oss_wyjsciowy;
//
//    oss_wyjsciowy << integers;
//
//    string napis="";
//    napis = oss_wyjsciowy.str();
//    SDL_Rect docelowe;
//    int pom_w=0, pom_h=0;
//    docelowe.x=x;
//    docelowe.y=y;
////    docelowe.w=this->pozycja.w;
////    docelowe.h=this->pozycja.h;
//    for(int i=0; i<static_cast<int>(napis.size()); i++)
//    {
//        for(int j=0; j<63; j++)
//        {
//            if(napis.at(i) == charactersTable[j])
//            {
//                //position.x=docelowe.w*j;
//                docelowe.x=x+i*docelowe.w;
////                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
//            }
//
//        }
//    }
//}

void ScreenWriter::initializeFontObjects()
{
    Vector2D<float> direction(0, 1);
    for(int i=0; i<NUMBER_OF_CHARACTERS; i++)
    {
        fonts.at(i)->verticesBaseData->initialize(17, 0, 0, direction, -1);
    }

}

void ScreenWriter::initializeFontSurfaces()
{
    for(int i=0; i<NUMBER_OF_CHARACTERS; i++)
    {
        //void initialize(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor);
        fonts.at(i)->surface->initialize(i*17, 0, 17, 17, GREEN);
    }
}

void ScreenWriter::prepareFontVertices()
{
    //A 6
    fonts[0]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[0]->verticesBaseData->worldVertices = new Vector2D<float>[6];
    fonts[0]->verticesBaseData->numberOfVertices = 6;

    fonts[0]->verticesBaseData->localVertices[0].x = -5;
    fonts[0]->verticesBaseData->localVertices[0].y = -7;

    fonts[0]->verticesBaseData->localVertices[1].x = 0;
    fonts[0]->verticesBaseData->localVertices[1].y = 7;


    fonts[0]->verticesBaseData->localVertices[2].x = 0;
    fonts[0]->verticesBaseData->localVertices[2].y = 7;

    fonts[0]->verticesBaseData->localVertices[3].x = 5;
    fonts[0]->verticesBaseData->localVertices[3].y = -7;


    fonts[0]->verticesBaseData->localVertices[4].x = -2;
    fonts[0]->verticesBaseData->localVertices[4].y = 0;

    fonts[0]->verticesBaseData->localVertices[5].x = 2;
    fonts[0]->verticesBaseData->localVertices[5].y = 0;

    //B 16
    fonts[1]->verticesBaseData->localVertices = new Vector2D<float>[16];
    fonts[1]->verticesBaseData->worldVertices = new Vector2D<float>[16];

    fonts[1]->verticesBaseData->numberOfVertices = 16;

    fonts[1]->verticesBaseData->localVertices[0].x = -5;
    fonts[1]->verticesBaseData->localVertices[0].y = -7;

    fonts[1]->verticesBaseData->localVertices[1].x = -5;
    fonts[1]->verticesBaseData->localVertices[1].y = 0;


    fonts[1]->verticesBaseData->localVertices[2].x = -5;
    fonts[1]->verticesBaseData->localVertices[2].y = 0;

    fonts[1]->verticesBaseData->localVertices[3].x = -5;
    fonts[1]->verticesBaseData->localVertices[3].y = 7;


    fonts[1]->verticesBaseData->localVertices[4].x = -5;
    fonts[1]->verticesBaseData->localVertices[4].y = 7;

    fonts[1]->verticesBaseData->localVertices[5].x = 5;
    fonts[1]->verticesBaseData->localVertices[5].y = 6;


    fonts[1]->verticesBaseData->localVertices[6].x = 5;
    fonts[1]->verticesBaseData->localVertices[6].y = 6;

    fonts[1]->verticesBaseData->localVertices[7].x = 5;
    fonts[1]->verticesBaseData->localVertices[7].y = 3;


    fonts[1]->verticesBaseData->localVertices[8].x = 5;
    fonts[1]->verticesBaseData->localVertices[8].y = 3;

    fonts[1]->verticesBaseData->localVertices[9].x = -5;
    fonts[1]->verticesBaseData->localVertices[9].y = 0;


    fonts[1]->verticesBaseData->localVertices[10].x = -5;
    fonts[1]->verticesBaseData->localVertices[10].y = 0;

    fonts[1]->verticesBaseData->localVertices[11].x = 5;
    fonts[1]->verticesBaseData->localVertices[11].y = -2;


    fonts[1]->verticesBaseData->localVertices[12].x = 5;
    fonts[1]->verticesBaseData->localVertices[12].y = -2;

    fonts[1]->verticesBaseData->localVertices[13].x = 5;
    fonts[1]->verticesBaseData->localVertices[13].y = -6;


    fonts[1]->verticesBaseData->localVertices[14].x = 5;
    fonts[1]->verticesBaseData->localVertices[14].y = -6;

    fonts[1]->verticesBaseData->localVertices[15].x = -5;
    fonts[1]->verticesBaseData->localVertices[15].y = -7;


    //C 6
    fonts[2]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[2]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[2]->verticesBaseData->numberOfVertices = 6;

    fonts[2]->verticesBaseData->localVertices[0].x = 5;
    fonts[2]->verticesBaseData->localVertices[0].y = -7;

    fonts[2]->verticesBaseData->localVertices[1].x = -5;
    fonts[2]->verticesBaseData->localVertices[1].y = -5;


    fonts[2]->verticesBaseData->localVertices[2].x = -5;
    fonts[2]->verticesBaseData->localVertices[2].y = -5;

    fonts[2]->verticesBaseData->localVertices[3].x = -5;
    fonts[2]->verticesBaseData->localVertices[3].y = 5;


    fonts[2]->verticesBaseData->localVertices[4].x = -5;
    fonts[2]->verticesBaseData->localVertices[4].y = 5;

    fonts[2]->verticesBaseData->localVertices[5].x = 5;
    fonts[2]->verticesBaseData->localVertices[5].y = 7;

    // D 8
    fonts[3]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[3]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[3]->verticesBaseData->numberOfVertices = 8;

    fonts[3]->verticesBaseData->localVertices[0].x = -5;
    fonts[3]->verticesBaseData->localVertices[0].y = -7;

    fonts[3]->verticesBaseData->localVertices[1].x = -5;
    fonts[3]->verticesBaseData->localVertices[1].y = 7;


    fonts[3]->verticesBaseData->localVertices[2].x = -5;
    fonts[3]->verticesBaseData->localVertices[2].y = 7;

    fonts[3]->verticesBaseData->localVertices[3].x = 5;
    fonts[3]->verticesBaseData->localVertices[3].y = 5;


    fonts[3]->verticesBaseData->localVertices[4].x = 5;
    fonts[3]->verticesBaseData->localVertices[4].y = 5;

    fonts[3]->verticesBaseData->localVertices[5].x = 5;
    fonts[3]->verticesBaseData->localVertices[5].y = -5;


    fonts[3]->verticesBaseData->localVertices[6].x = 5;
    fonts[3]->verticesBaseData->localVertices[6].y = -5;

    fonts[3]->verticesBaseData->localVertices[7].x = -5;
    fonts[3]->verticesBaseData->localVertices[7].y = -7;

    // E 10
    fonts[4]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[4]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[4]->verticesBaseData->numberOfVertices = 10;

    fonts[4]->verticesBaseData->localVertices[0].x = 5;
    fonts[4]->verticesBaseData->localVertices[0].y = -7;

    fonts[4]->verticesBaseData->localVertices[1].x = -5;
    fonts[4]->verticesBaseData->localVertices[1].y = -7;


    fonts[4]->verticesBaseData->localVertices[2].x = -5;
    fonts[4]->verticesBaseData->localVertices[2].y = -7;

    fonts[4]->verticesBaseData->localVertices[3].x = -5;
    fonts[4]->verticesBaseData->localVertices[3].y = 0;


    fonts[4]->verticesBaseData->localVertices[4].x = -5;
    fonts[4]->verticesBaseData->localVertices[4].y = 0;

    fonts[4]->verticesBaseData->localVertices[5].x = -5;
    fonts[4]->verticesBaseData->localVertices[5].y = 7;


    fonts[4]->verticesBaseData->localVertices[6].x = -5;
    fonts[4]->verticesBaseData->localVertices[6].y = 7;

    fonts[4]->verticesBaseData->localVertices[7].x = 5;
    fonts[4]->verticesBaseData->localVertices[7].y = 7;


    fonts[4]->verticesBaseData->localVertices[8].x = -5;
    fonts[4]->verticesBaseData->localVertices[8].y = 0;

    fonts[4]->verticesBaseData->localVertices[9].x = 5;
    fonts[4]->verticesBaseData->localVertices[9].y = 0;


    // F 8
    fonts[5]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[5]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[5]->verticesBaseData->numberOfVertices = 8;

    fonts[5]->verticesBaseData->localVertices[0].x = -5;
    fonts[5]->verticesBaseData->localVertices[0].y = -7;

    fonts[5]->verticesBaseData->localVertices[1].x = -5;
    fonts[5]->verticesBaseData->localVertices[1].y = 0;


    fonts[5]->verticesBaseData->localVertices[2].x = -5;
    fonts[5]->verticesBaseData->localVertices[2].y = 0;

    fonts[5]->verticesBaseData->localVertices[3].x = -5;
    fonts[5]->verticesBaseData->localVertices[3].y = 7;


    fonts[5]->verticesBaseData->localVertices[4].x = -5;
    fonts[5]->verticesBaseData->localVertices[4].y = 7;

    fonts[5]->verticesBaseData->localVertices[5].x = 5;
    fonts[5]->verticesBaseData->localVertices[5].y = 7;


    fonts[5]->verticesBaseData->localVertices[6].x = -5;
    fonts[5]->verticesBaseData->localVertices[6].y = 0;

    fonts[5]->verticesBaseData->localVertices[7].x = 5;
    fonts[5]->verticesBaseData->localVertices[7].y = 0;

    // G 10
    fonts[6]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[6]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[6]->verticesBaseData->numberOfVertices = 10;

    fonts[6]->verticesBaseData->localVertices[0].x = 1;
    fonts[6]->verticesBaseData->localVertices[0].y = -1;

    fonts[6]->verticesBaseData->localVertices[1].x = 4;
    fonts[6]->verticesBaseData->localVertices[1].y = -1;


    fonts[6]->verticesBaseData->localVertices[2].x = 4;
    fonts[6]->verticesBaseData->localVertices[2].y = -1;

    fonts[6]->verticesBaseData->localVertices[3].x = 5;
    fonts[6]->verticesBaseData->localVertices[3].y = -7;


    fonts[6]->verticesBaseData->localVertices[4].x = 5;
    fonts[6]->verticesBaseData->localVertices[4].y = -7;

    fonts[6]->verticesBaseData->localVertices[5].x = -5;
    fonts[6]->verticesBaseData->localVertices[5].y = -5;


    fonts[6]->verticesBaseData->localVertices[6].x = -5;
    fonts[6]->verticesBaseData->localVertices[6].y = -5;

    fonts[6]->verticesBaseData->localVertices[7].x = -5;
    fonts[6]->verticesBaseData->localVertices[7].y = 5;


    fonts[6]->verticesBaseData->localVertices[8].x = -5;
    fonts[6]->verticesBaseData->localVertices[8].y = 5;

    fonts[6]->verticesBaseData->localVertices[9].x = 5;
    fonts[6]->verticesBaseData->localVertices[9].y = 7;

    // H 6
    fonts[7]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[7]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[7]->verticesBaseData->numberOfVertices = 6;

    fonts[7]->verticesBaseData->localVertices[0].x = -5;
    fonts[7]->verticesBaseData->localVertices[0].y = -7;

    fonts[7]->verticesBaseData->localVertices[1].x = -5;
    fonts[7]->verticesBaseData->localVertices[1].y = 7;


    fonts[7]->verticesBaseData->localVertices[2].x = -5;
    fonts[7]->verticesBaseData->localVertices[2].y = 0;

    fonts[7]->verticesBaseData->localVertices[3].x = 5;
    fonts[7]->verticesBaseData->localVertices[3].y = 0;


    fonts[7]->verticesBaseData->localVertices[4].x = 5;
    fonts[7]->verticesBaseData->localVertices[4].y = 7;

    fonts[7]->verticesBaseData->localVertices[5].x = 5;
    fonts[7]->verticesBaseData->localVertices[5].y = -7;


    // I 6
    fonts[8]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[8]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[8]->verticesBaseData->numberOfVertices = 6;

    fonts[8]->verticesBaseData->localVertices[0].x = -1;
    fonts[8]->verticesBaseData->localVertices[0].y = -7;

    fonts[8]->verticesBaseData->localVertices[1].x = 1;
    fonts[8]->verticesBaseData->localVertices[1].y = -7;


    fonts[8]->verticesBaseData->localVertices[2].x = 0;
    fonts[8]->verticesBaseData->localVertices[2].y = -7;

    fonts[8]->verticesBaseData->localVertices[3].x = 0;
    fonts[8]->verticesBaseData->localVertices[3].y = 7;


    fonts[8]->verticesBaseData->localVertices[4].x = -1;
    fonts[8]->verticesBaseData->localVertices[4].y = 7;

    fonts[8]->verticesBaseData->localVertices[5].x = 1;
    fonts[8]->verticesBaseData->localVertices[5].y = 7;

    // J 10
    fonts[9]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[9]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[9]->verticesBaseData->numberOfVertices = 10;

    fonts[9]->verticesBaseData->localVertices[0].x = -2;
    fonts[9]->verticesBaseData->localVertices[0].y = -6;

    fonts[9]->verticesBaseData->localVertices[1].x = -1;
    fonts[9]->verticesBaseData->localVertices[1].y = -7;


    fonts[9]->verticesBaseData->localVertices[2].x = -1;
    fonts[9]->verticesBaseData->localVertices[2].y = -7;

    fonts[9]->verticesBaseData->localVertices[3].x = 0;
    fonts[9]->verticesBaseData->localVertices[3].y = -7;


    fonts[9]->verticesBaseData->localVertices[4].x = 0;
    fonts[9]->verticesBaseData->localVertices[4].y = -7;

    fonts[9]->verticesBaseData->localVertices[5].x = 1;
    fonts[9]->verticesBaseData->localVertices[5].y = -6;


    fonts[9]->verticesBaseData->localVertices[6].x = 1;
    fonts[9]->verticesBaseData->localVertices[6].y = -6;

    fonts[9]->verticesBaseData->localVertices[7].x = 1;
    fonts[9]->verticesBaseData->localVertices[7].y = 7;


    fonts[9]->verticesBaseData->localVertices[8].x = 1;
    fonts[9]->verticesBaseData->localVertices[8].y = 7;

    fonts[9]->verticesBaseData->localVertices[9].x = -1;
    fonts[9]->verticesBaseData->localVertices[9].y = 7;

    // K 8
    fonts[10]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[10]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[10]->verticesBaseData->numberOfVertices = 8;

    fonts[10]->verticesBaseData->localVertices[0].x = -5;
    fonts[10]->verticesBaseData->localVertices[0].y = -7;

    fonts[10]->verticesBaseData->localVertices[1].x = -5;
    fonts[10]->verticesBaseData->localVertices[1].y = 0;


    fonts[10]->verticesBaseData->localVertices[2].x = -5;
    fonts[10]->verticesBaseData->localVertices[2].y = 0;

    fonts[10]->verticesBaseData->localVertices[3].x = -5;
    fonts[10]->verticesBaseData->localVertices[3].y = 7;


    fonts[10]->verticesBaseData->localVertices[4].x = -5;
    fonts[10]->verticesBaseData->localVertices[4].y = 0;

    fonts[10]->verticesBaseData->localVertices[5].x = 5;
    fonts[10]->verticesBaseData->localVertices[5].y = 7;


    fonts[10]->verticesBaseData->localVertices[6].x = -5;
    fonts[10]->verticesBaseData->localVertices[6].y = 0;

    fonts[10]->verticesBaseData->localVertices[7].x = 5;
    fonts[10]->verticesBaseData->localVertices[7].y = -7;

    // L 4
    fonts[11]->verticesBaseData->localVertices = new Vector2D<float>[4];
    fonts[11]->verticesBaseData->worldVertices = new Vector2D<float>[4];

    fonts[11]->verticesBaseData->numberOfVertices = 4;

    fonts[11]->verticesBaseData->localVertices[0].x = -5;
    fonts[11]->verticesBaseData->localVertices[0].y = -7;

    fonts[11]->verticesBaseData->localVertices[1].x = 5;
    fonts[11]->verticesBaseData->localVertices[1].y = -7;


    fonts[11]->verticesBaseData->localVertices[2].x = -5;
    fonts[11]->verticesBaseData->localVertices[2].y = -7;

    fonts[11]->verticesBaseData->localVertices[3].x = -5;
    fonts[11]->verticesBaseData->localVertices[3].y = 7;

    // M 8
    fonts[12]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[12]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[12]->verticesBaseData->numberOfVertices = 8;

    fonts[12]->verticesBaseData->localVertices[0].x = -5;
    fonts[12]->verticesBaseData->localVertices[0].y = -7;

    fonts[12]->verticesBaseData->localVertices[1].x = -5;
    fonts[12]->verticesBaseData->localVertices[1].y = 7;


    fonts[12]->verticesBaseData->localVertices[2].x = -5;
    fonts[12]->verticesBaseData->localVertices[2].y = 7;

    fonts[12]->verticesBaseData->localVertices[3].x = 0;
    fonts[12]->verticesBaseData->localVertices[3].y = -7;


    fonts[12]->verticesBaseData->localVertices[4].x = 0;
    fonts[12]->verticesBaseData->localVertices[4].y = -7;

    fonts[12]->verticesBaseData->localVertices[5].x = 5;
    fonts[12]->verticesBaseData->localVertices[5].y = 7;


    fonts[12]->verticesBaseData->localVertices[6].x = 5;
    fonts[12]->verticesBaseData->localVertices[6].y = 7;

    fonts[12]->verticesBaseData->localVertices[7].x = 5;
    fonts[12]->verticesBaseData->localVertices[7].y = -7;

    // N 6
    fonts[13]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[13]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[13]->verticesBaseData->numberOfVertices = 6;

    fonts[13]->verticesBaseData->localVertices[0].x = -5;
    fonts[13]->verticesBaseData->localVertices[0].y = -7;

    fonts[13]->verticesBaseData->localVertices[1].x = -5;
    fonts[13]->verticesBaseData->localVertices[1].y = 7;


    fonts[13]->verticesBaseData->localVertices[2].x = -5;
    fonts[13]->verticesBaseData->localVertices[2].y = 7;

    fonts[13]->verticesBaseData->localVertices[3].x = 5;
    fonts[13]->verticesBaseData->localVertices[3].y = -7;


    fonts[13]->verticesBaseData->localVertices[4].x = 5;
    fonts[13]->verticesBaseData->localVertices[4].y = -7;

    fonts[13]->verticesBaseData->localVertices[5].x = 5;
    fonts[13]->verticesBaseData->localVertices[5].y = 7;

    // O 8
    fonts[14]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[14]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[14]->verticesBaseData->numberOfVertices = 8;

    fonts[14]->verticesBaseData->localVertices[0].x = -5;
    fonts[14]->verticesBaseData->localVertices[0].y = -7;

    fonts[14]->verticesBaseData->localVertices[1].x = -5;
    fonts[14]->verticesBaseData->localVertices[1].y = 7;


    fonts[14]->verticesBaseData->localVertices[2].x = -5;
    fonts[14]->verticesBaseData->localVertices[2].y = 7;

    fonts[14]->verticesBaseData->localVertices[3].x = 5;
    fonts[14]->verticesBaseData->localVertices[3].y = 7;


    fonts[14]->verticesBaseData->localVertices[4].x = 5;
    fonts[14]->verticesBaseData->localVertices[4].y = 7;

    fonts[14]->verticesBaseData->localVertices[5].x = 5;
    fonts[14]->verticesBaseData->localVertices[5].y = -7;


    fonts[14]->verticesBaseData->localVertices[6].x = -5;
    fonts[14]->verticesBaseData->localVertices[6].y = -7;

    fonts[14]->verticesBaseData->localVertices[7].x = 5;
    fonts[14]->verticesBaseData->localVertices[7].y = -7;

    // P 10
    fonts[15]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[15]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[15]->verticesBaseData->numberOfVertices = 10;

    fonts[15]->verticesBaseData->localVertices[0].x = -5;
    fonts[15]->verticesBaseData->localVertices[0].y = -7;

    fonts[15]->verticesBaseData->localVertices[1].x = -5;
    fonts[15]->verticesBaseData->localVertices[1].y = 0;


    fonts[15]->verticesBaseData->localVertices[2].x = -5;
    fonts[15]->verticesBaseData->localVertices[2].y = 0;

    fonts[15]->verticesBaseData->localVertices[3].x = -5;
    fonts[15]->verticesBaseData->localVertices[3].y = 7;


    fonts[15]->verticesBaseData->localVertices[4].x = -5;
    fonts[15]->verticesBaseData->localVertices[4].y = 7;

    fonts[15]->verticesBaseData->localVertices[5].x = 5;
    fonts[15]->verticesBaseData->localVertices[5].y = 7;


    fonts[15]->verticesBaseData->localVertices[6].x = 5;
    fonts[15]->verticesBaseData->localVertices[6].y = 7;

    fonts[15]->verticesBaseData->localVertices[7].x = 5;
    fonts[15]->verticesBaseData->localVertices[7].y = 0;


    fonts[15]->verticesBaseData->localVertices[8].x = 5;
    fonts[15]->verticesBaseData->localVertices[8].y = 0;

    fonts[15]->verticesBaseData->localVertices[9].x = -5;
    fonts[15]->verticesBaseData->localVertices[9].y = 0;

    // Q 10
    fonts[16]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[16]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[16]->verticesBaseData->numberOfVertices = 10;

    fonts[16]->verticesBaseData->localVertices[0].x = -5;
    fonts[16]->verticesBaseData->localVertices[0].y = -7;

    fonts[16]->verticesBaseData->localVertices[1].x = -5;
    fonts[16]->verticesBaseData->localVertices[1].y = 7;


    fonts[16]->verticesBaseData->localVertices[2].x = -5;
    fonts[16]->verticesBaseData->localVertices[2].y = 7;

    fonts[16]->verticesBaseData->localVertices[3].x = 5;
    fonts[16]->verticesBaseData->localVertices[3].y = 7;


    fonts[16]->verticesBaseData->localVertices[4].x = 5;
    fonts[16]->verticesBaseData->localVertices[4].y = 7;

    fonts[16]->verticesBaseData->localVertices[5].x = 5;
    fonts[16]->verticesBaseData->localVertices[5].y = -7;


    fonts[16]->verticesBaseData->localVertices[6].x =  5;
    fonts[16]->verticesBaseData->localVertices[6].y = -7;

    fonts[16]->verticesBaseData->localVertices[7].x = -5;
    fonts[16]->verticesBaseData->localVertices[7].y = -7;


    fonts[16]->verticesBaseData->localVertices[8].x = 3;
    fonts[16]->verticesBaseData->localVertices[8].y = -5;

    fonts[16]->verticesBaseData->localVertices[9].x = 7;
    fonts[16]->verticesBaseData->localVertices[9].y = -8;

    // R 12
    fonts[17]->verticesBaseData->localVertices = new Vector2D<float>[12];
    fonts[17]->verticesBaseData->worldVertices = new Vector2D<float>[12];

    fonts[17]->verticesBaseData->numberOfVertices = 12;

    fonts[17]->verticesBaseData->localVertices[0].x = -5;
    fonts[17]->verticesBaseData->localVertices[0].y = -7;

    fonts[17]->verticesBaseData->localVertices[1].x = -5;
    fonts[17]->verticesBaseData->localVertices[1].y = 0;


    fonts[17]->verticesBaseData->localVertices[2].x = -5;
    fonts[17]->verticesBaseData->localVertices[2].y = 0;

    fonts[17]->verticesBaseData->localVertices[3].x = -5;
    fonts[17]->verticesBaseData->localVertices[3].y = 7;


    fonts[17]->verticesBaseData->localVertices[4].x = -5;
    fonts[17]->verticesBaseData->localVertices[4].y = 7;

    fonts[17]->verticesBaseData->localVertices[5].x = 5;
    fonts[17]->verticesBaseData->localVertices[5].y = 7;


    fonts[17]->verticesBaseData->localVertices[6].x = 5;
    fonts[17]->verticesBaseData->localVertices[6].y = 7;

    fonts[17]->verticesBaseData->localVertices[7].x = 5;
    fonts[17]->verticesBaseData->localVertices[7].y = 0;


    fonts[17]->verticesBaseData->localVertices[8].x = 5;
    fonts[17]->verticesBaseData->localVertices[8].y = 0;

    fonts[17]->verticesBaseData->localVertices[9].x = -5;
    fonts[17]->verticesBaseData->localVertices[9].y = 0;


    fonts[17]->verticesBaseData->localVertices[10].x = -5;
    fonts[17]->verticesBaseData->localVertices[10].y = 0;

    fonts[17]->verticesBaseData->localVertices[11].x = 5;
    fonts[17]->verticesBaseData->localVertices[11].y = -7;

    // S 10
    fonts[18]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[18]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[18]->verticesBaseData->numberOfVertices = 10;

    fonts[18]->verticesBaseData->localVertices[0].x = -5;
    fonts[18]->verticesBaseData->localVertices[0].y = -7;

    fonts[18]->verticesBaseData->localVertices[1].x = 5;
    fonts[18]->verticesBaseData->localVertices[1].y = -7;


    fonts[18]->verticesBaseData->localVertices[2].x = 5;
    fonts[18]->verticesBaseData->localVertices[2].y = -7;

    fonts[18]->verticesBaseData->localVertices[3].x = 5;
    fonts[18]->verticesBaseData->localVertices[3].y = 0;


    fonts[18]->verticesBaseData->localVertices[4].x = 5;
    fonts[18]->verticesBaseData->localVertices[4].y = 0;

    fonts[18]->verticesBaseData->localVertices[5].x = -5;
    fonts[18]->verticesBaseData->localVertices[5].y = 0;


    fonts[18]->verticesBaseData->localVertices[6].x = -5;
    fonts[18]->verticesBaseData->localVertices[6].y = 0;

    fonts[18]->verticesBaseData->localVertices[7].x = -5;
    fonts[18]->verticesBaseData->localVertices[7].y = 7;


    fonts[18]->verticesBaseData->localVertices[8].x = -5;
    fonts[18]->verticesBaseData->localVertices[8].y = 7;

    fonts[18]->verticesBaseData->localVertices[9].x = 5;
    fonts[18]->verticesBaseData->localVertices[9].y = 7;

    // T 4
    fonts[19]->verticesBaseData->localVertices = new Vector2D<float>[4];
    fonts[19]->verticesBaseData->worldVertices = new Vector2D<float>[4];

    fonts[19]->verticesBaseData->numberOfVertices = 4;

    fonts[19]->verticesBaseData->localVertices[0].x = -5;
    fonts[19]->verticesBaseData->localVertices[0].y = 7;

    fonts[19]->verticesBaseData->localVertices[1].x = 5;
    fonts[19]->verticesBaseData->localVertices[1].y = 7;

    fonts[19]->verticesBaseData->localVertices[2].x = 0;
    fonts[19]->verticesBaseData->localVertices[2].y = 7;

    fonts[19]->verticesBaseData->localVertices[3].x = 0;
    fonts[19]->verticesBaseData->localVertices[3].y = -7;

    // U 6
    fonts[20]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[20]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[20]->verticesBaseData->numberOfVertices = 6;

    fonts[20]->verticesBaseData->localVertices[0].x = -5;
    fonts[20]->verticesBaseData->localVertices[0].y = 7;

    fonts[20]->verticesBaseData->localVertices[1].x = -5;
    fonts[20]->verticesBaseData->localVertices[1].y = -7;


    fonts[20]->verticesBaseData->localVertices[2].x = -5;
    fonts[20]->verticesBaseData->localVertices[2].y = -7;

    fonts[20]->verticesBaseData->localVertices[3].x = 5;
    fonts[20]->verticesBaseData->localVertices[3].y = -7;


    fonts[20]->verticesBaseData->localVertices[4].x = 5;
    fonts[20]->verticesBaseData->localVertices[4].y = -7;

    fonts[20]->verticesBaseData->localVertices[5].x = 5;
    fonts[20]->verticesBaseData->localVertices[5].y = 7;

    // V 4
    fonts[21]->verticesBaseData->localVertices = new Vector2D<float>[4];
    fonts[21]->verticesBaseData->worldVertices = new Vector2D<float>[4];

    fonts[21]->verticesBaseData->numberOfVertices = 4;

    fonts[21]->verticesBaseData->localVertices[0].x = -5;
    fonts[21]->verticesBaseData->localVertices[0].y = 7;

    fonts[21]->verticesBaseData->localVertices[1].x = 0;
    fonts[21]->verticesBaseData->localVertices[1].y = -7;


    fonts[21]->verticesBaseData->localVertices[2].x = 0;
    fonts[21]->verticesBaseData->localVertices[2].y = -7;

    fonts[21]->verticesBaseData->localVertices[3].x = 5;
    fonts[21]->verticesBaseData->localVertices[3].y = 7;

    // W 8
    fonts[22]->verticesBaseData->localVertices = new Vector2D<float>[8];
    fonts[22]->verticesBaseData->worldVertices = new Vector2D<float>[8];

    fonts[22]->verticesBaseData->numberOfVertices = 8;

    fonts[22]->verticesBaseData->localVertices[0].x = -5;
    fonts[22]->verticesBaseData->localVertices[0].y = 7;

    fonts[22]->verticesBaseData->localVertices[1].x = -3;
    fonts[22]->verticesBaseData->localVertices[1].y = -7;


    fonts[22]->verticesBaseData->localVertices[2].x = -3;
    fonts[22]->verticesBaseData->localVertices[2].y = -7;

    fonts[22]->verticesBaseData->localVertices[3].x = 0;
    fonts[22]->verticesBaseData->localVertices[3].y = 7;


    fonts[22]->verticesBaseData->localVertices[4].x = 0;
    fonts[22]->verticesBaseData->localVertices[4].y = 7;

    fonts[22]->verticesBaseData->localVertices[5].x = 3;
    fonts[22]->verticesBaseData->localVertices[5].y = -7;


    fonts[22]->verticesBaseData->localVertices[6].x = 3;
    fonts[22]->verticesBaseData->localVertices[6].y = -7;

    fonts[22]->verticesBaseData->localVertices[7].x = 5;
    fonts[22]->verticesBaseData->localVertices[7].y = 7;

    // X 4
    fonts[23]->verticesBaseData->localVertices = new Vector2D<float>[4];
    fonts[23]->verticesBaseData->worldVertices = new Vector2D<float>[4];

    fonts[23]->verticesBaseData->numberOfVertices = 4;

    fonts[23]->verticesBaseData->localVertices[0].x = -5;
    fonts[23]->verticesBaseData->localVertices[0].y = 7;

    fonts[23]->verticesBaseData->localVertices[1].x = 5;
    fonts[23]->verticesBaseData->localVertices[1].y = -7;


    fonts[23]->verticesBaseData->localVertices[2].x = -5;
    fonts[23]->verticesBaseData->localVertices[2].y = -7;

    fonts[23]->verticesBaseData->localVertices[3].x = 5;
    fonts[23]->verticesBaseData->localVertices[3].y = 7;

    // Y 6
    fonts[24]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[24]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[24]->verticesBaseData->numberOfVertices = 6;

    fonts[24]->verticesBaseData->localVertices[0].x = -5;
    fonts[24]->verticesBaseData->localVertices[0].y = 7;

    fonts[24]->verticesBaseData->localVertices[1].x = 0;
    fonts[24]->verticesBaseData->localVertices[1].y = 0;


    fonts[24]->verticesBaseData->localVertices[2].x = 0;
    fonts[24]->verticesBaseData->localVertices[2].y = 0;

    fonts[24]->verticesBaseData->localVertices[3].x = 0;
    fonts[24]->verticesBaseData->localVertices[3].y = -7;


    fonts[24]->verticesBaseData->localVertices[4].x = 0;
    fonts[24]->verticesBaseData->localVertices[4].y = 0;

    fonts[24]->verticesBaseData->localVertices[5].x = 5;
    fonts[24]->verticesBaseData->localVertices[5].y = 7;

    // Z 6
    fonts[25]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[25]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[25]->verticesBaseData->numberOfVertices = 6;

    fonts[25]->verticesBaseData->localVertices[0].x = -5;
    fonts[25]->verticesBaseData->localVertices[0].y = 7;

    fonts[25]->verticesBaseData->localVertices[1].x = 5;
    fonts[25]->verticesBaseData->localVertices[1].y = 7;


    fonts[25]->verticesBaseData->localVertices[2].x = 5;
    fonts[25]->verticesBaseData->localVertices[2].y = 7;

    fonts[25]->verticesBaseData->localVertices[3].x = -5;
    fonts[25]->verticesBaseData->localVertices[3].y = -7;


    fonts[25]->verticesBaseData->localVertices[4].x = -5;
    fonts[25]->verticesBaseData->localVertices[4].y = -7;

    fonts[25]->verticesBaseData->localVertices[5].x = 5;
    fonts[25]->verticesBaseData->localVertices[5].y = -7;

    // 0 10
    fonts[26]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[26]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[26]->verticesBaseData->numberOfVertices = 10;

    fonts[26]->verticesBaseData->localVertices[0].x = -5;
    fonts[26]->verticesBaseData->localVertices[0].y = -7;

    fonts[26]->verticesBaseData->localVertices[1].x = -5;
    fonts[26]->verticesBaseData->localVertices[1].y = 7;


    fonts[26]->verticesBaseData->localVertices[2].x = -5;
    fonts[26]->verticesBaseData->localVertices[2].y = 7;

    fonts[26]->verticesBaseData->localVertices[3].x = 5;
    fonts[26]->verticesBaseData->localVertices[3].y = 7;


    fonts[26]->verticesBaseData->localVertices[4].x = 5;
    fonts[26]->verticesBaseData->localVertices[4].y = 7;

    fonts[26]->verticesBaseData->localVertices[5].x = 5;
    fonts[26]->verticesBaseData->localVertices[5].y = -7;


    fonts[26]->verticesBaseData->localVertices[6].x = -5;
    fonts[26]->verticesBaseData->localVertices[6].y = -7;

    fonts[26]->verticesBaseData->localVertices[7].x = 5;
    fonts[26]->verticesBaseData->localVertices[7].y = -7;


    fonts[26]->verticesBaseData->localVertices[8].x = -3;
    fonts[26]->verticesBaseData->localVertices[8].y = 5;

    fonts[26]->verticesBaseData->localVertices[9].x = 3;
    fonts[26]->verticesBaseData->localVertices[9].y = -5;

    // 1 6
    fonts[27]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[27]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[27]->verticesBaseData->numberOfVertices = 6;

    fonts[27]->verticesBaseData->localVertices[0].x = -1;
    fonts[27]->verticesBaseData->localVertices[0].y = -7;

    fonts[27]->verticesBaseData->localVertices[1].x = 1;
    fonts[27]->verticesBaseData->localVertices[1].y = -7;


    fonts[27]->verticesBaseData->localVertices[2].x = 0;
    fonts[27]->verticesBaseData->localVertices[2].y = -7;

    fonts[27]->verticesBaseData->localVertices[3].x = 0;
    fonts[27]->verticesBaseData->localVertices[3].y = 7;


    fonts[27]->verticesBaseData->localVertices[4].x = 0;
    fonts[27]->verticesBaseData->localVertices[4].y = 7;

    fonts[27]->verticesBaseData->localVertices[5].x = -2;
    fonts[27]->verticesBaseData->localVertices[5].y = 5;

    // 2 10
    fonts[28]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[28]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[28]->verticesBaseData->numberOfVertices = 10;

    fonts[28]->verticesBaseData->localVertices[0].x = -5;
    fonts[28]->verticesBaseData->localVertices[0].y = -7;

    fonts[28]->verticesBaseData->localVertices[1].x = 5;
    fonts[28]->verticesBaseData->localVertices[1].y = -7;


    fonts[28]->verticesBaseData->localVertices[2].x = -5;
    fonts[28]->verticesBaseData->localVertices[2].y = -7;

    fonts[28]->verticesBaseData->localVertices[3].x = -5;
    fonts[28]->verticesBaseData->localVertices[3].y = 2;


    fonts[28]->verticesBaseData->localVertices[4].x = -5;
    fonts[28]->verticesBaseData->localVertices[4].y = 2;

    fonts[28]->verticesBaseData->localVertices[5].x = 5;
    fonts[28]->verticesBaseData->localVertices[5].y = 2;


    fonts[28]->verticesBaseData->localVertices[6].x = 5;
    fonts[28]->verticesBaseData->localVertices[6].y = 2;

    fonts[28]->verticesBaseData->localVertices[7].x = 5;
    fonts[28]->verticesBaseData->localVertices[7].y = 7;


    fonts[28]->verticesBaseData->localVertices[8].x = 5;
    fonts[28]->verticesBaseData->localVertices[8].y = 7;

    fonts[28]->verticesBaseData->localVertices[9].x = -5;
    fonts[28]->verticesBaseData->localVertices[9].y = 7;

    // 3 10
    fonts[29]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[29]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[29]->verticesBaseData->numberOfVertices = 10;

    fonts[29]->verticesBaseData->localVertices[0].x = -5;
    fonts[29]->verticesBaseData->localVertices[0].y = -7;

    fonts[29]->verticesBaseData->localVertices[1].x = 5;
    fonts[29]->verticesBaseData->localVertices[1].y = -7;


    fonts[29]->verticesBaseData->localVertices[2].x = 5;
    fonts[29]->verticesBaseData->localVertices[2].y = -7;

    fonts[29]->verticesBaseData->localVertices[3].x = 5;
    fonts[29]->verticesBaseData->localVertices[3].y = 2;


    fonts[29]->verticesBaseData->localVertices[4].x = -5;
    fonts[29]->verticesBaseData->localVertices[4].y = 2;

    fonts[29]->verticesBaseData->localVertices[5].x = 5;
    fonts[29]->verticesBaseData->localVertices[5].y = 2;


    fonts[29]->verticesBaseData->localVertices[6].x = 5;
    fonts[29]->verticesBaseData->localVertices[6].y = 2;

    fonts[29]->verticesBaseData->localVertices[7].x = 5;
    fonts[29]->verticesBaseData->localVertices[7].y = 7;


    fonts[29]->verticesBaseData->localVertices[8].x = -5;
    fonts[29]->verticesBaseData->localVertices[8].y = 7;

    fonts[29]->verticesBaseData->localVertices[9].x = 5;
    fonts[29]->verticesBaseData->localVertices[9].y = 7;

    // 4 6
    fonts[30]->verticesBaseData->localVertices = new Vector2D<float>[6];
    fonts[30]->verticesBaseData->worldVertices = new Vector2D<float>[6];

    fonts[30]->verticesBaseData->numberOfVertices = 6;

    fonts[30]->verticesBaseData->localVertices[0].x = -5;
    fonts[30]->verticesBaseData->localVertices[0].y = -4;

    fonts[30]->verticesBaseData->localVertices[1].x = 5;
    fonts[30]->verticesBaseData->localVertices[1].y = -4;


    fonts[30]->verticesBaseData->localVertices[2].x = -5;
    fonts[30]->verticesBaseData->localVertices[2].y = -4;

    fonts[30]->verticesBaseData->localVertices[3].x = 4;
    fonts[30]->verticesBaseData->localVertices[3].y = 7;


    fonts[30]->verticesBaseData->localVertices[4].x = 4;
    fonts[30]->verticesBaseData->localVertices[4].y = 7;

    fonts[30]->verticesBaseData->localVertices[5].x = 4;
    fonts[30]->verticesBaseData->localVertices[5].y = -7;

    // 5 10
    fonts[31]->verticesBaseData->localVertices = new Vector2D<float>[10];
    fonts[31]->verticesBaseData->worldVertices = new Vector2D<float>[10];

    fonts[31]->verticesBaseData->numberOfVertices = 10;

    fonts[31]->verticesBaseData->localVertices[0].x = -5;
    fonts[31]->verticesBaseData->localVertices[0].y = -7;

    fonts[31]->verticesBaseData->localVertices[1].x = 5;
    fonts[31]->verticesBaseData->localVertices[1].y = -7;


    fonts[31]->verticesBaseData->localVertices[2].x = 5;
    fonts[31]->verticesBaseData->localVertices[2].y = -7;

    fonts[31]->verticesBaseData->localVertices[3].x = 5;
    fonts[31]->verticesBaseData->localVertices[3].y = 2;


    fonts[31]->verticesBaseData->localVertices[4].x = -5;
    fonts[31]->verticesBaseData->localVertices[4].y = 2;

    fonts[31]->verticesBaseData->localVertices[5].x = 5;
    fonts[31]->verticesBaseData->localVertices[5].y = 2;


    fonts[31]->verticesBaseData->localVertices[6].x = -5;
    fonts[31]->verticesBaseData->localVertices[6].y = 2;

    fonts[31]->verticesBaseData->localVertices[7].x = -5;
    fonts[31]->verticesBaseData->localVertices[7].y = 7;


    fonts[31]->verticesBaseData->localVertices[8].x = -5;
    fonts[31]->verticesBaseData->localVertices[8].y = 7;

    fonts[31]->verticesBaseData->localVertices[9].x = 5;
    fonts[31]->verticesBaseData->localVertices[9].y = 7;

    // 6 12
    fonts[32]->verticesBaseData->localVertices = new Vector2D<float>[12];
    fonts[32]->verticesBaseData->worldVertices = new Vector2D<float>[12];

    fonts[32]->verticesBaseData->numberOfVertices = 12;

    fonts[32]->verticesBaseData->localVertices[0].x = -5;
    fonts[32]->verticesBaseData->localVertices[0].y = -7;

    fonts[32]->verticesBaseData->localVertices[1].x = 5;
    fonts[32]->verticesBaseData->localVertices[1].y = -7;


    fonts[32]->verticesBaseData->localVertices[2].x = 5;
    fonts[32]->verticesBaseData->localVertices[2].y = -7;

    fonts[32]->verticesBaseData->localVertices[3].x = 5;
    fonts[32]->verticesBaseData->localVertices[3].y = 2;


    fonts[32]->verticesBaseData->localVertices[4].x = 5;
    fonts[32]->verticesBaseData->localVertices[4].y = 2;

    fonts[32]->verticesBaseData->localVertices[5].x = -5;
    fonts[32]->verticesBaseData->localVertices[5].y = 2;


    fonts[32]->verticesBaseData->localVertices[6].x = -5;
    fonts[32]->verticesBaseData->localVertices[6].y = -7;

    fonts[32]->verticesBaseData->localVertices[7].x = -5;
    fonts[32]->verticesBaseData->localVertices[7].y = 2;


    fonts[32]->verticesBaseData->localVertices[8].x = -5;
    fonts[32]->verticesBaseData->localVertices[8].y = 2;

    fonts[32]->verticesBaseData->localVertices[9].x = -5;
    fonts[32]->verticesBaseData->localVertices[9].y = 7;


    fonts[32]->verticesBaseData->localVertices[10].x = -5;
    fonts[32]->verticesBaseData->localVertices[10].y = 7;

    fonts[32]->verticesBaseData->localVertices[11].x = 5;
    fonts[32]->verticesBaseData->localVertices[11].y = 7;

    // 7 4
    fonts[33]->verticesBaseData->localVertices = new Vector2D<float>[4];
    fonts[33]->verticesBaseData->worldVertices = new Vector2D<float>[4];

    fonts[33]->verticesBaseData->numberOfVertices = 4;

    fonts[33]->verticesBaseData->localVertices[0].x = -2;
    fonts[33]->verticesBaseData->localVertices[0].y = -7;

    fonts[33]->verticesBaseData->localVertices[1].x = 5;
    fonts[33]->verticesBaseData->localVertices[1].y = 7;


    fonts[33]->verticesBaseData->localVertices[2].x = -5;
    fonts[33]->verticesBaseData->localVertices[2].y = 7;

    fonts[33]->verticesBaseData->localVertices[3].x = 5;
    fonts[33]->verticesBaseData->localVertices[3].y = 7;

    // 8 14
    fonts[34]->verticesBaseData->localVertices = new Vector2D<float>[14];
    fonts[34]->verticesBaseData->worldVertices = new Vector2D<float>[14];

    fonts[34]->verticesBaseData->numberOfVertices = 14;

    fonts[34]->verticesBaseData->localVertices[0].x = -5;
    fonts[34]->verticesBaseData->localVertices[0].y = -7;

    fonts[34]->verticesBaseData->localVertices[1].x = 5;
    fonts[34]->verticesBaseData->localVertices[1].y = -7;


    fonts[34]->verticesBaseData->localVertices[2].x = 5;
    fonts[34]->verticesBaseData->localVertices[2].y = -5;

    fonts[34]->verticesBaseData->localVertices[3].x = 5;
    fonts[34]->verticesBaseData->localVertices[3].y = 0;


    fonts[34]->verticesBaseData->localVertices[4].x = 5;
    fonts[34]->verticesBaseData->localVertices[4].y = 0;

    fonts[34]->verticesBaseData->localVertices[5].x = -5;
    fonts[34]->verticesBaseData->localVertices[5].y = 0;


    fonts[34]->verticesBaseData->localVertices[6].x = -5;
    fonts[34]->verticesBaseData->localVertices[6].y = -7;

    fonts[34]->verticesBaseData->localVertices[7].x = -5;
    fonts[34]->verticesBaseData->localVertices[7].y = 0;


    fonts[34]->verticesBaseData->localVertices[8].x = -5;
    fonts[34]->verticesBaseData->localVertices[8].y = 0;

    fonts[34]->verticesBaseData->localVertices[9].x = -5;
    fonts[34]->verticesBaseData->localVertices[9].y = 7;


    fonts[34]->verticesBaseData->localVertices[10].x = -5;
    fonts[34]->verticesBaseData->localVertices[10].y = 7;

    fonts[34]->verticesBaseData->localVertices[11].x = 5;
    fonts[34]->verticesBaseData->localVertices[11].y = 7;


    fonts[34]->verticesBaseData->localVertices[12].x = 5;
    fonts[34]->verticesBaseData->localVertices[12].y = 7;

    fonts[34]->verticesBaseData->localVertices[13].x = 5;
    fonts[34]->verticesBaseData->localVertices[13].y = 0;

    // 9 12
    fonts[35]->verticesBaseData->localVertices = new Vector2D<float>[12];
    fonts[35]->verticesBaseData->worldVertices = new Vector2D<float>[12];

    fonts[35]->verticesBaseData->numberOfVertices = 12;

    fonts[35]->verticesBaseData->localVertices[0].x = -5;
    fonts[35]->verticesBaseData->localVertices[0].y = -7;

    fonts[35]->verticesBaseData->localVertices[1].x = 5;
    fonts[35]->verticesBaseData->localVertices[1].y = -7;


    fonts[35]->verticesBaseData->localVertices[2].x = 5;
    fonts[35]->verticesBaseData->localVertices[2].y = -7;

    fonts[35]->verticesBaseData->localVertices[3].x = 5;
    fonts[35]->verticesBaseData->localVertices[3].y = 0;


    fonts[35]->verticesBaseData->localVertices[4].x = 5;
    fonts[35]->verticesBaseData->localVertices[4].y = 0;

    fonts[35]->verticesBaseData->localVertices[5].x = -5;
    fonts[35]->verticesBaseData->localVertices[5].y = 0;


    fonts[35]->verticesBaseData->localVertices[6].x = -5;
    fonts[35]->verticesBaseData->localVertices[6].y = 0;

    fonts[35]->verticesBaseData->localVertices[7].x = -5;
    fonts[35]->verticesBaseData->localVertices[7].y = 7;


    fonts[35]->verticesBaseData->localVertices[8].x = -5;
    fonts[35]->verticesBaseData->localVertices[8].y = 7;

    fonts[35]->verticesBaseData->localVertices[9].x = 5;
    fonts[35]->verticesBaseData->localVertices[9].y = 7;


    fonts[35]->verticesBaseData->localVertices[10].x = 5;
    fonts[35]->verticesBaseData->localVertices[10].y = 7;

    fonts[35]->verticesBaseData->localVertices[11].x = 5;
    fonts[35]->verticesBaseData->localVertices[11].y = 0;

    //   SPACE (PL SPACJA)
    fonts[36]->verticesBaseData->localVertices = new Vector2D<float>[2];
    fonts[36]->verticesBaseData->worldVertices = new Vector2D<float>[2];

    fonts[36]->verticesBaseData->numberOfVertices = 2;

    fonts[36]->verticesBaseData->localVertices[0].x = -5;
    fonts[36]->verticesBaseData->localVertices[0].y = -7;

    fonts[36]->verticesBaseData->localVertices[1].x = 5;
    fonts[36]->verticesBaseData->localVertices[1].y = -7;
}
