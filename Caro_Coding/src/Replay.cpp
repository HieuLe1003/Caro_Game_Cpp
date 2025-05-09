#include "Replay.h"
#include<fstream>
#include<thread>
#include<chrono>
#include<conio.h>
#include<ctime>

Replay::Replay(const string& file, BoardManager& b): filename(file), board(b){
    load_game();
}

Replay::~Replay(){}

//Hàm lưu một nước đi (tọa độ) vào vector moves
void Replay::save_move(const pair<int, int>& move){
    moves.push_back(move);
}

void Replay::save_game(const string& player1, const string& player2){
    time_t now = time(0);//lấy thời gian thực
    tm*local_time = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time); //Định dạng thời gian thành chuỗi
    string game_name = player1 + "(X) vs " + player2 + "(O) (" + time_str + ")";
    ofstream file(filename, ios::app); // Mở file ở chế độ ghi thêm
    if(!file){
        cerr << "Can't open file" << endl; //Hiển thị thông báo lỗi nếu không mở được file
        return;
    }
    file << game_name << endl; //Ghi tên ván đấu vào file
    for(const auto& move: moves){
        file << move.first << " " << move.second << endl;
    } //Ghi lần lượt các nước đi vào file
    file << "___" << endl; //Đánh dấu kết thúc game
    file.close(); //Đóng file
    moves.clear(); //Xóa danh sách các nước đi trong vector moves sau khi đã lưu
}

// Mở file để lấy danh sách trận đấu và lưu vào vector games
void Replay::load_game(){
    ifstream file(filename); //Mở file chế độ chỉ đọc
    if(!file){
        cerr << "Can't open file" << endl; //Thông báo lỗi nếu không mở được file
        return; //Thoát hàm
    }
    string line;
    games.clear(); //Xóa dữ liệu cũ trong vector
    while(getline(file, line)){
        if(line.find(" vs ") != string::npos){
            games.push_back(line);
        }
    } //Tìm kiếm tên trận đấu (có chữ "vs") và lưu vào vector games
    file.close(); //Đóng file
}

//Phát lại 1 ván đấu
void Replay::replay_game(int index){
    if(index < 0 || index >= games.size()){
        cout << string(LEFT_PADDING, ' ') << "Invalid index" << endl;
        return; //Hiện thông báo lỗi và thoát nếu nhập giá trị không hợp lệ
    }
    string game_info = games[index];
    size_t vs_pos = game_info.find(" vs ");
    if (vs_pos == string::npos) {
        cerr << string(LEFT_PADDING, ' ') << "Invalid game format" << endl;
        return; // Thoát nếu định dạng không hợp lệ
    }
    // Tách tên người chơi 1 và loại bỏ phần "(X)"
    string player1 = game_info.substr(0, vs_pos);
    player1 = player1.substr(0, player1.find(" ("));

    // Tách tên người chơi 2 và loại bỏ phần "(O)"
    string player2 = game_info.substr(vs_pos + 4);
    player2 = player2.substr(0, player2.find(" ("));
    ifstream file(filename); //Mở file ở chế độ đọc
    if(!file){
        cerr << string(LEFT_PADDING, ' ') << "Can't open file" << endl;
        return;//Hiện thông báo và thoát nếu không mở được file
    }
    cout << string(LEFT_PADDING, ' ') << "Replaying game: " << games[index] << endl;
    string line;
    int i = -1;
    moves.clear(); //Xóa danh sách các nước đi cũ
    while(getline(file, line)){
        if(line.find(" vs ") != string::npos)
            i++; //Tăng i cho đến khi tìm được trận đấu cần replay
        if(i == index){
            if(line == "___") break; // Kết thúc trận đấu
            if(line.find(" vs ") == string::npos){
                int r, c;
                sscanf(line.c_str(), "%d %d", &r, &c); // chuyển đổi chuỗi thành pair<int, int>
                moves.push_back({r, c});
            } //Nếu là dòng chứa các nước đi thì lưu nước đi vào moves
        }
    }
    file.close(); //Đóng file
    board.reset_game(); //Reset bàn cờ trước khi replay
    control_replay(player1, player2); // Replay trận đấu
    moves.clear(); //Xóa danh sách các nước đi sau khi replay xong
}

