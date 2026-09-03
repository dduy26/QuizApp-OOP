#include "ExamSession.h"

#include <iostream>
#include <iomanip>

using namespace std;

//Constructor
// Constructor nhận danh sách câu hỏi của bài thi.
ExamSession::ExamSession(const vector<Question*>& questions)
    : m_questions(questions),
      m_currentIndex(0),
      m_isStarted(false)
{
    // Tạo số ô đáp án bằng đúng số câu hỏi.
    m_answers.resize(m_questions.size());

    m_status.resize(
        m_questions.size(),
        AnswerStatus::Unanswered
    );
}


//bắt đầu bài thi
void ExamSession::startExam()
{
    m_startTime = chrono::steady_clock::now();

    m_isStarted = true;
}

//lấy tổng số câu hỏi
int ExamSession::getTotalQuestions() const
{
    return static_cast<int>(m_questions.size());
}


// lấy số thự tự câu hiện tại
int ExamSession::getCurrentQuestionNumber() const
{
    return m_currentIndex + 1;
}

//chuyển tới một câu hỏi
bool ExamSession::goToQuestion(int questionNumber)
{
    // Kiểm tra số câu có hợp lệ không.
    if (questionNumber < 1 ||
        questionNumber > getTotalQuestions()) {

        cout << "So cau hoi khong hop le." << endl;

        return false;
    }

    // Chuyển từ số thứ tự sang index của vector.
    m_currentIndex = questionNumber - 1;

    return true;
}

// Chuyển tới câu hỏi theo ID
bool ExamSession::goToQuestionById(int questionId)
{
    // Duyệt qua toàn bộ danh sách câu hỏi
    for (int i = 0;
         i < static_cast<int>(m_questions.size());
         i++)
    {
        // Nếu tìm thấy câu có ID giống với ID cần tìm
        if (m_questions[i]->getId() == questionId)
        {
            // Lưu vị trí câu hỏi hiện tại
            m_currentIndex = i;

            return true;
        }
    }

    // Không tìm thấy ID
    cout << "Khong tim thay cau hoi co ID "
         << questionId
         << "."
         << endl;

    return false;
}

//Hiển thị câu hỏi hiện tại
void ExamSession::displayCurrentQuestion() const
{
    // Nếu không có câu hỏi thì không thể hiển thị.
    if (m_questions.empty()) {
        cout << "Khong co cau hoi trong bai thi." << endl;
        return;
    }

    cout << "\n====================================\n";

    cout << "Cau "
         << getCurrentQuestionNumber()
         << "/"
         << getTotalQuestions()
         << endl;

   
    m_questions[m_currentIndex]->display();

cout << "\nTrang thai: ";

if (m_status[m_currentIndex] == AnswerStatus::Skipped) {
    cout << "Da bo qua";
}
else if (m_status[m_currentIndex] == AnswerStatus::Answered) {
    cout << "Da tra loi";
}
else {
    cout << "Chua tra loi";
}

cout << endl;

// Hien thi trang thai cua cau hien tai
cout << "\nTrang thai: ";

if (m_status[m_currentIndex] == AnswerStatus::Answered) {
    cout << "Da tra loi";
}
else if (m_status[m_currentIndex] == AnswerStatus::Skipped) {
    cout << "Da bo qua";
}
else {
    cout << "Chua tra loi";
}

cout << endl;


// Hien thi dap an hien tai
cout << "Dap an hien tai: ";

if (m_answers[m_currentIndex].empty()) {
    cout << "Chua co dap an";
}
else {
    cout << m_answers[m_currentIndex];
}

cout << endl;

    cout << endl;

    // Hiển thị thời gian làm bài.
    displayTime();

    cout << "====================================\n";
}

//trả lời câu hiện tại
bool ExamSession::answerCurrentQuestion(
    const string& answer
)
{
    // Không có câu hỏi thì không thể trả lời.
    if (m_questions.empty()) {
        return false;
    }

    // Không cho lưu đáp án rỗng.
    if (answer.empty()) {
        cout << "Dap an khong duoc de trong." << endl;
        return false;
    }

    // Lưu đáp án của câu hiện tại.
    m_answers[m_currentIndex] = answer;

    // Đánh dấu câu này đã trả lời.
    m_status[m_currentIndex] =
        AnswerStatus::Answered;

    return true;
}

// bỏ qua câu hỏi hiện tại
bool ExamSession::skipCurrentQuestion()
{
    if (m_questions.empty()) {
        return false;
    }

    // Chỉ chuyển sang Skipped nếu câu chưa được trả lời.
    if (m_status[m_currentIndex]
        != AnswerStatus::Answered) {

        m_status[m_currentIndex] =
            AnswerStatus::Skipped;
    }

    return true;
}


//sửa đáp án
bool ExamSession::modifyAnswer(
    int questionNumber,
    const string& newAnswer
)
{
    // Kiểm tra số câu hợp lệ.
    if (questionNumber < 1 ||
        questionNumber > getTotalQuestions()) {

        cout << "So cau hoi khong hop le." << endl;

        return false;
    }

    // Không nhận đáp án rỗng.
    if (newAnswer.empty()) {

        cout << "Dap an moi khong duoc de trong."
             << endl;

        return false;
    }

    // Chuyển số câu sang index của vector.
    int index = questionNumber - 1;

    // Ghi đè đáp án cũ bằng đáp án mới.
    m_answers[index] = newAnswer;

    // Sau khi sửa thì câu này được xem là đã trả lời.
    m_status[index] = AnswerStatus::Answered;

    return true;
}

