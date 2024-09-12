#include "paginator.h"
#include "request_queue.h"
#include "search_server.h"

#include <string>

using namespace std::string_literals;

int main() {
    using namespace std;

    SearchServer search_server("и в на"s);
    
    // Явно игнорируем результат метода AddDocument, чтобы избежать предупреждения
    // о неиспользуемом результате его вызова
    (void)search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });

    try {
        search_server.AddDocument(1, "пушистый пёс и модный ошейник"s, DocumentStatus::ACTUAL, { 1, 2 });
    }
    catch(const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "unknown exception"s << endl;
    }

    try {
        search_server.AddDocument(-1, "пушистый пёс и модный ошейник"s, DocumentStatus::ACTUAL, { 1, 2 });
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "unknown exception"s << endl;
    }

    try {
        search_server.AddDocument(3, "большой пёс скво\x12рец"s, DocumentStatus::ACTUAL, { 1, 3, 2 });
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "unknown exception"s << endl;
    }

    try {
        const auto documents = search_server.FindTopDocuments("--пушистый"s);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "unknown exception"s << endl;
    }

    try {
        const auto documents = search_server.FindTopDocuments("кот -"s);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "unknown exception"s << endl;
    }
}