#ifndef MODULES
#define MODULES

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

bool isValidInfo(string info);
bool isValidDate(string date);
string convertName(string name);
bool isSort(string name1, string name2);


class Student{
public:
    string name;
    string ID;
    string birth;
    string sex;
    string className;
    string mark;
    Student* next;

    /* Ham khoi tao doi tuong student */
    Student(string name, string ID, string sex, string birth, string className, string mark){
        this->name = name;
        this->ID = ID;
        this->sex = sex;
        this->birth = birth;
        this->className = className;
        this->mark = mark;
        this->next = nullptr;
    };

    /* Ham giai phong vung nho duoc su dung boi con tro */
    ~Student(){};
};

class Class{
public:
    string className;
    Student* head;
    Class* next;
    int count;

    /* Ham khoi tao doi tuong class */
    Class(string className){
        this->className = className;
        this->next = nullptr;
        this->count = 0;
    }
    /* Ham giai phong vung nho duoc su dung boi con tro */
    ~Class(){
        this->clear();
    };

    /* Ham dung de them student moi vao mot class (su dung doi voi classList chua ton tai class nay) */
    void addStudent(string name, string ID, string sex,string birth, string className, string mark){
        Student* newStu = new Student(name, ID, sex, birth, className, mark);
        if (this->count == 0){
            this->head = newStu;
            this->count++;
            return;
        }
        Student* curr = this->head;
        if (isSort(newStu->name, curr->name)){
            newStu->next = curr;
            this->head = newStu;
            this->count++;
            return;
        }
        while(curr->next){
            Student* nextCurr = curr->next;
            if (isSort(curr->name, newStu->name) && isSort(newStu->name, nextCurr->name)){
                curr->next = newStu;
                newStu->next = nextCurr;
                this->count++;
                return;
            }
            curr = curr->next;
        }
        curr->next = newStu;
        this->count++;
    };

    /* Ham dung de in tat ca student cua mot class */
    void print(){
        if (this->count == 0){
            return; 
        };
        Student* curr = this->head;
        while(curr){
            cout << "Ten: " << curr->name << ", ID: " << curr->ID << ", gioi tinh: " << curr->sex << ", ngay sinh: " << curr->birth << ", lop: " << curr->className << ", diem: " << curr->mark << endl;
            curr = curr->next;
        }
    };

    void clear(){
        Student* curr = this->head;
        Student* nextCurr;
        while(curr){
            nextCurr = curr->next;
            curr->next = nullptr;
            delete curr;
            curr = nextCurr;
        }
        this->head = nullptr;
        this->count = 0;
    }
};

class ClassList{
public:
    Class* head;
    int count;

    ClassList(){
        this->head = new Class("");
        this->count = 0;
        this->readData();
    };

    ~ClassList(){
        this->clear();
    }

    /* Ham dung de doc du lieu thong tin sinh vien tu file va luu tru duoi dang danh sach lien ket */
    void readData(){
        ifstream myFile;
        myFile.open("dssv.txt");
        if(myFile.is_open()){
            string record;
            while(getline(myFile, record)){
                string name, ID, sex, birth, className;
                string mark = "";
                int indexArr[5]{0};
                int index = 0;

                for (int i=0;i<record.length();i++){
                    if (record[i] == ','){
                        indexArr[index] = i;
                        index++;
                    }
                }

                if (indexArr[4] == 0){
                    indexArr[4] = record.length();
                }else{
                    mark = record.substr(indexArr[4]+1, record.length() - indexArr[4] - 1).c_str();
                }

                name = record.substr(0, indexArr[0]);
                ID = record.substr(indexArr[0]+1, indexArr[1] - indexArr[0] - 1);
                sex = record.substr(indexArr[1]+1, indexArr[2] - indexArr[1] - 1);
                birth = record.substr(indexArr[2]+1, indexArr[3] - indexArr[2] - 1);
                className = record.substr(indexArr[3]+1, indexArr[4] - indexArr[3] - 1);

                this->addStudent(name, ID, sex, birth, className, mark);
            }
            myFile.close();
        }
    }

    /* Ham dung de them mot class chua ton tai vao classList */
    void addClass(string className){
        if (this->count == 0){
            Class* curr = this->head;
            curr->className = className;
            this->count++;
            return;
        }
        Class* newClass = new Class(className);
        Class* curr = this->head;
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newClass;
        this->count++;
        return;
    };

    /* Ham dung de them mot student vao class (su dung khi classList da ton tai class nay) */
    void addStudent(string name, string ID, string sex,string birth, string className, string mark){
        if(this->isExistClassName(className)){
            this->find(className)->addStudent(name, ID, sex, birth, className, mark);
        }else{
            this->addClass(className);
            this->find(className)->addStudent(name, ID, sex, birth, className, mark);
        }
    }

