#pragma once
#include "common.h"


PBYTE
XORData(
	_In_ LPSTR key,
	_In_ PBYTE ct,
	_In_ size_t keySize,
	_In_ size_t textSize,
	_Out_writes_bytes_(textSize) PBYTE pt
);
