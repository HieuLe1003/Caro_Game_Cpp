#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "BoardManager.h"
#include<map>
class PlayerInfo
{
private:
    string filename;
    struct Info
    {
        int win = 0;
        int draw = 0;
        int loss = 0;
    }; //Struct lưu thông số người chơi
    map<string, Info> players; //lưu trữ thông tin người chơi với key là tên người chơi và value là thông số người chơi
public:
    PlayerInfo();
    PlayerInfo(const string&);
    ~PlayerInfo();
    void read_data(); // Đọc dữ liệu từ file và lưu thông tin người chơi vào map players
    void save_data(BoardManager&); //Lưu thông tin người chơi vào file
    void update_player(BoardManager&, const string&, int); //Cập nhật thông tin người chơi
    double win_rate(const string&); //Tính toán tỷ lệ thắng
    string find_player(const string&); //Tìm kiếm đối thủ ngang tầm
    void displayInfo(const string&); //Hiển thị thông số người chơi
    void rank_by_total_games(); //Xếp hạng theo tổng số ván đấu
    void rank_by_win_rate(); //Xếp hạng theo tỷ lệ thắng
    void rank_by_total_points(); //Xếp hạng theo tổng số điểm (thắng +3, hòa +1, thua +0)
};

#endif