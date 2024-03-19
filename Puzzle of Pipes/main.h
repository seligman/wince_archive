#pragma once

#define POCKET_PC

#ifdef UNDER_CE
#pragma warning ( disable : 4201 )
#pragma warning ( disable : 4514 )
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

#ifndef UNDER_CE
#define _T(f)			f
#define _tcslen(f)		strlen(f)
#define _tcscpy(f,g)	strcpy(f,g)
#endif

#define MAINWND_GUID	_T("{8B7FFE90-2B48-11d4-B85C-00B0D040070E}")
#define MAINWND_CLASS	_T("PuzzleOfPipesClass")
#define MAINWND_TITLE	_T("Puzzle Of Pipes")

#define WM_USER_OBJECT	(WM_USER + 10)

#define PIPE_SIZE		28
#ifdef UNDER_CE
  #define PIPES_X			8
  #define PIPES_Y			8
#else
  #define PIPES_X			8
  #define PIPES_Y			8
//  #define PIPES_X			32
//  #define PIPES_Y			32
#endif

#define MAINWND_X	(16 + PIPES_X * PIPE_SIZE)
#ifdef POCKET_PC
#define Y_TOP		26
#else
#define Y_TOP		0
#endif
#define MAINWND_Y	(96 + PIPES_X * PIPE_SIZE) - Y_TOP

enum Pipes {
	PipeBlock,
	PipeCross,
	PipeVertical,
	PipeStartRight,
	PipeStartLeft,
	PipeStartBottom,
	PipeRightTop,
	PipeRightBottom,
	PipeLeftTop,
	PipeLeftBottom,
	PipeHorizontal,
	PipeBlank,
	PipeStartTop,
	PipeCount
};

enum Entries {
	Top,
	Bottom,
	Left,
	Right,
	Middle,
	Blocked
};

extern HINSTANCE g_hInstance;
