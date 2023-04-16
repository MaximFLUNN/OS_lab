#include <windows.h>
#include <stdio.h>

int volatile Var = 10;

#define MAX_THREADS 20
#define CYCLE 100000
#define BUF_SIZE 255
#define ERRORCODE -1

DWORD WINAPI PlusVar(LPVOID lpParam);
DWORD WINAPI MinusVar(LPVOID lpParam);

int main(int argc, char* argv[]) {
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS];
    // Создание потоков в нужном кол-ве
    for (int i = 0; i < MAX_THREADS; i++) {
        // Создайте поток, который начнет выполнение самостоятельно.
        hThreadArray[i] = CreateThread(
            NULL,                   // атрибуты безопасности по умолчанию
            NULL,                      // используйте размер стека по умолчанию  
            (i >= MAX_THREADS / 2 ? PlusVar : MinusVar),       // имя функции потока
            NULL,          // аргумент для потоковой функции 
            NULL,                      // используйте флаги создания по умолчанию 
            &dwThreadIdArray[i]);   // возвращает идентификатор потока 


        // Проверяем возвращаемое значение на предмет успеха.
        // Если CreateThread завершается с ошибкой, завершите выполнение. 
        // Это автоматически очистит потоки и память. 
        if (hThreadArray[i] == NULL) {
            printf("Erorr create thread #%d\n", i);
            ExitProcess(ERRORCODE);
        }
    } // Завершение цикла создания основного потока.

    // Ждём, пока все потоки не завершатся.
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Закрываем все дескрипторы потоков и освобождаем выделенную память.
    for (int i = 0; i < MAX_THREADS; i++) {
        CloseHandle(hThreadArray[i]);
    }
    printf("%d", Var);
    return 0;
}

DWORD WINAPI PlusVar(LPVOID lpParam) {
    for (int i = 0; i < CYCLE; i++)
        ++Var;
    return 0;
}
DWORD WINAPI MinusVar(LPVOID lpParam) {
    for (int i = 0; i < CYCLE; i++)
        --Var;
    return 0;
}
