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
    // �������� ������� � ������ ���-��
    for (int i = 0; i < MAX_THREADS; i++) {
        // �������� �����, ������� ������ ���������� ��������������.
        hThreadArray[i] = CreateThread(
            NULL,                   // �������� ������������ �� ���������
            NULL,                      // ����������� ������ ����� �� ���������  
            (i >= MAX_THREADS / 2 ? PlusVar : MinusVar),       // ��� ������� ������
            NULL,          // �������� ��� ��������� ������� 
            NULL,                      // ����������� ����� �������� �� ��������� 
            &dwThreadIdArray[i]);   // ���������� ������������� ������ 


        // ��������� ������������ �������� �� ������� ������.
        // ���� CreateThread ����������� � �������, ��������� ����������. 
        // ��� ������������� ������� ������ � ������. 
        if (hThreadArray[i] == NULL) {
            printf("Erorr create thread #%d\n", i);
            ExitProcess(ERRORCODE);
        }
    } // ���������� ����� �������� ��������� ������.

    // ���, ���� ��� ������ �� ����������.
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // ��������� ��� ����������� ������� � ����������� ���������� ������.
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
