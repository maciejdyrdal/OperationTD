# OperationTD - tower defence game (very early beta version)
## Installation on Windows (in Visual Studio)
1. Clone the repository from within Visual Studio
2. Download the [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-VC.zip), [SDL2_image](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip) and [plog](https://github.com/SergiusTheBest/plog) libraries, unpack them and put them in **/OperationTD/libs/**
3. Rename the plog library's folder from **plog-master** to **plog**
4. Make sure your build configuration is set to Debug x64 (at the top of the screen)
5. (Optional) Build and run the project (Ctrl+F5) - it won't work, but that's supposed to happen
6. Go into Windows Settings and search for **Edit the system environment variables**
7. Click Environment Variables and under System Variables select Path and click Edit
8. Click New, then browse to add the library directories for your build configuation (`/path_to_project_folder/libs/SDL2-x.x.x/lib/x64` and `/path_to_project_folder/libs/SDL2_image-x.x.x/lib/x64`)
9. Restart Visual Studio
10. Launch the app 

## Visuals
This is what the game currently looks like:
![earlyGameScreenshot](https://github.com/maciejdyrdal/OperationTD/assets/64736385/e5495088-3c08-472c-a3e4-3f8b306c3fef)
The player character can move around the map with the arrow keys and place a tower with the space key.
