# OperationTD - Simple tower defence game 
## Installation on Windows (in Visual Studio)
1. Clone the repository from within Visual Studio
2. Download the [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-VC.zip), [SDL2_image](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip), [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases) and [plog](https://github.com/SergiusTheBest/plog) libraries, unpack them and put them in **/OperationTD/libs/**
3. Rename the plog library's folder from **plog-master** to **plog**
4. Make sure your build configuration is set to Debug x64 (at the top of the screen)
5. (Optional) Build and run the project (Ctrl+F5) - it won't work, but that's supposed to happen
6. Go into Windows Settings and search for **Edit the system environment variables**
7. Click Environment Variables and under System Variables select Path and click Edit
8. Click New, then browse to add the library directories for your build configuation (`/path_to_project_folder/libs/SDL2-x.x.x/lib/x64`, `/path_to_project_folder/libs/SDL2_image-x.x.x/lib/x64` and `/path_to_project_folder/libs/SDL2_ttf-2.20.2/lib/x64`)
9. Restart Visual Studio
10. Launch the app 

## Overview
OperationTD is a basic tower defence-type game with a twist - the player also controls an in-game character with the ability to attack, thougn only a limited number of times during the course of the game. Of course, the main way of dealing damage to the enemies is to place down towers, of which there are 3 types with different characteristics:  
* The arrow tower has the greatest range, but deals the least damage and can attack a limited number of enemies each second
* The lava tower has short range, but deals lots of damage and can attack many enemies each turn
* The magic tower is the most balanced of the 3, providing moderate damage, range and attacks per turn
   
There are also several types of enemies:  
* Small goblins are fast, but low in health
* Large gobline are slow, but tanky
* Assassins have moderate speed and slightly more health tnan small goblins
* Knights are slightly slower than assassins, but have much more health  

On death, the enemies have a chance to drop some resources, which are nesessary for tower placement.  
  
The player is able to upgrade their character's damage from the same menu as the tower placement, but the cost goes up each time they choose to do so.

## Visuals
### Starting menu:
![image](https://github.com/maciejdyrdal/OperationTD/assets/64736385/b52d1d4d-c098-4e86-8156-5705dbf961e2)
This screen contains the game instructions and is the first thing the player sees on startup.

### Game window:
![image](https://github.com/maciejdyrdal/OperationTD/assets/64736385/a6e1a730-9564-4a0e-8791-b4b307193b53)
This is the game window, it is here that the gameplay takes place. The player can move around with the protagonist, place towers and attack (though only a limited number of times).

### Result screen:
![image](https://github.com/maciejdyrdal/OperationTD/assets/64736385/f70ab578-14cf-4605-b1c2-29e090f4d024)
This is the screen displayed at the end of the game, either signifying victory or failure. The game pauses at that point and the user must close the window and start the game again if they wish to play another round.

## Documentation
### App.cpp and the main() function
The core file, App.cpp, contains several functions, the ``main()`` function among them. 

``init()``  
This function initializes the main game components, such as the SDL instance, the window, renderer, as well as PNG and font loading.

``loadMedia()``  
This function receives all texture variables as arguments and loads them from the corresponding files. It is not written in a very concise way due to SDL's issues with storing texture pointers inside compile time-generated data structures.

``generateTiles()`` and ``generateSelectionTiles()``  
These functions create grids of Tile objects, which (among other things) serve the function of checking whether a building has been placed on a particular tile.

``generateViewportTiles()`` and ``generateSelectionViewportTiles()``  
These functions create vectors of Viewport SDL variables which hold the coordinates of each tile in the game window and selection menu.

``main()``  
The ``main()`` function handles the main game loop, creation of all the texture variables, keeping record of the in-game time, enemy movement and all the player actions (placing towers, attacking).

### GameState
The GameState class holds globally important information, such as the renderer pointer, screen and tile size, resource amounts and the enemy path. It also handles memory cleanup and destroys the renderer and window objects on exit.  
  
The class is initialized only once in the program, and the created object is passed to all functions that need the information held by it (for example, the ``render()`` method uses it to access the renderer).

### Enemy
The Enemy class holds the information on each enemy, such as their position, health, texture etc.  
  
``move()``  
This method moves the enemy to a tile if the provided coordinates are valid (i.e. not on a border between tiles).  

``takeDamage()``  
This method handles dealing damage to the enemy, reducing its HP and dropping resources on death.

### Player
The Player class holds the information on the player character, such as their position, texture, attacks left and damage.

### Random
The Random class is used for random number generation and has been provided courtesy of [the learncpp.com tutorial site](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/). 

### Tile
The Tile class holds information on a tile's position, and whether a building is present on it.

## SelectionTile
The SelectionTile class is similar to the Tile class, only used in the selection menu.

### Texture
The Texture class is a wrapper for the SDL Texture variable and provides some useful utilities built on it. It also handles resource freeing.  

``loadFromFile()``  
This method loads a texture from a provided file path.  

``loadFromRenderedText()``
This method creates a surface from a string and prepares it for rendering.  

``free()``  
This method frees the texture resources.  

``render()``  
This method renders the texture stored in the object.

### Timer
The Timer class is a wrapper for the SDL timer with some utilities added to it.  
The ``start()``, ``stop()``, ``pause()``, ``unpause()`` methods are self explanatory, and ``getTicks()`` returns the current time in miliseconds.


### Tower
The Tower class holds the information on each tower, such as its location, texture, range, damage and number of attacks performed each second.  

``dealDamage()``  
This method deals damage to a provided enemy if it is in range.
