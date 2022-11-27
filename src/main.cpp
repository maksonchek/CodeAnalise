#include <cmath>
#include <matplot/matplot.h>
#include <chrono>
#include <time.h>
/////////// for program1
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
/////////// for program2 +iostream +vector
#include <unordered_set>
//Для работы с файлами
#include <fstream>

using namespace matplot;

const int n = 200000;
const int iterStartNum = 1000;
const int step = 500;
const std::string path1 = "Data1.txt";
const std::string path2 = "Data2.txt";
const std::string pathMd = "Report_on_the_analysis_of_the_effectiveness_of_algorithms.md";
int masLen = (n - iterStartNum) / step;

double Program1(int n, std::vector<int> data) //возвращает время исполнения 1й программы
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> as(200001, -1);
    for (int i = 0; i < n; i += 1) {
        as[data[i]] = n - i - 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationTime = end - start;
    double time = durationTime.count();
    return time;
}

double Program2(int n, std::vector<int> data) //возвращает время исполнения 2й программы
{
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_set<int> unique;
    unique.reserve(200000);
    int idx_unique = n;
    for (int i = n - 1; 0 <= i; i -= 1) {
        if (!unique.contains(data[i])) {
            idx_unique = data[i];
            unique.insert(idx_unique);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationTime = end - start;
    double time = durationTime.count();
    return time;
}

std::vector<int> DataGenerator(int n) //Возвращает массив случайных номеров столовых длиной от 1 до указанного в аргументе количества столовых
{
    srand(time(0)); //Теперь генерация числе непредсказуема (менее предсказуема, чем без этой строки)
    std::vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
    {
        int num = 1 + rand() % (n);
        nums[i] = num;
    }
    return nums;
}

void ConvertDataToTxt(std::string path, std::vector<int> nums, std::vector<std::vector<int>> data, int iteration) //Данная функция используется в функцях замера времени считывания для программ
{
    std::ofstream saveToFile;
    saveToFile.open(path);

    if (saveToFile.is_open())
    {
        saveToFile << nums[iteration] << std::endl;
        for (int j = 0; j < nums[iteration]; j++)
        {
            saveToFile << data[iteration][j] << std::endl;
        }
        saveToFile << std::endl;
    }
    saveToFile.close();
}

std::vector<double> DataReadTime1(std::vector<int> nums, std::vector<std::vector<int>> data) //Возвращает массив времён считывания данных первой программой
{
    std::vector<double> time;

    for (int i = 0; i <= masLen; i++)
    {
        ConvertDataToTxt(path1, nums, data, i);
        auto start_input = std::chrono::high_resolution_clock::now();
        std::ifstream readFile;
        readFile.open(path1);
        if (readFile.is_open())
        {
            int n;
            readFile >> n;
            std::vector<int> as(200001, -1);
            for (int j = 0; j < n; j++)
            {
                int index;
                readFile >> index;
                as[index] = n - j - 1;
            }
        }
        readFile.close();
        auto end_input = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> inputDurationTime = end_input - start_input;
        time.push_back(inputDurationTime.count());
    }
    return time;
}

std::vector<double> DataReadTime2(std::vector<int> nums, std::vector<std::vector<int>> data) //Возвращает массив времён считывания данных второй программой
{
    std::vector<double> time;

    for (int i = 0; i <= masLen; i++)
    {
        ConvertDataToTxt(path2, nums, data, i);
        auto start_input = std::chrono::high_resolution_clock::now();
        std::ifstream readFile;
        readFile.open(path1);
        if (readFile.is_open())
        {
            int n;
            readFile >> n;
            std::vector<int> data2(n, 0);
            int idx_unique = n;
            for (int j = 0; j < n; j++)
            {
                readFile >> data2[j];
            }
        }
        readFile.close();
        auto end_input = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> inputDurationTime = end_input - start_input;
        time.push_back(inputDurationTime.count());
    }
    return time;
}


int main()
{
    setlocale(LC_ALL, "Rus");

    std::vector<int> nums;
    std::vector<double> timeDivided1;
    std::vector<double> timeDivided2;
    std::vector<std::vector<int>> dataN;

    int j = 0;
    for (int i = iterStartNum; i <= n; i += step)
    {
        dataN.push_back(DataGenerator(i));
    }
    for (int i = iterStartNum; i <= n; i += step)
    {
        double time = Program1(i, dataN[j]);
        double dividedTime = time * 1000;
        nums.push_back(i);
        timeDivided1.push_back((dividedTime) / i);
        j++;
    }
    j = 0;

    for (int i = iterStartNum; i <= n; i += step)
    {
        double time = Program2(i, dataN[j]);
        double dividedTime = time * 1000;
        timeDivided2.push_back((dividedTime) / i);
        j++;
    }

    j = 0;

    auto f = figure(true); //Почему-то благодаря этой строке картинки сохраняются. Может быть, эта команда превращает все графики в объекты?

    std::vector<double> inputTime1 = DataReadTime1(nums, dataN);
    std::vector<double> inputTime2 = DataReadTime2(nums, dataN);

    title("Statistics for the first algorithm");
    auto program1Input = plot(nums, inputTime1);
    program1Input->display_name("Data reading time");
    ylabel("Data reading time");
    xlabel("number of canteens");
    save("dataAnaliseVisualisation1.jpg");
    save("dataAnaliseVisualisation1.jpg");

    title("Statistics for the first algorithm");
    auto program1ExecutionTime = plot(nums, timeDivided1);
    program1ExecutionTime->display_name("Data reading time");
    ylabel("time/number of canteens");
    xlabel("number of canteens");
    save("dataAnaliseVisualisation2.jpg");

    title("Statistics for the second algorithm");
    auto program2Input = plot(nums, inputTime2);
    program2Input->display_name("Data reading time");
    ylabel("Data reading time");
    xlabel("number of canteens");
    save("dataAnaliseVisualisation3.jpg");

    title("Statistics for the second algorithm");
    auto program2ExecutionTime = plot(nums, timeDivided2);
    program2Input->display_name("Data reading time");
    ylabel("time/number of canteens");
    xlabel("number of canteens");
    save("dataAnaliseVisualisation4.jpg");

    //Запись в md файл
    
    std::ofstream fileMd;
    fileMd.open(pathMd);
    if (fileMd.is_open())
    {
        fileMd << "Статистика для алгоритмов, решающих задачу выбора столовых";
        fileMd << std::endl;
        fileMd << "Выполнил Максим Привалов";
        fileMd << std::endl;
        fileMd << "Ссылка на github проекта: https://github.com/maksonchek/CodeAnalise";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "Сгенерированные графики можно найти не только в md-файле, но и в папке build";
        fileMd << "Сгенерированный md-файл можно в папке build";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "Данные (номера столовых) были сгенерированы случайно. Каждый алгоритм был проанализировани на одном и том же наборе данных";
        fileMd << std::endl;
        fileMd << "Максимальное кол-во столовых: " << n << ". " << "Шаг, с которым подбирались количества столовых: " << step << ". " << "Замеры времени начались с " << iterStartNum << " количества столовых.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "График 1: показывает зависимость времени считывания данных из файла первым алгоритмом от количества столовых";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation1.jpg](dataAnaliseVisualisation1.jpg)";
        fileMd << std::endl;
        fileMd << "График 2: показывает зависимость отношения времени выполнения алгоритма 1 к кол-ву столовых от количества столовых";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation2.jpg](dataAnaliseVisualisation2.jpg)";
        fileMd<< std::endl;
        fileMd << "График 3: показывает зависимость времени считывания данных из файла вторым алгоритмом от количества столовых";
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation3.jpg](dataAnaliseVisualisation3.jpg)";
        fileMd << std::endl;
        fileMd << "График 4: показывает зависимость отношения времени выполнения алгоритма 2 к кол-ву столовых от количества столовых";
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation4.jpg](dataAnaliseVisualisation4.jpg)";
        fileMd << std::endl;
        fileMd << "Проанализировав эти графики, можно решить, какой из алгоритмов эффективнее";
        fileMd << std::endl;
        fileMd << std::endl;

        fileMd << "Сдесь можно увидеть выводы программы об эффективности алгоритмов в сравнении их друг с другом.";
        fileMd << std::endl;
        if (timeDivided1[0] > timeDivided2[0])
        {
            fileMd << "Скорее всего 1-й алгоритм эффективнее работает";
            fileMd << std::endl;
        }
        else if (timeDivided1[0] < timeDivided2[0])
        {
            fileMd << "Скорее всего 2-й алгоритм эффективнее работает";
            fileMd << std::endl;
        }
        else
        {
            fileMd << "Скорее всего оба алгоритма приблизительно равны по эффективности работы";
            fileMd << std::endl;
        }

        fileMd << std::endl;

        if (inputTime1[0] > inputTime2[0])
        {
            fileMd << "Скорее всего 1-й алгоритм эффективнее считывает данные из файла";
            fileMd << std::endl;
        }
        else if (inputTime1[0] < inputTime2[0])
        {
            fileMd << "Скорее всего 2-й алгоритм эффективнее считывает данные из файла";
            fileMd << std::endl;
        }
        else
        {
            fileMd << "Скорее всего оба алгоритма приблизительно равны по эффективности считывания данных из файла";
            fileMd << std::endl;
        }

        fileMd << std::endl;
        fileMd << std::endl;

        /// На английском
        fileMd << "Statistics for algorithms solving the problem of choosing canteens";
        fileMd << std::endl;
        fileMd << "Performed by Maxim Privalov";
        fileMd << std::endl;
        fileMd << "Link to the project's github:: https://github.com/maksonchek/CodeAnalise";
        fileMd << std::endl;
        fileMd << "The generated graphs can be found not only in the md file, but also in the build folder";
        fileMd << std::endl;
        fileMd << "The generated md file can be found in the build folder";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "The data (canteen numbers) were generated randomly. Each algorithm was analyzed on the same data set";
        fileMd << std::endl;
        fileMd << "Maximum number of canteens: " << n << ". " << "The step with which the number of canteens was selected: " << step << ". " << "The time measurements began with " << iterStartNum << " the number of canteens.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "Graph 1: shows the dependence of the time of reading data from the file by the first algorithm on the number of canteens.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation1.jpg](dataAnaliseVisualisation1.jpg)";
        fileMd << std::endl;
        fileMd << "Graph 2: shows the dependence of the ratio of the execution time of algorithm 1 to the number of canteens on the number of canteens.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation2.jpg](dataAnaliseVisualisation2.jpg)";
        fileMd << std::endl;
        fileMd << "Graph 3: shows the dependence of the time of reading data from the file by the second algorithm on the number of canteens.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation3.jpg](dataAnaliseVisualisation3.jpg)";
        fileMd << std::endl;
        fileMd << "Graph 4: shows the dependence of the ratio of the execution time of algorithm 2 to the number of canteens on the number of canteens.";
        fileMd << std::endl;
        fileMd << std::endl;
        fileMd << "![dataAnaliseVisualisation4.jpg](dataAnaliseVisualisation4.jpg)";
        fileMd << std::endl;
        fileMd << "After analyzing these graphs, you can decide which of the algorithms is more efficient.";     
        fileMd << std::endl;
        fileMd << std::endl;

        fileMd << "Here you can see the program's conclusions about the effectiveness of algorithms in comparison with each other.";
        fileMd << std::endl;
        if (timeDivided1[0] > timeDivided2[0])
        {
            fileMd << "Most likely, the 1st algorithm works more efficiently.";
            fileMd << std::endl;
        }
        else if (timeDivided1[0] < timeDivided2[0])
        {
            fileMd << "Most likely, the 2nd algorithm works more efficiently.";
            fileMd << std::endl;
        }
        else
        {
            fileMd << "Most likely, both algorithms are approximately equal in efficiency";
            fileMd << std::endl;
        }

        fileMd << std::endl;

        if (inputTime1[0] > inputTime2[0])
        {
            fileMd << "Most likely, the 1st algorithm reads data from the file more efficiently";
            fileMd << std::endl;
        }
        else if (inputTime1[0] < inputTime2[0])
        {
            fileMd << "Most likely, the 2nd algorithm reads data from the file more efficiently";
            fileMd << std::endl;
        }
        else
        {
            fileMd << "Most likely, both algorithms are approximately equal in efficiency of reading data from a file";
            fileMd << std::endl;
        }

    }
    fileMd.close();
    return 0;
}





