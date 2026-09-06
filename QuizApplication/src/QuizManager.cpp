#include "QuizManager.h"
#include "MCQQuestion.h"
#include "TrueFalseQuestion.h"

QuizManager::QuizManager(const string& qPath, const string& rPath)
    : m_fileManager(qPath, rPath) {}

QuizManager::~QuizManager() {
    for (Question* q : m_questions) {
        delete q;
    }
    m_questions.clear();
}

// STL
int QuizManager::countCorrectAnswers(ExamSession& session) {
    int correctCount = 0;
    int total = session.getTotalQuestions();
    
    for (int i = 1; i <= total; ++i) {
        string userAns = session.getAnswer(i);
        if (!userAns.empty() && m_questions[i - 1]->checkAnswer(userAns)) {
            correctCount++;
        }
    }
    return correctCount;
}

void QuizManager::showMainMenu() {
    cout << "\n====================================\n";
    cout << "     HE THONG QUAN LY THI TRAC NGHIEM\n";
    cout << "====================================\n";
    cout << "1. Nhap thong tin thi sinh\n";
    cout << "2. Bat dau lam bai thi\n";
    cout << "3. Thoat\n";
    cout << "====================================\n";
    cout << "Chon chuc nang: ";
}

void QuizManager::run() {
    m_questions = m_fileManager.loadQuestions();
    if (m_questions.empty()) {
        cout << "[Loi] Khong the tai danh sach cau hoi tu file!" << endl;
        return;
    }

    bool isRunning = true;
    bool hasCandidateInfo = false;

    while (isRunning) {
        showMainMenu();
        int choice;
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "\n--- NHAP THONG TIN THI SINH ---\n";
                cin >> m_candidate;
                hasCandidateInfo = true;
                cout << "=> Cap nhat thong tin thanh cong!\n";
                break;
            }
            case 2: {
                if (!hasCandidateInfo) {
                    cout << "\n[Nhac nho] Vui long nhap thong tin thi sinh truoc khi bat dau thi!\n";
                    break;
                }

                ExamSession session(m_questions);
                session.runExam();

                int total = session.getTotalQuestions();
                int correct = countCorrectAnswers(session);
                double score10 = calculateScore10(correct, total);
                double percent = calculatePercentage(correct, total);

                cout << "\n====================================\n";
                cout << "          KET QUA BAI THI\n";
                cout << "====================================\n";
                cout << m_candidate << "\n";
                cout << "------------------------------------\n";
                cout << "So cau dung : " << correct << "/" << total << "\n";
                cout << "Ty le dung  : " << fixed << setprecision(2) << percent << "%\n";
                cout << "Diem so (10): " << score10 << "/10.0\n";
                cout << "====================================\n";

                m_fileManager.saveResult(m_candidate, correct, total, score10);
                cout << "=> Da tu dong luu ket qua thi vao file.\n";
                break;
            }
            case 3: {
                cout << "\nCam on ban da su dung phan mem. Tam biet!\n";
                isRunning = false;
                break;
            }
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!\n";
                break;
        }
    }
}
