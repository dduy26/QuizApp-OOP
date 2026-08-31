#include "MCQQuestion.h"
#include <cctype>

    MCQQuestion::MCQQuestion(int id, const string& content, const vector<string>& options, const string& correctAnswer)
        :Question(id , content , correctAnswer , "MCQ") , m_options(options){}
    
    MCQQuestion::~MCQQuestion() {}
    //ép kiểu in ra màn hình đáp án ABCD từ vector thay vì mã ASCII 
    void MCQQuestion::display() const {
        cout << "\n[Cau " << m_id << " - Trac nghiem]: " << m_content << "\n";
        for (size_t i = 0; i < m_options.size(); ++i) {
            char label = static_cast<char>('A' + i);
            cout << "  " << label << ". " << m_options[i] << "\n";
        }
    }
    // check answer khi user skip hoặc k nhập gì , tránh việc crash 
    // toupper để so sánh k phân biệt hoa thường 
    bool MCQQuestion::checkAnswer(const string& answer) const {
        if (answer.empty()) return false;
        char userChoice = toupper(answer[0]);
        char actualChoice = toupper(m_correctAnswer[0]);
        return userChoice == actualChoice;
    }

    vector<string> MCQQuestion::getOptions() const {
        return m_options;
    }