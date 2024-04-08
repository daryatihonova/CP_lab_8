#pragma once


#include <string>
using namespace std;
struct App {
    string name; // наименование
    string manufacturer; // производитель
    float size; // размер на диске
    float price; // цена
    App* prev = nullptr;
    App* next = nullptr;
};



