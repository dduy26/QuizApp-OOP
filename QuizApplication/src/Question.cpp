#pragma once
#include"Question.h"

// tạo class Question
    Question::Question(int id , string content , string correctAnswer , string type)
    :m_id(id), m_content(content), m_correctAnswer(correctAnswer),m_type(type){}
    Question::~Question();
    //get
    int Question::getId(){
        return m_id;
    }
    string Question::getContent(){
        return m_content;
    }
    string Question::getCorrectAnswer(){
        return m_correctAnswer;
    }
    string Question::getType(){
        return m_type;
    }