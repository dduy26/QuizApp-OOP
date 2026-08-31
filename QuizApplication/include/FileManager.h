#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Question.h"
#include "Candidate.h"

using namespace std;

class FileManager {
private:
    string questionFilePath;
    string resultFilePath;

public:
    // Constructor khởi tạo đường dẫn file
    FileManager(string qPath = "data/QuestionBank.txt", string rPath = "data/Result.txt");

    // Đọc danh sách câu hỏi từ file
    vector<Question*> loadQuestions();

    // Ghi kết quả bài thi ra file
    void saveResult(const Candidate& c, int correct, int total, double score);
};