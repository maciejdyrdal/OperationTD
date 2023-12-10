# OperationTD - tower defence game
## Installation on Windows (in Visual Studio)
1. Clone the repository from within Visual Studio
2. Make sure your build configuration is set to Debug x64 (at the top of the screen)
3. Go to **Project -> OperationTD Properties -> VC++ Directories -> Include Directories -> Edit**
4. Add the include directory (`/path_to_project/SDL2-x.x.x/include`)
5. Go to **Project -> OperationTD Properties -> Linker -> Input -> Additional Dependencies -> Edit**
6. Add `SDL2.lib; SDL2main.lib;`
7. Go to **Project -> OperationTD Properties -> VC++ Directories -> Include Directories -> Edit**
8. Add the library directory (`/path_to_project/SDL2-x.x.x/lib/x64`)
9. Go into Windows Settings and search for **Edit the system environment variables**
10. Click Environment Variables and under System Variables select Path and click Edit
11. Click new, then browse to add the library directory for your build configuation (`/path_to_project/SDL2-x.x.x/lib/x64`)
12. Restart Visual Studio
13. Pray

If you're having trouble, consult this website: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php<br>
It follows mostly the same tutorial as written above, but it has pictures (just keep in mind that our SDL2 library folder is in the cloned repository's folder, not **C:\vclib** like on the website).
