#include "../include/QuizManager.h"

int main() {
    QuizManager app("data/QuestionBank.txt", "data/Result.txt");
    app.run();

    return 0;
}
