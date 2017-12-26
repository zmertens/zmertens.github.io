#!/usr/bin/bash

<<<<<<< HEAD
/usr/lib/emscripten/em++ -std=c++11 -O3 -s USE_SDL=2 -s FULL_ES2=1 Main.cpp -o index.html
=======
#em++ -std=c++11 -O3 -s USE_SDL=2 -s FULL_ES2=1 Main.cpp -o Main.html
emcc -s USE_SDL=2 -s FULL_ES2=1 testdraw2.c SDL_test_common.c -o SDL_test_draw2.html
>>>>>>> remotes/origin/dev
