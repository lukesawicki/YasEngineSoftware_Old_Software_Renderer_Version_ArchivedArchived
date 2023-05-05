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
    position.x=0;
    position.y=0;
    viewPortSizes.x=21;
    viewPortSizes.y=32;
//    charactersVertices = IMG_Load("charactersVertices.png");
}
void ScreenWriter::initialize(int szerokosc_znaku, int wysokosc_znaku, const char* plik_znakow)
{
    position.x=0;
    position.y=0;
//    viewPortSizes.w=szerokosc_znaku;
//    viewPortSizes.h=wysokosc_znaku;
//    charactersVertices = IMG_Load(plik_znakow);
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
                position.x=docelowe.w*j;
                docelowe.x=x+i*docelowe.w;
//                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
            }

        }
    }
}
void ScreenWriter::write(int x, int y, const char * text, SDL_Surface *na_czym)
{

    string napis = text;
    SDL_Rect docelowe;
    docelowe.x=x;
    docelowe.y=y;
//    docelowe.w=this->pozycja.w;
//    docelowe.h=this->pozycja.h;
    for(int i=0; i<static_cast<int>(napis.size()); i++)
    {
        for(int j=0; j<63; j++)
        {
            if(napis.at(i) == charactersTable[j])
            {
                position.x=docelowe.w*j;
                docelowe.x=x+i*docelowe.w;
//                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
            }

        }
    }
}
void ScreenWriter::write(int x, int y, string text, SDL_Surface *na_czym)
{
    SDL_Rect docelowe;
    docelowe.x=x;
    docelowe.y=y;
//    docelowe.w=this->pozycja.w;
//    docelowe.h=this->pozycja.h;
    for(int i=0; i<static_cast<int>(text.size()); i++)
    {
        for(int j=0; j<63; j++)
        {
            if(text.at(i) == charactersTable[j])
            {
                position.x=docelowe.w*j;
                docelowe.x=x+i*docelowe.w;
//                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
            }

        }
    }

}
void ScreenWriter::write(int x, int y, short integers, SDL_Surface *na_czym)
{
    ostringstream oss_wyjsciowy;

    oss_wyjsciowy << integers;

    string napis="";
    napis = oss_wyjsciowy.str();
    SDL_Rect docelowe;
    int pom_w=0, pom_h=0;
    docelowe.x=x;
    docelowe.y=y;
//    docelowe.w=this->pozycja.w;
//    docelowe.h=this->pozycja.h;
    for(int i=0; i<static_cast<int>(napis.size()); i++)
    {
        for(int j=0; j<63; j++)
        {
            if(napis.at(i) == charactersTable[j])
            {
                position.x=docelowe.w*j;
                docelowe.x=x+i*docelowe.w;
//                SDL_BlitSurface(charactersVertices , &pozycja, na_czym, &docelowe );
            }

        }
    }
}

