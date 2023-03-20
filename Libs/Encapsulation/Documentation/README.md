# Encapsulation of graphical lib

## How it work ?

dans le game engine, une seule class qui appellera les interfaces et classes de l'encapsulation pour les initialiser, après on retrouve que les interfaces

## The Encapsulation

For the project, we use the Raylib. A library write in ```C```. because our engine is in C++, we need to encapsulate to use it as it's object oriented

For that, we create 6 different interfaces:

- [IGraphical](../include/IGraphical.hpp): For initialize the window and handle it and start all the main parameters
- [IElement](../include/IElement.hpp): For the sprite, with this class you can create, draw and handle parameters of all sprites
- [Iinteraction](../include/Iinteraction.hpp): This class is here to ctach all user interactions such as keyboard input or mouse
- [IShapes](../include/IShapes.hpp): This class is here for handle collision between shapes (circle, rectangle...) and draw the outline of the shapes if needed
- [ISound](../include/ISound.hpp): This class is here for playing background music or effect (click on button...)
- [IText](../include/IText.hpp): This class is here for load text font and print text

## Why use Interface ?

We used interface, so that if the user want to use it own graphical library (```like SFML or SDL```), he can easily change it.

### How to add our own graphical library ?

Firstly, you need to go in ``` Libs/Encapsulation/``` and create your own directory

After that, you need to organize your directory the following way:
```
dir/ --
      |-> src/ --
      |        |-> Lib.cpp
      |        |-> Lib.hpp
      |        |-> Element/ ------
      |                          | -> Element.cpp
      |                          | -> Element.hpp
      |        |-> Interaction/ --
      |                          | -> Interaction.cpp
      |                          | -> Interaction.hpp 
      |        |-> Shapes/ -------
      |                          | -> Shapes.cpp
      |                          | -> Shapes.hpp
      |        |-> Sound/ --------
      |                          | -> Sound.cpp
      |                          | -> Sound.hpp
      |        |-> Text/ ---------
      |                          | -> Text.cpp
      |                          | -> Text.hpp
```

In CMakeLists.txt, change ``` set(DIRECTORY_ENCAPSULATION you_dir) ``` with your directory

(Each of your class must inherits from the interfaces and have an extern C method like in the raylib)

#### if you need to link with a lib, you can change the following lines (or remove them if you don't need to link to an external lib)

Finaly, in ```Engine/Loader/ClassLoader```, you need to change the include with yours

``` cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}path/to/your/lib/finder)

FIND_PACKAGE(libName REQUIRED)

TARGET_LINK_LIBRARIES(graphical_lib libName)
```

[home](/../../)
