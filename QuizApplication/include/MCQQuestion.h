#pragma once
#include "Question.h"

//multi choice question
class MCQQuestion : public Question{
private:
    vector<string> m_options;
    int m_correctOption;
public:
    MCQQuestion(int id, const string& content, const vector<string>& options, const string& correctAnswer);
    ~MCQQuestion() override;

    void display() const override;
    bool checkAnswer(const string& answer) const override;
    
    vector<string> getOptions() const;

}