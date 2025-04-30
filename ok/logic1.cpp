#include "logic1.h"
#include <SDL_image.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include <fstream>
#include <iomanip>
#include "graphic.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

// PHẦN 1

vector<Card> createShuffledCards(SDL_Renderer* renderer) {
    // tạo texture ảnh mặt sau cho tất cả các thẻ
    SDL_Texture* backTexture = LoadTexture("assets/back.png", renderer);

    // tạo 1 vector để lưu các texture ảnh mặt trước từ file ảnh.png để thực hiện tạo thẻ sau đó
    vector<SDL_Texture*> frontTextures;
    for (int i = 1; i <= 5; ++i) {
        string path = "assets/card" + to_string(i) + ".png";
        frontTextures.push_back(LoadTexture(path.c_str(), renderer));
    }

    vector<Card> cards;
    // mỗi i tương ứng với 1 ảnh mặt trước
    for (int i = 0; i < 5; ++i) {
        // mỗi ảnh mặt trước sẽ tạo ra 2 thẻ, có cùng id
        for (int j = 0; j < 2; ++j) {
            Card temp;
            temp.setFront(frontTextures[i]);
            temp.setBack(backTexture);
            temp.setId(i);
            cards.push_back(temp);
        }
    }

    // rand
    srand(static_cast<unsigned>(time(nullptr)));
    random_shuffle(cards.begin(), cards.end());

    return cards;
}

void calculateCardPositions(vector<Card> &cards) {
    int spacing = 10; // khoảng cách giữa mỗi thẻ là 10 pixel
    int columns = 5;
    int rows = ceil((double) cards.size() / columns); // ép kiểu nguyên trc khi chia và làm tròn lên

    for (int i = 0; i < cards.size(); ++i) {
        // tính chỉ số hàng và cột cho mỗi card cards[i];
        int row = i / columns;
        int col = i % columns;

        // tính tổng chiều rộng và chiều cao của các thẻ để căn giữa thuận tiện
        int totalWidth = columns * cards[i].getWidth() + (columns - 1) * spacing;
        int totalHeight = rows * cards[i].getHeight() + (rows - 1) * spacing;

        // tính tọa độ x và y để căn giữa
        int offsetX = (SCREEN_WIDTH - totalWidth) / 2;
        int offsetY = (SCREEN_HEIGHT - totalHeight) / 2;

        // cập nhật thông số mỗi thẻ (x,y,rộng,cao)
        SDL_Rect rect = {
            offsetX + col * (cards[i].getWidth() + spacing),
            offsetY + row * (cards[i].getHeight() + spacing),
            cards[i].getWidth(),
            cards[i].getHeight()
        };

        cards[i].setRect(rect);
    }
}



Card* firstFlippedCard = nullptr;
bool waitingToFlipBack = false;
Uint32 flipBackStartTime = 0;
int COUNT = 0;

void handleMouseClick(vector<Card>& cards, int mouseX, int mouseY, int &x) {
    if (waitingToFlipBack) return; // Đang chờ lật lại, không xử lý click

    // Kiểm tra số lượng thẻ đã lật lên (không tính thẻ đã matched)
    int flippedCount = 0;
    for (const Card& card : cards) {
        if (card.getCheck() && !card.getMatched()) {
            flippedCount++;
        }
    }

    // Nếu đã lật đủ 2 thẻ, không làm gì thêm
    if (flippedCount >= 2) return;

    // Dành cho trường hợp chưa lật được thẻ nào, hoặc lật thẻ thứ 2
    for (Card& card : cards) {
        if (!card.getCheck() && !card.getMatched()) {
            SDL_Rect rect = card.getRect();

            if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                mouseY >= rect.y && mouseY <= rect.y + rect.h) {

                card.setCheck(true);

                // Nếu là thẻ đầu tiên được lật trong turn
                if (firstFlippedCard == nullptr) {
                    firstFlippedCard = &card;
                    x ++;
                }
                // Nếu là thẻ thứ 2 được lật
                else {
                    if (firstFlippedCard->getId() == card.getId()) {
                        firstFlippedCard->setMatched(true);
                        card.setMatched(true);
                        firstFlippedCard = nullptr; // Reset thẻ đầu tiên
                    }
                    else {
                        waitingToFlipBack = true; // Đang chờ lật lại
                        flipBackStartTime = SDL_GetTicks(); // Ghi lại thời gian bắt đầu
                    }
                    x ++;
                }
                break; // Thoát vòng lặp sau khi lật xong thẻ
            }
        }
    }
}

