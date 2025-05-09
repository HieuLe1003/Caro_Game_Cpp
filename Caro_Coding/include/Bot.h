#ifndef BOT_H
#define BOT_H

#include "BoardManager.h"

class Bot
{
private:
    int level;
    bool around(BoardManager&, int, int); //Hàm kiểm tra xem 1 ô có quân nào bên cạnh không
    vector<pair<int, int>> move_ordering(BoardManager&); //Lưu trữ các nước đi khả thi và sắp xếp theo điểm số giảm dần
    int evaluate(BoardManager&); //Hàm tính điểm bàn cờ theo từng ô
    int minimax(BoardManager&, int, bool, int, int); //Thuật toán minimax để tìm nước đi có điểm cao nhất
public:
    Bot();
    Bot(int);
    ~Bot();
    void set_level(int);
    void make_move(BoardManager&, bool);
    pair<int, int> easy_level(BoardManager&); //Hàm triển khai bot mức độ dễ
    pair<int, int> normal_level(BoardManager&); //Hàm triển khai bot mức độ trung bình
    pair<int, int> hard_level(BoardManager&); //Hàm triển khai bot mức độ khó
};

#endif