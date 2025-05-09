#ifndef REPLAY_H
#define REPLAY_H

#include "BoardManager.h"
class Replay
{
private:
    vector<pair<int, int>> moves;//vector lưu các nước đi
    string filename; // file lưu các nước đi
    vector<string> games; //vector lưu các game đã chơi
    BoardManager& board;
public:
    Replay(const string&, BoardManager&);
    ~Replay();
    void save_move(const pair<int, int>&); //Hàm lưu nước đi theo tọa độ
    void save_game(const string&, const string&); //Hàm lưu trận đấu vào file
    void load_game(); //Hàm đọc danh sách trận đấu
    void replay_game(int); // Hàm phát lại trận đấu
    void control_replay(const string&, const string&); //Hàm điều khiển việc phát lại trận đấu
    vector<string> get_games(); //Hàm lấy danh sách thông tin các ván đấu (tên người chơi, thời gian)
    void moves_clear(); //Hàm xóa danh sách nước đi
};

#endif