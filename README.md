# VDEngine #
---
VDEngine - (Virtual Dimension) Engine is a finalized game engine that was in development 2013. It was part of an assignment in secondary school.



## Features ##
---
The engine uses SDL2 for window management and OpenGL for rendering in order enable cross platform support. The engine has a minimum requirement of OpenGL 2.0. Thus the fixed rendering pipeline is not supported.

* Custom Script - Custom script that is attachable to game-object with callback event such as update, preculled and etc.
* PostEffect - Posteffect for adding visual effects such as guassian-blur, glow, Depth-to-Field and etc.
* RenderingPipe - Support forward and deferred rendering.
* Shadow - Hard and PCF shadows.
* Physic - Physic components can be attached to object in order to perform physic simulation.
* Animation - 
* Audio - Audio is supported through either FMOD or OpenAL. Where OpenAL is compiled by default. Because it can be installed with a packet manager.
* Morph - Morph animation is 
* Material - 




## Installation ##
---
In order to install the engine, see the following command.
```bash
cmake .
make 
make install
```
This will install the header in order develop game with as well the shared library.  

 


## Dependencies ##
----------------
In order to compile the program, the following Debian packages has to be installed.
```bash
apt-get install libsdl2-dev libopenal-dev libglm-dev libassimp-dev libcurl4-openssl-dev libbullet-dev libglew-dev
```

## License ##
---
The project is under the GPL+3 [license](LICENSE).