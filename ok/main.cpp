#include <iostream>
#include <fstream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include "sinhvien.h"
#include "logic1.h"
#include "graphic.h"
#include "game.h"

using namespace std;

int main (int argc, char* argv[]) {
    if (!init(window, renderer)) {
        return -1;
    }

    setupMenuButtons(playButton, introButton, backButton, menuBackground, textHelp, renderer);

    mainloop(renderer, window, background, state);

    close(window, renderer, menuBackground);

    cout << "ban da ket thuc phan 1 voi tong so luot lat the la: " << count << endl;
    ready();

    // vector chứa các svien + thông tin( ban đầu rỗng)
    vector<sv> v;

    createPart2(v);
    ready();

    // hàm bắt đầu chơi và đưa ra gợi ý dựa trên số lượt gợi ý mà người chơi nhận được sau khi kết thúc p1, ở đây giả sử người chơi có 3 lượt
    startPart2(numofsuggest(count), v);
    ready();

    // bắt đầu chơi phần 2;
    // sử dụng cấp phát động để lưu tất cả các câu hỏi
    string* arr = new string[10];
    ifstream file("cauhoi.txt");
    string line;
    int i = 0;
    while(getline(file, line) && i < 10) {
        arr[i] = line; // arr[i] = *(arr + i)
        i ++;
    }

    // hàm random 5 số trong 10 số tương ứng với 5 câu hỏi bất kì trong 10 câu hỏi
    vector<int> vv = listRandomnumber(5, 10);

    // vòng lặp chính của game, in ra câu hỏi, người chơi nhập vào, kiểm tra kết quả, cập nhật điểm tích lũy
    for (int i = 0; i < vv.size(); i ++) {
        printQuestion(arr[vv[i] - 1]);
        deleteScreen();
        int x = vv.size() - 1;
        check_update(i, vv[i], x, v); // chỉ số i hiện tại, số của vv[i], vv.size() - 1, vector v
    }

    // kết thúc trò chơi và giải phóng vùng nhớ được cấp phát động để lưu câu hỏi
    delete[] arr;

    return 0;
}
