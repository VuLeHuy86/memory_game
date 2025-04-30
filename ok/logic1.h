#ifndef LOGIC1_H
#define LOGIC1_H

#include "sinhvien.h"
#include <SDL.h>
#include <vector>
#include "Card.h"
#include <string>

using namespace std;

// PHẦN 1
// truyền tham chiếu của con trỏ để thay đổi con trỏ
vector<Card> createShuffledCards(SDL_Renderer* renderer);

void calculateCardPositions(vector<Card> &cards);

void handleMouseClick(vector<Card>& cards, int mouseX, int mouseY, int &x);// hàm xử lí sự kiện

void handleCardFlipBack(vector<Card> &cards);

bool checkWin(const vector<Card> &cards);





// PHẦN 2
vector<sv> sortgpa(const vector<sv>& v);
vector<sv> sortage(const vector<sv>& v);
vector<sv> sortmsv(const vector<sv>& v);
vector<sv> sortlop(const vector<sv>& v);
vector<sv> alphabet(const vector<sv>& v);

string checkgpamax(const vector<sv>& v);
string checkgpamin(const vector<sv>& v);
string checkyoungest(const vector<sv>& v);
string checkoldest(const vector<sv>& v);
string checkreverseid(const vector<sv>& v);
string checkhighestclass(const vector<sv>& v);
string checkfirstname(const vector<sv>& v);
string checklastname(const vector<sv>& v);

vector<sv> scholarship(const vector<sv>& v);
vector<sv> notgraduate(const vector<sv>& v);



// HÀM HỖ TRỢ GIAO DIỆN PHẦN 2

void topline();
// hàm in ra dòng trên của bảng

void botline();
// hàm in ra dòng dưới của bảng

void adjust(string s, int x);
// hàm điều chỉnh độ rộng của bảng cho cân đối

void print(const vector<sv>& v, const vector<sv>& vv);
// tham số là 2 vector lưu ds thông tin svien, 1 cái là gốc để làm chuẩn, 1 cái cần ra ds sau khi sx

void createPart2(vector<sv>& v);
// hàm khởi tạo p2

void startPart2(int x, const vector<sv>& v);
// hàm chuẩn bị chơi p2

void ready ();
// hàm sẵn sàng

void deleteScreen();
// hàm xóa màn hình



// HÀM HỖ TRỢ VỀ LOGIC CHO PHẦN 2

int numofsuggest(int x);

string chuanhoa(const string& s);
// hàm chuẩn hóa để đưa tên svien lên trước họ và tên đệm sau đó thực hiện so sánh xâu kí tự

string chuanhoa2(const string& s);
//hàm chuẩn hóa để trả về tên svien sau khi đã thực hiện so sánh xong (đưa tên trở về vị trí cũ sau họ, đên đệm)

bool reversed(string s);
// hàm check xâu kí tự đối xứng

vector<int> listRandomnumber(int a, int b);
// hàm random trả về là a số trong khoảng từ 1 đến b (mỗi số tương ứng với 1 câu hỏi)

vector<sv> sortby(int x, const vector<sv>& v);
// hàm trả về 1 danh sách mới sau khi đã được sắp xếp theo tiêu chí nào đó (gợi ý)

void printQuestion (string s);
// hàm in ra 1 câu hỏi lên mh

string ans (int x, const vector<sv>& v);
// hàm đối chiếu đáp án người chơi nhập vào với kết quả của chương trình

bool check_update(string a, string b);
// hàm kiểm tra đáp án người chơi nhập vào để cập nhật

void checkkk(int i, int x, int y, const vector<sv> &v);

#endif // LOGIC1_H


















