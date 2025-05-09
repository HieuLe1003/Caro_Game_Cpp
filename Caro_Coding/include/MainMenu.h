#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Bot.h"
#include "Human.h"
#include "PlayerInfo.h"
#include "Replay.h"
#include<thread>
#include<chrono>
#include<conio.h>
#include<ctime>
#include<algorithm>

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();
    void menu();//Nhập tùy chọn, điều khiển các chức năng
    void intro();//Mở đầu game
    void print_title(const string&);
    void PvP(BoardManager&, Human&, PlayerInfo&, Replay&);//Triển khai chế độ người với người
    void PvB(BoardManager&, Bot&, Human&, PlayerInfo&, Replay&); //Triển khai chế độ người với bot
    void Show_Info(PlayerInfo&);//Hiển thị bảng xếp hạng và tìm kiếm thông tin người chơi
    void Replay_Game(Replay&);//Phát lại trận đấu
    void choice_replay(Replay&, const string&, const string&);//Tùy chọn lưu trận đấu để phát lại hay không
};

#endif