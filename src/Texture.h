#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

#include <string>

class GameState;

// SDL Texture wrapper class
class Texture
{
public:
    Texture();

    ~Texture();

    // Load image at specified path
    bool loadFromFile(const std::string& path, GameState& gameState);

    // Create image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, GameState& gameState);

    // Deallocate texture
    void free();

    // Render texture at given point
    void render(int x, int y, GameState& gameState);

    // Get image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

#endif // !TEXTURE_H