//lấy đáp án của một câu
string ExamSession::getAnswer(
    int questionNumber
) const
{
    // Nếu số câu không hợp lệ,
    // trả về chuỗi rỗng
    if (questionNumber < 1 ||
        questionNumber > getTotalQuestions()) {

        return "";
    }

    return m_answers[questionNumber - 1];
}

// lấy trạng thái của câu hỏi
AnswerStatus ExamSession::getStatus(
    int questionNumber
) const
{
    if (questionNumber < 1 ||
        questionNumber > getTotalQuestions()) {

        return AnswerStatus::Unanswered;
    }

    return m_status[questionNumber - 1];
}

//tính thời gian làm bài
long long ExamSession::getElapsedSeconds() const
{
    // Nếu chưa gọi startExam(),
    // thời gian làm bài là 0
    if (!m_isStarted) {
        return 0;
    }

    // Lấy thời gian hiện tại trừ thời gian bắt đầu
    // Sau đó đổi kết quả thành giây
    return chrono::duration_cast<chrono::seconds>(
        chrono::steady_clock::now() - m_startTime
    ).count();
}


// hiển thị thời gian
void ExamSession::displayTime() const
{
    long long totalSeconds = getElapsedSeconds();

    long long minutes = totalSeconds / 60;

    long long seconds = totalSeconds % 60;

    cout << "Thoi gian: "
         << setfill('0')
         << setw(2) << minutes
         << ":"
         << setw(2) << seconds
         << setfill(' ')
         << endl;
}


//Hiển Thị tiến độ bài làm
void ExamSession::displayProgress() const
{
    cout << "\n===== TIEN DO LAM BAI =====\n";

    for (
        int i = 0;
        i < static_cast<int>(m_questions.size());
        i++
    ) {
        cout << "Cau " << i + 1 << ": ";

        // Kiểm tra trạng thái của từng câu.
        switch (m_status[i]) {

        case AnswerStatus::Answered:

            cout << "Da tra loi";

            // Nếu đã có đáp án thì hiển thị luôn.
            if (!m_answers[i].empty()) {
                cout << " [" << m_answers[i] << "]";
            }

            break;


        case AnswerStatus::Skipped:

            cout << "Da bo qua";

            break;


        case AnswerStatus::Unanswered:

            cout << "Chua tra loi";

            break;
        }

        cout << endl;
    }

    cout << "===========================\n";
}


void ExamSession::runExam()
{
    if (m_questions.empty()) {
        cout << "Khong co cau hoi trong bai thi." << endl;
        return;
    }

    startExam();

    bool submitted = false;

    while (!submitted)
    {
        cout << "\n\n====================================\n";
        cout << "          MENU LAM BAI\n";
        cout << "====================================\n";

        displayCurrentQuestion();

        cout << "\n1. Tra loi cau hien tai";
        cout << "\n2. Chuyen den cau theo so thu tu";
        cout << "\n3. Chuyen den cau theo ID";
        cout << "\n4. Bo qua cau hien tai";
        cout << "\n5. Sua dap an";
        cout << "\n6. Xem tien do lam bai";
        cout << "\n7. Nop bai";

        cout << "\n\nLua chon: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string answer;

            cout << "Nhap dap an: ";
            cin >> answer;

            if (answerCurrentQuestion(answer)) {
                cout << "Da luu dap an." << endl;
            }

            break;
        }

        case 2:
        {
            int questionNumber;

            cout << "Nhap so thu tu cau hoi: ";
            cin >> questionNumber;

            goToQuestion(questionNumber);

            break;
        }

        case 3:
        {
            int questionId;

            cout << "Nhap ID cau hoi: ";
            cin >> questionId;

            goToQuestionById(questionId);

            break;
        }

        case 4:
        {
            if (skipCurrentQuestion()) {
                cout << "Da bo qua cau hoi." << endl;
            }

            break;
        }

        case 5:
        {
            int questionNumber;
            string newAnswer;

            cout << "Nhap so thu tu cau muon sua: ";
            cin >> questionNumber;

            cout << "Nhap dap an moi: ";
            cin >> newAnswer;

            if (modifyAnswer(questionNumber, newAnswer)) {
                cout << "Da cap nhat dap an." << endl;
            }

            break;
        }

        case 6:
        {
            displayProgress();
            break;
        }

        case 7:
        {
            cout << "\nBan co chac muon nop bai? (Y/N): ";

            char confirm;
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                submitted = true;

                cout << "\nDa nop bai." << endl;

                cout << "Tong thoi gian lam bai: ";
                displayTime();

                cout << "\nTrang thai bai lam:" << endl;

                displayProgress();
            }

            break;
        }

        default:
        {
            cout << "Lua chon khong hop le." << endl;
            break;
        }
        }
    }
}