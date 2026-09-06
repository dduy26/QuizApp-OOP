#include "TrueFalseQuestion.h"


TrueFalseQuestion::TrueFalseQuestion(int id, const string& content, const string& correctAnswer)
    : Question(id, content, correctAnswer, "TF") {}

TrueFalseQuestion::~TrueFalseQuestion() {}

void TrueFalseQuestion::display() const {
    cout << "\n[Cau " << m_id << " - Dung / Sai]: " << m_content << "\n";
    cout << "  [T] True (Dung)       [F] False (Sai)\n";
}

bool TrueFalseQuestion::checkAnswer(const string& answer) const {
    // 1. Kiểm tra chuỗi rỗng để tránh crash khi thí sinh nhấn Enter mà không nhập gì
    if (answer.empty()) {
        return false;
    }

    // 2. Chuẩn hóa ký tự đầu tiên về chữ in hoa ('t' -> 'T', 'f' -> 'F')
    char userChoice = toupper(answer[0]);
    char actualChoice = toupper(m_correctAnswer[0]);

    // 3. So khớp kết quả
    return userChoice == actualChoice;
}