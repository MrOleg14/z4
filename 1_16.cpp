#include <iostream>
#include <algorithm>

class LineSegment {
private:
    double x1, x2; // Координаты начала и конца отрезка
public:
    // Конструктор по умолчанию
    LineSegment() : x1(0), x2(0) {}

    // Конструктор с параметрами (если конец > начала, меняет их местами)
    LineSegment(double start, double end) {
        if (start <= end) {
            x1 = start;
            x2 = end;
        }
        else {
            x1 = end;
            x2 = start;
        }
    }
    // Конструктор копирования (создаем нью объект и копируем координаты из другого)
    LineSegment(const LineSegment& other) : x1(other.x1), x2(other.x2) {}

    // Геттеры (ф_ии, возврат нач и конеч координаты отрезка)
    double getStart() const { return x1; }
    double getEnd() const { return x2; }

    // Сеттеры (ф-ии, позволяющие изменять координаты с проверкой корректность)
    void setStart(double start) {
        if (start <= x2) x1 = start;
        else {
            x2 = start;
            x1 = x2;
        }
    }
    void setEnd(double end) {
        if (end >= x1) x2 = end;
        else {
            x1 = end;
            x2 = x1;
        }
    }
    // Метод для определения пересечения отрезков
    static LineSegment* intersection(const LineSegment& seg1, const LineSegment& seg2) {
        if (seg1.x2 < seg2.x1 || seg2.x2 < seg1.x1) {  // Если отрезки не пересекаются
            return nullptr;
        }
        // Находим координаты пересечения
        double start = std::max(seg1.x1, seg2.x1);
        double end = std::min(seg1.x2, seg2.x2);

        return new LineSegment(start, end);  // Возарат нью объекта
    }
    // Перегрузка оператора вывода (позволяет вывести [x1, x2])
    friend std::ostream& operator<<(std::ostream& os, const LineSegment& seg) {
        os << "[" << seg.x1 << ", " << seg.x2 << "]";
        return os;
    }
};
// Ф-ия для безопасного ввода числа (очищает поток и делает тест на корректность)
double inputNumber(const std::string& prompt) {
    double number;
    while (true) {
        std::cout << prompt;
        if (std::cin >> number) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Error. Enter a number\n";
    }
    return number;
}
int main() {

    // Тест конструкторов по умолчанию
    std::cout << "Default constructor: " << LineSegment() << std::endl;

    // Тест конструктора с параметрами (ввод от пользователя)
    double start = inputNumber("Enter the beginning of the first segment: ");
    double end = inputNumber("Enter the end of the first segment: ");
    LineSegment segment1(start, end);
    std::cout << "First segment: " << segment1 << std::endl;

    // Тест конструктора копирование
    LineSegment segment1Copy(segment1);
    std::cout << "Copy of the first segment: " << segment1Copy << std::endl;

    // Создание второго отрезка для теста пересечение
    start = inputNumber("Enter the beginning of the second segment: ");
    end = inputNumber("Enter the end of the second segment: ");
    LineSegment segment2(start, end);
    std::cout << "Second segment: " << segment2 << std::endl;

    // Тест метода пересечения и вывод результата
    LineSegment* intersection = LineSegment::intersection(segment1, segment2);
    if (intersection) {
        std::cout << "The segments intersect. Intersection segment: " << *intersection << std::endl;
        delete intersection;
    }
    else {
        std::cout << "The segments do not intersect" << std::endl;
    }

    // Тест сеттеров (чел может поменять координаты 1ого отрезка)
    std::cout << "\nTesting the change in coordinates of the first segment:" << std::endl;
    start = inputNumber("Enter a new start of the segment: ");
    segment1.setStart(start);
    end = inputNumber("Enter a new end of the segment: ");
    segment1.setEnd(end);
    std::cout << "Modified segment: " << segment1 << std::endl;

    return 0;
}
