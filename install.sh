#!/bin/bash
echo "\033[0;33mChecking required libraries...\033[0m"

if brew ls --versions sfml; then
  echo "\033[0;36mSFML is already installed\033[0m"
else
  echo "\033[0;31mSFML is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sfml
  echo "\033[0;32mSFML installation completed\033[0m"
fi

if brew ls --versions sdl2; then
  echo "\033[0;36mSDL2 is already installed\033[0m"
else
  echo "\033[0;31mSDL2 is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2
  echo "\033[0;32mSDL2 installation completed\033[0m"
fi

if brew ls --versions sdl2_image; then
  echo "\033[0;36mSDL2_Image is already installed\033[0m"
else
  echo "\033[0;31mSDL2_Image is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_image
  echo "\033[0;32mSDL2_Image installation completed\033[0m"
fi

if brew ls --versions sdl2_ttf; then
  echo "\033[0;36mSDL2_TTF is already installed\033[0m"
else
  echo "\033[0;31mSDL2_TTF is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_ttf
  echo "\033[0;32mSDL2_TTF installation completed\033[0m"
fi

if brew ls --versions glfw; then
  echo "\033[0;36mGLFW is already installed\033[0m"
else
  echo "\033[0;31mGLFW is required in order to start the game. Please wait until it is installed\033[0m"
  brew install glfw
  echo "\033[0;32mGLFW installation completed\033[0m"
fi

if brew ls --versions glew; then
  echo "\033[0;36mGLFW is already installed\033[0m"
else
  echo "\033[0;31mGLFW is required in order to start the game. Please wait until it is installed\033[0m"
  brew install glew
  echo "\033[0;32mGLFW installation completed\033[0m"
fi

if brew ls --versions freetype; then
  echo "\033[0;36mFreeType is already installed\033[0m"
else
  echo "\033[0;31mFreeType is required in order to start the game. Please wait until it is installed\033[0m"
  brew install freetype
  echo "\033[0;32mFreeType installation completed\033[0m"
fi

if brew ls --versions ftgl; then
  echo "\033[0;36mFTGL is already installed\033[0m"
else
  echo "\033[0;31mFTGL is required in order to start the game. Please wait until it is installed\033[0m"
  brew install ftgl
  echo "\033[0;32mFTGL installation completed\033[0m"
fi

echo "\033[0;33mDownloading and installing a SOIL library (macos compatible)...\033[0m"
curl -O http://www.lonesock.net/files/soil.zip
unzip  soil.zip && mv "Simple OpenGL Image Library" "SOIL"
rm -rf soil.zip
cd SOIL/lib && rm -rf libSOIL.a
cd SOIL/projects/makefile && mkdir obj
cd SOIL/projects/makefile && make
mv SOIL ~/.brew/
echo "\033[0;32mSOIL installation completed\033[0m"