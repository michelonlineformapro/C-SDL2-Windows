#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

//LES SOURCES : http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

//largeur et hauteur de la fenètre
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Liste des touches dans uen enumation (a la place de int blabla = 0)
enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

//3fonction
//Demarre SDL + creer la fenètre
bool init();
//Charge les medias
bool loadMedia();
//Ferme App
void close();

//Charger les images individuellement
SDL_Surface* loadSurface(std::string path);

//Initialisation des reference aux variables (pointeur*) + &var
//Ces variables ont une portée globale
//Init du rendu
SDL_Window* gWindow = NULL;
//La surface contenue dans la fenètre
//SDL surface est une donnée image qui contient des pixels il use le Processeur GPU
SDL_Surface* gScreenSurface = NULL;

//Une image lors de touche préssée
SDL_Surface* gKeyPressedSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Image courante affichée
SDL_Surface* gCurrentSurface = NULL;


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

    //Charger la surface & image par defaut
    gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/splash2.bmp");
    if(gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        printf("Erreur de chargement de la photo");
        success = false;
    }

    //Charger image UP
    gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if(gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
        printf("Erreur de chargement de la photo");
        success = false;
    }

    //Image down
    gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if(gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
        printf("Erreur de chargement de la photo");
        success = false;
    }

    //Image left
    gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if(gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
        printf("Erreur de chargement de la photo");
        success = false;
    }

    //Image right
    gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if(gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
        printf("Erreur de chargement de la photo");
        success = false;
    }

    //Chargement de l'image d'accueil = LoadBMP = chemin.bmp
    /*
    gImage = SDL_LoadBMP("images/splash.bmp");
    if(gImage == NULL){
        printf("Impossible de charger l'image %s\n", "images/splash.bmp", SDL_GetError());
        success = false;
    }
     */
    return success;
}

//Fonction fermer la fenètre
//Libere les medias et arrete SDL
void close(){
    //Dealloué la surface = on boucle sur le nombre touche possible dans enumeration
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        //Dealloué la surface de l'image
        SDL_FreeSurface(gKeyPressedSurfaces[i]);
        gKeyPressedSurfaces[i] = NULL;
    }

    //Detruis la fenètre
    SDL_DestroyWindow(gWindow);
    //Quitte le sous syteme SDL
    gWindow = NULL;
    SDL_Quit();
}

//Chager les différentes images
SDL_Surface* loadSurface(std::string path){

    //Variable pour optimiser les photos
    SDL_Surface* optimizedSurface = NULL;

    //Charger une image avec un chemin precis
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

    //Si la photo n'a pas la bonne taille (800*600) on optimise la photo avec strech

    if(loadedSurface == NULL){
        printf("Erreur de chargement des photos BMP %s!", path.c_str(), SDL_GetError());
    }else{
        //convertit la surface auformat de l'ecran
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface == NULL){
            printf("Erreur de coversion de l'image %s", path.c_str(), SDL_GetError());
        }
        //Copy de l'original et conversion au nouveau format
        //L'original est encore en memoire et on doit liberer l'espace
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}



int main(int argc, char* argv[]) {
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

            SDL_Event event;
            //Image par defaut
            gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            //Boucle d'attente que app soit quitter
            while (!quit){
                while (SDL_PollEvent(&event) != 0){
                    //Utilisateur quitte la fenètre
                    if(event.type == SDL_QUIT){
                        quit = true;
                        //Detecte un evenement une touche présée
                    } else if(event.type == SDL_KEYDOWN){
                        //On creer un Switch case et on appel image grace a enumeration
                        switch (event.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;
                            default:
                                gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }
                //Appliquer l'etirement de l'image pour l'optimiser
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                //Sinon tous marche (source de image + null + destination image + null)
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
                //Mise a jour de la fenètre
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    //Libere la resources et ferme SDL
    close();
    return 0;
}