#include "stdafx.h"
#include <stdio.h>
#include <malloc.h>

#if defined(DEBUG) || defined(_DEBUG)

struct MEM_REF
{
	LPVOID		lpVoid;
	UINT		nLine;
	char		szFile[MAX_PATH];
	MEM_REF*	pmrNext;
};

MEM_REF * pmrFirst = NULL;
MEM_REF * pmrLast = NULL;

void tracker_Cleanup()
{
	MEM_REF * pmr;
	pmr = pmrFirst;

	if (pmr)
	{
		OutputDebugString(_T("---- Dump of all memory leaks\n"));
		while (pmr)
		{
			char szIn[MAX_PATH * 2];
			sprintf(szIn, "%s(%d): Never freed!\n", pmr->szFile, pmr->nLine);
			#ifdef UNDER_CE
				DWORD dwSize = strlen(szIn);
				DWORD count = mbstowcs(NULL, szIn, dwSize);
				LPWSTR szOut = (WCHAR *) malloc ((count + 1) * sizeof(WCHAR));
				memset(szOut, 0, ((count + 1) * sizeof(WCHAR)));
				mbstowcs(szOut, szIn, dwSize);
				OutputDebugString(szOut);
				free(szOut);
			#else
				OutputDebugString(szIn);
			#endif
			pmr = pmr->pmrNext;
		}
		OutputDebugString(_T("---- \n"));
	}
	else
	{
		OutputDebugString(_T("---- No memory leaks detected\n"));
	}

}

void tracker_Track(LPVOID s, UINT l, char * f)
{
	MEM_REF * pmr = (MEM_REF *) malloc(sizeof(MEM_REF));

	pmr->lpVoid = s;
	pmr->nLine = l;
	pmr->pmrNext = NULL;
	strcpy(pmr->szFile, f);

	if (pmrFirst == NULL)
	{
		pmrFirst = pmr;
		pmrLast = pmr;
	}
	else
	{
		pmrLast->pmrNext = pmr;
		pmrLast = pmr;
	}
}

void tracker_Untrack(LPVOID lpv)
{
	bool bFound = false;
	MEM_REF * pmr = NULL;
	MEM_REF * pmrPrev = NULL;
	pmr = pmrFirst;
	while (!bFound && pmr)
	{
		if (pmr->lpVoid == lpv)
		{
			bFound = true;
		}
		else
		{
			pmrPrev = pmr;
			pmr = pmr->pmrNext;
		}
	}
	if (!bFound)
	{
		OutputDebugString(_T("Error!  Attempt to uninitalize unalloced memory!\n"));
		return;
	}
	if (pmrFirst == pmr)
	{
		pmrFirst = pmr->pmrNext;
	}
	if (pmrLast == pmr)
	{
		pmrLast = pmrPrev;
	}
	if (pmrPrev)
	{
		pmrPrev->pmrNext = pmr->pmrNext;
	}
	free(pmr);
}

#endif //DEBUG
