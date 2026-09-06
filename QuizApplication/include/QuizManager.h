#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Candidate.h"
#include "FileManager.h"
#include "ExamSession.h"
#include "Question.h"

using namespace std;

template <typename T>
double calculatePercentage(T correct, T total) {
    if (total == 0) return 0.0;
    return (static_cast<double>(correct) / total) * 100.0;
}

template <typename T>
double calculateScore10(T correct, T total) {
    if (total == 0) return 0.0;
    return (static_cast<double>(correct) / total) * 10.0;
}

class QuizManager {
private:
    Candidate m_candidate;
    FileManager m_fileManager;
    vector<Question*> m_questions;

    //STL
    int countCorrectAnswers(ExamSession& session);

public:
    QuizManager(const string& qPath = "data/QuestionBank.txt", 
                const string& rPath = "data/Result.txt");
    ~QuizManager();

    void showMainMenu();
    void run();
};
