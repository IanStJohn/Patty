# Patty - 3D Game Engine
Patty is a 3D game engine based on SDL and OpenGL developed for the final project of George Mason Universities CS425 Game Programming course. Over the course of 2 weeks the engine went from being able to display a black screen, to loading in custom .obj files with custom .bmp textures and placed within a scene. Using SDL2, music and inputs were handeled, causing the bulk of the work on this engine to be the specific integration of OpenGL with SDL.

## Libraries Used
* [Simple DirectMedia Library 2 (SDL2)](https://www.libsdl.org/index.php)
* [OpenGL 4.3](https://www.opengl.org/)
* [OpenGL Extension Wrangler (GLEW)](http://glew.sourceforge.net/)
* [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm)
* [Dirent](https://github.com/tronkko/dirent)

## Available Features
* Load .obj files and place in scene as a model.
  - Object can be placed in space (position).
  - Object can be rotated about axis (rotation).
  - Object can be scaled in 3 dimensions independently.
  - Objects can be nested (child/parent relations).
  - Children are positioned/rotated/scaled relative to parent position.
  - Objects can dynamically move around scene.
* Load .bmp files and place on a model as a texture.
* Load .wav files for background music in scene.
* W/A/S/D and mouse control to move camera in scene.
  - Keyboard movements move a player object with a mesh attatched.
  - Camera moves freely with mesh object fixed in view (possible UI/HUD element).
* Dynamically place objects/models in scene without recompiling due to custom scene file format.
  - Without recompiling change the background music, the starting location of the player, and the position/rotation/scale of all mesh objects.

## Planned Features
* Use SDL True Type Font (TTF) package and hook it up to OpenGL to render text dynamically.
* Read in different file formats for textures.
  - .png files will allow for transparency.
* Create Texture Manager so models can reference the same texture for more effecient loading.
* Create a component system that can easily be attatched to scene objects in the scene file to change object behavior without compiling.
  - Rotator Component could allow for parent object of the component to spin at a specified rate.
  - Trigger Component could be linked to a boolean system in the scene to trigger events dynamically.
* Load more than just .obj files for 3D models.
  - .fbx files are smaller and I personally use theme more often.
* Add scene transitioning.
* ... and more!

# Supermassive Omega
This was the theoretical game to be made with the engine, but as time went on and setbacks kept occuring with engine development, the scope of the game was greatly reduced to meet deadlines. At the moment, the game is no more than a sandbox, where 3D artists can load in their models, load in textures and move around an environment with them. Getting a game working with clickable buttons, a menu system, a scoring system, etc... wasn't possible with the time remaining. So instead of creating a half baked game, time was spent on polishing the engine in hopes that a game could be better integrated into it soon.

## Behind the Scenes Progress
### 11/28/2020 Progress Video
[![11/28/2020 Progress Viedo](https://img.youtube.com/vi/1SMLMJfSh4g/0.jpg)](https://www.youtube.com/watch?v=1SMLMJfSh4g)
In this short clip I show how I got OpenGL hooked into SDL with music and a cool fragment shader effect, I also let off some steam about not being able to render text, which as of writting this on 12/14/2020 is still a goal.
### Progress Screenshots

