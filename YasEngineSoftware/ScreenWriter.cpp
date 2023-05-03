#include"ScreenWriter.hpp"
#include<iostream>
#include<sstream>

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
