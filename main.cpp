#include <SDL2/SDL.h>
#include "utils.h"
#include "Image.h"
#include "ppm.h"

SDL_Window* window = nullptr;
Image img;
uint32_t WIDTH;
uint32_t HEIGHT;

int DRAW (int newW, int newH) {
        
    SDL_Surface* surface = SDL_GetWindowSurface(window);    
    if (!surface) { 
        std::cerr << SDL_GetError() << "\n"; 
        return 1; 
    }

    SDL_LockSurface(surface);

    uint32_t* pix = (uint32_t*)surface->pixels;

    for (int y = 0; y < newH; y++) { // BETTER CACHE LOCALITY
        for (int x = 0; x < newW; x++) {

            // Nearest neighbor scaling
            int srcX = x * WIDTH / newW;
            int srcY = y * HEIGHT / newH;

            uint8_t r = img.get_pixels()[(srcY * WIDTH + srcX) * 3 + 0];
            uint8_t g = img.get_pixels()[(srcY * WIDTH + srcX) * 3 + 1]; 
            uint8_t b = img.get_pixels()[(srcY * WIDTH + srcX) * 3 + 2];

            uint32_t color = SDL_MapRGB(surface->format, r, g, b);

            pix[y * surface->w + x] = color;
        }
    }

    SDL_UnlockSurface(surface);
            
    if(SDL_UpdateWindowSurface(window) != 0){
        std::cerr << "SDL Update Window Error : " << SDL_GetError() << "\n";
        return 1;
    }
        
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <image_file>\n";
        return 1;
    }

    const std::string filepath = argv[1];
    std::cout << "Opening: " << filepath << std::endl;

    try{
        img = loadPPM(filepath);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << "\n";
        return 1;
    }

    WIDTH  = img.get_width();
    HEIGHT = img.get_height();

    window = SDL_CreateWindow("Image Viewer", 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 
                                        SDL_WINDOW_RESIZABLE
                                    );

    if (!window) { 
        std::cerr << SDL_GetError() << "\n"; 
        return 1;
    }

    if( DRAW(WIDTH, HEIGHT) != 0){ // INITIAL DRAW
        std::cerr << "Initial Draw Error\n";
        return 1;
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                running = false;
            }
            else if (e.type == SDL_WINDOWEVENT &&
                e.window.event == SDL_WINDOWEVENT_RESIZED) {

                int newW = e.window.data1;
                int newH = e.window.data2;

                if( DRAW(newW, newH) != 0){ // REDRAW AGAIN 
                    std::cerr << "Scaling Error\n";
                    return 1;
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
} 