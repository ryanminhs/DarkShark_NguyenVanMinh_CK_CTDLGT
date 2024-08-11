#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <unordered_map>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

class Xe {
public:
    string maXe;
    string soXe;
    string loaiXe;
    string hoTenChuXe;
    int donGiaGui;
    time_t ngayGui;
    Xe() : donGiaGui(0), ngayGui(0) {}
    Xe(string maXe, string soXe, string loaiXe, string hoTenChuXe, int donGiaGui, time_t ngayGui)
        : maXe(maXe), soXe(soXe), loaiXe(loaiXe), hoTenChuXe(hoTenChuXe), donGiaGui(donGiaGui), ngayGui(ngayGui) {}
};

void displayXeInfo(const Xe& xe) {
    tm ngayGuiTm;
    localtime_s(&ngayGuiTm, &xe.ngayGui);
    stringstream ss;
    ss << put_time(&ngayGuiTm, "%d/%m/%Y");
    string ngayGuiStr = ss.str();

    cout << "Ma xe: " << xe.maXe
        << ", So xe: " << xe.soXe
        << ", Loai xe: " << xe.loaiXe
        << ", Ho ten chu xe: " << xe.hoTenChuXe
        << ", Don gia goi: " << xe.donGiaGui
        << ", Ngay goi: " << ngayGuiStr << endl;
}


Xe nhapThongTinXe() {
    string maXe, soXe, loaiXe, hoTenChuXe;
    int donGiaGui;
    tm ngayGui = {};
    time_t ngayGuiTime;

    cout << "Nhap ma xe: ";
    cin >> maXe;
    cout << "Nhap so xe: ";
    cin >> soXe;
    cout << "Nhap loai xe: ";
    cin >> loaiXe;
    cout << "Nhap ho ten chu xe: ";
    cin >> hoTenChuXe;
    cout << "Nhap don gia goi: ";
    cin >> donGiaGui;
    cout << "Nhap ngay goi (dd/mm/yyyy): ";
    string ngayGuiStr;
    cin >> ngayGuiStr;

    stringstream ss(ngayGuiStr);
    string token;
    getline(ss, token, '/');
    int day = stoi(token);
    getline(ss, token, '/');
    int month = stoi(token);
    getline(ss, token);
    int year = stoi(token);

    ngayGui.tm_mday = day;
    ngayGui.tm_mon = month - 1;
    ngayGui.tm_year = year - 1900;
    ngayGui.tm_hour = 0;
    ngayGui.tm_min = 0;
    ngayGui.tm_sec = 0;
    ngayGui.tm_isdst = -1;
    ngayGuiTime = mktime(&ngayGui);

    return Xe(maXe, soXe, loaiXe, hoTenChuXe, donGiaGui, ngayGuiTime);
}

void themXeVaoStack(stack<Xe>& baiXe) {
    Xe xe = nhapThongTinXe();
    baiXe.push(xe);
    cout << "Xe da duoc them vao bai xe." << endl;
}

string timLoaiXeNhieuNhat(stack<Xe> baiXe) {
    unordered_map<string, int> demLoaiXe;
    int maxSoXe = 0;
    string loaiXeNhieuNhat;

    while (!baiXe.empty()) {
        Xe xe = baiXe.top();
        baiXe.pop();
        demLoaiXe[xe.loaiXe]++;
        if (demLoaiXe[xe.loaiXe] > maxSoXe) {
            maxSoXe = demLoaiXe[xe.loaiXe];
            loaiXeNhieuNhat = xe.loaiXe;
        }
    }

    return loaiXeNhieuNhat;
}

bool kiemTraLoaiXeTrongBaiXe(stack<Xe> baiXe, const string& loaiXe) {
    while (!baiXe.empty()) {
        Xe xe = baiXe.top();
        baiXe.pop();
        if (xe.loaiXe == loaiXe) {
            return true;
        }
    }
    return false;
}

void thongKeTheoDonGiaGui(stack<Xe> baiXe) {
    unordered_map<int, int> demTheoDonGia;
    while (!baiXe.empty()) {
        Xe xe = baiXe.top();
        baiXe.pop();
        demTheoDonGia[xe.donGiaGui]++;
    }
    cout << "Thong ke so luong xe theo don gia goi:" << endl;
    for (const auto& it : demTheoDonGia) {
        cout << "Don gia goi: " << it.first << ", So luong xe: " << it.second << endl;
    }
}

void demSoLuongXeTheoLoai(stack<Xe> baiXe) {
    unordered_map<string, int> demTheoLoaiXe;
    stack<Xe> tempStack = baiXe;
    while (!tempStack.empty()) {
        Xe xe = tempStack.top();
        tempStack.pop();
        demTheoLoaiXe[xe.loaiXe]++;
    }
    cout << "So luong xe theo tung loai xe:" << endl;
    for (const auto& it : demTheoLoaiXe) {
        cout << "Loai xe: " << it.first << ", So luong xe: " << it.second << endl;
    }
}

