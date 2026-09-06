#pragma once
#include "Question.h"

class TrueFalseQuestion : public Question {
public:
    TrueFalseQuestion(int id, const string& content, const string& correctAnswer);
    ~TrueFalseQuestion() override;

    void display() const override;
    bool checkAnswer(const string& answer) const override;
};
