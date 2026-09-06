#include"Question.h"

// tạo class Question
    Question::Question(int id , string content , string correctAnswer , string type)
    :m_id(id), m_content(content), m_correctAnswer(correctAnswer),m_type(type){}
    Question::~Question(){}
    //get
    int Question::getId() const {
        return m_id;
    }
    string Question::getContent() const {
        return m_content;
    }
    string Question::getCorrectAnswer() const {
        return m_correctAnswer;
    }
    string Question::getType() const {
        return m_type;
    }