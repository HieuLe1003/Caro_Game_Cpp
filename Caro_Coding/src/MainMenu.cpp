#include "MainMenu.h"
MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}

void MainMenu::menu(){
    BoardManager board;
    Bot bot;
    Human human;
    PlayerInfo player_info("player_info.txt");
    Replay replay("replay.txt", board);
    int key0;
    intro();
    _getch(); // ấn một phím bất kỳ để vào game
    while (true) {
        system("cls");
        print_title("MAIN MENU");
        cout << string(LEFT_PADDING, ' ') << "1. Player vs Player (PvP)" << endl;
        cout << string(LEFT_PADDING, ' ') << "2. Player vs Bot (PvB)" << endl;
        cout << string(LEFT_PADDING, ' ') << "3. Player Information" << endl;
        cout << string(LEFT_PADDING, ' ') << "4. Replay Game" << endl;
        cout << string(LEFT_PADDING, ' ') << "5. Game Rules" << endl;
        cout << string(LEFT_PADDING, ' ') << "6. Exit" << endl;
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
        while (true) {
            cin >> key0;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        switch (key0) {
            case 1: PvP(board, human, player_info, replay); break;
            case 2: PvB(board, bot, human, player_info, replay); break;
            case 3: Show_Info(player_info); break;
            case 4: Replay_Game(replay); break;
            case 5:
                system("cls");
                print_title("GAME RULES");
                cout << string(LEFT_PADDING, ' ') << "1. The game is played on a 10x10 grid." << endl;
                cout << string(LEFT_PADDING, ' ') << "2. Players take turns placing their marks" << endl;
                cout << string(LEFT_PADDING, ' ') << "(X or O) in empty cells." << endl;
                cout << string(LEFT_PADDING, ' ') << "3. The first player to get 4 marks in a row" << endl;
                cout << string(LEFT_PADDING, ' ') << "(horizontally, vertically, or diagonally) wins." << endl;
                cout << string(LEFT_PADDING, ' ') << "4. If all cells are filled and no player has " << endl;
                cout << string(LEFT_PADDING, ' ') << "4 marks in a row, the game is a draw." << endl;
                cout << string(LEFT_PADDING, ' ') << "5. Players can choose to play against each" << endl;
                cout << string(LEFT_PADDING, ' ') << "other" << endl << endl;
                cout << string(LEFT_PADDING, ' ') << "Press any key to exit";
                _getch(); // Đợi người dùng nhấn phím
                system("cls");
                break;
            case 6:
                system("cls"); // Exit
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << string(LEFT_PADDING + 15, ' ') << "𝕋ℍ𝔸ℕ𝕂 𝕐𝕆𝕌 𝔽𝕆ℝ ℙ𝕃𝔸𝕐𝕀ℕ𝔾!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                exit(0); // Thoát chương trình
            default: cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl; 
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    }
}

void MainMenu::intro() {
    for (int i = 0; i < 5; i++)
    {
        cout << endl;
    }
    cout << R"(


                                             ██████╗  █████╗ ███╗   ███╗███████╗
                                            ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
                                            ██║  ███╗███████║██╔████╔██║█████╗  
                                            ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  
                                            ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
                                             ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
                                             ██████╗ █████╗ ██████╗  ██████╗    
                                            ██╔════╝██╔══██╗██╔══██╗██╔═══██╗   
                                            ██║     ███████║██████╔╝██║   ██║   
                                            ██║     ██╔══██║██╔══██╗██║   ██║   
                                            ╚██████╗██║  ██║██║  ██║╚██████╔╝   
                                             ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝    

                                                 ℙℝ𝔼𝕊𝕊 𝔸ℕ𝕐 𝕂𝔼𝕐 𝕋𝕆 𝕊𝕋𝔸ℝ𝕋
    )" << endl;
}

void MainMenu::print_title(const string& title) {
    cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
    cout << string(LEFT_PADDING, ' ') << "              " << title << endl;
    cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
}

void MainMenu::PvP(BoardManager& board, Human& human, PlayerInfo& player_info, Replay& replay) {
    string player1, player2;
    bool player = true;
    while(true){
        system("cls");
        print_title("PLAYER VS PLAYER (PvP)");
        cout << string(LEFT_PADDING, ' ') << "1. Play with Friend " << endl; //Chế độ 2 người chơi tự nhập tên và chơi với nhau
        cout << string(LEFT_PADDING, ' ') << "2. Quick Match " << endl; //Chế độ tìm kiếm người chơi có  tỷ lệ thắng gần nhất với mình
        cout << string(LEFT_PADDING, ' ') << "3. Back to Main Menu" << endl;
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
        int key1;
        while (true) {
            cin >> key1;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        system("cls");
        print_title("PLAYER VS PLAYER (PvP)");
        switch (key1) {
            case 1: { // Play with Friend
                cout << string(LEFT_PADDING, ' ') << "Enter Player 1 Name: ";
                cin >> player1;
                cout << string(LEFT_PADDING, ' ') << "Enter Player 2 Name: ";
                cin >> player2;
                system("cls");
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                if(player1 == player2) {
                    cout << string(LEFT_PADDING, ' ') << "Player names cannot be the same!" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    break;
                }
                else {
                cout << string(LEFT_PADDING + 15, ' ') << player1 << " vs " << player2 << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                }
                board.reset_game();
                board.draw_board();
                while(true){
                    if(player) cout << string(LEFT_PADDING, ' ') << player1 << "'s turn (X): ";
                    else cout << string(LEFT_PADDING, ' ') << player2 << "'s turn (O): ";
                    human.make_move(board, player);
                    board.update_board(board.get_last_move(player).first, board.get_last_move(player).second, player);
                    replay.save_move(board.get_last_move(player));
                    int result = board.check_result(board.get_last_move(player).first, board.get_last_move(player).second);
                    if(result != 2){
                        if (result == 1) {
                            cout << string(LEFT_PADDING, ' ') << player1 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            player_info.update_player(board ,player2, board.result().second);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        } else if (result == -1) {
                            cout << string(LEFT_PADDING, ' ') << player2 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            player_info.update_player(board ,player2, board.result().second);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        } else if (result == 0) {
                            cout << string(LEFT_PADDING, ' ') << "It's a draw!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        }
                    }
                    player = !player; // Chuyển lượt
                }
                break;
            }
            case 2: { // Quick Match
                cout << string(LEFT_PADDING, ' ') << "Enter Player Name: ";
                cin >> player1;
                player2 = player_info.find_player(player1);
                if(player2.empty()) {
                    cout << string(LEFT_PADDING, ' ') << "No suitable player found for quick match." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    break;
                }
                cout << string(LEFT_PADDING, ' ') << "Found player: " << player2 << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << string(LEFT_PADDING + 15, ' ') << player1 << " vs " << player2 << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                board.reset_game();
                board.draw_board();
                while(true){
                    if(player) cout << string(LEFT_PADDING, ' ') << player1 << "'s turn (X): ";
                    else cout << string(LEFT_PADDING, ' ') << player2 << "'s turn (O): ";
                    human.make_move(board, player);
                    board.update_board(board.get_last_move(player).first, board.get_last_move(player).second, player);
                    replay.save_move(board.get_last_move(player));
                    int result = board.check_result(board.get_last_move(player).first, board.get_last_move(player).second);
                    if(result != 2){
                        if (result == 1) {
                            cout << string(LEFT_PADDING, ' ') << player1 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            player_info.update_player(board ,player2, board.result().second);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        } else if (result == -1) {
                            cout << string(LEFT_PADDING, ' ') << player2 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            player_info.update_player(board ,player2, board.result().second);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        } else if (result == 0) {
                            cout << string(LEFT_PADDING, ' ') << "It's a draw!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            player_info.update_player(board ,player2, board.result().second);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, player2);
                            break;
                        }
                    }
                    player = !player; // Chuyển lượt
                }
                break;
            }
            case 3:
                return; // Quay lại menu chính
            default:
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
        }
    }
}

void MainMenu::PvB(BoardManager& board, Bot& bot, Human& human, PlayerInfo& player_info, Replay& replay){
    while(true){
        system("cls");
        print_title("PLAYER VS BOT (PvB)");
        cout << string(LEFT_PADDING, ' ') << "1. Enter Player Name" << endl;
        cout << string(LEFT_PADDING, ' ') << "2. Back to Main Menu" << endl;
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
        int key1;
        while (true) {
            cin >> key1;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        switch (key1)
        {
        case 1:{
            system("cls");
            print_title("PLAYER VS BOT (PvB)");
            cout << string(LEFT_PADDING, ' ') << "Enter Player Name: ";
            string player1;
            cin >> player1;
            int key2;
            while(true){
                system("cls");
                print_title("SELECT BOT DIFFICULTY");
                cout << string(LEFT_PADDING, ' ') << "1. Easy" << endl;
                cout << string(LEFT_PADDING, ' ') << "2. Normal" << endl;
                cout << string(LEFT_PADDING, ' ') << "3. Hard" << endl;
                cout << string(LEFT_PADDING, ' ') << "4. Back" << endl;
                cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
                cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
                while (true) {
                    cin >> key2;
            
                    if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                        cin.clear(); // Xóa trạng thái lỗi của `cin`
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                        cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
                    } else {
                        break; // Thoát vòng lặp nếu nhập đúng
                    }
                }
                if(key2 == 4) break; // Quay lại menu chính
                else if(key2 < 1 || key2 > 3){
                    cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    continue;
                }
                else bot.set_level(key2); // Cài đặt độ khó cho bot
                system("cls");
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << string(LEFT_PADDING + 15, ' ') << player1 << " vs Bot" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                board.reset_game();
                board.draw_board();
                while(true){
                    cout << string(LEFT_PADDING, ' ') << player1 << "'s turn (X): ";
                    human.make_move(board, true);
                    board.update_board(board.get_last_move(true).first, board.get_last_move(true).second, true);
                    replay.save_move(board.get_last_move(true));
                    int result = board.check_result(board.get_last_move(true).first, board.get_last_move(true).second);
                    if(result != 2){
                        if (result == 1) {
                            cout << string(LEFT_PADDING, ' ') << player1 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, "Bot");
                            break;
                        } else if (result == -1) {
                            cout << string(LEFT_PADDING, ' ') << "Bot wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, "Bot");
                            break;
                        } else if (result == 0) {
                            cout << string(LEFT_PADDING, ' ') << "It's a draw!" << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                        }
                    }
                    cout << string(LEFT_PADDING, ' ') << "Bot's turn (O): ";
                    bot.make_move(board, false);
                    board.update_board(board.get_last_move(false).first, board.get_last_move(false).second, false);
                    replay.save_move(board.get_last_move(false));
                    result = board.check_result(board.get_last_move(false).first, board.get_last_move(false).second);
                    if(result != 2){
                        if (result == 1) {
                            cout << string(LEFT_PADDING, ' ') << player1 << " wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, "Bot");
                            break;
                        } else if (result == -1) {
                            cout << string(LEFT_PADDING, ' ') << "Bot wins!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, "Bot");
                            break;
                        } else if (result == 0) {
                            cout << string(LEFT_PADDING, ' ') << "It's a draw!" << endl;
                            player_info.update_player(board ,player1, board.result().first);
                            this_thread::sleep_for(chrono::seconds(2));
                            choice_replay(replay, player1, "Bot");
                            break;
                        }
                    }
                }
            }
            }
            break;
        case 2:
            return;
        default:
            system("cls");
            print_title("PLAYER VS BOT (PvP)");
            cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            break;
        }
    }
}

void MainMenu::Show_Info(PlayerInfo& player_info){
    while (true)
    {
        system("cls");
        print_title("PLAYER INFORMATION");
        cout << string(LEFT_PADDING, ' ') << "1. Rank by Total Games" << endl;
        cout << string(LEFT_PADDING, ' ') << "2. Rank by Win Rate" << endl;
        cout << string(LEFT_PADDING, ' ') << "3. Rank by Total Points" << endl;
        cout << string(LEFT_PADDING, ' ') << "4. Search Player" << endl;
        cout << string(LEFT_PADDING, ' ') << "5. Back to Main Menu" << endl;
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
        int key1;
        while (true) {
            cin >> key1;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        switch (key1) {
            case 1: 
                system("cls");
                player_info.rank_by_total_games(); 
                cout << string(LEFT_PADDING, ' ') << "Press any key to exit.";
                _getch(); // Đợi người dùng nhấn phím
                system("cls");
                break;
            case 2: 
                system("cls");
                player_info.rank_by_win_rate(); 
                cout << string(LEFT_PADDING, ' ') << "Press any key to exit.";
                _getch(); // Đợi người dùng nhấn phím
                system("cls");
                break;
            case 3: 
                system("cls");
                player_info.rank_by_total_points(); 
                cout << string(LEFT_PADDING, ' ') << "Press any key to exit.";
                _getch(); // Đợi người dùng nhấn phím
                system("cls");
                break;
            case 4: {
                string name;
                system("cls");
                print_title("SEARCH PLAYER");
                cout << string(LEFT_PADDING, ' ') << "Enter Player Name: ";
                cin >> name;
                system("cls");
                player_info.displayInfo(name);
                cout << string(LEFT_PADDING, ' ') << "Press any key to exit.";
                _getch(); // Đợi người dùng nhấn phím
                system("cls");
                break;
            }
            case 5: return; // Quay lại menu chính
            default:
                system("cls");
                print_title("PLAYER INFORMATION");
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                break;
        }
    }
    
}

void MainMenu::Replay_Game(Replay& replay){
    while (true)
    {
        system("cls");
        print_title("REPLAY GAME");
        replay.load_game();
        const vector<string>& games = replay.get_games();
        if (games.empty()) {
            cout << string(LEFT_PADDING, ' ') << "No games available for replay." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            return;
        }
        for (int i = 0; i < games.size(); i++) {
            cout << string(LEFT_PADDING, ' ') << i + 1 << ". " << games[i] << endl;
        }
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "1. Enter the game number to replay" << endl;
        cout << string(LEFT_PADDING, ' ') << "2. Back to Main Menu" << endl;
        cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
        cout << string(LEFT_PADDING, ' ') << "Enter your choice: ";
        int key1;
        while (true) {
            cin >> key1;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        switch (key1)
        {
        case 1:
            system("cls");
            print_title("REPLAY GAME");
            for (int i = 0; i < games.size(); i++) {
                cout << string(LEFT_PADDING, ' ') << i + 1 << ". " << games[i] << endl;
            }
            cout << string(LEFT_PADDING, ' ') << "==========================================" << endl;
            cout << string(LEFT_PADDING, ' ') << "Enter the game number to replay: ";
            int index;
            while (true) {
                cin >> index;
        
                if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                    cin.clear(); // Xóa trạng thái lỗi của `cin`
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                    cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
                } else {
                    break; // Thoát vòng lặp nếu nhập đúng
                }
            }
            if(index < 1 || index > games.size()) {
                cout << string(LEFT_PADDING, ' ') << "Invalid game number." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            } else replay.replay_game(index - 1);
            break;
        case 2:
            return;
        default:
            system("cls");
                print_title("REPLAY GAME");
            cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            break;
        }
        
    }
    
}

void MainMenu::choice_replay(Replay& replay, const string& player1, const string& player2){
    cout << string(LEFT_PADDING, ' ') << "Do you want to save the replay of the match (Y/N)? ";
    char choice;
    while (true) {
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            replay.save_game(player1, player2);
            break; // Thoát vòng lặp sau khi lưu replay
        } else if (choice == 'N' || choice == 'n') {
            replay.moves_clear(); // Xóa dữ liệu replay
            break; // Thoát vòng lặp
        } else {
            cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please enter Y or N: ";
        }
    }
}