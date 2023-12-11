# OperationTD - tower defence game
## Installation on Windows (in Visual Studio)
1. Clone the repository from within Visual Studio
2. Download the [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-VC.zip) and [plog](https://github.com/SergiusTheBest/plog) libraries, unpack them and put them in **/OperationTD/libs/**
3. Make sure your build configuration is set to Debug x64 (at the top of the screen)
4. Build and run the project (Ctrl+F5) - it won't work, but that's supposed to happen
5. ~~Go to **Project -> OperationTD Properties -> VC++ Directories -> Include Directories -> Edit**~~
6. ~~Add the include directory (`/path_to_libs_folder/SDL2-x.x.x/include`)~~
7. ~~Go to **Project -> OperationTD Properties -> Linker -> Input -> Additional Dependencies -> Edit**~~
8. ~~Add `SDL2.lib; SDL2main.lib;`~~
9. ~~Go to **Project -> OperationTD Properties -> VC++ Directories -> Include Directories -> Edit**~~
10. ~~Add the library directory (`/path_to_libs_folder/SDL2-x.x.x/lib/x64`)~~
11. Go into Windows Settings and search for **Edit the system environment variables**
12. Click Environment Variables and under System Variables select Path and click Edit
13. Click new, then browse to add the library directory for your build configuation (`/path_to_libs_folder/SDL2-x.x.x/lib/x64`)
14. Restart Visual Studio
15. Pray

If you're having trouble, consult this website: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php<br>
It follows mostly the same tutorial as written above, but it has pictures (just keep in mind that our SDL2 library folder is in the cloned repository's folder, not **C:\vclib** like on the website).