    /* Ham dung de cap nhat diem cho cac sinh vien chua co diem */
    void addMark(){
        if (this->count == 0){
            return;
        }
        int numOfStu = 0;
        Class* curr = this->head;
        while(curr){
            Student* currStu = curr->head;
            while(currStu){
                if (currStu->mark == ""){
                    numOfStu++;
                    cout << "Ten: " << currStu->name << ", ID: " << currStu->ID << ", gioi tinh: " << currStu->sex << ", ngay sinh: " << currStu->birth << ", lop: " << currStu->className << endl;
                    cout << "Vui long nhap diem so ban can cap nhat: ";
                    getline(cin, currStu->mark);
                }
                currStu = currStu->next;
            }
            curr = curr->next;
        };
        if (numOfStu == 0){
            cout << "Tat ca sinh vien deu da co diem !!!" << endl << endl;
        }
        return;
    }

    /* Kiem tra lop cua student da ton tai hay chua */
    bool isExistClassName(string className){
        if (this->count == 0){
            return false;
        }
        Class* curr = this->head;
        while(curr){
            if (curr->className == className){
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    /* Tim va tra ve con tro den class co ten trung voi ten lop cua student */
    Class* find(string className){
        Class* curr = this->head;
        while(curr){
            if (curr->className == className){
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /* In ra tat ca student cua classList (student cua tat ca cac class)*/
    void printAllStudent(){
        if (this->count == 0){
            return;
        }
        string className = "";
        Class* curr = this->head;
        while(curr){
            if (className != curr->className){
                cout << "********** DANH SACH SINH VIEN LOP " << curr->className << " *********" << endl;
                className = curr->className;
            }
            curr->print();
            cout << endl;
            curr = curr->next;
        }
    }

    /* Ham dung de luu lai thong tin sinh vien vao file */
    void saveData(){
        if (this->count == 0){
            return;
        }
        string fileData = "";
        Class* curr = this->head;
        while(curr){
            Student* currStu = curr->head;
            while(currStu){
                if (curr->next == nullptr && currStu->next == nullptr){
                    if (currStu->mark ==""){
                        fileData += currStu->name + "," + currStu->ID + "," + currStu->sex + "," + currStu->birth + "," + currStu->className;
                    }else{
                        fileData += currStu->name + "," + currStu->ID + "," + currStu->sex + "," + currStu->birth + "," + currStu->className + "," + currStu->mark;
                    }
                }else{
                    if (currStu->mark ==""){
                        fileData += currStu->name + "," + currStu->ID + "," + currStu->sex + "," + currStu->birth + "," + currStu->className + '\n';
                    }else{
                        fileData += currStu->name + "," + currStu->ID + "," + currStu->sex + "," + currStu->birth + "," + currStu->className + "," + currStu->mark + '\n';
                    }
                }
                currStu = currStu->next;
            }
            curr = curr->next;
        };

        ofstream myFile;
        myFile.open("dssv.txt");
        
        if (myFile.is_open()){
            myFile << fileData;
            myFile.close();
        }
    }

    void clear(){
        if (this->count == 0){
            return;
        }
        Class* curr = this->head;
        Class* nextCurr;
        while(curr){
            nextCurr = curr->next;
            curr->next = nullptr;
            curr->clear();
            delete curr;
            curr = nextCurr;
        }
        this->head = nullptr;
        this->count = 0;
    }
};

/* Ham kiem tra cac thong tin co ban cua sinh vien bao gom: ten, mssv, gioi tinh, ngay sinh, ten lop co rong hay khong */
bool isValidInfo(string info){
    if (info == ""){
        return false;
    }
    return true;
};

bool isValidDate(string date){
    if (date.length() < 10){
        return false;
    }
    if (date.length() != 10){
        return false;
    }
    int indexArr[2]{0};
    int index = 0;
    for (int i=0;i<date.length();i++){
        if (date[i] == '/'){
            indexArr[index] = i;
            index++;
        }
    }
    if (indexArr[0] != 2 || indexArr[1] != 5){
        return false;
    }
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));
    
    if (day <= 0 || month <= 0 || year <= 0){
        return false;
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 && day >0 && day<=31){
        return true;
    }
    if(month == 4 || month == 6 || month == 9|| month == 11 && day>0 && day<=30){
        return true;
    }
    if (month == 2){
        if ((year%400 ==0 || (year%100 != 0 && year%4 == 0)) && day>0 && day<=29){
            return true;
        }
        if (day>=0 && day<=28){
            return true;
        }
        return false;
    }
    return false;
}

string convertName(string name){
    int index = 0;
    for (int i=0;i<name.length();i++){
        if (name[i] == ' '){
            index = i;
        }
    }
    string result;
    index == 0 ? result = name : result = name.substr(index+1, name.length() - index - 1) + " " + name.substr(0,index);
    for (int i=0;i<result.length();i++){
        result[i] = tolower(result[i]);
    }
    return result;
}

bool isSort(string name1, string name2){
    return convertName(name1) < convertName(name2) ? true : false;
}

#endif