#include "mylib.h"
#include <chrono>
#include <locale>

void performTasks(const string& fileName) {
    auto start = std::chrono::high_resolution_clock::now();

    vector<studentas> grupe;
    ifstream input(fileName);

    if (!input.is_open()) {
        std::cerr << "Error opening file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    getline(input, line);

    while (getline(input, line)) {
        std::istringstream iss(line);
        string vard, pav;
        vector<int> paz;
        int egz;
        iss >> vard >> pav;

        for (int i = 0; i < 15; i++) {
            int nd;
            iss >> nd;
            paz.push_back(nd);
        }

        iss >> egz;

        studentas K(vard, pav, paz, egz);
        grupe.push_back(K);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Duomenu nuskaitymas is failo užtruko: " << duration.count() << " ms" << endl;

    start = std::chrono::high_resolution_clock::now();

    vector<studentas> vargsiukai;
    vector<studentas> galvociai;

    for (const auto& student : grupe) {
        if (student.getRez() < 5.0)
            vargsiukai.push_back(student);
        else
            galvociai.push_back(student);
    }

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Studentu rūšiavimas užtruko: " << duration.count() << " ms" << endl;

    start = std::chrono::high_resolution_clock::now();

    ofstream vargsiukaiFile("vargsiukai.txt");
    for (const auto& student : vargsiukai) {
        vargsiukaiFile << student.getVardas() << " " << student.getPavarde() << " " << student.getRez() << endl;
    }
    vargsiukaiFile.close();


    ofstream galvociaiFile("galvociai.txt");
    for (const auto& student : galvociai) {
        galvociaiFile << student.getVardas() << " " << student.getPavarde() << " " << student.getRez() << endl;
    }
    galvociaiFile.close();

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Surusiuotu studentu isvedimas i du naujus failus uztruko: " << duration.count() << " ms" << endl;
}

int main() {
    setlocale(LC_ALL, "Lithuanian");
    cout << "Kaip skaicuoti galutini? v/m ";
    cin >> skaiciavimo_Strategija;

    cout << "Pasirinkite txt faila (1, 2, ar 3): ";
    int fileChoice;
    cin >> fileChoice;

    string fileName;
    switch (fileChoice) {
    case 1:
        fileName = "studentai10000.txt.txt";
        break;
    case 2:
        fileName = "studentai100000.txt.txt";
        break;
    case 3:
        fileName = "studentai1000000.txt.txt";
        break;
    default:
        std::cerr << "Invalid file choice." << endl;
        return EXIT_FAILURE;
    }

    performTasks(fileName);

    system("pause");
    return 0;
}
