#pragma once

#include <vector>
#include <string>
#include <chrono>
#include "Question.h"

using namespace std;

// Trạng thái của một câu hỏi trong lúc làm bài
enum class AnswerStatus {
    Unanswered, 
    Answered,   
    Skipped    
};

class ExamSession {
private:
    // Danh sách câu hỏi của bài thi
    vector<Question*> m_questions;

    // Lưu đáp án mà thí sinh đã chọn cho từng câu.
    vector<string> m_answers;

    // Lưu trạng thái của từng câu
    vector<AnswerStatus> m_status;

    // Vị trí câu hỏi đang được xem
    int m_currentIndex;

    // Thời điểm bắt đầu làm bài
    chrono::steady_clock::time_point m_startTime;

    // Kiểm tra bài thi đã bắt đầu hay chưa
    bool m_isStarted;

public:
    // Constructor
    ExamSession(const vector<Question*>& questions);

    // Bắt đầu bài thi và bắt đầu tính thời gian
    void startExam();

    // Trả về tổng số câu hỏi
    int getTotalQuestions() const;

    // Trả về số thứ tự câu hỏi hiện tại
    int getCurrentQuestionNumber() const;

    // Chuyển tới một câu hỏi theo số thứ tự
    bool goToQuestion(int questionNumber);

    // Chuyển tới câu hỏi theo ID
    bool goToQuestionById(int questionId);

    // Hiển thị câu hỏi hiện tại
    void displayCurrentQuestion() const;

    // Hiển thị trạng thái toàn bộ bài thi
    void displayProgress() const;

    // Hiển thị thời gian đã làm bài
    void displayTime() const;

    // Trả lời câu hỏi hiện tại
    bool answerCurrentQuestion(const string& answer);

    // Bỏ qua câu hỏi hiện tại
    bool skipCurrentQuestion();

    // Sửa đáp án của một câu đã làm
    bool modifyAnswer(
        int questionNumber,
        const string& newAnswer
    );

    // Lấy đáp án của một câu
    string getAnswer(int questionNumber) const;

    // Lấy trạng thái của một câu hỏi
    AnswerStatus getStatus(int questionNumber) const;

    // Trả về số giây đã trôi qua từ khi bắt đầu thi
    long long getElapsedSeconds() const;

    // Chạy menu làm bài thi
    void runExam();
};