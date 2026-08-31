#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<cctype>
using namespace std;

class Question{
protected:
    int m_id;
    string m_content;
    string m_correctAnswer;
    string m_type;
public:
    Question(int id , string content , string correctAnswer , string type);
    virtual ~Question();
    virtual void display() const = 0;
    virtual bool checkAnswer(const string& answer) const = 0;
    //get
    int getId() const;
    string getContent() const;
    string getCorrectAnswer() const;
    string getType() const;
};