void xoaLoaiXe(stack<Xe>& baiXe, const string& loaiXeCanXoa) {
    stack<Xe> tempStack;
    bool xeDaXoa = false;

    // Đưa các xe khác loại xe cần xóa vào tempStack
    while (!baiXe.empty()) {
        Xe xe = baiXe.top();
        baiXe.pop();
        if (xe.loaiXe != loaiXeCanXoa) {
            tempStack.push(xe);
        }
        else {
            xeDaXoa = true;
        }
    }

    // Đưa các xe còn lại vào lại stack chính
    while (!tempStack.empty()) {
        Xe xe = tempStack.top();
        tempStack.pop();
        baiXe.push(xe);
    }

    if (xeDaXoa) {
        cout << "Loai xe " << loaiXeCanXoa << " da duoc xoa khoi bai xe." << endl;
    }
    else {
        cout << "Khong tim thay loai xe " << loaiXeCanXoa << " trong bai xe." << endl;
    }
}




int demTongSoXe(stack<Xe> baiXe) {
    return baiXe.size();
}
time_t convertToTimeT(int day, int month, int year) {
    tm timeStruct = {};
    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1; // Tháng bắt đầu từ 0
    timeStruct.tm_year = year - 1900; // Năm bắt đầu từ 1900
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    return mktime(&timeStruct);
}
void thongKeDoanhThuChiTiet(stack<Xe> baiXe, const string& kieuThongKe) {
    unordered_map<string, int> doanhThuChiTiet;
    int tongDoanhThu = 0; // Biến để lưu tổng doanh thu

    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm* currentTime = localtime(&now);

    tm startTm = *currentTime;
    tm endTm = *currentTime;

    // Xác định khoảng thời gian dựa trên kieuThongKe
    if (kieuThongKe == "tuan") {
        startTm.tm_mday -= (currentTime->tm_wday); // Ngày đầu tuần
        endTm.tm_mday += (6 - currentTime->tm_wday); // Ngày cuối tuần
    }
    else if (kieuThongKe == "thang") {
        startTm.tm_mday = 1; // Ngày đầu tháng
        endTm.tm_mon += 1; // Đặt tháng tiếp theo
        endTm.tm_mday = 0; // Ngày cuối tháng hiện tại
    }
    else if (kieuThongKe == "quy") {
        int month = (currentTime->tm_mon / 3) * 3; // Bắt đầu quý
        startTm.tm_mon = month;
        endTm.tm_mon = month + 3; // Kết thúc quý
        endTm.tm_mday = 0; // Ngày cuối quý
    }

    // Chuyển startTm và endTm thành time_t
    time_t ngayBatDau = mktime(&startTm);
    time_t ngayKetThuc = mktime(&endTm);

    // Chạy qua tất cả các xe trong bãi
    while (!baiXe.empty()) {
        Xe xe = baiXe.top();
        baiXe.pop();

        if (xe.ngayGui >= ngayBatDau && xe.ngayGui <= ngayKetThuc) {
            tm ngayGuiTm;
            localtime_s(&ngayGuiTm, &xe.ngayGui);
            stringstream ss;

            if (kieuThongKe == "ngay") {
                ss << put_time(&ngayGuiTm, "%d/%m/%Y");
            }
            else if (kieuThongKe == "tuan") {
                int tuan = (ngayGuiTm.tm_yday / 7) + 1;
                ss << "Tuan " << tuan << " Nam " << (ngayGuiTm.tm_year + 1900);
            }
            else if (kieuThongKe == "thang") {
                ss << "Thang " << (ngayGuiTm.tm_mon + 1) << " Nam " << (ngayGuiTm.tm_year + 1900);
            }
            else if (kieuThongKe == "quy") {
                int quy = (ngayGuiTm.tm_mon / 3) + 1;
                ss << "Quy " << quy << " Nam " << (ngayGuiTm.tm_year + 1900);
            }

            string chiTietStr = ss.str();
            doanhThuChiTiet[chiTietStr] += xe.donGiaGui;
            tongDoanhThu += xe.donGiaGui; // Cộng doanh thu vào tổng doanh thu
        }
    }

    cout << "Thong ke doanh thu chi tiet:" << endl;

    for (const auto& pair : doanhThuChiTiet) {
        cout << pair.first << ": Doanh thu = " << pair.second << endl;
    }

    // In tổng doanh thu
    cout << "Tong doanh thu: " << tongDoanhThu << endl;
}



