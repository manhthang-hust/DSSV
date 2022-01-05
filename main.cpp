#include"modules.h"

using namespace std;

int main(){
Menu:
    cout << "*******************CAC CHUC NANG BAN CO THE THUC HIEN*******************" << endl;
    cout << "1. Bo sung ho so sinh vien moi !!!" << endl;
    cout << "2. Cap nhat diem cho sinh vien !!!" << endl;
    cout << "3. In danh sach tat ca sinh vien !!!" << endl;
    cout << "An 1,2,3 de chon cac chuc nang tuong ung, an nut bat ki de thoat chuong trinh !!!" << endl;

    int userSelect;
    cin >> userSelect;
    bool isExit = false;
    while(!isExit){
        if (userSelect == 1){
            cin.ignore();
            ClassList* classList = new ClassList();
            string name,ID,sex,birth,className, mark;

            cout << "**************THONG TIN SINH VIEN MOI**************" << endl;
        inputName:
            cout << "Ho va ten sinh vien: ";
            getline(cin, name);
            if (!isValidInfo(name)){
                cout << "Thong tin nay khong duoc bo trong !!!" << endl << endl;
                goto inputName;
            }
        inputID:
            cout << "Ma so sinh vien: ";
            getline(cin, ID);
            if (!isValidInfo(ID)){
                cout << "Thong tin nay khong duoc bo trong !!!" << endl << endl;
                goto inputID;
            }
        inputSex:
            cout << "Gioi tinh sinh vien: ";
            getline(cin, sex);
            if (!isValidInfo(sex)){
                cout << "Thong tin nay khong duoc bo trong !!!" << endl << endl;
                goto inputSex;
            }
        inputBirth:
            cout << "Ngay sinh cua sinh vien (dinh dang dd/mm/yyyy): ";
            getline(cin, birth);
            if (!isValidInfo(birth)){
                cout << "Thong tin nay khong duoc bo trong !!!" << endl << endl;
                goto inputBirth;
            }
            if (!isValidDate(birth)){
                cout << "Ngay sinh ma ban nhap khong dung dinh dang, vui long nhap lai !!! " << endl << endl;
                goto inputBirth;
            }
        inputClassName:
            cout << "Ten lop cua sinh vien: ";
            getline(cin, className);
            if (!isValidInfo(className)){
                cout << "Thong tin nay khong duoc bo trong !!!" << endl << endl;
                goto inputClassName;
            }
            cout << "Diem cua sinh vien (Enter neu chua co diem): ";
            getline(cin, mark);
            classList->addStudent(name, ID, sex, birth, className, mark);
            classList->saveData();
            cout << endl << endl;
            goto Menu;
        }
        if (userSelect == 2){
            ClassList* classList = new ClassList();
            cin.ignore();
            classList->addMark();
            classList->saveData();
            cout << endl << endl;
            goto Menu;
        }
        if (userSelect == 3){
            ClassList* classList = new ClassList();
            classList->printAllStudent();
            cout << endl << endl;
            goto Menu;
        }
        isExit = true;
    }
    return 0;
}