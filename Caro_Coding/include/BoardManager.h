#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H
#define BOARD_SIZE 10
#define TOP_PADDING 2
#define LEFT_PADDING 40
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class BoardManager
{
private:
    vector<vector<string>> board;
    int last_human_r = -1, last_human_c = -1; //Nước đi gần nhất của người chơi
    int last_bot_r = -1, last_bot_c = -1; //Nước đi gần nhất của bot
    int count_step(int, int, int, int); //Đếm số nước đi liên tiếp
    bool game_over = false;
    int result1, result2; //Kết quả của người chơi 1 và 2
public:
    BoardManager();
    ~BoardManager();
    void draw_board(); //Hàm vẽ bàn cờ
    void update_board(int, int, bool);//Hàm cập nhật bàn cờ sau mỗi nước đi
    int check_result(int, int); //Hàm kiểm tra kết quả sau mỗi nước đi
    bool is_empty(int, int); //Kiểm tra ô trống
    bool check_over(); //Kiểm tra kết thúc trận đấu
    void reset_game(); //Đưa bàn cờ về trạng thái ban đầu lúc chưa đánh
    void set_cell(int, int, const string&); //Đánh vào 1 ô trên bàn cờ
    const string get_cell(int, int) const; //Truy xuất giá trị 1 ô trên bàn cờ
    void set_last_move(int, int, bool); //Lưu nước đi gần nhất
    int get_count_step(int, int, int, int);//Truy xuất thông tin về số nước đi liên tiếp
    pair<int, int> get_last_move(bool); //Truy xuất nước đi gần nhất
    pair<int, int> result(); //Lưu kết quả của 2 người chơi
    int is_blocked(int, int, int, int); //Kiểm tra xem nước đi có bị chặn hay không
};

#endif