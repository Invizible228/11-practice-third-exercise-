// ThirdEx.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(1251);

    HANDLE hEvent = CreateEvent(0, TRUE, FALSE, TEXT("MySyncRun"));
    if (hEvent)
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS) // первичный запуск
        {
            PROCESS_INFORMATION pi[3];
            memset(pi, 0, sizeof(pi));

            WCHAR fileName[MAX_PATH] = { 0 };
            GetModuleFileName(0, fileName, MAX_PATH);

            printf("Запуск процессов...\n");
            for (int i = 0; i < 3; i++)
            {
                STARTUPINFO si;
                memset(&si, 0, sizeof(si));
                if (!CreateProcess(fileName, 0, 0, 0, FALSE, CREATE_NEW_CONSOLE, 0, 0, &si, &pi[i]))
                    printf("Ошибка создания процесса!\n");
            }

            system("pause");

            printf("Сигнал синхронизации\n");
            SetEvent(hEvent);

            printf("Ожидание завершения работы процессов...\n");
            for (int i = 0; i < 3; i++)
            {
                if (pi[i].hProcess)
                    WaitForSingleObject(pi[i].hProcess, 500);
            }

            system("pause");
        }
        else // вторичный запуск
        {
            printf("Ожидание синхронизации...\n");
            WaitForSingleObject(hEvent, 1000);

            printf("Работа...\n");
            Sleep(3000);
        }

        CloseHandle(hEvent);
    }
    else
    {
        printf("Ошибка! CreateEvent\n");
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
