#include "Bot.h"
#include<climits>
#include<algorithm>
Bot::Bot(){}
Bot::Bot(int lv): level(lv){}
Bot::~Bot(){}

// Hàm khởi tạo cấp độ cho bot
void Bot::set_level(int lv){
    level = lv;
}

// Tìm các ô có ít nhất 1 quân bên cạnh
bool Bot::around(BoardManager& board, int r, int c){
    // Kiểm tra các ô xung quanh (8 ô) xem có quân nào không
    // Nếu có quân bên cạnh thì trả về true, ngược lại false
    for (int rs = -1; rs <= 1; rs++)
    {
        for (int cs = -1; cs <= 1; cs++)
        {
            if(rs == 0 && cs == 0) continue;
            int rss = r + rs, css = c + cs;
            if(rss >= 0 && css >= 0 && rss < BOARD_SIZE && css < BOARD_SIZE && !board.is_empty(rss, css))
                return true; // Có quân bên cạnh
        }
    }
    return false; // Không có quân bên cạnh
}

// hàm lưu trữ các nước đi khả thi và sắp xếp theo điểm số
vector<pair<int, int>> Bot::move_ordering(BoardManager& board) {
    // vector lưu trữ các nước đi khả thi
    vector<pair<int, int>> moves;
    // vector lưu trữ điểm số tương ứng với các nước đi
    vector<pair<int, pair<int, int>>> scored_moves;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j) && around(board, i, j)) {
                int score = evaluate(board);
                scored_moves.push_back({score, {i, j}});
            }
        }
    }
    
    // Sắp xếp nước đi từ cao -> thấp để cắt nhánh tốt hơn
    sort(scored_moves.rbegin(), scored_moves.rend());
    
    for (auto &move : scored_moves) {
        moves.push_back(move.second);
    }

    return moves;
}

// Hàm đánh giá điểm số bàn cờ cho từng ô trong bàn cờ
int Bot::evaluate(BoardManager& board) {
    int score = 0;
    int rs[] = {0, 1, 1, -1};
    int cs[] = {1, 0, 1, 1};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.get_cell(i, j) == "O") {
                for (int d = 0; d < 4; d++) {
                    int count = board.get_count_step(i, j, rs[d], cs[d]);
                    int block1 = board.is_blocked(i, j, rs[d], cs[d]);
                    int block2 = board.is_blocked(i, j, -rs[d], -cs[d]);
                    int block_status = block1 + block2;
                    if (count == 4) score += 10000;  // Chuỗi 4 quân thắng ngay
                    else if (count == 3 && block_status == 0) score += 5000;  // Chuỗi 3 quân hở 2 đầu
                    else if (count == 3 && block_status == 1) score += 1000;  // Chuỗi 3 quân chặn 1 đầu
                    else if (count == 2 && block_status == 0) score += 500;  // Chuỗi 2 quân hở 2 đầu
                    else if (count == 2 && block_status == 1) score += 100;  // Chuỗi 2 quân chặn 1 đầu
                }
            }

            if (board.get_cell(i, j) == "X") {  // Điểm cho người chơi
                for (int d = 0; d < 4; d++) {
                    int count = board.get_count_step(i, j, rs[d], cs[d]);
                    int block1 = board.is_blocked(i, j, rs[d], cs[d]);
                    int block2 = board.is_blocked(i, j, -rs[d], -cs[d]);
                    int block_status = block1 + block2;
                    if (count == 4) score -= 10000;  // Chuỗi 4 quân thắng ngay
                    else if (count == 3 && block_status == 0) score -= 5000;  // Chuỗi 3 quân hở 2 đầu
                    else if (count == 3 && block_status == 1) score -= 1000;  // Chuỗi 3 quân chặn 1 đầu
                    else if (count == 2 && block_status == 0) score -= 500;  // Chuỗi 2 quân hở 2 đầu
                    else if (count == 2 && block_status == 1) score -= 100;  // Chuỗi 2 quân chặn 1 đầu
                }
            }
        }
    }
    return score;
}