//Hàm điều khiển việc phát lại trận đấu
void Replay::control_replay(const string& player1, const string& player2) {
    int i = 0;//Chỉ số của nước đi
    bool pause = false; //Biến biểu diễn trạng thái Pause/Play
    bool draw = true; //Biến kiểm soát việc vẽ lại bàn cờ
    auto last_move_time = chrono::steady_clock::now(); //Lưu thời gian của nước đi cuối cùng để tính khoảng thời gian giữa các nước đi

    //Vòng lặp chạy cho đến khi hết nước đi
    //Trong vòng lặp chương trình xử lý các sự kiện nhập từ bàn phím và cập nhật trạng thái bàn cờ
    while (i <= moves.size()) {
        // Xử lý input
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') {
                pause = !pause; //Chuyển đổi trạng thái pause/play khi ấn space từ bàn phím
                draw = true; //Yêu cầu vẽ lại bàn cờ
                last_move_time = chrono::steady_clock::now(); // Reset timer
            }
            else if (key == -32) { //Phím mũi tên
                key = _getch();
                if (key == 77 && i < moves.size()) { // Right arrow - Next
                    i++; //Tăng nước đi hiện tại
                    draw = true; //Yêu cầu vẽ lại bàn cờ
                    last_move_time = chrono::steady_clock::now(); // Reset timer
                }
                else if (key == 75 && i > 0) { // Left arrow - Prev
                    i--; //Giảm i để quay lại nước đi trước đó
                    draw = true;//Yêu cầu vẽ lại bàn cờ
                    last_move_time = chrono::steady_clock::now(); // Reset timer
                }
            }
        }

        // Cập nhật bàn cờ sau mỗi nước đi hoặc khi ấn phím điều khiển
        if (draw && i <= moves.size()) {
            board.reset_game(); //Reset lại bàn cờ
            
            // Đánh lại tất cả các nước đi đến thời điểm hiện tại
            for (int j = 0; j < i; j++) {
                pair<int, int> move = moves[j];
                string player = j % 2 == 0 ? "X" : "O";
                board.set_cell(move.first, move.second, player);
            }

            system("cls");
            board.draw_board(); //Vẽ lại bảng
            
            //Hiện thông tin về nước đi
            if (i < moves.size()) {
                string current_player = i % 2 == 0 ? player1 : player2;
                cout << string(LEFT_PADDING, ' ') << current_player << " move " << i + 1 << " [" 
                     << moves[i].first << ", " 
                     << moves[i].second << "]" << endl;
            } else {
                cout << string(LEFT_PADDING, ' ') << "End of game" << endl;
                break;
            } //Hiện thông báo khi kết thúc replay

            if (pause) {
                cout << string(LEFT_PADDING, ' ') << "Game paused" << endl;
            } //Hiện thông báo khi ấn pause

            draw = false; //Đặt lại biến draw để tránh vẽ lại liên tục
        }

        // Tự động chạy nếu không pause và đã đủ 2 giây
        if (!pause && i < moves.size()) {
            auto now = chrono::steady_clock::now(); //Lấy thời gian hiện tại
            //Tính khoảng thời gian đã trôi qua kể từ lần phát lại cuối cùng
            //Chuyển thời gian vừa tính được sang đơn vị mili giây
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - last_move_time).count();
            
            if (elapsed >= 2000) { // Đợi đủ 2 giây
                i++; //Tăng chỉ số nước đi
                draw = true; //Cập nhật lại bảng
                last_move_time = now; // Reset timer
            }
        }
        
        // Tránh CPU usage cao bằng cách tạm dừng vòng lặp trong 100ms
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << string(LEFT_PADDING, ' ') << "Press any key to exit" << endl;
    _getch();
    system("cls");
}

vector<string> Replay::get_games(){
    return games;
}

void Replay::moves_clear(){
    moves.clear();
}