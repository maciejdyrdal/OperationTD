#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

#include <string>

class GameState;

//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(std::string path, GameState& gameState);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, GameState& gameState);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // !TEXTURE_H
