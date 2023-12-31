#!/bin/bash
rm game_ray
cc -o game_ray gameray.c gameutils.c -ggdb -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./game_ray
