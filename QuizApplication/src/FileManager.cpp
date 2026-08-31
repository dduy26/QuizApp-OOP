#include "FileManager.h"
#include "MCQQuestion.h"
#include "TrueFalseQuestion.h"

FileManager::FileManager(string qPath, string rPath) {
    questionFilePath = qPath;
    resultFilePath = rPath;
}

// Hàm đọc file câu hỏi
vector<Question*> FileManager::loadQuestions() {
    vector<Question*> list;
    ifstream file(questionFilePath);

    if (!file.is_open()) {
        cout << "Khong mo duoc file de thi!" << endl;
        return list;
    }

    string type;
    while (file >> type) {
        int id;
        string content, a, b, c, d, correctAns;

        file >> id;
        file.ignore(); // Xóa ký tự xuống dòng
        getline(file, content);

        if (type == "MCQ") {
            getline(file, a);
            getline(file, b);
            getline(file, c);
            getline(file, d);
            getline(file, correctAns);

            list.push_back(new MCQQuestion(id, content, a, b, c, d, correctAns));
        }
        else if (type == "TF") {
            getline(file, correctAns);

            list.push_back(new TrueFalseQuestion(id, content, correctAns));
        }
    } 

    file.close();
    return list;
}

// Hàm lưu kết quả thi
void FileManager::saveResult(const Candidate& c, int correct, int total, double score) {
    ofstream file(resultFilePath, ios::app);

    if (!file.is_open()) {
        cout << "Khong mo duoc file ket qua!" << endl;
        return;
    }

    file << "MSSV: " << c.getCandidateID() << endl;
    file << "Ho Ten: " << c.getFullName() << endl;
    file << "Lop: " << c.getClassName() << endl;
    file << "So cau dung: " << correct << "/" << total << endl;
    file << "Tong diem: " << score << endl;
    file << "-------------------------" << endl;

    file.close();
}