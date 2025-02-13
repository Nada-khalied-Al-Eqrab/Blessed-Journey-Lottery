#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// دالة لاختيار عنصر عشوائي من قائمة
template <typename T>
T getRandomElement(const vector<T>& elements) {
    return elements[rand() % elements.size()];
}

int main() {
    // تهيئة المولد العشوائي
    srand(time(0));

    // اختيار اللغة
    int languageChoice;
    cout << "Select language / اختر اللغة:\n1. English\n2. العربية\nChoice / الاختيار: ";
    cin >> languageChoice;

    bool isEnglish = (languageChoice == 1);

    // إدخال أسماء المشاركين
    vector<string> participants(5);
    cout << (isEnglish ? "Enter names of five participants:\n" : "أدخل أسماء خمسة مشاركين:\n");
    for (int i = 0; i < 5; i++) {
        cout << (isEnglish ? "Participant " : "المشارك ") << i + 1 << ": ";
        cin >> participants[i];
    }

    // قائمة الجوائز باستخدام map
    map<int, pair<string, string>> prizes = {
        {0, {"Fully Paid Hajj", "حجة مجانية مدفوعة التكاليف بالكامل"}},
        {1, {"Free Umrah", "عمرة مجانية"}},
        {2, {"50% Discount on Umrah", "خصم 50% على العمرة"}},
        {3, {"50% Discount on Hajj", "خصم 50% على الحجة"}},
        {4, {"Better Luck Next Time", "حظ أوفر المرة القادمة"}},
        {5, {"Cash Prize of 500 SAR", "جائزة نقدية 500 ريال"}},
        {6, {"Shopping Voucher of 200 SAR", "قسيمة شرائية بقيمة 200 ريال"}},
        {7, {"3 Days Free Stay in Mecca", "إقامة مجانية لمدة 3 أيام في مكة"}},
        {8, {"Free Flight Ticket", "تذكرة طيران مجانية"}}
    };

    vector<int> prizeKeys;
    for (const auto& pair : prizes) {
        prizeKeys.push_back(pair.first);
    }

    // إمكانية منع الفائز السابق من الفوز مرة أخرى
    vector<string> previousWinners;
    char anotherDraw;
    do {
        string winner;
        do {
            winner = getRandomElement(participants);
        } while (find(previousWinners.begin(), previousWinners.end(), winner) != previousWinners.end());

        previousWinners.push_back(winner);
        auto prize = prizes[getRandomElement(prizeKeys)];

        // عرض النتيجة
        cout << "\n==========================\n";
        if (prize.second == "حظ أوفر المرة القادمة") {
            cout << (isEnglish ? "Better luck next time, no winner this round.\n" : "حظ أوفر المرة القادمة، لم يفز أحد بالجائزة هذه المرة.\n");
        } else {
            cout << (isEnglish ? "Congratulations to the winner " : "مبروك للفائز ") << winner << "!\n";
            cout << (isEnglish ? "The prize is: " : "الجائزة هي: ") << (isEnglish ? prize.first : prize.second) << "\n";
        }
        cout << "==========================\n";

        // التحقق من إمكانية إجراء سحب آخر
        if (previousWinners.size() >= participants.size()) {
            cout << (isEnglish ? "All participants have been chosen, no more draws possible.\n" : "تم اختيار جميع المشاركين، لا يمكن إجراء سحب آخر.\n");
            break;
        }

        cout << (isEnglish ? "Do you want to choose another winner? (y/n): " : "هل ترغب في اختيار فائز آخر؟ (y/n): ");
        cin >> anotherDraw;
    } while (anotherDraw == 'y' || anotherDraw == 'Y');

    return 0;
}