void handleCardFlipBack(vector<Card>& cards) {
    if (waitingToFlipBack && SDL_GetTicks() - flipBackStartTime >= 1000) {
        for (auto& card : cards) {
            if (card.getCheck() && !card.getMatched()) {
                card.setCheck(false);
            }
        }
        firstFlippedCard = nullptr;
        waitingToFlipBack = false;
    }
}

bool checkWin(const vector<Card> &cards) {
    for (const Card &card : cards) {
        if (!card.getMatched()) return false;
    }
    return true;
}



// PHẦN 2

vector<sv> sortgpa(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getGpa() > ve[j + 1].getGpa()) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    return ve;
}

vector<sv> sortage(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            string temp1 = ve[j].getNgaysinh().substr(6, 4);
            string temp2 = ve[j + 1].getNgaysinh().substr(6, 4);
            string temp3 = ve[j].getNgaysinh().substr(3, 2);
            string temp4 = ve[j + 1].getNgaysinh().substr(3, 2);
            string temp5 = ve[j].getNgaysinh().substr(0, 2);
            string temp6 = ve[j + 1].getNgaysinh().substr(0, 2);
            if(temp1 < temp2 || (temp1 == temp2 && temp3 < temp4) || (temp1 == temp2 && temp3 == temp4 && temp5 < temp6)) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    return ve;
}

vector<sv> sortmsv(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getMsv() > ve[j + 1].getMsv()) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    return ve;
}

vector<sv> sortlop(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getLop().substr(4, 1) > ve[j + 1].getLop().substr(4, 1)) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    return ve;
}

vector<sv> alphabet(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa(ve[i].getTen()));
    }
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getTen() > ve[j + 1].getTen()) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa2(ve[i].getTen()));
    }
    return ve;
}

string checkgpamax (const vector<sv>& v) {
    double max = 0;
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() > max) {
            max = v[i].getGpa();
        }
    }
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() == max) {
            return v[i].getTen();
        }
    }
}

string checkgpamin(const vector<sv>& v) {
    double min = 5;
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() < min) {
            min = v[i].getGpa();
        }
    }
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() == min) {
            return v[i].getTen();
        }
    }
}

string checkyoungest(const vector<sv>& v) {
    string max = "0";
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getNgaysinh().substr(6, 4) > max) {
            max = v[i].getNgaysinh().substr(6, 4);
        }
    }
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getNgaysinh().substr(6, 4) == max) {
            return v[i].getTen();
        }
    }
}

string checkoldest(const vector<sv>& v) {
    string min = "2100";
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getNgaysinh().substr(6, 4) < min) {
            min = v[i].getNgaysinh().substr(6, 4);
        }
    }
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getNgaysinh().substr(6, 4) == min) {
            return v[i].getTen();
        }
    }
}

string checkreverseid(const vector<sv>& v) {
    for (int i = 0; i < v.size(); i ++) {
        if (doixung(v[i].getMsv())) {
            return v[i].getTen();
        }
    }
}

string checkhighestclass(const vector<sv>& v) {
    double max = 0;
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() > max) {
            max = v[i].getGpa();
        }
    }
    for (int i = 0; i < v.size(); i ++) {
        if (v[i].getGpa() == max) {
            return v[i].getLop();
        }
    }
}

string checkfirstname(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa(ve[i].getTen()));
    }
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getTen() > ve[j + 1].getTen()) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa2(ve[i].getTen()));
    }
    return ve[0].getTen();
}

string checklastname(const vector<sv>& v) {
    vector<sv> ve = v;
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa(ve[i].getTen()));
    }
    for (int i = 0; i < ve.size() - 1; i ++) {
        for (int j = 0; j < ve.size() - i - 1; j ++) {
            if(ve[j].getTen() > ve[j + 1].getTen()) {
                sv temp = ve[j];
                ve[j] = ve[j + 1];
                ve[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < ve.size(); i ++) {
        ve[i].setTen(chuanhoa2(ve[i].getTen()));
    }
    return ve[ve.size()-1].getTen();
}

vector<sv> scholarship(const vector<sv>& v) {
    vector<sv> temp;
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() >= 3.6) {
            temp.push_back(v[i]);
        }
    }
    return temp;
}

