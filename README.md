# Thomas Was Alone Recoding Project
### by [Axel Dona](https://github.com/AxelDona) and [Mattéo Leclercq](https://github.com/MatteoL-W/)
### Setup forked from [SDL2_Boilerplate](https://github.com/MatteoL-W/SDL2_Boilerplate)

## Installation
### Linux
- Install CMAKE
- Clone the repo : ```git clone --recurse-submodules https://github.com/MatteoL-W/Thomas_Was_Alone_Recoding```
- At the cloned repo root, execute ```cmake --build "build"```
- Start the game ```./bin/thomas_was_not_alone```

### Windows
- Install CMAKE
- Install a G++ compiler (this setup is made for MinGW)
- If you're not on MinGW, install SDL2 on your compiler
- Clone the repo : ```git clone https://github.com/MatteoL-W/Thomas_Was_Alone_Recoding```
- At the cloned repo root, execute ```cmake --build "build"```
- Start the game ```./bin/thomas_was_not_alone.exe```

If you have the following build error: ```cannot find -SDL2_mixer``` in example, I advise you to move the content of the following library into your libraries MINGW folder. In my case, I needed to add ``` Thomas_Was_Alone\lib\SDL2_mixer-2.0.4\x86_64-w64-mingw32\lib ``` content into ```C:\MinGW\lib```. I don't know how to fix this one, sorry.
