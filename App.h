#pragma once


#include <string>
using namespace std;
struct App {
    string name; // ������������
    string manufacturer; // �������������
    float size; // ������ �� �����
    float price; // ����
    App* prev = nullptr;
    App* next = nullptr;
};



