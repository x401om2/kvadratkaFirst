#!/bin/bash

echo "Компиляция kvadratka..."

g++ -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ \
    -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body \
    -Wfloat-equal -Wformat-nonliteral -Wformat-security \
    -Wformat=2 -Winline -Wnon-virtual-dtor \
    -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
    -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
    -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default \
    -Wswitch-enum -Wundef -Wunreachable-code -Wunused \
    -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing \
    -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
    -fsized-deallocation -fstack-protector -fstrict-overflow \
    -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla \
    -fsanitize=address,undefined \
    main.cpp equation.cpp io_functions.cpp tests.cpp cat_art.cpp \
    -o kvadratka

if [ $? -eq 0 ]; then
    echo "Сборка успешна!"
    echo "Для запуска: ./kvadratka"
else
    echo "Ошибка при компиляции!"
    exit 1
fi