// Thuật toán Minimax kết hợp cắt nhánh alpha-beta
int Bot::minimax(BoardManager& board, int depth, bool player, int alpha, int beta){
    int score = evaluate(board);

    // Nếu bot thắng hoặc người chơi thắng hoặc độ sâu = 0 thì trả về điểm số
    if(score >= 10000 || score <= -10000 || depth == 0) return score;

    // Vector lưu trữ các nước đi khả thi được sắp xếp theo điểm số giảm dần
    vector<pair<int, int>> moves = move_ordering(board);

    // Trả về 0 điểm nếu không còn nước đi nào khả thi (hòa)
    if (moves.empty()) {
        return 0;  // Trạng thái hòa
    }
    if(player == false){
        int bestscore = INT_MIN; // khởi tạo bestscore cho bot là giá trị nhỏ nhất

            // Duyệt qua các nước đi khả thi
            // Nếu ô trống thì bot đánh thử vào ô đó
            // Gọi hàm minimax đệ quy để tìm điểm số cho nước đi đó và cập nhật bestscore
            // Trả lại nước đi vừa đánh về ô trống
            // Cập nhật alpha và beta
            // Nếu beta <= alpha thì dừng duyệt các nước đi còn lại
            // Trả về bestscore cho bot
            for (auto [i, j] : moves)
            {
                if(board.is_empty(i, j)){
                    board.set_cell(i, j, "O");
                    bestscore = max(bestscore, minimax(board, depth - 1, true, alpha, beta));
                    board.set_cell(i, j, " ");
                    alpha = max(alpha, bestscore);
                    if(beta <= alpha) break;
                }
            }
        return bestscore;
    }
    else{
        int bestscore = INT_MAX; // khởi tạo giá trị bestscore cho người chơi là giá trị lớn nhất

            // Duyệt qua các nước đi khả thi
            // Nếu ô trống thì mô phỏng người chơi đánh thử vào ô đó
            // Gọi hàm minimax đệ quy để tìm điểm số cho nước đi đó và cập nhật bestscore
            // Trả lại nước đi vừa đánh về ô trống
            // Cập nhật alpha và beta
            // Nếu beta <= alpha thì dừng duyệt các nước đi còn lại
            // Trả về bestscore của người chơi
            for (auto [i, j] : moves)
            {
                if(board.is_empty(i, j)){
                    board.set_cell(i, j, "X");
                    bestscore = min(bestscore, minimax(board, depth -1, false, alpha, beta));
                    board.set_cell(i, j, " ");
                    beta = min(beta, bestscore);
                    if(beta <= alpha) break;
                }
            }
    return bestscore;
    } 
}

pair<int, int> Bot::easy_level(BoardManager& board) {
    // Ưu tiên thắng ngay nếu có thể
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                board.set_cell(i, j, "O");
                if (board.check_result(i, j) == -1) { // Bot thắng
                    board.set_cell(i, j, " ");
                    return {i, j};
                }
                board.set_cell(i, j, " ");
            }
        }
    }

    // Chặn nước thắng của đối thủ
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                board.set_cell(i, j, "X");
                if (board.check_result(i, j) == 1) { // Người chơi thắng
                    board.set_cell(i, j, " ");
                    return {i, j};
                }
                board.set_cell(i, j, " ");
            }
        }
    }

    // Ưu tiên tạo chuỗi 2 hoặc chặn chuỗi 2 của đối thủ
    int rs[] = {0, 1, 1, -1};
    int cs[] = {1, 0, 1, 1};
    
    // ưu tiên chặn nước 2 hở của địch
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                for (int d = 0; d < 4; d++) {
                    board.set_cell(i, j, "X");
                    int count = board.get_count_step(i, j, rs[d], cs[d]);
                    int block1 = board.is_blocked(i, j, rs[d], cs[d]);
                    int block2 = board.is_blocked(i, j, -rs[d], -cs[d]);
                    board.set_cell(i, j, " ");
                    
                    if (count >= 3 && (block1 + block2) == 0) {
                        return {i, j};
                    }
                }
            }
        }
    }
    // Tìm nước tạo chuỗi 2 hở cho bot
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                for (int d = 0; d < 4; d++) {
                    board.set_cell(i, j, "O");
                    int count = board.get_count_step(i, j, rs[d], cs[d]);
                    int block1 = board.is_blocked(i, j, rs[d], cs[d]);
                    int block2 = board.is_blocked(i, j, -rs[d], -cs[d]);
                    board.set_cell(i, j, " ");
                    
                    if (count >= 3 && (block1 + block2) < 2) {
                        return {i, j};
                    }
                }
            }
        }
    }

    // Chọn ngẫu nhiên quanh các quân đã đánh
    vector<pair<int, int>> around_move;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j) && around(board, i, j)) {
                around_move.push_back({i, j});
            }
        }
    }
    
    if (!around_move.empty()) {
        return around_move[rand() % around_move.size()];
    }

    // Dự phòng: chọn ngẫu nhiên nếu không tìm được nước tốt
    int r, c;
    do {
        r = rand() % BOARD_SIZE;
        c = rand() % BOARD_SIZE;
    } while (!board.is_empty(r, c));
    return {r, c};
}

