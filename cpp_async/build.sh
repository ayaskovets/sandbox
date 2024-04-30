#!/bin/bash
COMPILER="clang++"
FLAGS="-std=c++20 -Wall"
INCLUDE="-I/usr/local/include"
LINK="-L/usr/local/lib -lboost_coroutine -lboost_context-mt -lfmt"
SOURCES="main.cpp"

MACOSX_DEPLOYMENT_TARGET="13.6.5" $COMPILER $FLAGS $INCLUDE $LINK $SOURCES