#include "BoardManager.h"

BoardManager::BoardManager(): board(BOARD_SIZE, vector<string>(BOARD_SIZE, " ")){}
BoardManager::~BoardManager(){}

// Hàm đếm số nước đi cùng loại liên tiếp
int BoardManager::count_step(int r, int c, int rs, int cs){
    if(board[r][c] == " ") return 0;
    int count = 1;
    int i = 1;
    while (c+i*cs < BOARD_SIZE && r+i*rs < BOARD_SIZE && c+i*cs >= 0 && r+i*rs >= 0 && board[r+i*rs][c+i*cs] == board[r][c])
    {
        count++;
        i++;
    }
    i = 1;
    while (c-i*cs>=0 && r-i*rs>=0 && c-i*cs < BOARD_SIZE && r-i*rs < BOARD_SIZE && board[r-i*rs][c-i*cs] == board[r][c])
    {
        count++;
        i++;
    }
    return count;
}

// Hàm vẽ bàn cờ
void BoardManager::draw_board(){
    for (int i = 0; i < TOP_PADDING; i++)
    {
        cout << endl;
    }
    
    string line = "\033[33m  |---|---|---|---|---|---|---|---|---|---|\033[0m";
    cout << string(LEFT_PADDING, ' ') << "   ";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << "\033[35m " << i << "  \033[0m";
    }
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++){
        string row = "";
        cout << string(LEFT_PADDING, ' ') << line << endl;
        cout << string(LEFT_PADDING, ' ') << "\033[35m" << i << "\033[0m\033[33m |\033[0m";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            row += " " + board[i][j] + "\033[33m |\033[0m";
        }
        cout << row << endl;
    }
    cout << string(LEFT_PADDING, ' ') << line << endl;
}

void BoardManager::set_last_move(int r, int c, bool player){
    if(player){
        last_human_r = r;
        last_human_c = c;
    }
    else{
        last_bot_r = r;
        last_bot_c = c;
    }
}

// Truy suất vị trí nước đi mới nhất
pair<int, int> BoardManager::get_last_move(bool player){
    if (player)
    {
        return {last_human_r, last_human_c};
    }
    else{
        return {last_bot_r, last_bot_c};
    }
}

// Cập nhật lại bàn cờ
void BoardManager::update_board(int r, int c, bool player){
    system("cls");
    if(board[r][c] == " "){
        board[r][c] = player ?  "X" : "O";
        draw_board();
    }
}

int BoardManager::check_result(int r, int c){
    if(count_step(r, c, 0, 1) >= 4 || count_step(r, c, 1, 0) >= 4 || count_step(r, c, 1, -1) >= 4 || count_step(r, c, 1, 1) >= 4){
        game_over = true;
        if(board[r][c] == "X"){
            result1 = 1;
            result2 = -1;
            return 1; // X thắng
        }
        else{
            result1 = -1;
            result2 = 1;
            return -1; // O thắng
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j] == " ") return 2; // Chỉ cần còn 1 ô trống, game vẫn tiếp tục
        }
    }
    result1 = 0;
    result2 = 0;
    game_over = true;
    return 0; // Hòa
}

// Trả về các giá trị tương ứng với kết quả của từng người
pair<int, int> BoardManager::result(){
    return {result1, result2};
}

// Kiểm tra ô trống 
bool BoardManager::is_empty(int r, int c){
    return board[r][c] == " ";
}

// Kiểm tra ván đấu kết thúc chưa
bool BoardManager::check_over(){
    return game_over;
}

// Reset lại bàn cờ về ban đầu, trả giá trị kiểm tra kết thúc ván đấu về false
void BoardManager::reset_game(){
    game_over = false;
    board = vector<vector<string>>(BOARD_SIZE, vector<string>(BOARD_SIZE, " "));
}
 
// Truy suất số nước liên tiếp theo 1 hướng
int BoardManager::get_count_step(int r, int c, int rs, int cs){
    return count_step(r, c, rs, cs);
}

// Câc hàm truy suất từng ô 
void BoardManager::set_cell(int r, int c, const string& value){
    board[r][c] = value;
}

const string BoardManager::get_cell(int r, int c) const{
    if(r >= 0 && c >= 0 && r < BOARD_SIZE && c <BOARD_SIZE)
        return board[r][c];
    else return " ";
}

int BoardManager::is_blocked(int r, int c, int dr, int dc) {
    // Nếu ô hiện tại trống thì không bị chặn
    if (board[r][c] == " ") return 0;

    string current = board[r][c];
    
    // Kiểm tra đầu phía (dr, dc)
    int r_end = r, c_end = c;
    while (true) {
        r_end += dr;
        c_end += dc;
        // Nếu ra ngoài bàn cờ coi như bị chặn
        if (r_end < 0 || r_end >= BOARD_SIZE || c_end < 0 || c_end >= BOARD_SIZE) return 1;
        // Nếu gặp quân khác loại, nếu khác loại thì bị chặn, nếu là ô trống tức là không bị chặn
        if (board[r_end][c_end] != current) {
            return (board[r_end][c_end] == " ") ? 0 : 1;
        }
    }
}