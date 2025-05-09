#include "PlayerInfo.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iomanip>
PlayerInfo::PlayerInfo(){}
PlayerInfo::~PlayerInfo(){}

// Đọc dữ liệu từ file và lưu thông tin người chơi vào map players
void PlayerInfo::read_data(){
    ifstream file(filename); // Mở file ở chế độ đọc
    if(!file) return;
    string line, name;
    int w, d, l;
    // Đọc từng dòng trong file và tách lấy dữ liệu thành tên, thắng, hòa, thua
    while(getline(file, line)){
        istringstream iss(line); // Tách các giá trị từng dòng
        if(iss >> name >> w >> d >> l)
            players[name] = {w, d, l}; // Lưu thông tin vào map player với key là name và struct Info(chứa w, d, l) là value
    }
    file.close(); // Đóng file
}
// Khi khởi tạo obj,tiến hành đọc file và lấy thông tin
PlayerInfo::PlayerInfo(const string& file): filename(file){
    read_data();
}

// Ghi thông tin người chơi từ map vào file
void PlayerInfo::save_data(BoardManager& board){
    ofstream file(filename); // Mở file ở chế độ ghi, tạo file mới nếu chưa có
    for(auto& [name, p]: players){
        file << name << " " << p.win << " " << p.draw << " " << p.loss << endl;
    } // Duyệt qua từng phần tử trong map player và ghi thông tin vào file
    file.close(); // Đóng file
}

//Cập nhật dữ liệu người chơi
void PlayerInfo::update_player(BoardManager& board, const string& name, int result){
    if(players.find(name) == players.end()){
        players[name] = {0, 0, 0};
    } //Thêm người chơi mới nếu chưa tồn tại

    //Cập nhật kết quả các ván đấu cho map
    if(result == 1) players[name].win++;
    else if(result == 0) players[name].draw++;
    else players[name].loss++;
    save_data(board); // Gọi hàm để lưu thông tin từ map vào file
}

//Tính tỷ lệ thắng
double PlayerInfo::win_rate(const string& name){
    if(players.find(name)==players.end()) return 0;
    return (double)players[name].win/(players[name].win + players[name].draw + players[name].loss);
}

//Tìm kiếm đối thủ theo tỷ lệ thắng same same nhau
string PlayerInfo::find_player(const string& player1){
    if(players.find(player1) == players.end()){
        string player2;
        double min_rate = 1;
        for(auto& [name, p] : players){
            int total = p.win + p.draw + p.loss;
            if(total == 0) continue;
            double winrate = (double)p.win/total;
            if(winrate < min_rate){
                min_rate = winrate;
                player2 = name;
            }
        }
        return player2;
    } // Nếu là người chơi mới, tìm người có tỷ lệ thắng thấp nhất để ghép cặp

    Info p1 = players[player1]; // Gán struct số liệu trận đấu cho biến p1
    int total_games = p1.win + p1.draw + p1.loss;
    if(total_games == 0) return "";
    double winrate = (double)p1.win/total_games; //Tính tỷ lệ thắng
    string player2;
    double min_rate = 1;
    for(auto& [name, p] : players){
        if(name == player1) continue;
        int total = p.win + p.draw + p.loss;
        if(total == 0) continue;
        double rate = (double)p.win/total;
        //Tìm chênh lệch tỷ lệ thắng nhỏ nhất
        if(abs(rate - winrate) < min_rate){
            min_rate = abs(rate - winrate);
            player2 = name;
        }
    }
    return player2; //Trả về tên đối thủ được tìm thấy
}

void PlayerInfo::displayInfo(const string& name) {
    auto it = players.find(name); // Tìm kiếm người chơi theo tên
    if (it == players.end()) { // Nếu không tìm thấy
        cout << "Player '" << name << "' not found." << endl;
        return;
    }

    // Hiển thị thông tin người chơi với định dạng bảng
    cout << string(LEFT_PADDING, ' ') << "Player Information:" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
    cout << string(LEFT_PADDING, ' ') << "Name\tWin\tDraw\tLoss" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;

    const Info& p = it->second;
    cout << string(LEFT_PADDING, ' ') << name << "\t" << p.win << "\t" << p.draw << "\t" << p.loss << endl;

    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
}

// Xếp hạng theo tổng số ván đấu
void PlayerInfo::rank_by_total_games(){
    vector<pair<string, int>> ranking;
    for(auto& [name, p] : players){
        int total_games = p.win + p.draw + p.loss;
        ranking.push_back({name, total_games});
    }
    sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b){
        return a.second > b.second;
    });
    cout << string(LEFT_PADDING, ' ') << "Ranking by Total Games:" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
    cout << string(LEFT_PADDING, ' ') << "Rank\tName\tTotal Games" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;

    for(size_t i = 0; i < ranking.size(); i++){
        cout << string(LEFT_PADDING, ' ') << i+1 << "\t" << ranking[i].first << "\t" << ranking[i].second << endl;
    }
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
}

// Xếp hạng theo tỷ lệ thắng
void PlayerInfo::rank_by_win_rate(){
    vector<pair<string, double>> ranking;
    for(auto& [name, p] : players){
        int total_games = p.win + p.draw + p.loss;
        if(total_games == 0) continue;
        double winrate = (double)p.win/total_games;
        ranking.push_back({name, winrate});
    }
    sort(ranking.begin(), ranking.end(), [](const pair<string, double>& a, const pair<string, double>& b){
        return a.second > b.second;
    });
    cout << string(LEFT_PADDING, ' ') << "Ranking by Win Rate:" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
    cout << string(LEFT_PADDING, ' ') << "Rank\tName\tWin Rate" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;

    for(size_t i = 0; i < ranking.size(); i++){
        cout << string(LEFT_PADDING, ' ') << i+1 << "\t" << ranking[i].first << "\t" << fixed << setprecision(2) << ranking[i].second*100 << "%" << endl;
    }
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
}

void PlayerInfo::rank_by_total_points(){
    vector<pair<string, int>> ranking;
    for(auto& [name, p] : players){
        int total_points = p.win * 3 + p.draw;
        ranking.push_back({name, total_points});
    }
    sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b){
        return a.second > b.second;
    });
    cout << string(LEFT_PADDING, ' ') << "Ranking by Total Points:" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
    cout << string(LEFT_PADDING, ' ') << "Rank\tName\tTotal Points" << endl;
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;

    for(size_t i = 0; i < ranking.size(); i++){
        cout << string(LEFT_PADDING, ' ') << i+1 << "\t" << ranking[i].first << "\t" << ranking[i].second << endl;
    }
    cout << string(LEFT_PADDING, ' ') << "---------------------------------" << endl;
}