void ghiDuLieuXeVaoFile(const stack<Xe>& baiXe, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Loi mo file " << filename << endl;
        return;
    }

    stack<Xe> tempStack = baiXe;
    while (!tempStack.empty()) {
        Xe xe = tempStack.top();
        tempStack.pop();
        tm ngayGuiTm;
        localtime_s(&ngayGuiTm, &xe.ngayGui);
        file << xe.maXe << " " << xe.soXe << " " << xe.loaiXe << " "
            << xe.hoTenChuXe << " " << xe.donGiaGui << " "
            << put_time(&ngayGuiTm, "%d/%m/%Y") << endl;
    }

    file.close();
    cout << "Da ghi du lieu vao file " << filename << endl;
}

void docDuLieuXeTuFile(stack<Xe>& baiXe, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Loi mo file " << filename << endl;
        return;
    }

    string maXe, soXe, loaiXe, hoTenChuXe;
    int donGiaGui;
    tm ngayGui = {};

    while (file >> maXe >> soXe >> loaiXe >> hoTenChuXe >> donGiaGui ) {
        file >> get_time(&ngayGui, "%d/%m/%Y");
        time_t ngayGuiTime = mktime(&ngayGui);
        baiXe.push(Xe(maXe, soXe, loaiXe, hoTenChuXe, donGiaGui, ngayGuiTime));
    }

    file.close();
    cout << "Da doc du lieu tu file " << filename << endl;
}

int main() {
    stack<Xe> baiXe;
    string loaiXe;
    string loaiXeCanXoa;
    time_t ngayBatDau, ngayKetThuc;
    string loaiXeCanXoa;
    int choice;

    do {
        cout << "\n================ MENU ================" << endl;
        cout << "1. Nhap tu ban phim thong tin xe" << endl;
        cout << "2. Doc du lieu xe tu file txt." << endl;
        cout << "3. Ghi du lieu xe tu file txt." << endl;
   
        cout << "4. Hien thi tat ca thong tin xe bang Stack" << endl;
        cout << "5. Them mot xe X vao (Stack)." << endl;
        cout << "6. Tim loai xe co nhieu so xe nhat(Stack)." << endl;
        cout << "7. Tim loai xe X trong bai xe(Stack)." << endl;
        cout << "8. Thong ke xe theo don gia goi(Stack)." << endl;
        cout << "9. Dem so luong xe theo tung loai xe(Stack)." << endl;
        cout << "10. Xoa xe ra khoi bai xe(Stack)." << endl;
        cout << "11. Dem tong so xe goi trong bai xe(Stack)." << endl;
        cout << "12. Thong ke doanh thu theo ngay/tuan/thang/quy,tu ngay den ngay(Stack)." << endl;
        cout << "0. Thoat." << endl;
        cout << "======================================" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            themXeVaoStack(baiXe);
            break;
        case 2:
            docDuLieuXeTuFile(baiXe, "filedoc.txt");
            break;
        case 3:
            ghiDuLieuXeVaoFile(baiXe, "fileghi.txt");
            break;
        
        case 4:
        {
            stack<Xe> tempStack = baiXe;
            cout << "Danh sach cac xe trong bai xe:" << endl;
            while (!tempStack.empty()) {
                Xe xe = tempStack.top();
                tempStack.pop();
                displayXeInfo(xe); 
            }
            break;
        }
        case 5:
            themXeVaoStack(baiXe);
            break;
        case 6:
            cout << "Loai xe co nhieu xe nhat la: " << timLoaiXeNhieuNhat(baiXe) << endl;
            break;
        case 7:
            cout << "Nhap loai xe can tim: ";
            cin >> loaiXe;
            if (kiemTraLoaiXeTrongBaiXe(baiXe, loaiXe)) {
                cout << "Loai xe " << loaiXe << " ton tai trong bai xe." << endl;
            }
            else {
                cout << "Loai xe " << loaiXe << " khong ton tai trong bai xe." << endl;
            }
            break;
        case 8:
            thongKeTheoDonGiaGui(baiXe);
            break;
        case 9:
            demSoLuongXeTheoLoai(baiXe);
            break;
        case 10:
        {
            cout << "Nhap loai xe can xoa: ";
            cin >> loaiXeCanXoa;
            xoaLoaiXe(baiXe, loaiXeCanXoa);
            break;
        }
        case 11:
            cout << "Tong so xe gui trong bai xe la: " << demTongSoXe(baiXe) << endl;
            break;
        case 12: {
            cout << "Chon kieu thong ke (ngay/tuan/thang/quy): ";
            string kieuThongKe;
            cin >> kieuThongKe;

            thongKeDoanhThuChiTiet(baiXe, kieuThongKe);
            break;
        }
        case 0:
            cout << "Thoat chuong trinh." << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
