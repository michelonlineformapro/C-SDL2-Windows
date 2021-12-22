#include <iostream>
#include <SDL.h>
#include <cstdlib>
//LES SOURCES : http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

//largeur et hauteur de la fenètre
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//3fonction
//Demarre SDL + creer la fenètre
bool init();
//Charge les medias
bool loadMedia();
//Ferme App
void close();

//Initialisation des reference aux variables (pointeur*) + &var
//Ces variables ont une portée globale
//Init du rendu
SDL_Window* gWindow = NULL;
//La surface contenue dans la fenètre
//SDL surface est une donnée image qui contient des pixels il use le Processeur GPU
SDL_Surface* gScreenSurface = NULL;
//Une image chargée dans la fenètre
SDL_Surface* gImage = NULL;
//Quiiter l'application
bool quit = false;
//Ajouter des evenements (key_press + mouse_motion + joy_button_press etc...)
SDL_Event event;

//Les pointeur alloue la memoire (pour utiliser la meme image au lieu de l'appeler plusieur fois)

//les fonctions appelée dans main
//Demarre SDL et creer la fenètre
//la fonction init()
bool init(){
    //est ce que ca marche
    bool success = true;
    //Init de SDL
    //Initialiser SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        //Message d'erreur
        printf("Erreur : SDL ne peut pas etre initialiser %s\n", SDL_GetError());
        //la condition est fausse
        success = false;
    }else{
        //Creer la fenetre (on use le pointeur declarer au dessus)
        gWindow = SDL_CreateWindow("SDL Tuto apres 2 jour d'instalation !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow== NULL){
            printf("La fenètre ne peut pas etre creer ! SDL erreur %s\n", SDL_GetError());
            success = false;
        }else{
            //Surface de la fenètre (on utilise le pointeur)
            gScreenSurface = SDL_GetWindowSurface(gWindow);

        }
    }
    return success;
}

//Charger les medias
//Charge les medias
bool loadMedia(){
    //de nouveau une condition de succès
    bool success = true;

    //Chargement de l'image d'accueil = LoadBMP = chemin.bmp
    gImage = SDL_LoadBMP("images/splash.bmp");
    if(gImage == NULL){
        printf("Impossible de charger l'image %s\n", "images/splash.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

//Fonction fermer la fenètre
//Libere les medias et arrete SDL
void close(){
    //Dealloué la surface de l'image
    SDL_FreeSurface(gImage);
    //Detruis la fenètre
    SDL_DestroyWindow(gWindow);
    //Quitte le sous syteme SDL
    SDL_Quit();
}



int WinMain(int argc, char* argv[]) {
    //Appel de la fonction init()
    if(!init()){
        printf("Erreur d'initialisation SDL !");
    }else{
        //Appel de la fonction de chargement des medias
        if(!loadMedia()){
            printf("Erreur de chargement des medias");
        }else{
            //On attend que l'utilisateur quitte l'app
            bool quit = false;

            //Boucle d'attente que app soit quitter
            while (!quit){
                while (SDL_PollEvent(&event) != 0){
                    //Utilisateur quitte la fenètre
                    if(event.type == SDL_QUIT){
                        quit = true;
                    }
                }
                //Sinon tous marche (source de image + null + destination image + null)
                SDL_BlitSurface(gImage, nullptr, gScreenSurface, nullptr);
                //Mise a jour de la fenètre
                SDL_UpdateWindowSurface(gWindow);
                SDL_Delay(2000);
            }

        }
    }
    //Libere la resources et ferme SDL
    close();
    return 0;
}