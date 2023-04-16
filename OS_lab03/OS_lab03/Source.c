#include <windows.h>
#include <stdio.h>
#include <tchar.h>	

int main(int argc, TCHAR* argv[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

    // Запускаем дочерний процесс. 
    if (!CreateProcess(
        TEXT("C:\\Windows\\notepad.exe"), // Запускаемый модуль, при вызове system("notepad") при закрытии ошибка 87
        argv[1],               // Командная строка.
        NULL,                  // Дескриптор процесса не наследуемый.
        NULL,                  // Дескриптор потока не наследуемый.
        FALSE,                 // Установим наследование дескриптора в FALSE.
        0,                     // Флажков создания нет.
        NULL,                  // Используйте блок конфигурации родителя.
        NULL,                  // Используйте блок конфигурации родителя.
        &si,                   // Указатель на структуру STARTUPINFO.
        &pi)                   // Указатель на структуру PROCESS_INFORMATION.
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Ждать до тех пор, пока дочерний процесс не выйдет из работы.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Закроем дескрипторы процесса и потока.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
	return 0;
}