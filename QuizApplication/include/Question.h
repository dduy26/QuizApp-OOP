#pragma once
#include<iostream>
using namespace std;

class Question{
protected:
    int m_id;
    string m_content;
    string m_correctAnswer;
    string m_type;
public:
    Question(int id , string content , string correctAnswer , string type);
    ~Question();
    virtual bool display() = 0;
    virtual bool checkAnswer(const string& answer) const = 0;
    //get
    int getId();
    string getContent();
    string getCorrectAnswer();
    string getType();
}