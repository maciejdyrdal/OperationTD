#ifndef APP_H
#define APP_H

//Screen dimension constants
extern constexpr int SCREEN_WIDTH{ 640 };
extern constexpr int SCREEN_HEIGHT{ 480 };

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

#endif // !APP_H