void ScreenWriter::initializeFontObjects()
{
    Vector2D<float> direction(0, 1);
    for(int i=0; i<NUMBER_OF_CHARACTERS; i++)
    {
        fonts.at(i)->vertisecBaseData->initialize(17, 0, 0, direction, -1);
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
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[0]->vertisecBaseData->localVertices[0].x = ;
    fonts[0]->vertisecBaseData->localVertices[0].y = ;

    fonts[0]->vertisecBaseData->localVertices[1].x = ;
    fonts[0]->vertisecBaseData->localVertices[1].y = ;

    fonts[0]->vertisecBaseData->localVertices[2].x = ;
    fonts[0]->vertisecBaseData->localVertices[2].y = ;

    fonts[0]->vertisecBaseData->localVertices[3].x = ;
    fonts[0]->vertisecBaseData->localVertices[3].y = ;

    fonts[0]->vertisecBaseData->localVertices[4].x = ;
    fonts[0]->vertisecBaseData->localVertices[4].y = ;

    fonts[0]->vertisecBaseData->localVertices[5].x = ;
    fonts[0]->vertisecBaseData->localVertices[5].y = ;

    //B 16
    fonts[1]->vertisecBaseData->localVertices = new Vector2D<float>[16];

    fonts[1]->vertisecBaseData->localVertices[0].x = ;
    fonts[1]->vertisecBaseData->localVertices[0].y = ;

    fonts[1]->vertisecBaseData->localVertices[1].x = ;
    fonts[1]->vertisecBaseData->localVertices[1].y = ;

    fonts[1]->vertisecBaseData->localVertices[2].x = ;
    fonts[1]->vertisecBaseData->localVertices[2].y = ;

    fonts[1]->vertisecBaseData->localVertices[3].x = ;
    fonts[1]->vertisecBaseData->localVertices[3].y = ;

    fonts[1]->vertisecBaseData->localVertices[4].x = ;
    fonts[1]->vertisecBaseData->localVertices[4].y = ;

    fonts[1]->vertisecBaseData->localVertices[5].x = ;
    fonts[1]->vertisecBaseData->localVertices[5].y = ;

    fonts[1]->vertisecBaseData->localVertices[6].x = ;
    fonts[1]->vertisecBaseData->localVertices[6].y = ;

    fonts[1]->vertisecBaseData->localVertices[7].x = ;
    fonts[1]->vertisecBaseData->localVertices[7].y = ;

    fonts[1]->vertisecBaseData->localVertices[8].x = ;
    fonts[1]->vertisecBaseData->localVertices[8].y = ;

    fonts[1]->vertisecBaseData->localVertices[9].x = ;
    fonts[1]->vertisecBaseData->localVertices[9].y = ;

    fonts[1]->vertisecBaseData->localVertices[10].x = ;
    fonts[1]->vertisecBaseData->localVertices[10].y = ;

    fonts[1]->vertisecBaseData->localVertices[11].x = ;
    fonts[1]->vertisecBaseData->localVertices[11].y = ;

    fonts[1]->vertisecBaseData->localVertices[12].x = ;
    fonts[1]->vertisecBaseData->localVertices[12].y = ;

    fonts[1]->vertisecBaseData->localVertices[13].x = ;
    fonts[1]->vertisecBaseData->localVertices[13].y = ;

    fonts[1]->vertisecBaseData->localVertices[14].x = ;
    fonts[1]->vertisecBaseData->localVertices[14].y = ;

    fonts[1]->vertisecBaseData->localVertices[15].x = ;
    fonts[1]->vertisecBaseData->localVertices[15].y = ;


    //C 6
    fonts[2]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[2]->vertisecBaseData->localVertices[0].x = ;
    fonts[2]->vertisecBaseData->localVertices[0].y = ;

    fonts[2]->vertisecBaseData->localVertices[1].x = ;
    fonts[2]->vertisecBaseData->localVertices[1].y = ;

    fonts[2]->vertisecBaseData->localVertices[2].x = ;
    fonts[2]->vertisecBaseData->localVertices[2].y = ;

    fonts[2]->vertisecBaseData->localVertices[3].x = ;
    fonts[2]->vertisecBaseData->localVertices[3].y = ;

    fonts[2]->vertisecBaseData->localVertices[4].x = ;
    fonts[2]->vertisecBaseData->localVertices[4].y = ;

    fonts[2]->vertisecBaseData->localVertices[5].x = ;
    fonts[2]->vertisecBaseData->localVertices[5].y = ;

    // D 8
    fonts[3]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[3]->vertisecBaseData->localVertices[0].x = ;
    fonts[3]->vertisecBaseData->localVertices[0].y = ;

    fonts[3]->vertisecBaseData->localVertices[1].x = ;
    fonts[3]->vertisecBaseData->localVertices[1].y = ;

    fonts[3]->vertisecBaseData->localVertices[2].x = ;
    fonts[3]->vertisecBaseData->localVertices[2].y = ;

    fonts[3]->vertisecBaseData->localVertices[3].x = ;
    fonts[3]->vertisecBaseData->localVertices[3].y = ;

    fonts[3]->vertisecBaseData->localVertices[4].x = ;
    fonts[3]->vertisecBaseData->localVertices[4].y = ;

    fonts[3]->vertisecBaseData->localVertices[5].x = ;
    fonts[3]->vertisecBaseData->localVertices[5].y = ;

    fonts[3]->vertisecBaseData->localVertices[6].x = ;
    fonts[3]->vertisecBaseData->localVertices[6].y = ;

    fonts[3]->vertisecBaseData->localVertices[7].x = ;
    fonts[3]->vertisecBaseData->localVertices[7].y = ;

    // E 10
    fonts[4]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[4]->vertisecBaseData->localVertices[0].x = ;
    fonts[4]->vertisecBaseData->localVertices[0].y = ;

    fonts[4]->vertisecBaseData->localVertices[1].x = ;
    fonts[4]->vertisecBaseData->localVertices[1].y = ;

    fonts[4]->vertisecBaseData->localVertices[2].x = ;
    fonts[4]->vertisecBaseData->localVertices[2].y = ;

    fonts[4]->vertisecBaseData->localVertices[3].x = ;
    fonts[4]->vertisecBaseData->localVertices[3].y = ;

    fonts[4]->vertisecBaseData->localVertices[4].x = ;
    fonts[4]->vertisecBaseData->localVertices[4].y = ;

    fonts[4]->vertisecBaseData->localVertices[5].x = ;
    fonts[4]->vertisecBaseData->localVertices[5].y = ;

    fonts[4]->vertisecBaseData->localVertices[6].x = ;
    fonts[4]->vertisecBaseData->localVertices[6].y = ;

    fonts[4]->vertisecBaseData->localVertices[7].x = ;
    fonts[4]->vertisecBaseData->localVertices[7].y = ;

    fonts[4]->vertisecBaseData->localVertices[8].x = ;
    fonts[4]->vertisecBaseData->localVertices[8].y = ;

    fonts[4]->vertisecBaseData->localVertices[9].x = ;
    fonts[4]->vertisecBaseData->localVertices[9].y = ;


    // F 8
    fonts[5]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[5]->vertisecBaseData->localVertices[0].x = ;
    fonts[5]->vertisecBaseData->localVertices[0].y = ;

    fonts[5]->vertisecBaseData->localVertices[1].x = ;
    fonts[5]->vertisecBaseData->localVertices[1].y = ;

    fonts[5]->vertisecBaseData->localVertices[2].x = ;
    fonts[5]->vertisecBaseData->localVertices[2].y = ;

    fonts[5]->vertisecBaseData->localVertices[3].x = ;
    fonts[5]->vertisecBaseData->localVertices[3].y = ;

    fonts[5]->vertisecBaseData->localVertices[4].x = ;
    fonts[5]->vertisecBaseData->localVertices[4].y = ;

    fonts[5]->vertisecBaseData->localVertices[5].x = ;
    fonts[5]->vertisecBaseData->localVertices[5].y = ;

    fonts[5]->vertisecBaseData->localVertices[6].x = ;
    fonts[5]->vertisecBaseData->localVertices[6].y = ;

    fonts[5]->vertisecBaseData->localVertices[7].x = ;
    fonts[5]->vertisecBaseData->localVertices[7].y = ;

    // G 10
    fonts[6]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[6]->vertisecBaseData->localVertices[0].x = ;
    fonts[6]->vertisecBaseData->localVertices[0].y = ;

    fonts[6]->vertisecBaseData->localVertices[1].x = ;
    fonts[6]->vertisecBaseData->localVertices[1].y = ;

    fonts[6]->vertisecBaseData->localVertices[2].x = ;
    fonts[6]->vertisecBaseData->localVertices[2].y = ;

    fonts[6]->vertisecBaseData->localVertices[3].x = ;
    fonts[6]->vertisecBaseData->localVertices[3].y = ;

    fonts[6]->vertisecBaseData->localVertices[4].x = ;
    fonts[6]->vertisecBaseData->localVertices[4].y = ;

    fonts[6]->vertisecBaseData->localVertices[5].x = ;
    fonts[6]->vertisecBaseData->localVertices[5].y = ;

    fonts[6]->vertisecBaseData->localVertices[6].x = ;
    fonts[6]->vertisecBaseData->localVertices[6].y = ;

    fonts[6]->vertisecBaseData->localVertices[7].x = ;
    fonts[6]->vertisecBaseData->localVertices[7].y = ;

    fonts[6]->vertisecBaseData->localVertices[8].x = ;
    fonts[6]->vertisecBaseData->localVertices[8].y = ;

    fonts[6]->vertisecBaseData->localVertices[9].x = ;
    fonts[6]->vertisecBaseData->localVertices[9].y = ;

    // H 10
    fonts[7]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[7]->vertisecBaseData->localVertices[0].x = ;
    fonts[7]->vertisecBaseData->localVertices[0].y = ;

    fonts[7]->vertisecBaseData->localVertices[1].x = ;
    fonts[7]->vertisecBaseData->localVertices[1].y = ;

    fonts[7]->vertisecBaseData->localVertices[2].x = ;
    fonts[7]->vertisecBaseData->localVertices[2].y = ;

    fonts[7]->vertisecBaseData->localVertices[3].x = ;
    fonts[7]->vertisecBaseData->localVertices[3].y = ;

    fonts[7]->vertisecBaseData->localVertices[4].x = ;
    fonts[7]->vertisecBaseData->localVertices[4].y = ;

    fonts[7]->vertisecBaseData->localVertices[5].x = ;
    fonts[7]->vertisecBaseData->localVertices[5].y = ;

    fonts[7]->vertisecBaseData->localVertices[6].x = ;
    fonts[7]->vertisecBaseData->localVertices[6].y = ;

    fonts[7]->vertisecBaseData->localVertices[7].x = ;
    fonts[7]->vertisecBaseData->localVertices[7].y = ;

    fonts[7]->vertisecBaseData->localVertices[8].x = ;
    fonts[7]->vertisecBaseData->localVertices[8].y = ;

    fonts[7]->vertisecBaseData->localVertices[9].x = ;
    fonts[7]->vertisecBaseData->localVertices[9].y = ;

    // I 6
    fonts[8]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[8]->vertisecBaseData->localVertices[0].x = ;
    fonts[8]->vertisecBaseData->localVertices[0].y = ;

    fonts[8]->vertisecBaseData->localVertices[1].x = ;
    fonts[8]->vertisecBaseData->localVertices[1].y = ;

    fonts[8]->vertisecBaseData->localVertices[2].x = ;
    fonts[8]->vertisecBaseData->localVertices[2].y = ;

    fonts[8]->vertisecBaseData->localVertices[3].x = ;
    fonts[8]->vertisecBaseData->localVertices[3].y = ;

    fonts[8]->vertisecBaseData->localVertices[4].x = ;
    fonts[8]->vertisecBaseData->localVertices[4].y = ;

    fonts[8]->vertisecBaseData->localVertices[5].x = ;
    fonts[8]->vertisecBaseData->localVertices[5].y = ;

    // J 10
    fonts[9]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[9]->vertisecBaseData->localVertices[0].x = ;
    fonts[9]->vertisecBaseData->localVertices[0].y = ;

    fonts[9]->vertisecBaseData->localVertices[1].x = ;
    fonts[9]->vertisecBaseData->localVertices[1].y = ;

    fonts[9]->vertisecBaseData->localVertices[2].x = ;
    fonts[9]->vertisecBaseData->localVertices[2].y = ;

    fonts[9]->vertisecBaseData->localVertices[3].x = ;
    fonts[9]->vertisecBaseData->localVertices[3].y = ;

    fonts[9]->vertisecBaseData->localVertices[4].x = ;
    fonts[9]->vertisecBaseData->localVertices[4].y = ;

    fonts[9]->vertisecBaseData->localVertices[5].x = ;
    fonts[9]->vertisecBaseData->localVertices[5].y = ;

    fonts[9]->vertisecBaseData->localVertices[6].x = ;
    fonts[9]->vertisecBaseData->localVertices[6].y = ;

    fonts[9]->vertisecBaseData->localVertices[7].x = ;
    fonts[9]->vertisecBaseData->localVertices[7].y = ;

    fonts[9]->vertisecBaseData->localVertices[8].x = ;
    fonts[9]->vertisecBaseData->localVertices[8].y = ;

    fonts[9]->vertisecBaseData->localVertices[9].x = ;
    fonts[9]->vertisecBaseData->localVertices[9].y = ;

    // K 8
    fonts[10]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[10]->vertisecBaseData->localVertices[8].x = ;
    fonts[10]->vertisecBaseData->localVertices[8].y = ;

    fonts[10]->vertisecBaseData->localVertices[9].x = ;
    fonts[10]->vertisecBaseData->localVertices[9].y = ;

    fonts[10]->vertisecBaseData->localVertices[10].x = ;
    fonts[10]->vertisecBaseData->localVertices[10].y = ;

    fonts[10]->vertisecBaseData->localVertices[11].x = ;
    fonts[10]->vertisecBaseData->localVertices[11].y = ;

    fonts[10]->vertisecBaseData->localVertices[12].x = ;
    fonts[10]->vertisecBaseData->localVertices[12].y = ;

    fonts[10]->vertisecBaseData->localVertices[13].x = ;
    fonts[10]->vertisecBaseData->localVertices[13].y = ;

    fonts[10]->vertisecBaseData->localVertices[14].x = ;
    fonts[10]->vertisecBaseData->localVertices[14].y = ;

    fonts[10]->vertisecBaseData->localVertices[15].x = ;
    fonts[10]->vertisecBaseData->localVertices[15].y = ;

    fonts[10]->vertisecBaseData->localVertices[16].x = ;
    fonts[10]->vertisecBaseData->localVertices[16].y = ;

    // L 4
    fonts[11]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[11]->vertisecBaseData->localVertices[0].x = ;
    fonts[11]->vertisecBaseData->localVertices[0].y = ;

    fonts[11]->vertisecBaseData->localVertices[1].x = ;
    fonts[11]->vertisecBaseData->localVertices[1].y = ;

    fonts[11]->vertisecBaseData->localVertices[2].x = ;
    fonts[11]->vertisecBaseData->localVertices[2].y = ;

    fonts[11]->vertisecBaseData->localVertices[3].x = ;
    fonts[11]->vertisecBaseData->localVertices[3].y = ;

    // M 8
    fonts[12]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[12]->vertisecBaseData->localVertices[0].x = ;
    fonts[12]->vertisecBaseData->localVertices[0].y = ;

    fonts[12]->vertisecBaseData->localVertices[1].x = ;
    fonts[12]->vertisecBaseData->localVertices[1].y = ;

    fonts[12]->vertisecBaseData->localVertices[2].x = ;
    fonts[12]->vertisecBaseData->localVertices[2].y = ;

    fonts[12]->vertisecBaseData->localVertices[3].x = ;
    fonts[12]->vertisecBaseData->localVertices[3].y = ;

    fonts[12]->vertisecBaseData->localVertices[4].x = ;
    fonts[12]->vertisecBaseData->localVertices[4].y = ;

    fonts[12]->vertisecBaseData->localVertices[5].x = ;
    fonts[12]->vertisecBaseData->localVertices[5].y = ;

    fonts[12]->vertisecBaseData->localVertices[6].x = ;
    fonts[12]->vertisecBaseData->localVertices[6].y = ;

    fonts[12]->vertisecBaseData->localVertices[7].x = ;
    fonts[12]->vertisecBaseData->localVertices[7].y = ;

    fonts[12]->vertisecBaseData->localVertices[8].x = ;
    fonts[12]->vertisecBaseData->localVertices[8].y = ;

    // N 6
    fonts[13]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[13]->vertisecBaseData->localVertices[0].x = ;
    fonts[13]->vertisecBaseData->localVertices[0].y = ;

    fonts[13]->vertisecBaseData->localVertices[1].x = ;
    fonts[13]->vertisecBaseData->localVertices[1].y = ;

    fonts[13]->vertisecBaseData->localVertices[2].x = ;
    fonts[13]->vertisecBaseData->localVertices[2].y = ;

    fonts[13]->vertisecBaseData->localVertices[3].x = ;
    fonts[13]->vertisecBaseData->localVertices[3].y = ;

    fonts[13]->vertisecBaseData->localVertices[4].x = ;
    fonts[13]->vertisecBaseData->localVertices[4].y = ;

    fonts[13]->vertisecBaseData->localVertices[5].x = ;
    fonts[13]->vertisecBaseData->localVertices[5].y = ;

    // O 8
    fonts[14]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[14]->vertisecBaseData->localVertices[0].x = ;
    fonts[14]->vertisecBaseData->localVertices[0].y = ;

    fonts[14]->vertisecBaseData->localVertices[1].x = ;
    fonts[14]->vertisecBaseData->localVertices[1].y = ;

    fonts[14]->vertisecBaseData->localVertices[2].x = ;
    fonts[14]->vertisecBaseData->localVertices[2].y = ;

    fonts[14]->vertisecBaseData->localVertices[3].x = ;
    fonts[14]->vertisecBaseData->localVertices[3].y = ;

    fonts[14]->vertisecBaseData->localVertices[4].x = ;
    fonts[14]->vertisecBaseData->localVertices[4].y = ;

    fonts[14]->vertisecBaseData->localVertices[5].x = ;
    fonts[14]->vertisecBaseData->localVertices[5].y = ;

    fonts[14]->vertisecBaseData->localVertices[6].x = ;
    fonts[14]->vertisecBaseData->localVertices[6].y = ;

    fonts[14]->vertisecBaseData->localVertices[7].x = ;
    fonts[14]->vertisecBaseData->localVertices[7].y = ;

    // P 10
    fonts[15]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[15]->vertisecBaseData->localVertices[0].x = ;
    fonts[15]->vertisecBaseData->localVertices[0].y = ;

    fonts[15]->vertisecBaseData->localVertices[1].x = ;
    fonts[15]->vertisecBaseData->localVertices[1].y = ;

    fonts[15]->vertisecBaseData->localVertices[2].x = ;
    fonts[15]->vertisecBaseData->localVertices[2].y = ;

    fonts[15]->vertisecBaseData->localVertices[3].x = ;
    fonts[15]->vertisecBaseData->localVertices[3].y = ;

    fonts[15]->vertisecBaseData->localVertices[4].x = ;
    fonts[15]->vertisecBaseData->localVertices[4].y = ;

    fonts[15]->vertisecBaseData->localVertices[5].x = ;
    fonts[15]->vertisecBaseData->localVertices[5].y = ;

    fonts[15]->vertisecBaseData->localVertices[6].x = ;
    fonts[15]->vertisecBaseData->localVertices[6].y = ;

    fonts[15]->vertisecBaseData->localVertices[7].x = ;
    fonts[15]->vertisecBaseData->localVertices[7].y = ;

    fonts[15]->vertisecBaseData->localVertices[8].x = ;
    fonts[15]->vertisecBaseData->localVertices[8].y = ;

    fonts[15]->vertisecBaseData->localVertices[9].x = ;
    fonts[15]->vertisecBaseData->localVertices[9].y = ;

    // Q 10
    fonts[16]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[16]->vertisecBaseData->localVertices[0].x = ;
    fonts[16]->vertisecBaseData->localVertices[0].y = ;

    fonts[16]->vertisecBaseData->localVertices[1].x = ;
    fonts[16]->vertisecBaseData->localVertices[1].y = ;

    fonts[16]->vertisecBaseData->localVertices[2].x = ;
    fonts[16]->vertisecBaseData->localVertices[2].y = ;

    fonts[16]->vertisecBaseData->localVertices[3].x = ;
    fonts[16]->vertisecBaseData->localVertices[3].y = ;

    fonts[16]->vertisecBaseData->localVertices[4].x = ;
    fonts[16]->vertisecBaseData->localVertices[4].y = ;

    fonts[16]->vertisecBaseData->localVertices[5].x = ;
    fonts[16]->vertisecBaseData->localVertices[5].y = ;

    fonts[16]->vertisecBaseData->localVertices[6].x = ;
    fonts[16]->vertisecBaseData->localVertices[6].y = ;

    fonts[16]->vertisecBaseData->localVertices[7].x = ;
    fonts[16]->vertisecBaseData->localVertices[7].y = ;

    fonts[16]->vertisecBaseData->localVertices[8].x = ;
    fonts[16]->vertisecBaseData->localVertices[8].y = ;

    fonts[16]->vertisecBaseData->localVertices[9].x = ;
    fonts[16]->vertisecBaseData->localVertices[9].y = ;

    // R 12
    fonts[17]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[17]->vertisecBaseData->localVertices[0].x = ;
    fonts[17]->vertisecBaseData->localVertices[0].y = ;

    fonts[17]->vertisecBaseData->localVertices[1].x = ;
    fonts[17]->vertisecBaseData->localVertices[1].y = ;

    fonts[17]->vertisecBaseData->localVertices[2].x = ;
    fonts[17]->vertisecBaseData->localVertices[2].y = ;

    fonts[17]->vertisecBaseData->localVertices[3].x = ;
    fonts[17]->vertisecBaseData->localVertices[3].y = ;

    fonts[17]->vertisecBaseData->localVertices[4].x = ;
    fonts[17]->vertisecBaseData->localVertices[4].y = ;

    fonts[17]->vertisecBaseData->localVertices[5].x = ;
    fonts[17]->vertisecBaseData->localVertices[5].y = ;

    fonts[17]->vertisecBaseData->localVertices[6].x = ;
    fonts[17]->vertisecBaseData->localVertices[6].y = ;

    fonts[17]->vertisecBaseData->localVertices[7].x = ;
    fonts[17]->vertisecBaseData->localVertices[7].y = ;

    fonts[17]->vertisecBaseData->localVertices[8].x = ;
    fonts[17]->vertisecBaseData->localVertices[8].y = ;

    fonts[17]->vertisecBaseData->localVertices[9].x = ;
    fonts[17]->vertisecBaseData->localVertices[9].y = ;

    fonts[17]->vertisecBaseData->localVertices[10].x = ;
    fonts[17]->vertisecBaseData->localVertices[10].y = ;

    fonts[17]->vertisecBaseData->localVertices[11].x = ;
    fonts[17]->vertisecBaseData->localVertices[11].y = ;

    // S 10
    fonts[18]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[18]->vertisecBaseData->localVertices[0].x = ;
    fonts[18]->vertisecBaseData->localVertices[0].y = ;

    fonts[18]->vertisecBaseData->localVertices[1].x = ;
    fonts[18]->vertisecBaseData->localVertices[1].y = ;

    fonts[18]->vertisecBaseData->localVertices[2].x = ;
    fonts[18]->vertisecBaseData->localVertices[2].y = ;

    fonts[18]->vertisecBaseData->localVertices[3].x = ;
    fonts[18]->vertisecBaseData->localVertices[3].y = ;

    fonts[18]->vertisecBaseData->localVertices[4].x = ;
    fonts[18]->vertisecBaseData->localVertices[4].y = ;

    fonts[18]->vertisecBaseData->localVertices[5].x = ;
    fonts[18]->vertisecBaseData->localVertices[5].y = ;

    fonts[18]->vertisecBaseData->localVertices[6].x = ;
    fonts[18]->vertisecBaseData->localVertices[6].y = ;

    fonts[18]->vertisecBaseData->localVertices[7].x = ;
    fonts[18]->vertisecBaseData->localVertices[7].y = ;

    fonts[18]->vertisecBaseData->localVertices[8].x = ;
    fonts[18]->vertisecBaseData->localVertices[8].y = ;

    fonts[18]->vertisecBaseData->localVertices[9].x = ;
    fonts[18]->vertisecBaseData->localVertices[9].y = ;

    // T 2
    fonts[19]->vertisecBaseData->localVertices = new Vector2D<float>[2];

    fonts[19]->vertisecBaseData->localVertices[0].x = ;
    fonts[19]->vertisecBaseData->localVertices[0].y = ;

    fonts[19]->vertisecBaseData->localVertices[1].x = ;
    fonts[19]->vertisecBaseData->localVertices[1].y = ;

    // U 6
    fonts[20]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[20]->vertisecBaseData->localVertices[0].x = ;
    fonts[20]->vertisecBaseData->localVertices[0].y = ;

    fonts[20]->vertisecBaseData->localVertices[1].x = ;
    fonts[20]->vertisecBaseData->localVertices[1].y = ;

    fonts[20]->vertisecBaseData->localVertices[2].x = ;
    fonts[20]->vertisecBaseData->localVertices[2].y = ;

    fonts[20]->vertisecBaseData->localVertices[3].x = ;
    fonts[20]->vertisecBaseData->localVertices[3].y = ;

    fonts[20]->vertisecBaseData->localVertices[4].x = ;
    fonts[20]->vertisecBaseData->localVertices[4].y = ;

    fonts[20]->vertisecBaseData->localVertices[5].x = ;
    fonts[20]->vertisecBaseData->localVertices[5].y = ;

    // V 4
    fonts[21]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[21]->vertisecBaseData->localVertices[0].x = ;
    fonts[21]->vertisecBaseData->localVertices[0].y = ;

    fonts[21]->vertisecBaseData->localVertices[1].x = ;
    fonts[21]->vertisecBaseData->localVertices[1].y = ;

    fonts[21]->vertisecBaseData->localVertices[2].x = ;
    fonts[21]->vertisecBaseData->localVertices[2].y = ;

    fonts[21]->vertisecBaseData->localVertices[3].x = ;
    fonts[21]->vertisecBaseData->localVertices[3].y = ;

    // W 8
    fonts[22]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[22]->vertisecBaseData->localVertices[0].x = ;
    fonts[22]->vertisecBaseData->localVertices[0].y = ;

    fonts[22]->vertisecBaseData->localVertices[1].x = ;
    fonts[22]->vertisecBaseData->localVertices[1].y = ;

    fonts[22]->vertisecBaseData->localVertices[2].x = ;
    fonts[22]->vertisecBaseData->localVertices[2].y = ;

    fonts[22]->vertisecBaseData->localVertices[3].x = ;
    fonts[22]->vertisecBaseData->localVertices[3].y = ;

    fonts[22]->vertisecBaseData->localVertices[4].x = ;
    fonts[22]->vertisecBaseData->localVertices[4].y = ;

    fonts[22]->vertisecBaseData->localVertices[5].x = ;
    fonts[22]->vertisecBaseData->localVertices[5].y = ;

    fonts[22]->vertisecBaseData->localVertices[6].x = ;
    fonts[22]->vertisecBaseData->localVertices[6].y = ;

    fonts[22]->vertisecBaseData->localVertices[7].x = ;
    fonts[22]->vertisecBaseData->localVertices[7].y = ;

    // X 4
    fonts[23]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[23]->vertisecBaseData->localVertices[0].x = ;
    fonts[23]->vertisecBaseData->localVertices[0].y = ;

    fonts[23]->vertisecBaseData->localVertices[1].x = ;
    fonts[23]->vertisecBaseData->localVertices[1].y = ;

    fonts[23]->vertisecBaseData->localVertices[2].x = ;
    fonts[23]->vertisecBaseData->localVertices[2].y = ;

    fonts[23]->vertisecBaseData->localVertices[3].x = ;
    fonts[23]->vertisecBaseData->localVertices[3].y = ;

    // Y 6
    fonts[24]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[24]->vertisecBaseData->localVertices[0].x = ;
    fonts[24]->vertisecBaseData->localVertices[0].y = ;

    fonts[24]->vertisecBaseData->localVertices[1].x = ;
    fonts[24]->vertisecBaseData->localVertices[1].y = ;

    fonts[24]->vertisecBaseData->localVertices[2].x = ;
    fonts[24]->vertisecBaseData->localVertices[2].y = ;

    fonts[24]->vertisecBaseData->localVertices[3].x = ;
    fonts[24]->vertisecBaseData->localVertices[3].y = ;

    fonts[24]->vertisecBaseData->localVertices[4].x = ;
    fonts[24]->vertisecBaseData->localVertices[4].y = ;

    fonts[24]->vertisecBaseData->localVertices[5].x = ;
    fonts[24]->vertisecBaseData->localVertices[5].y = ;

    // Z 6
    fonts[25]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[25]->vertisecBaseData->localVertices[0].x = ;
    fonts[25]->vertisecBaseData->localVertices[0].y = ;

    fonts[25]->vertisecBaseData->localVertices[1].x = ;
    fonts[25]->vertisecBaseData->localVertices[1].y = ;

    fonts[25]->vertisecBaseData->localVertices[2].x = ;
    fonts[25]->vertisecBaseData->localVertices[2].y = ;

    fonts[25]->vertisecBaseData->localVertices[3].x = ;
    fonts[25]->vertisecBaseData->localVertices[3].y = ;

    fonts[25]->vertisecBaseData->localVertices[4].x = ;
    fonts[25]->vertisecBaseData->localVertices[4].y = ;

    fonts[25]->vertisecBaseData->localVertices[5].x = ;
    fonts[25]->vertisecBaseData->localVertices[5].y = ;

    // 0 10
    fonts[26]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[26]->vertisecBaseData->localVertices[0].x = ;
    fonts[26]->vertisecBaseData->localVertices[0].y = ;

    fonts[26]->vertisecBaseData->localVertices[1].x = ;
    fonts[26]->vertisecBaseData->localVertices[1].y = ;

    fonts[26]->vertisecBaseData->localVertices[2].x = ;
    fonts[26]->vertisecBaseData->localVertices[2].y = ;

    fonts[26]->vertisecBaseData->localVertices[3].x = ;
    fonts[26]->vertisecBaseData->localVertices[3].y = ;

    fonts[26]->vertisecBaseData->localVertices[4].x = ;
    fonts[26]->vertisecBaseData->localVertices[4].y = ;

    fonts[26]->vertisecBaseData->localVertices[5].x = ;
    fonts[26]->vertisecBaseData->localVertices[5].y = ;

    fonts[26]->vertisecBaseData->localVertices[6].x = ;
    fonts[26]->vertisecBaseData->localVertices[6].y = ;

    fonts[26]->vertisecBaseData->localVertices[7].x = ;
    fonts[26]->vertisecBaseData->localVertices[7].y = ;

    fonts[26]->vertisecBaseData->localVertices[8].x = ;
    fonts[26]->vertisecBaseData->localVertices[8].y = ;

    fonts[26]->vertisecBaseData->localVertices[9].x = ;
    fonts[26]->vertisecBaseData->localVertices[9].y = ;

    // 1 6
    fonts[27]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[27]->vertisecBaseData->localVertices[0].x = ;
    fonts[27]->vertisecBaseData->localVertices[0].y = ;

    fonts[27]->vertisecBaseData->localVertices[1].x = ;
    fonts[27]->vertisecBaseData->localVertices[1].y = ;

    fonts[27]->vertisecBaseData->localVertices[2].x = ;
    fonts[27]->vertisecBaseData->localVertices[2].y = ;

    fonts[27]->vertisecBaseData->localVertices[3].x = ;
    fonts[27]->vertisecBaseData->localVertices[3].y = ;

    fonts[27]->vertisecBaseData->localVertices[4].x = ;
    fonts[27]->vertisecBaseData->localVertices[4].y = ;

    fonts[27]->vertisecBaseData->localVertices[5].x = ;
    fonts[27]->vertisecBaseData->localVertices[5].y = ;

    // 2 10
    fonts[28]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[28]->vertisecBaseData->localVertices[0].x = ;
    fonts[28]->vertisecBaseData->localVertices[0].y = ;

    fonts[28]->vertisecBaseData->localVertices[1].x = ;
    fonts[28]->vertisecBaseData->localVertices[1].y = ;

    fonts[28]->vertisecBaseData->localVertices[2].x = ;
    fonts[28]->vertisecBaseData->localVertices[2].y = ;

    fonts[28]->vertisecBaseData->localVertices[3].x = ;
    fonts[28]->vertisecBaseData->localVertices[3].y = ;

    fonts[28]->vertisecBaseData->localVertices[4].x = ;
    fonts[28]->vertisecBaseData->localVertices[4].y = ;

    fonts[28]->vertisecBaseData->localVertices[5].x = ;
    fonts[28]->vertisecBaseData->localVertices[5].y = ;

    fonts[28]->vertisecBaseData->localVertices[6].x = ;
    fonts[28]->vertisecBaseData->localVertices[6].y = ;

    fonts[28]->vertisecBaseData->localVertices[7].x = ;
    fonts[28]->vertisecBaseData->localVertices[7].y = ;

    fonts[28]->vertisecBaseData->localVertices[8].x = ;
    fonts[28]->vertisecBaseData->localVertices[8].y = ;

    fonts[28]->vertisecBaseData->localVertices[9].x = ;
    fonts[28]->vertisecBaseData->localVertices[9].y = ;

    // 3 10
    fonts[29]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[29]->vertisecBaseData->localVertices[0].x = ;
    fonts[29]->vertisecBaseData->localVertices[0].y = ;

    fonts[29]->vertisecBaseData->localVertices[1].x = ;
    fonts[29]->vertisecBaseData->localVertices[1].y = ;

    fonts[29]->vertisecBaseData->localVertices[2].x = ;
    fonts[29]->vertisecBaseData->localVertices[2].y = ;

    fonts[29]->vertisecBaseData->localVertices[3].x = ;
    fonts[29]->vertisecBaseData->localVertices[3].y = ;

    fonts[29]->vertisecBaseData->localVertices[4].x = ;
    fonts[29]->vertisecBaseData->localVertices[4].y = ;

    fonts[29]->vertisecBaseData->localVertices[5].x = ;
    fonts[29]->vertisecBaseData->localVertices[5].y = ;

    fonts[29]->vertisecBaseData->localVertices[6].x = ;
    fonts[29]->vertisecBaseData->localVertices[6].y = ;

    fonts[29]->vertisecBaseData->localVertices[7].x = ;
    fonts[29]->vertisecBaseData->localVertices[7].y = ;

    fonts[29]->vertisecBaseData->localVertices[8].x = ;
    fonts[29]->vertisecBaseData->localVertices[8].y = ;

    fonts[29]->vertisecBaseData->localVertices[9].x = ;
    fonts[29]->vertisecBaseData->localVertices[9].y = ;

    // 4 6
    fonts[30]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[30]->vertisecBaseData->localVertices[0].x = ;
    fonts[30]->vertisecBaseData->localVertices[0].y = ;

    fonts[30]->vertisecBaseData->localVertices[1].x = ;
    fonts[30]->vertisecBaseData->localVertices[1].y = ;

    fonts[30]->vertisecBaseData->localVertices[2].x = ;
    fonts[30]->vertisecBaseData->localVertices[2].y = ;

    fonts[30]->vertisecBaseData->localVertices[3].x = ;
    fonts[30]->vertisecBaseData->localVertices[3].y = ;

    fonts[30]->vertisecBaseData->localVertices[4].x = ;
    fonts[30]->vertisecBaseData->localVertices[4].y = ;

    fonts[30]->vertisecBaseData->localVertices[5].x = ;
    fonts[30]->vertisecBaseData->localVertices[5].y = ;

    // 5 10
    fonts[31]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[31]->vertisecBaseData->localVertices[0].x = ;
    fonts[31]->vertisecBaseData->localVertices[0].y = ;

    fonts[31]->vertisecBaseData->localVertices[1].x = ;
    fonts[31]->vertisecBaseData->localVertices[1].y = ;

    fonts[31]->vertisecBaseData->localVertices[2].x = ;
    fonts[31]->vertisecBaseData->localVertices[2].y = ;

    fonts[31]->vertisecBaseData->localVertices[3].x = ;
    fonts[31]->vertisecBaseData->localVertices[3].y = ;

    fonts[31]->vertisecBaseData->localVertices[4].x = ;
    fonts[31]->vertisecBaseData->localVertices[4].y = ;

    fonts[31]->vertisecBaseData->localVertices[5].x = ;
    fonts[31]->vertisecBaseData->localVertices[5].y = ;

    fonts[31]->vertisecBaseData->localVertices[6].x = ;
    fonts[31]->vertisecBaseData->localVertices[6].y = ;

    fonts[31]->vertisecBaseData->localVertices[7].x = ;
    fonts[31]->vertisecBaseData->localVertices[7].y = ;

    fonts[31]->vertisecBaseData->localVertices[8].x = ;
    fonts[31]->vertisecBaseData->localVertices[8].y = ;

    fonts[31]->vertisecBaseData->localVertices[9].x = ;
    fonts[31]->vertisecBaseData->localVertices[9].y = ;

    // 6 12
    fonts[32]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[32]->vertisecBaseData->localVertices[0].x = ;
    fonts[32]->vertisecBaseData->localVertices[0].y = ;

    fonts[32]->vertisecBaseData->localVertices[1].x = ;
    fonts[32]->vertisecBaseData->localVertices[1].y = ;

    fonts[32]->vertisecBaseData->localVertices[2].x = ;
    fonts[32]->vertisecBaseData->localVertices[2].y = ;

    fonts[32]->vertisecBaseData->localVertices[3].x = ;
    fonts[32]->vertisecBaseData->localVertices[3].y = ;

    fonts[32]->vertisecBaseData->localVertices[4].x = ;
    fonts[32]->vertisecBaseData->localVertices[4].y = ;

    fonts[32]->vertisecBaseData->localVertices[5].x = ;
    fonts[32]->vertisecBaseData->localVertices[5].y = ;

    fonts[32]->vertisecBaseData->localVertices[6].x = ;
    fonts[32]->vertisecBaseData->localVertices[6].y = ;

    fonts[32]->vertisecBaseData->localVertices[7].x = ;
    fonts[32]->vertisecBaseData->localVertices[7].y = ;

    fonts[32]->vertisecBaseData->localVertices[8].x = ;
    fonts[32]->vertisecBaseData->localVertices[8].y = ;

    fonts[32]->vertisecBaseData->localVertices[9].x = ;
    fonts[32]->vertisecBaseData->localVertices[9].y = ;

    fonts[32]->vertisecBaseData->localVertices[10].x = ;
    fonts[32]->vertisecBaseData->localVertices[10].y = ;

    fonts[32]->vertisecBaseData->localVertices[11].x = ;
    fonts[32]->vertisecBaseData->localVertices[11].y = ;

    // 7 4
    fonts[33]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[33]->vertisecBaseData->localVertices[0].x = ;
    fonts[33]->vertisecBaseData->localVertices[0].y = ;

    fonts[33]->vertisecBaseData->localVertices[1].x = ;
    fonts[33]->vertisecBaseData->localVertices[1].y = ;

    fonts[33]->vertisecBaseData->localVertices[2].x = ;
    fonts[33]->vertisecBaseData->localVertices[2].y = ;

    fonts[33]->vertisecBaseData->localVertices[3].x = ;
    fonts[33]->vertisecBaseData->localVertices[3].y = ;

    // 8 14
    fonts[34]->vertisecBaseData->localVertices = new Vector2D<float>[14];

    fonts[34]->vertisecBaseData->localVertices[0].x = ;
    fonts[34]->vertisecBaseData->localVertices[0].y = ;

    fonts[34]->vertisecBaseData->localVertices[1].x = ;
    fonts[34]->vertisecBaseData->localVertices[1].y = ;

    fonts[34]->vertisecBaseData->localVertices[2].x = ;
    fonts[34]->vertisecBaseData->localVertices[2].y = ;

    fonts[34]->vertisecBaseData->localVertices[3].x = ;
    fonts[34]->vertisecBaseData->localVertices[3].y = ;

    fonts[34]->vertisecBaseData->localVertices[4].x = ;
    fonts[34]->vertisecBaseData->localVertices[4].y = ;

    fonts[34]->vertisecBaseData->localVertices[5].x = ;
    fonts[34]->vertisecBaseData->localVertices[5].y = ;

    fonts[34]->vertisecBaseData->localVertices[6].x = ;
    fonts[34]->vertisecBaseData->localVertices[6].y = ;

    fonts[34]->vertisecBaseData->localVertices[7].x = ;
    fonts[34]->vertisecBaseData->localVertices[7].y = ;

    fonts[34]->vertisecBaseData->localVertices[8].x = ;
    fonts[34]->vertisecBaseData->localVertices[8].y = ;

    fonts[34]->vertisecBaseData->localVertices[9].x = ;
    fonts[34]->vertisecBaseData->localVertices[9].y = ;

    fonts[34]->vertisecBaseData->localVertices[10].x = ;
    fonts[34]->vertisecBaseData->localVertices[10].y = ;

    fonts[34]->vertisecBaseData->localVertices[11].x = ;
    fonts[34]->vertisecBaseData->localVertices[11].y = ;

    fonts[34]->vertisecBaseData->localVertices[12].x = ;
    fonts[34]->vertisecBaseData->localVertices[12].y = ;

    fonts[34]->vertisecBaseData->localVertices[13].x = ;
    fonts[34]->vertisecBaseData->localVertices[13].y = ;

    // 9 12
    fonts[35]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[35]->vertisecBaseData->localVertices[0].x = ;
    fonts[35]->vertisecBaseData->localVertices[0].y = ;

    fonts[35]->vertisecBaseData->localVertices[1].x = ;
    fonts[35]->vertisecBaseData->localVertices[1].y = ;

    fonts[35]->vertisecBaseData->localVertices[2].x = ;
    fonts[35]->vertisecBaseData->localVertices[2].y = ;

    fonts[35]->vertisecBaseData->localVertices[3].x = ;
    fonts[35]->vertisecBaseData->localVertices[3].y = ;

    fonts[35]->vertisecBaseData->localVertices[4].x = ;
    fonts[35]->vertisecBaseData->localVertices[4].y = ;

    fonts[35]->vertisecBaseData->localVertices[5].x = ;
    fonts[35]->vertisecBaseData->localVertices[5].y = ;

    fonts[35]->vertisecBaseData->localVertices[6].x = ;
    fonts[35]->vertisecBaseData->localVertices[6].y = ;

    fonts[35]->vertisecBaseData->localVertices[7].x = ;
    fonts[35]->vertisecBaseData->localVertices[7].y = ;

    fonts[35]->vertisecBaseData->localVertices[8].x = ;
    fonts[35]->vertisecBaseData->localVertices[8].y = ;

    fonts[35]->vertisecBaseData->localVertices[9].x = ;
    fonts[35]->vertisecBaseData->localVertices[9].y = ;

    fonts[35]->vertisecBaseData->localVertices[10].x = ;
    fonts[35]->vertisecBaseData->localVertices[10].y = ;

    fonts[35]->vertisecBaseData->localVertices[11].x = ;
    fonts[35]->vertisecBaseData->localVertices[11].y = ;

    //   SPACE (PL SPACJA)
    fonts[36]->vertisecBaseData->localVertices[0].x = ;
    fonts[36]->vertisecBaseData->localVertices[0].y = ;

    fonts[36]->vertisecBaseData->localVertices[1].x = ;
    fonts[36]->vertisecBaseData->localVertices[1].y = ;
}
