# EKTOKLEPTO
<img src="https://github.com/MatteoL-W/EKTOKLEPTO/blob/master/assets/img/menu/ektoklepto.png" width="200">

## by [Axel Dona](https://github.com/AxelDona) and [Mattéo Leclercq](https://github.com/MatteoL-W/)
### Setup forked from [SDL2_Boilerplate](https://github.com/MatteoL-W/SDL2_Boilerplate)

## Installation
### Linux
- Install CMAKE
- Install lib ```sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev```
- Clone the repo **with the submodule** : ```git clone --recurse-submodules https://github.com/MatteoL-W/Thomas_Was_Alone_Recoding```
- At the cloned repo root, execute ```cmake --build "build"```
- Start the game ```./bin/thomas_was_not_alone```

### Windows
- Install CMAKE
- Install a G++ compiler (this setup is made for MinGW)
- If you're not on MinGW, install SDL2 on your compiler
- Clone the repo : ```git clone https://github.com/MatteoL-W/Thomas_Was_Alone_Recoding```
- At the cloned repo root, execute ```cmake --build build```
- Start the game ```./bin/thomas_was_not_alone.exe```

If you have the following build error: ```cannot find -SDL2_mixer``` in example, I advise you to move the content of the following library into your libraries MINGW folder. In my case, I needed to add ``` Thomas_Was_Alone\lib\SDL2_mixer-2.0.4\x86_64-w64-mingw32\lib ``` content into ```C:\MinGW\lib```. Same for the ```bin/``` folder. I don't know how to fix this one, sorry.
