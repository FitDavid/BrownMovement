#include "CircleVector.h"
#include <iostream>
/**
 * @brief read the code, it's simple enough.
 * @param argc
 * @param args
 * @return 
 */
int main(int argc, char* args[])
{
    try
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window * window;
        window = SDL_CreateWindow("Brown-movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        SDL_Renderer * renderer;
        renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        CircleVector circVect(renderer);
        bool quit = false;
        SDL_Event event;
        while(!quit)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            SDL_RenderClear(renderer);
            circVect.move();
            circVect.render();
            SDL_RenderPresent(renderer);
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        SDL_Quit();
    }
    catch(const char * message)
    {
        std::cout << message << std::endl;
    }
    return 0;
}
