#include <iostream>
#include <SDL.h>
#include <cstdlib>
//LES SOURCES : http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int WinMain(int argc, char* argv[]) {

    //Rendu de la fenètre
    SDL_Window* window = NULL;
    //Surface qui contient la fenètre
    SDL_Surface* screenSurface = NULL;

    //Initialiser SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Erreur : SDL ne peut pas etre initialiser %s\n", SDL_GetError());
    }else{
        //Creer la fenetre
        window = SDL_CreateWindow("SDL Tuto apres 2 jour d'instalation !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("La fenètre ne peut pas etre creer ! SDL erreur %s\n", SDL_GetError());
        }else{
            //Surface de la fenètre
            screenSurface = SDL_GetWindowSurface(window);

            //Remplir de blanc
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            //Mise a jour de la surface
            SDL_UpdateWindowSurface(window);
            //Delay de demarage 2s
            SDL_Delay(8000);
        }
    }

    //On detruis la fenètre a la fermeture
    SDL_DestroyWindow(window);
    //Quitte SDL sous sytème
    SDL_Quit();

    return 0;
}