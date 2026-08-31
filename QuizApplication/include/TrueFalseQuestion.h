#pragma once
#include "Question.h"

class TFQuestion : public Question {
public:
    // Constructor nhận id, nội dung câu hỏi và đáp án đúng ("T" hoặc "F")
    TFQuestion(int id, const string& content, const string& correctAnswer);

    // Destructor ảo override
    ~TFQuestion() override;

    // override 2 phương thức thuần ảo từ lớp cha Question
    void display() const override;
    bool checkAnswer(const string& answer) const override;
};
