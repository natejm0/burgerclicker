#define SDL_MAIN_HANDLED
#define ASSETS_PATH "..\\assets\\"
#define SPRITES_PATH "sprites\\"
#define BURGER_SPRITE ASSETS_PATH SPRITES_PATH "burger.png"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    
    int screenWidth = 1080;
    int screenHeight = 720;

    int burgerWidth = 256;
    int burgerHeight = 256;     
    
    SDL_Texture *imageTexture = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 1;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Burger Clicker",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    if (renderer == 0) {
        printf("Failed to load renderer");
        goto cleanup;
    }

    // Set BG Color
    SDL_SetRenderDrawColor( renderer, 216, 102, 53, 255 );

    SDL_Event event;

    printf(BURGER_SPRITE);
    SDL_Surface *loadedSurface = IMG_Load(BURGER_SPRITE);
    


    if (loadedSurface == 0) {
        printf("Failed to load burger sprite");
        goto cleanup;
    }

    imageTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!imageTexture) {
        printf("Failed to create texture");
        goto cleanup;
    }    
    
    SDL_FreeSurface(loadedSurface);

    int gameIsRunning = 1;
    
    int image_width, image_height;
    SDL_QueryTexture(imageTexture, NULL, NULL, &image_width, &image_height);
    
    SDL_Rect rect;
    rect.x = screenWidth - screenWidth/2 - burgerWidth/2;
    rect.y = screenHeight - screenHeight/2 - burgerHeight/2;
    rect.w = burgerWidth;
    rect.h = burgerHeight;

    while(gameIsRunning) {
        if ( SDL_PollEvent( &event ) ) {
            if (SDL_KEYDOWN == event.type) {
                if (SDLK_ESCAPE == event.key.keysym.sym) {
                    gameIsRunning = 0;
                }
            }
        }
        
        SDL_RenderClear( renderer );
        
        SDL_RenderCopy(renderer, imageTexture, NULL, &rect); // Render the whole texture to the screen
        
        SDL_RenderPresent(renderer);
    }

cleanup:
    
    if (imageTexture) {
        SDL_DestroyTexture(imageTexture);
    }
    if (renderer) {
        
        SDL_DestroyRenderer(renderer);
    }
    
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    SDL_Quit();

    return 0;
}