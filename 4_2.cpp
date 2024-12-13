#include <iostream>
#include <limits>  // работа с пределами данных

class LineSegment {  // представляем отрезок
private:
    double x1, x2; // координаты начала и конца отрезка
public:
    LineSegment() : x1(0), x2(0) {}  // конструктор по умолчанию
    LineSegment(double start, double end) {  // конструктор с заданными параметрами
        if (start > end) {
            x1 = end;
            x2 = start;
        } else {
            x1 = start;
            x2 = end;
        }
    }
    // LineSegment(const LineSegment& other) : x1(other.x1), x2(other.x2) {}
    
    // перегрузка оператора вывода для вывода в формате [x1, x2]
    friend std::ostream& operator<<(std::ostream& os, const LineSegment& segment) {
        os << "[" << segment.x1 << ", " << segment.x2 << "]";  // объект вывода
        return os;
    }

    // метод для определения пересечения отрезков
    LineSegment* intersect(const LineSegment& other) {  // проверка на пересечение 
        double maxStart = std::max(this->x1, other.x1);
        double minEnd = std::min(this->x2, other.x2);
        
        if (maxStart <= minEnd) {
            return new LineSegment(maxStart, minEnd);  // объект переечения
        }
        return nullptr; // нет пересечения
    }
    // унарная операция !
    LineSegment operator!() {
        return LineSegment(0, (x2 - x1));
    }
    // неявная операция приведения int
    operator int() const {
        return static_cast<int>(x2);  // возвращает целую часть кооринаты х2
    }
    // явная операция приведения double
    explicit operator double() const {  // возвращает координату х1
        return x1;
    }
    // операция сложение
    LineSegment operator+(int offset) const {
        return LineSegment(x1 + offset, x2 + offset);
    }
    // операция сравнения >
    bool operator>(const LineSegment& other) const {  // вывод true или false
        return (this->x1 <= other.x1 && this->x2 >= other.x2);
    }
};
double getValidInput() {  // проверка ввода
    double value;
    while (true) {
        std::cout << "Введите значение: ";
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear(); // сбрасываем состояние потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорим неверный ввод
            std::cout << "Ошибка: введите число " << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем буфер
            return value;
        }
    }
}
int main() {
    int choice;
    LineSegment segment1, segment2;
    // меню выбора действия
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать отрезок х\n";
        std::cout << "2. Создать отрезок у\n";
        std::cout << "3. Вывести отрезки\n";
        std::cout << "4. Найти пересечение\n";
        std::cout << "5. Применить унарную операцию !\n";
        std::cout << "6. Привести к int\n";
        std::cout << "7. Привести к double\n";
        std::cout << "8. Сложить с целым числом\n";
        std::cout << "9. Проверить включение отрезков\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите номер действия: ";
        
        choice = static_cast<int>(getValidInput());
        // объединяем все выбора из меню
        switch (choice) {
            case 1:  // ввод координат отрезка х
                {
                    double start = getValidInput();
                    double end = getValidInput();
                    segment1 = LineSegment(start, end);
                    break;
                }
            case 2:  // ввод координат отрезка у
                {
                    double start = getValidInput();
                    double end = getValidInput();
                    segment2 = LineSegment(start, end);
                    break;
                }
            case 3:  // вывод отрезков
                std::cout << "Отрезок х: " << segment1 << "\nОтрезок у: " << segment2 << std::endl;
                break;
            case 4:  // поиск пересений отрезков
                {
                    LineSegment* intersection = segment1.intersect(segment2);
                    if (intersection) {  // если есть пересечение
                        std::cout << "Пересечение: " << *intersection << std::endl;
                        delete intersection; // чистим память
                    } else {
                        std::cout << "Отрезки не пересекаются" << std::endl;
                    }
                    break;
                }
            case 5:  // вывод унарной операции
                {
                    LineSegment result = !segment1;
                    std::cout << "Результат применения ! к отрезку х: " << result << std::endl;
                    break;
                }
            case 6:  // вывод приведения к int
                std::cout << "Целая часть координаты y отрезка у: " << static_cast<int>(segment2) << std::endl;
                break;
            case 7:  // вывод приведения к double
                std::cout << "Координата x отрезка х: " << static_cast<double>(segment1) << std::endl;
                break;
            case 8:  // ввод числа и операция сложения с ним
                {
                    int offset = static_cast<int>(getValidInput());
                    LineSegment result = segment1 + offset;
                    std::cout << "Результат сложения с целым числом: " << result << std::endl;
                    break;
                }
            case 9:  // вывод проверки на включение
                if (segment1 > segment2)
                    std::cout << "Отрезок х включает отрезок у" << std::endl;
                else
                    std::cout << "Отрезок х не включает отрезок у" << std::endl;
                break;
            case 0:
                std::cout << "Выход" << std::endl;
                break;
            default:  // если введено неверное число из меню
                std::cout << "Ошибка: введите число от 0 до 9 " << std::endl;
                break;
        }
    } while (choice != 0);
    return 0;
}
