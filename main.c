#define SDL_MAIN_HANDLED
#define ASSETS_PATH "..\\assets\\"
#define SPRITES_PATH "sprites\\"
#define BURGER_SPRITE ASSETS_PATH SPRITES_PATH "burger.png"
#define CLICKABLE_BURGER_SPRITE ASSETS_PATH SPRITES_PATH "clickableburger.png"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    SDL_Surface *surf;
    SDL_Texture *tex;
} Sprite;

Sprite loadSprite(char *filepath, SDL_Renderer *renderer) {
    Sprite loadedSprite;
    loadedSprite.surf = IMG_Load(filepath);
    loadedSprite.tex = SDL_CreateTextureFromSurface(renderer, loadedSprite.surf);

    SDL_FreeSurface(loadedSprite.surf);

    return loadedSprite;
}

void cleanupSprite(Sprite spr) {
    // cleanup the surface and texture of sprite (call at end of main func)
    SDL_DestroyTexture(spr.tex);
}

float max(float val1, float val2) {

    if (val1 > val2) {
        return val1;
    }
     
    return val2;
}

float randomFloatRange(float start, float end) {
    float r = (float)rand() / (float)RAND_MAX;
    float rangeSize = end - start;
    return r*rangeSize + start;
}

int main(int argc, char* argv[]) {
    
    // Game stuff
    int gameIsRunning = 1;
    
    // Resolutions
    int screenWidth = 1080;
    int screenHeight = 720;

    int burgerWidth = 256;
    int burgerHeight = 256;     
    
    // Initialization
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

    // Create window
    window = SDL_CreateWindow(
        "Burger Clicker",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_SHOWN
    );
    
    // Create renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    // Set BG Color
    SDL_SetRenderDrawColor( renderer, 216, 102, 53, 255 );

    // Create event
    SDL_Event event;

    // Load burger sprite
    Sprite burgerSprite = loadSprite(BURGER_SPRITE, renderer);
    
    // Initilize burger sprite to draw
    int image_width, image_height;
    SDL_QueryTexture(imageTexture, NULL, NULL, &image_width, &image_height);
    
    // Create burgers
    SDL_Rect rect[100];
    Point positions[100];

    float fallspeeds[100];
    for (int i = 0; i < 100; ++i) {
        fallspeeds[i] = randomFloatRange(.05, .1);
    }

    // Initilize rectangle
    for (int i = 0; i < 100; i++)
    {
        rect[i].x = 10 + 32*i;
        rect[i].y = 0 - burgerHeight;
        rect[i].w = 64;
        rect[i].h = 64;
        positions[i].x = (float)rect[i].x;
        positions[i].y = (float)rect[i].y;
    }

    // Game loop
    while(gameIsRunning) {
        if ( SDL_PollEvent( &event ) ) {
            // Check if key pressed
            if (SDL_KEYDOWN == event.type) {
                // Quit game if "esc" is pressed
                if (SDLK_ESCAPE == event.key.keysym.sym) {
                    gameIsRunning = 0;
                }
            }
        }
        
        // Clear renderer
        SDL_RenderClear( renderer );
        
        // Draw burger sprite
        for (int i = 0; i < 100; i++)
        {
            positions[i].y = positions[i].y + fallspeeds[i];

            rect[i].y = positions[i].y;

            if (positions[i].y > screenHeight + 64) {
                positions[i].y = 0 - 64;
            }

            SDL_RenderCopy(renderer, burgerSprite.tex, NULL, &rect[i]);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

// Quit game and cleanup
cleanup:
    
    if (burgerSprite.tex) {
        cleanupSprite(burgerSprite);
    }
    
    if (renderer) { 
        SDL_DestroyRenderer(renderer);
    }
    
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    SDL_Quit();

    return 0;
}