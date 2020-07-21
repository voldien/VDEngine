# VDEngine #
---
VDEngine - (Virtual Dimension) Engine is a finalized game engine that were in development 2013. The engine was influenced by the Unity3D engine as a result of previous knowledge of how to make game in the engine.

This game engines design is highly entangled thus it's not recommend to continue the development of this engine. However it's useful enough to make small game projects and for setting up some 3D scene.

## Features ##
---
The engine uses SDL2 for window management and OpenGL for the rendering in order enable support for cross platform. The engine has a minimum requirement of OpenGL 2.0. Thus the fixed rendering pipeline is not supported.

The following are some of the features:
* Custom Script - Custom script that is attachable to game-object with callback event such as update, preculled and etc.
* PostEffect - Posteffect for adding visual effects such as *Guassian-Blur*, *glow*, *Depth-to-Field* and etc.
* RenderingPipe - Support forward rendering only.
* Light - point, directional and spot light supported.
* Shadow - Hard and PCF shadows supported.
* Physic - Physic components can be attached to object in order to perform physic simulation.
* Animation - Animation can be linked to the *Transform* object and to object and their methods.
* Audio - Audio is supported through either FMOD or OpenAL. Where OpenAL is compiled by default. Because it can be installed easily via a packet management program.
* Material - Every rendering object have a material attached.

# Motivation #
The primary motivation were to create a simple, customizable 3D rendering game engine, supported on multiple platforms. The main feature of the engine were to be
able to create custom script with multiple callback for allowing to create more intricate script behaviour. That were to interact easily with physical elements in the scene to create a more of an immersive experience.

# Installation #
---
In order to install the engine, see the following command:
```bash
cmake .
make 
make install
```
This will install the headers in order develop game with as well the shared library. It will install the default built-in shader source files as an archive zip file.

# Examples #
-----------
1. The following code will initialize the engine and start running the engine.

```c++
#include<VDEngine/API.h>
int main(int argc, const char** argv){
	VDEngine::init(argc, argv, VDEngine::eDefault);
	VDEngine::run();
}
```

# Dependencies #
----------------
In order to compile the program, the following Debian packages has to be installed.
```bash
apt-get install libsdl2-dev libopenal-dev libglm-dev libassimp-dev libcurl4-openssl-dev libbullet-dev libglew-dev
```

# License #

This project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details.
