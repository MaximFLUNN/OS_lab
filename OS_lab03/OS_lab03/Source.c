#include <windows.h>
#include <stdio.h>
#include <tchar.h>	

int main(int argc, TCHAR* argv[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

    // ��������� �������� �������. 
    if (!CreateProcess(
        TEXT("C:\\Windows\\notepad.exe"), // ����������� ������, ��� ������ system("notepad") ��� �������� ������ 87
        argv[1],               // ��������� ������.
        NULL,                  // ���������� �������� �� �����������.
        NULL,                  // ���������� ������ �� �����������.
        FALSE,                 // ��������� ������������ ����������� � FALSE.
        0,                     // ������� �������� ���.
        NULL,                  // ����������� ���� ������������ ��������.
        NULL,                  // ����������� ���� ������������ ��������.
        &si,                   // ��������� �� ��������� STARTUPINFO.
        &pi)                   // ��������� �� ��������� PROCESS_INFORMATION.
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // ����� �� ��� ���, ���� �������� ������� �� ������ �� ������.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ������� ����������� �������� � ������.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
	return 0;
}