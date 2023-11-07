#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

template <typename T>
class UniqueSet {
private:
    T* elements;
    int size;
    int capacity;

public:
    // Конструктор по умолчанию: создает пустое множество
    UniqueSet() : elements(nullptr), size(0), capacity(0) {}

    // Конструктор с параметрами: массив значений для заполнения
    UniqueSet(const T* values, int count) : elements(nullptr), size(0), capacity(0) {
        for (int i = 0; i < count; ++i) {
            insert(values[i]);
        }
    }

    // Конструктор с параметрами, заполняющий множество случайным образом
    UniqueSet(int count, T min_val, T max_val) : elements(nullptr), size(0), capacity(0) {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < count; ++i) {
            T value = min_val + static_cast<T>(rand()) % (max_val - min_val + 1);
            insert(value);
        }
    }

    // Конструктор копирования
    UniqueSet(const UniqueSet<T>& other) : elements(nullptr), size(0), capacity(0) {
        for (int i = 0; i < other.size; ++i) {
            insert(other.elements[i]);
        }
    }

    // Оператор присваивания
    UniqueSet<T>& operator=(const UniqueSet<T>& other) {
        if (this != &other) {
            clear();
            for (int i = 0; i < other.size; ++i) {
                insert(other.elements[i]);
            }
        }
        return *this;
    }

    // Деструктор для освобождения памяти
    ~UniqueSet() {
        clear();
    }

    // Оператор [] для получения числа по его индексу
    T operator[](int index) const {
        if (index >= 0 && index < size) {
            return elements[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Оператор объединения множеств
    UniqueSet<T> operator+(const UniqueSet<T>& other) const {
        UniqueSet<T> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.insert(other.elements[i]);
        }
        return result;
    }

    // Оператор разности множеств
    UniqueSet<T> operator-(const UniqueSet<T>& other) const {
        UniqueSet<T> result = *this;
        for (int i = 0; i < other.size; ++i) {
            result.remove(other.elements[i]);
        }
        return result;
    }

    // Оператор сложения множества с числом
    UniqueSet<T> operator+(const T& value) const {
        UniqueSet<T> result = *this;
        result.insert(value);
        return result;
    }

    UniqueSet<T>& operator+=(const T& value) {
        insert(value);
        return *this;
    }

    // Оператор вычитания числа из множества
    UniqueSet<T> operator-(const T& value) const {
        UniqueSet<T> result = *this;
        result.remove(value);
        return result;
    }

    UniqueSet<T>& operator-=(const T& value) {
        remove(value);
        return *this;
    }

    // Вычисление пересечения двух множеств
    UniqueSet<T> intersection(const UniqueSet<T>& other) const {
        UniqueSet<T> result;
        for (int i = 0; i < size; ++i) {
            if (other.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    // Функция проверки наличия числа во множестве
    bool contains(const T& value) const {
        for (int i = 0; i < size; ++i) {
            if (elements[i] == value) {
                return true;
            }
        }
        return false;
    }

    // Вставка элемента в множество
    void insert(const T& value) {
        if (!contains(value)) {
            if (size == capacity) {
                resize();
            }
            elements[size++] = value;
        }
    }

    // Удаление элемента из множества
    void remove(const T& value) {
        for (int i = 0; i < size; ++i) {
            if (elements[i] == value) {
                for (int j = i; j < size - 1; ++j) {
                    elements[j] = elements[j + 1];
                }
                --size;
                return;
            }
        }
    }

    // Вспомогательная функция для увеличения размера массива
    void resize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newElements = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

    // Вывод элементов множества
    void display() const {
        for (int i = 0; i < size; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "\"" << elements[i] << "\" ";
            }
            else if constexpr (std::is_same_v<T, std::pair<int, double>>) {
                std::cout << "(" << elements[i].first << ", " << elements[i].second << ") ";
            }
            else {
                std::cout << elements[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    // Определение, является ли текущее множество подмножеством другого множества
    bool isSubsetOf(const UniqueSet<T>& other) const {
        for (int i = 0; i < size; ++i) {
            if (!other.contains(elements[i])) {
                return false;
            }
        }
        return true;
    }

    // Определение, является ли текущее множество надмножеством другого множества
    bool isSupersetOf(const UniqueSet<T>& other) const {
        for (int i = 0; i < other.size; ++i) {
            if (!contains(other.elements[i])) {
                return false;
            }
        }
        return true;
    }

    // Очистка множества и освобождение памяти
    void clear() {
        delete[] elements;
        elements = nullptr;
        size = 0;
        capacity = 0;
    }
};

int main() {
    int intValues1[] = { 1, 2, 3, 4, 5 };
    int intValues2[] = { 3, 4, 5, 6, 7 };

    UniqueSet<int> intSet1(intValues1, sizeof(intValues1) / sizeof(intValues1[0]));
    UniqueSet<int> intSet2(intValues2, sizeof(intValues2) / sizeof(intValues2[0]));

    std::cout << "intSet1: ";
    intSet1.display();
    std::cout << "intSet2: ";
    intSet2.display();

    UniqueSet<int> unionSet = intSet1 + intSet2;
    std::cout << "Union: ";
    unionSet.display();

    // Добавление и удаление элементов для intSet1
    intSet1 = intSet1 + 8;
    intSet1 = intSet1 - 3;

    // Добавление и удаление элементов для intSet2
    intSet2 = intSet2 + 10;
    intSet2 = intSet2 - 6;

    // Пересечение множеств
    UniqueSet<int> intersectionSet = intSet1.intersection(intSet2);
    std::cout << "Intersection: ";
    intersectionSet.display();

    // Проверка на подмножество и надмножество
    std::cout << "intSet1 isSubsetOf intSet2: " << intSet1.isSubsetOf(intSet2) << std::endl;
    std::cout << "intSet2 isSubsetOf intSet1: " << intSet2.isSubsetOf(intSet1) << std::endl;

    std::cout << "intSet1 isSupersetOf intSet2: " << intSet1.isSupersetOf(intSet2) << std::endl;
    std::cout << "intSet2 isSupersetOf intSet1: " << intSet2.isSupersetOf(intSet1) << std::endl;

    // Работа с std::string
    std::string strValues1[] = { "apple", "banana", "cherry", "date", "fig"};
    std::string strValues2[] = { "banana", "date", "fig" };

    UniqueSet<std::string> strSet1(strValues1, sizeof(strValues1) / sizeof(strValues1[0]));
    UniqueSet<std::string> strSet2(strValues2, sizeof(strValues2) / sizeof(strValues2[0]));

    std::cout << "strSet1: ";
    strSet1.display();
    std::cout << "strSet2: ";
    strSet2.display();

    UniqueSet<std::string> strUnionSet = strSet1 + strSet2;
    std::cout << "String Union: ";
    strUnionSet.display();

    // Проверка на подмножество и надмножество для strSet1 и strSet2
    std::cout << "strSet1 isSubsetOf strSet2: " << strSet1.isSubsetOf(strSet2) << std::endl;
    std::cout << "strSet2 isSubsetOf strSet1: " << strSet2.isSubsetOf(strSet1) << std::endl;

    std::cout << "strSet1 isSupersetOf strSet2: " << strSet1.isSupersetOf(strSet2) << std::endl;
    std::cout << "strSet2 isSupersetOf strSet1: " << strSet2.isSupersetOf(strSet1) << std::endl;

    // Работа с std::pair<int, double>
    std::pair<int, double> pairValues1[] = { std::make_pair(1, 1.1), std::make_pair(2, 2.2), std::make_pair(3, 3.3) };
    std::pair<int, double> pairValues2[] = { std::make_pair(2, 2.2), std::make_pair(3, 3.3) };

    UniqueSet<std::pair<int, double>> pairSet1(pairValues1, sizeof(pairValues1) / sizeof(pairValues1[0]));
    UniqueSet<std::pair<int, double>> pairSet2(pairValues2, sizeof(pairValues2) / sizeof(pairValues2[0]));

    std::cout << "pairSet1: ";
    pairSet1.display();
    std::cout << "pairSet2: ";
    pairSet2.display();

    UniqueSet<std::pair<int, double>> pairUnionSet = pairSet1 + pairSet2;
    std::cout << "Pair Union: ";
    pairUnionSet.display();


    // Проверка на подмножество и надмножество для pair
    std::cout << "pairSet1 isSubsetOf pairSet2: " << pairSet1.isSubsetOf(pairSet2) << std::endl;
    std::cout << "pairSet2 isSubsetOf pairSet1: " << pairSet2.isSubsetOf(pairSet1) << std::endl;

    std::cout << "pairSet1 isSupersetOf pairSet2: " << pairSet1.isSupersetOf(pairSet2) << std::endl;
    std::cout << "pairSet2 isSupersetOf pairSet1: " << pairSet2.isSupersetOf(pairSet1) << std::endl;

    return 0;
}