vector<sv> notgraduate(const vector<sv>& v) {
    vector<sv> temp;
    for (int i = 0; i < v.size(); i ++) {
        if(v[i].getGpa() < 2.0) {
            temp.push_back(v[i]);
        }
    }
    return temp;
}


void topline() {
    for (int i = 1; i <= 40; i ++) {
        if (i == 7) {
            cout << "Ten";
        }
        else if (i == 19) {
            cout << "Ngay sinh";
        }
        else if (i == 25) {
            cout << "MSV";
        }
        else if (i == 32) {
            cout << "Lop";
        }
        else if (i == 37) {
            cout << "GPA";
        }
        else cout << "-";
    }
    cout << endl;
}

void botline() {
    for (int i = 1; i <= 56; i ++) {
        cout << "-";
    }
    cout << endl << endl;
}

void modify(string s, int x) {
    int a = x - s.size();
    for (int i = 1; i <= a; i ++) {
        cout << " ";
    }
}

void print(const vector<sv>& v, const vector<sv>& vv) {
    // v là chuẩn

    // vector lưu tên các svien để tìm ra tên có độ dài lớn nhất
    vector<string> ve;
    for (int i = 0; i < v.size(); i ++) {
        ve.push_back(v[i].getTen());
    }

    int max = 0;
    for (int i = 0; i < ve.size(); i ++) {
        if(ve[i].size() > max) {
            max = ve[i].size();
        }
    }

    for (int i = 0; i < vv.size(); i ++) {
        cout << vv[i].getTen();
        modify(vv[i].getTen(), max);
        cout << " | " << vv[i].getNgaysinh() << " | " << vv[i].getMsv() << " | " << vv[i].getLop() << " | " << fixed << setprecision(2) << vv[i].getGpa() << " |" << endl;
    }
}

void khoitaoPart2(vector<sv>& v) {
    ifstream file("thongtin_sinhvien.txt");
    string temp;
    while(getline(file, temp)) {
        sv sinhvien;
        sinhvien.nhapthongtin(temp);
        v.push_back(sinhvien);
    }

    topline();
    print(v, v);
    botline();

    cout << "Tren day la danh sach thong tin cua 10 sinh vien" << endl;
    cout << "*LUU Y: khi nhap cau tra loi phai nhap day du ca ho va ten cua sinh vien" << endl;
}

void startPart2(int x, const vector<sv>& v) {
    // 1 set lưu x số khác nhau tương ứng với x gợi ý khác nhau random (số hóa mỗi gợi ý rồi random lưu vào 1 set)
    set<int> se;
    srand(static_cast<unsigned>(time(nullptr)));
    while(se.size() < x) {
        int random = rand() % 7 + 1;
        se.insert(random);
    }

    for (int x : se) {

        switch(x) {
            case 1:
                cout << "Duoi day la danh sach sinh vien da duoc sap xep theo alphabet:" << endl;
                break;
            case 2:
                cout << "Duoi day la danh sach sinh vien da duoc sap xep theo gpa tang dan:" << endl;
                break;
            case 3:
                cout << "Duoi day la danh sach sinh vien da duoc sap xep theo do tuoi tang dan:" << endl;
                break;
            case 4:
                cout << "Duoi day la danh sach sinh vien da duoc sap xep theo msv tang dan:" << endl;
                break;
            case 5:
                cout << "Duoi day la danh sach sinh vien da duoc sap xep theo lop tang dan:" << endl;
                break;
            case 6:
                cout << "Duoi day la danh sach sinh vien du dieu kien xet hoc bong(gpa >= 3.60):" << endl;
                break;
            case 7:
                cout << "Duoi day la danh sach sinh vien chua du dieu kien tot nghiep(gpa < 2.0):" << endl;
                break;
        }

        topline();
        print(v, sapxep(x, v));
        botline();

        }

        cout << "Tren day la " << x << " goi y ban nhan duoc truoc khi bat dau choi phan 2" << endl;
}

