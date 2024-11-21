#include "DataGenerator.h"
#include "Student.h"
#include <random>
#include <cmath>

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double generateRandomDouble(int min, int max, int accuracy) {
    double factor = pow(10, accuracy);
    int minScaled = min * factor;
    int maxScaled = max * factor;
    return generateRandomNumber(minScaled, maxScaled) / pow(10.0, accuracy);
}

void generateRandomArray(int *arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = generateRandomNumber(min, max);
    }
}

std::vector<std::string> maleNames = {
        "Alexey", "Ivan", "Dmitry", "Nikita", "Maxim", "Artem", "Vladimir", "Oleg", "Konstantin", "Roman",
        "Sergey", "Daniil", "Georgiy", "Yegor", "Anatoly", "Vyacheslav", "Pyotr", "Vasily", "Mikhail", "Timofey"
};

std::vector<std::string> femaleNames = {
        "Ekaterina", "Maria", "Sophia", "Anna", "Olga", "Anastasia", "Irina", "Tatyana", "Elena", "Darya",
        "Victoria", "Evgenia", "Polina", "Yulia", "Alena", "Natalya", "Nina", "Lyudmila", "Larisa", "Zoya"
};

std::vector<std::string> surnames = {
        "Smirnov", "Ivanov", "Kuznetsov", "Sokolov", "Popov", "Lebedev", "Kozlov", "Novikov", "Morozov", "Petrov",
        "Volkov", "Solovyov", "Vasiliev", "Zaytsev", "Pavlov", "Semenov", "Golubev", "Vinogradov", "Bogdanov",
        "Vorobyov", "Fyodorov", "Mikhailov", "Belyaev", "Tarasov", "Belov", "Komarov", "Orlov", "Kiselyov", "Makarov",
        "Andreev", "Kovalev", "Ilyin", "Gusev", "Titov", "Kuzmin", "Kudryavtsev", "Baranov", "Kulikov", "Alexeev",
        "Stepanov", "Yakoblev", "Sorokin", "Sergeev", "Romanov", "Zakharov", "Borisov", "Korolev", "Gerasimov",
        "Ponomaryov", "Grigoryev", "Lazarev", "Medvedev", "Ershov", "Nikitin", "Sobolev", "Ryabov", "Polyakov",
        "Tsvetkov", "Danilov", "Zhukov", "Frolov", "Zhuravlyov", "Nikolaev", "Krylov", "Maximov", "Sidorov", "Osipov",
        "Belozuyov", "Fedotov", "Dorofeev", "Yegorov", "Matveev", "Bobrov", "Dmitriev", "Kalinin", "Anisimov",
        "Petukhov", "Antonov", "Timofeev", "Nikiforov", "Veselov", "Filippov", "Markov", "Bolshakov", "Sukhanov",
        "Mironov", "Shiryayev", "Alexandrov", "Konovalov", "Shestakov", "Kazakov", "Efimov", "Denisov", "Gromov",
        "Fomin", "Davydov", "Melnikov", "Shcherbakov", "Blinov", "Kolesnikov", "Karpev", "Afanasyev", "Vlasov",
        "Maslov", "Isakov", "Tikhonov", "Aksyonov", "Gavrilov", "Rodionov", "Kotov", "Gorbunov", "Kudryashov", "Bykov",
        "Zuev", "Tretyakov", "Saveliev", "Panov", "Rybakov", "Suvorov", "Abramov", "Voronov", "Mukhin", "Arhipov",
        "Trofimov", "Martynov", "Emelyanov", "Gorshkov", "Chernov", "Ovchinnikov", "Seleznev", "Panfilov", "Kopylov",
        "Mikheev", "Galkin", "Nazrov", "Lobanov", "Lukin", "Belyakov", "Potapov", "Nikrasov", "Khokhlov", "Zhdanov",
        "Naumov", "Shilov", "Vorontsov", "Ermakov", "Drozdov", "Ignatyev", "Savin", "Loginov", "Safonov", "Kapustin",
        "Kirillov", "Moiseev", "Yeliseev", "Koshelev", "Kostin", "Gorbachev", "Orekhov", "Efremov", "Isayev", "Evdokimov",
        "Kalashnikov", "Kabanov", "Noskov", "Yudin", "Kulagin", "Lapin", "Prokhorov", "Nesterov", "Kharitonov",
        "Agafonov", "Muravyov", "Laryonov", "Fedoseev", "Zimin", "Pakhomov", "Shubin", "Ignatov", "Filatov", "Kryukov",
        "Rogov", "Kulakov", "Terentyev", "Molchanov", "Vladimirov", "Artemyev", "Guryev", "Zinovyev", "Grishin",
        "Kononov", "Dementyev", "Sitnikov", "Simonov", "Mishin", "Fadeev", "Komissarov", "Mamonov", "Nosov", "Gulyaev",
        "Sharov", "Ustinov", "Vishnyakov", "Yevseev", "Lavrentyev", "Bragin", "Konstantinov", "Kornilov", "Avdeev",
        "Zykov", "Biryukov", "Sharapov", "Nikonomov", "Shchukin", "Dyachkov", "Odintsov", "Sazonov", "Yakushev",
        "Krasilnikov", "Gordeyev", "Samoylov", "Knyazev", "Bespalov", "Uvarov", "Shashkov", "Bobylev", "Doronin",
        "Belozyorov", "Roshkov", "Samsonov", "Myasnikov", "Likhachev", "Burov", "Sysoev", "Fomichev", "Rusakov",
        "Strelkov", "Gushchin", "Teterin", "Kolobov", "Subbotin", "Fokin", "Blokhin", "Seliverstov", "Pestov",
        "Kondratiev", "Silin", "Merkushev", "Lytkin", "Turov"
};

Student generateStudent() {
    int age = generateRandomNumber(17, 30);
    int course = generateRandomNumber(1, 4);
    double marks = generateRandomDouble(3, 5, 2);
    std::string name;
    std::string surname = surnames[generateRandomNumber(0, surnames.size() - 1)];
    bool isFemale = generateRandomNumber(0, 1) == 0;
    if (isFemale) {
        name = femaleNames[generateRandomNumber(0, femaleNames.size() - 1)];
        surname += "a";
    } else {
        name = maleNames[generateRandomNumber(0, maleNames.size() - 1)];
    }
    return Student(name, surname, course, age, marks);
}

void generateStudentArray(Student *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = generateStudent();
    }
}
