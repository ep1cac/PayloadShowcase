#pragma once

#include "common.h"

#include <tlhelp32.h>
#include <tchar.h>

DWORD
WINAPI
GetProcessByName(
	_In_ LPWSTR lpProcessName
);


DWORD
WINAPI
ExecuteRemoteThread(
	_In_ DWORD dwProcId,
	_In_ PBYTE pbShellCode,
	_In_ size_t shellCodeSize
);
