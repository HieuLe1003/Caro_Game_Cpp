#include "MainMenu.h"
#define WIN32_LEAN_AND_MEAN
#include<windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8); // Đặt mã hóa đầu ra console thành UTF-8
    MainMenu menu;
    menu.menu();
    return 0;
}