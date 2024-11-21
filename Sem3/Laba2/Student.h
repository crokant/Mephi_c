#pragma once

#include <string>

class Student {
public:
    std::string name;
    std::string surname;
    int course;
    int age;
    double averageScore;

    Student() : name(""), surname(""), course(0), age(0), averageScore(0.0) {}

    Student(const std::string &name, const std::string &surname, int course, int age, double averageScore)
            : name(name), surname(surname), course(course), age(age), averageScore(averageScore) {}

    ~Student() = default;

    std::string getName() const {
        return name;
    }

    std::string getSurname() const {
        return surname;
    }

    int getCourse() const {
        return course;
    }

    int getAge() const {
        return age;
    }

    double getAverageScore() const {
        return averageScore;
    }

    static bool compareByAge(const Student &a, const Student &b) {
        return a.age < b.age;
    }

    static bool compareByAverageScore(const Student &a, const Student &b) {
        return a.averageScore < b.averageScore;
    }

    static bool compareByCourse(const Student &a, const Student &b) {
        return a.course < b.course;
    }
};
