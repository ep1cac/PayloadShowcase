#include "crypt.h"
#include <stdio.h>

_Use_decl_annotations_
PBYTE
XORData(
	LPSTR key,
	PBYTE ct,
	size_t keySize,
	size_t textSize,
	PBYTE pt
)
{
	for (size_t i = 0; i < textSize; ++i)
	{
		pt[i] = ct[i] ^ key[i % keySize];
	}

	return pt;
}