pair<int, int> Bot::normal_level(BoardManager& board){
    int bestscore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    vector<pair<int, int>> moves = move_ordering(board);
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board.is_empty(i, j)){
                board.set_cell(i, j, "O");
                if (board.check_result(i, j) == -1)
                {
                    board.set_cell(i, j, " ");
                    return {i, j};
                }
                board.set_cell(i, j, " ");
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                board.set_cell(i, j, "X");
                if (board.check_result(i, j) == 1) {  // Kiểm tra nếu đối thủ thắng
                    board.set_cell(i, j, " ");
                    return {i, j};  // Trả về nước đi chặn đối thủ
                }
                board.set_cell(i, j, " ");
            }
        }
    }
    for (auto [i, j] : moves)
    {
        if (board.is_empty(i, j))
        {
            board.set_cell(i, j, "O");
            int moveScore = minimax(board, 2, true, INT_MIN, INT_MAX);
            board.set_cell(i, j, " ");
            if(moveScore > bestscore){
                bestscore = moveScore;
                bestMove = {i, j};
            }
        }
    }
    return bestMove;
}
pair<int, int> Bot::hard_level(BoardManager& board){
    
    // Kiểm tra xem có thể thắng ngay không
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board.is_empty(i, j)){
                board.set_cell(i, j, "O");
                if (board.check_result(i, j) == -1)
                {
                    board.set_cell(i, j, " ");
                    return {i, j};
                }
                board.set_cell(i, j, " ");
            }
        }
    }

    // Kiểm tra xem có nước đi nào chặn đối thủ thắng không
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.is_empty(i, j)) {
                board.set_cell(i, j, "X");
                if (board.check_result(i, j) == 1) 
                {
                    board.set_cell(i, j, " ");
                    return {i, j};  // Trả về nước đi chặn đối thủ
                }
                board.set_cell(i, j, " ");
            }
        }
    }

    int bestscore = INT_MIN; // khởi tạo bestscore cho bot là giá trị nhỏ nhất
    pair<int, int> bestMove = {-1, -1}; // khởi tạo bestMove là -1, -1
    vector<pair<int, int>> moves = move_ordering(board);

    // Duyệt qua các nước đi khả thi và dùng minimax để tìm nước đi tốt nhất
    for (auto [i, j] : moves)
    {
        if (board.is_empty(i, j))
        {
            board.set_cell(i, j, "O");
            int moveScore = minimax(board, 3, true, INT_MIN, INT_MAX);
            board.set_cell(i, j, " ");
            if(moveScore > bestscore){
                bestscore = moveScore;
                bestMove = {i, j};
            }
        }
    }
    return bestMove;
}

void Bot::make_move(BoardManager& board, bool player) {
    pair<int, int> move;
    if (level == 1) {
        move = easy_level(board);
    } else if(level == 2){
        move = normal_level(board);
    } else{
        move = hard_level(board);
    }
    board.set_last_move(move.first, move.second, false);
}