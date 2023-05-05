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
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

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
    fonts[]->vertisecBaseData->localVertices[13].y = ;

    fonts[1]->vertisecBaseData->localVertices[14].x = ;
    fonts[1]->vertisecBaseData->localVertices[14].y = ;

    fonts[1]->vertisecBaseData->localVertices[15].x = ;
    fonts[1]->vertisecBaseData->localVertices[15].y = ;


    //C 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    //D 8
    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    E 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;


    F 8
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    G 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    H 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    J 12
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

    K 8
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

    fonts[]->vertisecBaseData->localVertices[12].x = ;
    fonts[]->vertisecBaseData->localVertices[12].y = ;

    fonts[]->vertisecBaseData->localVertices[13].x = ;
    fonts[]->vertisecBaseData->localVertices[13].y = ;

    fonts[]->vertisecBaseData->localVertices[14].x = ;
    fonts[]->vertisecBaseData->localVertices[14].y = ;

    fonts[]->vertisecBaseData->localVertices[15].x = ;
    fonts[]->vertisecBaseData->localVertices[15].y = ;

    fonts[]->vertisecBaseData->localVertices[16].x = ;
    fonts[]->vertisecBaseData->localVertices[16].y = ;

    L 4
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    M 8
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    N 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    O 8
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    P 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    Q 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    R 12
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

    S 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    T 2
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[2];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    U 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    V 4
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    W 8
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[8];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    X 4
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    Y 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    Z 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    0 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    1 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    2 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    3 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    4 6
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[6];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    5 10
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[10];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    6 12
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

    7 4
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[4];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    8 14
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[14];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

    fonts[]->vertisecBaseData->localVertices[12].x = ;
    fonts[]->vertisecBaseData->localVertices[12].y = ;

    fonts[]->vertisecBaseData->localVertices[13].x = ;
    fonts[]->vertisecBaseData->localVertices[13].y = ;

    9 12
    fonts[0]->vertisecBaseData->localVertices = new Vector2D<float>[12];

    fonts[]->vertisecBaseData->localVertices[0].x = ;
    fonts[]->vertisecBaseData->localVertices[0].y = ;

    fonts[]->vertisecBaseData->localVertices[1].x = ;
    fonts[]->vertisecBaseData->localVertices[1].y = ;

    fonts[]->vertisecBaseData->localVertices[2].x = ;
    fonts[]->vertisecBaseData->localVertices[2].y = ;

    fonts[]->vertisecBaseData->localVertices[3].x = ;
    fonts[]->vertisecBaseData->localVertices[3].y = ;

    fonts[]->vertisecBaseData->localVertices[4].x = ;
    fonts[]->vertisecBaseData->localVertices[4].y = ;

    fonts[]->vertisecBaseData->localVertices[5].x = ;
    fonts[]->vertisecBaseData->localVertices[5].y = ;

    fonts[]->vertisecBaseData->localVertices[6].x = ;
    fonts[]->vertisecBaseData->localVertices[6].y = ;

    fonts[]->vertisecBaseData->localVertices[7].x = ;
    fonts[]->vertisecBaseData->localVertices[7].y = ;

    fonts[]->vertisecBaseData->localVertices[8].x = ;
    fonts[]->vertisecBaseData->localVertices[8].y = ;

    fonts[]->vertisecBaseData->localVertices[9].x = ;
    fonts[]->vertisecBaseData->localVertices[9].y = ;

    fonts[]->vertisecBaseData->localVertices[10].x = ;
    fonts[]->vertisecBaseData->localVertices[10].y = ;

    fonts[]->vertisecBaseData->localVertices[11].x = ;
    fonts[]->vertisecBaseData->localVertices[11].y = ;

}
