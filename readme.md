# 📘 Quy Chuẩn Lập Trình (Coding Conventions) & Cấu Trúc Dự Án C++ (OOP Quiz Application)

> **Dự án:** QuizApp - BTL Lập trình Hướng đối tượng (OOP)  
> **Mục tiêu:** Đồng nhất phong cách viết code cho cả 4 thành viên, giảm thiểu xung đột mã nguồn (merge conflict) khi làm việc với Git, và đạt điểm tối đa ở tiêu chí **Code Quality** khi bảo vệ đồ án.

---

## 📋 Mục Lục

1. [Cấu Trúc Thư Mục Dự Án](#1-cấu-trúc-thư-mục-dự-án)
2. [Quy Chuẩn Đặt Tên (Naming Conventions)](#2-quy-chuẩn-đặt-tên-naming-conventions)
3. [Quy Chuẩn Viết Code C++ & OOP Bắt Buộc](#3-quy-chuẩn-viết-code-c--oop-bắt-buộc)
   - [3.1 Header Guard](#31-header-guard)
   - [3.2 Const Correctness](#32-const-correctness)
   - [3.3 Lớp Cơ Sở & Hủy Ảo (Virtual Destructor)](#33-lớp-cơ-sở--hủy-ảo-virtual-destructor)
   - [3.4 Quản Lý Bộ Nhớ & Dọn Dẹp Con Trỏ](#34-quản-lý-bộ-nhớ--dọn-dẹp-con-trỏ)
   - [3.5 Tính Đóng Gói (Encapsulation)](#35-tính-đóng-gói-encapsulation)
4. [Hướng Dẫn Build & Chạy Chương Trình](#4-hướng-dẫn-build--chạy-chương-trình)
5. [Quy Trình Làm Việc Nhóm Với Git](#5-quy-trình-làm-việc-nhóm-với-git)

---

## 1. Cấu Trúc Thư Mục Dự Án

Tách biệt hoàn toàn giữa khai báo (Header `.h`) và định nghĩa logic (Source `.cpp`). **Không được viết toàn bộ code thực thi vào file header.**

```text
QuizApplication/
├── data/                    # Thư mục chứa dữ liệu tĩnh và đầu ra
│   ├── QuestionBank.txt     # File ngân hàng đề thi mẫu
│   └── Result.txt           # File kết quả xuất ra sau khi thi
├── include/                 # Chứa toàn bộ các file Header (.h)
│   ├── Candidate.h
│   ├── ExamSession.h
│   ├── FileManager.h
│   ├── MCQQuestion.h
│   ├── Question.h
│   ├── QuizManager.h
│   └── TFQuestion.h
├── src/                     # Chứa toàn bộ các file thực thi (.cpp)
│   ├── Candidate.cpp
│   ├── ExamSession.cpp
│   ├── FileManager.cpp
│   ├── MCQQuestion.cpp
│   ├── Question.cpp
│   ├── QuizManager.cpp
│   └── TFQuestion.cpp
├── main.cpp                 # Điểm khởi chạy chương trình (Entry point)
└── Readme.md                # Quy chuẩn code và hướng dẫn dự án
```

---

## 2. Quy Chuẩn Đặt Tên (Naming Conventions)

| Thành phần | Quy tắc đặt tên | Ví dụ chuẩn | Không nên dùng ❌ |
| :--- | :--- | :--- | :--- |
| **Tên File** | `PascalCase` cho Class/Header, chữ thường cho file thực thi chính | `Question.h`, `Question.cpp`, `ExamSession.h`, `main.cpp` | `question.h`, `exam_session.cpp` |
| **Class / Struct** | `PascalCase` (Danh từ, viết hoa chữ cái đầu mỗi từ) | `class Question`, `class ExamSession`, `class Candidate` | `class question`, `class exam_session` |
| **Hàm / Phương thức** | `camelCase` (Động từ + Danh từ) | `display()`, `checkAnswer()`, `loadQuestions()`, `calculateScore()` | `Display()`, `check_answer()`, `Handle()` |
| **Biến thành viên (Private/Protected)** | Tiền tố `m_` + `camelCase` | `m_id`, `m_fullName`, `m_correctAnswer`, `m_startTime` | `id`, `FullName`, `x`, `temp` |
| **Biến cục bộ (Local variables)** | `camelCase` (Rõ nghĩa, không viết tắt vô nghĩa) | `userInput`, `totalQuestions`, `questionId`, `currentIndex` | `a`, `b`, `ans_usr`, `str` |
| **Hằng số (Constants)** | `UPPER_SNAKE_CASE` | `MAX_OPTIONS = 4`, `DEFAULT_EXAM_TIME = 30` | `maxOptions`, `Max_Time` |
| **Tham số truyền vào (Parameters)** | `camelCase` (Khuyến khích dùng `const T&` cho kiểu dữ liệu phức tạp) | `void setFullName(const string& fullName)` | `void setFullName(string fn)` |

---

## 3. Quy Chuẩn Viết Code C++ & OOP Bắt Buộc

### 3.1 Header Guard
Tất cả các file header (`.h`) **bắt buộc** phải có chỉ thị `#pragma once` ở dòng đầu tiên để tránh lỗi khai báo lặp (redefinition / multiple inclusion).

```cpp
#pragma once
#include <string>
#include <iostream>

using namespace std;
```

### 3.2 Const Correctness
- **Getter & Hàm đọc dữ liệu:** Tất cả các phương thức không làm thay đổi trạng thái đối tượng phải được đánh dấu từ khóa `const` ở cuối hàm.
- **Tham số truyền vào:** Đối với kiểu chuỗi (`std::string`) hoặc các đối tượng/struct lớn, bắt buộc phải truyền bằng tham chiếu hằng (`const &`) để tránh sao chép lãng phí bộ nhớ.

```cpp
// ✅ CHUẨN
string getFullName() const;
bool checkAnswer(const string& answer) const;

// ❌ KHÔNG CHUẨN (Thiếu const, truyền tham trị tốn bộ nhớ)
string getFullName();
bool checkAnswer(string answer);
```

### 3.3 Lớp Cơ Sở & Hủy Ảo (Virtual Destructor)
Lớp trừu tượng/lớp cơ sở (`Question`) **bắt buộc** phải khai báo destructor ảo (`virtual ~Question() {}`). Điều này đảm bảo khi giải phóng mảng con trỏ `vector<Question*>`, destructor của lớp con (`MCQQuestion`, `TFQuestion`) được gọi đúng trình tự, tránh rò rỉ bộ nhớ (Memory Leak).

```cpp
class Question {
protected:
    int m_id;
    string m_content;
    string m_correctAnswer;

public:
    Question(int id, const string& content, const string& correctAnswer)
        : m_id(id), m_content(content), m_correctAnswer(correctAnswer) {}
    
    virtual ~Question() {} // ⚠️ BẮT BUỘC có destructor ảo

    virtual void display() const = 0;
    virtual bool checkAnswer(const string& answer) const = 0;
};
```

### 3.4 Quản Lý Bộ Nhớ & Dọn Dẹp Con Trỏ
Khi khởi tạo các câu hỏi bằng con trỏ động (`new MCQQuestion`, `new TFQuestion`), ở hàm kết thúc chương trình hoặc hàm hủy destructor của `QuizManager`, **bắt buộc** phải giải phóng toàn bộ vùng nhớ đã cấp phát:

```cpp
// Giải phóng từng con trỏ động trong ngân hàng câu hỏi
for (Question* q : m_questionBank) {
    delete q;
    q = nullptr;
}
m_questionBank.clear(); 
```

### 3.5 Tính Đóng Gói (Encapsulation)
- Thuộc tính của lớp (Member Variables) **không bao giờ** để ở phạm vi `public`.
- Đặt ở `private` (hoặc `protected` nếu cần cho lớp con kế thừa).
- Cung cấp các hàm Getter/Setter phù hợp có kiểm tra tính hợp lệ dữ liệu.

---

## 4. Hướng Dẫn Build & Chạy Chương Trình

### Biên dịch bằng G++ (Command Line / Terminal)

Biên dịch tất cả các file mã nguồn trong `src/` cùng với `main.cpp` và chỉ định thư mục chứa header `include/`:

```bash
# Biên dịch project
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o QuizApp

# Chạy chương trình trên Windows
.\QuizApp.exe

# Chạy chương trình trên Linux / macOS
./QuizApp
```

---

## 5. Quy Trình Làm Việc Nhóm Với Git

1. **Không commit trực tiếp vào nhánh `main`:**
   - Mỗi thành viên tạo nhánh riêng khi phát triển tính năng: `feature/mcq-question`, `feature/quiz-manager`, `feature/file-io`.
2. **Quy chuẩn Message Commit:**
   - `feat: thêm chức năng chấm điểm tự động`
   - `fix: sửa lỗi rò rỉ bộ nhớ khi hủy danh sách câu hỏi`
   - `docs: cập nhật quy chuẩn coding convention`
   - `refactor: tối ưu hóa hàm kiểm tra đáp án`
3. **Tạo Pull Request (PR) & Code Review:**
   - Trước khi merge vào `main`, phải tạo PR và nhờ ít nhất 1 thành viên khác review kiểm tra xem đã tuân thủ **Coding Convention** này chưa.