void ready () {
    cout << "De tiep duc nhap ok tu ban phim" << endl;
    string s;
    do {
        getline(cin, s);
        if (s != "ok") {
            cout << "Khong hop le!" << endl;
        }
    }while(s != "ok");
    cout << endl;
}

void xoamanhinh() {
    for (int i = 0; i <= 26; i ++) {
        cout << endl;
    }
}

int numofsuggest(int x) {
    if (x <= 20) return 5;
    else if (x <= 25) return 4;
    else if (x <= 30) return 3;
    else if (x <= 35) return 2;
    else if (x <= 45) return 1;
    else return 0;
}

string chuanhoa(const string& s) {
    vector<string> v;
    string word;
    stringstream ss(s);
    while(ss >> word) {
        v.push_back(word);
    }
    string temp = v[v.size()-1];
    for (int i = 0; i < v.size()-1; i ++) {
        temp += " ";
        temp += v[i];
    }
    return temp;
}

string chuanhoa2(const string& s) {
    vector<string> v;
    string word;
    stringstream ss(s);
    while(ss >> word) {
        v.push_back(word);
    }
    string temp;
    for (int i = 1; i < v.size(); i ++) {
        temp += v[i];
        temp += " ";
    }
    temp += v[0];
    return temp;
}

bool doixung(string s) {
    int left = 0, right = s.size() - 1;
    while (left <= right) {
        if(s[left] != s[right]) {
            return false;
        }
        left ++; right --;
    }
    return true;
}

vector<int> listRandomnumber(int a, int b) {
    set<int> se;
    srand(static_cast<unsigned>(time(nullptr)));
    while(se.size() < a) {
        int random = rand() % b + 1;
        se.insert(random);
    }
    vector<int> ve;
    for (int x : se) {
        ve.push_back(x);
    }
    return ve;
}

vector<sv> sapxep(int x, const vector<sv>& v) {
    switch(x) {
        case 1:
            return alphabet(v);
        case 2:
            return sortgpa(v);
        case 3:
            return sortage(v);
        case 4:
            return sortmsv(v);
        case 5:
            return sortlop(v);
        case 6:
            return scholarship(v);
        case 7:
            return notgraduate(v);
    }
}

void inracauhoi (string s) {
    cout << s;
}

string ans (int x, const vector<sv>& v) {
    switch(x) {
        case 1:
            return checkgpamax(v);
        case 2:
            return checkgpamin(v);
        case 3:
            return checkoldest(v);
        case 4:
            return checkyoungest(v);
        case 5:
            return checkhighestclass(v);
        case 6:
            return checkreverseid(v);
        case 7:
            return checkfirstname(v);
        case 8:
            return checklastname(v);
        case 9: {
            vector<sv> temp1 = scholarship(v);
            int a = temp1.size();
            string result1 = to_string(a);
            return result1;
        }
        case 10: {
            vector<sv> temp2 = notgraduate(v);
            int b = temp2.size();
            string result2 = to_string(b);
            return result2;
        }
    }
}

bool check_update(string a, string b) {
    if (a == b) {
        return 1;
    }
    else return 0;
}

int POINT = 0;
void checkkk(int i, int x, int y, const vector<sv> &v) {
	string s;
	getline(cin, s);
	string temp = ans(x, v);

	if (i < y) {
		if (check_update(s, temp)) {
			cout << "Correct!" << endl;
            POINT += 20;
            cout << "----- Your current point is: " << POINT << " -----" << endl;
	}
		else {
        	    cout << "Incorrect! Ihe correct answer is: " << ans(x, v) << endl;
            	cout << "----- Your current point is: " << POINT << " -----" << endl;
    	}
	}
	else {
		if (check_update(s, temp)) {
			cout << "Correct!" << endl;
            	POINT += 20;
            	cout << "----- Your final point is: " << POINT << " -----" << endl;
		}
		else {
            cout << "Incorrect! Ihe correct answer is: " << ans(x, v) << endl;
            cout << "----- Your final point is: " << POINT << " -----" << endl;
        }
	}
}


















