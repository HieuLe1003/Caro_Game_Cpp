#include "Human.h"
#include<limits>
void Human::make_move(BoardManager & board, bool player){
    int r, c;
    do{
        while (true) {
            cin >> r;
    
            if (cin.fail()) { // Kiểm tra nếu nhập sai kiểu dữ liệu
                cin.clear(); // Xóa trạng thái lỗi của `cin`
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dữ liệu còn lại trong bộ đệm
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break; // Thoát vòng lặp nếu nhập đúng
            }
        }
        while (true) {
            cin >> c;
    
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
            } else {
                break;
            }
        }
        // Nhập ngoài phạm vi thì nhập lại
    if(r > 9 || c > 9 || r < 0 || c < 0 || !board.is_empty(r, c)){
        cout << string(LEFT_PADDING, ' ') << "Invalid choice! Please try again: ";
    }
    } while (r > 9 || c > 9 || r < 0 || c < 0 || !board.is_empty(r, c));
    board.set_last_move(r, c, player);
}