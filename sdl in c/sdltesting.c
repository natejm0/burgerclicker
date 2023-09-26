#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Burger Clicker",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 700,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    SDL_RenderClear( renderer );

    SDL_Event event;

    while(1 == 1) {
        if ( SDL_PollEvent( &event ) ) {
            if (SDL_KEYDOWN == event.type) {
                if (SDLK_ESCAPE == event.key.keysym.sym) {
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                }
            }
    
        }
    }

    return 0;
}