#!/bin/bash
g++ -c fill.cpp                                                   
g++ fill.o -o fill-app -lsfml-graphics -lsfml-window -lsfml-system
./fill-app