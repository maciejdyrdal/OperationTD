#include "Texture.h"

#include "GameState.h"

#include <SDL.h>
#include <SDL_image.h>

Texture::Texture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    // Deallocate
    free();
}

bool Texture::loadFromFile(const std::string& path, GameState& gameState)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gameState.m_Renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, GameState& gameState)
{
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gameState.m_Font, textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gameState.m_Renderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    // Return success
    return mTexture != NULL;
}


void Texture::free()
{
    // Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, GameState& gameState)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    SDL_RenderCopy(gameState.m_Renderer, mTexture, NULL, &renderQuad);
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}
