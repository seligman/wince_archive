VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsMovement"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Enum ModeEnum
    mNrm = 0
    mCap = 1
    mAlt = 2
    mNum = 3
End Enum

Public Enum TypeEnum
    tChar = 0
    tCap = 1
    tAlt = 2
    tNum = 3
    tEnter = 4
    tBackSpace = 5
    tSpace = 6
    tNothing = 7
End Enum

Public m_nCurMode As ModeEnum
Private m_bModeLocked As Boolean

Private m_nTypes(0 To 3, 0 To 8, 0 To 8) As TypeEnum 'Mode,From,To
Private m_nChars(0 To 3, 0 To 8, 0 To 8) As String * 1

Private m_nLastPos1 As Long
Private m_nLastPos2 As Long

Public Event CharEntered(nType As TypeEnum, sChar As String)
Public Event NewMode(nMode As ModeEnum, bLock As Boolean)

Public Function GetMode() As ModeEnum
    GetMode = m_nCurMode
End Function

Public Sub Reset() 'on mousedown

    m_nLastPos1 = 4
    m_nLastPos2 = 4

End Sub

Public Sub IntoPosition(nPos As Long)

    Dim nType As TypeEnum
    Dim sChar As String

    nType = tNothing

    If nPos = 4 Then
        If m_nLastPos1 <> 4 Then
            If m_nLastPos2 = 4 Then
                m_nLastPos2 = m_nLastPos1
                m_nLastPos1 = 4
            End If
            nType = m_nTypes(m_nCurMode, m_nLastPos2, m_nLastPos1)
            sChar = m_nChars(m_nCurMode, m_nLastPos2, m_nLastPos1)
            m_nLastPos1 = 4
            m_nLastPos2 = 4
        End If
    Else
        If nPos <> m_nLastPos1 Then
            If m_nLastPos2 = 4 Then
                m_nLastPos2 = m_nLastPos1
            End If
            m_nLastPos1 = nPos
        End If
    End If
    
    If nType <> tNothing Then
        RaiseEvent CharEntered(nType, sChar)
        If nType = tAlt Or nType = tCap Or nType = tNum Then
            If m_nCurMode = nType Then
                If m_bModeLocked Then
                    m_bModeLocked = False
                    m_nCurMode = mNrm
                    RaiseEvent NewMode(m_nCurMode, False)
                Else
                    m_bModeLocked = True
                    RaiseEvent NewMode(m_nCurMode, True)
                End If
            Else
                m_bModeLocked = False
                m_nCurMode = nType
                RaiseEvent NewMode(m_nCurMode, False)
            End If
        ElseIf m_bModeLocked = False And m_nCurMode <> mNrm Then
            m_nCurMode = mNrm
            RaiseEvent NewMode(m_nCurMode, False)
        End If
    End If

End Sub

Public Sub GetInfo(ByVal x As Long, ByVal y As Long, nType As TypeEnum, sChar As String)

    nType = tNothing
    sChar = ""
    
    Dim nFrom As Long
    Dim nTo As Long
    
    nFrom = ((x) \ 3) + (((y) \ 3) * 3)
    nTo = ((x) Mod 3) + (((y) Mod 3) * 3)

    If nTo <> 4 Then
        If nFrom = nTo Then
            nTo = 4
        End If
    
        nType = m_nTypes(m_nCurMode, nFrom, nTo)
        sChar = m_nChars(m_nCurMode, nFrom, nTo)
    End If

End Sub

Private Sub SetupArray()

    Dim m As Long
    Dim f As Long
    Dim t As Long
    
    For m = 0 To 3
        For f = 0 To 8
            For t = 0 To 8
                m_nTypes(m, f, t) = tNothing
            Next
        Next
    Next
    
    For m = 0 To 3
        m_nTypes(m, 1, 0) = tAlt 'Square
        m_nTypes(m, 1, 4) = tBackSpace
        m_nTypes(m, 1, 2) = tCap 'Up
        m_nTypes(m, 7, 6) = tEnter
        m_nTypes(m, 7, 4) = tSpace
        m_nTypes(m, 7, 8) = tNum 'Circle
    Next
    
    '0 1 2
    '3 4 5
    '6 7 8

    '0 - Normal
    m_nTypes(0, 0, 6) = tChar: m_nChars(0, 0, 6) = "q"
    m_nTypes(0, 0, 3) = tChar: m_nChars(0, 0, 3) = "m"
    m_nTypes(0, 0, 4) = tChar: m_nChars(0, 0, 4) = "a"
    m_nTypes(0, 0, 1) = tChar: m_nChars(0, 0, 1) = "s"
    m_nTypes(0, 0, 2) = tChar: m_nChars(0, 0, 2) = "k"

    m_nTypes(0, 3, 0) = tChar: m_nChars(0, 3, 0) = "h"
    m_nTypes(0, 3, 4) = tChar: m_nChars(0, 3, 4) = "e"
    m_nTypes(0, 3, 6) = tChar: m_nChars(0, 3, 6) = "c"

    m_nTypes(0, 6, 0) = tChar: m_nChars(0, 6, 0) = "v"
    m_nTypes(0, 6, 3) = tChar: m_nChars(0, 6, 3) = "w"
    m_nTypes(0, 6, 4) = tChar: m_nChars(0, 6, 4) = "o"
    m_nTypes(0, 6, 7) = tChar: m_nChars(0, 6, 7) = "g"
    m_nTypes(0, 6, 8) = tChar: m_nChars(0, 6, 8) = "z"

    m_nTypes(0, 2, 0) = tChar: m_nChars(0, 2, 0) = "p"
    m_nTypes(0, 2, 1) = tChar: m_nChars(0, 2, 1) = "f"
    m_nTypes(0, 2, 4) = tChar: m_nChars(0, 2, 4) = "n"
    m_nTypes(0, 2, 5) = tChar: m_nChars(0, 2, 5) = "l"
    m_nTypes(0, 2, 8) = tChar: m_nChars(0, 2, 8) = "x"

    m_nTypes(0, 5, 2) = tChar: m_nChars(0, 5, 2) = "u"
    m_nTypes(0, 5, 4) = tChar: m_nChars(0, 5, 4) = "t"
    m_nTypes(0, 5, 8) = tChar: m_nChars(0, 5, 8) = "y"
    
    m_nTypes(0, 8, 6) = tChar: m_nChars(0, 8, 6) = "b"
    m_nTypes(0, 8, 7) = tChar: m_nChars(0, 8, 7) = "d"
    m_nTypes(0, 8, 4) = tChar: m_nChars(0, 8, 4) = "i"
    m_nTypes(0, 8, 5) = tChar: m_nChars(0, 8, 5) = "r"
    m_nTypes(0, 8, 2) = tChar: m_nChars(0, 8, 2) = "j"

    '1 - Upper Case
    m_nTypes(1, 0, 6) = tChar: m_nChars(1, 0, 6) = "Q"
    m_nTypes(1, 0, 3) = tChar: m_nChars(1, 0, 3) = "M"
    m_nTypes(1, 0, 4) = tChar: m_nChars(1, 0, 4) = "A"
    m_nTypes(1, 0, 1) = tChar: m_nChars(1, 0, 1) = "S"
    m_nTypes(1, 0, 2) = tChar: m_nChars(1, 0, 2) = "K"

    m_nTypes(1, 3, 0) = tChar: m_nChars(1, 3, 0) = "H"
    m_nTypes(1, 3, 4) = tChar: m_nChars(1, 3, 4) = "E"
    m_nTypes(1, 3, 6) = tChar: m_nChars(1, 3, 6) = "C"

    m_nTypes(1, 6, 0) = tChar: m_nChars(1, 6, 0) = "V"
    m_nTypes(1, 6, 3) = tChar: m_nChars(1, 6, 3) = "W"
    m_nTypes(1, 6, 4) = tChar: m_nChars(1, 6, 4) = "O"
    m_nTypes(1, 6, 7) = tChar: m_nChars(1, 6, 7) = "G"
    m_nTypes(1, 6, 8) = tChar: m_nChars(1, 6, 8) = "Z"

    m_nTypes(1, 2, 0) = tChar: m_nChars(1, 2, 0) = "P"
    m_nTypes(1, 2, 1) = tChar: m_nChars(1, 2, 1) = "F"
    m_nTypes(1, 2, 4) = tChar: m_nChars(1, 2, 4) = "N"
    m_nTypes(1, 2, 5) = tChar: m_nChars(1, 2, 5) = "L"
    m_nTypes(1, 2, 8) = tChar: m_nChars(1, 2, 8) = "X"

    m_nTypes(1, 5, 2) = tChar: m_nChars(1, 5, 2) = "U"
    m_nTypes(1, 5, 4) = tChar: m_nChars(1, 5, 4) = "T"
    m_nTypes(1, 5, 8) = tChar: m_nChars(1, 5, 8) = "Y"
    
    m_nTypes(1, 8, 6) = tChar: m_nChars(1, 8, 6) = "B"
    m_nTypes(1, 8, 7) = tChar: m_nChars(1, 8, 7) = "D"
    m_nTypes(1, 8, 4) = tChar: m_nChars(1, 8, 4) = "I"
    m_nTypes(1, 8, 5) = tChar: m_nChars(1, 8, 5) = "R"
    m_nTypes(1, 8, 2) = tChar: m_nChars(1, 8, 2) = "J"

    '2 - Alt / Symbols
    m_nTypes(2, 0, 6) = tNothing
    m_nTypes(2, 0, 3) = tChar: m_nChars(2, 0, 3) = "@"
    m_nTypes(2, 0, 4) = tChar: m_nChars(2, 0, 4) = "/"
    m_nTypes(2, 0, 1) = tChar: m_nChars(2, 0, 1) = "\"
    m_nTypes(2, 0, 2) = tChar: m_nChars(2, 0, 2) = "|"

    m_nTypes(2, 3, 0) = tChar: m_nChars(2, 3, 0) = "#"
    m_nTypes(2, 3, 4) = tChar: m_nChars(2, 3, 4) = ";"
    m_nTypes(2, 3, 6) = tChar: m_nChars(2, 3, 6) = ":"

    m_nTypes(2, 6, 0) = tChar: m_nChars(2, 6, 0) = "^"
    m_nTypes(2, 6, 3) = tChar: m_nChars(2, 6, 3) = "*"
    m_nTypes(2, 6, 4) = tChar: m_nChars(2, 6, 4) = "*"
    m_nTypes(2, 6, 7) = tChar: m_nChars(2, 6, 7) = "{"
    m_nTypes(2, 6, 8) = tChar: m_nChars(2, 6, 8) = "}"

    m_nTypes(2, 2, 0) = tChar: m_nChars(2, 2, 0) = "("
    m_nTypes(2, 2, 1) = tChar: m_nChars(2, 2, 1) = ")"
    m_nTypes(2, 2, 4) = tChar: m_nChars(2, 2, 4) = ","
    m_nTypes(2, 2, 5) = tChar: m_nChars(2, 2, 5) = "["
    m_nTypes(2, 2, 8) = tChar: m_nChars(2, 2, 8) = "]"

    m_nTypes(2, 5, 2) = tChar: m_nChars(2, 5, 2) = """"
    m_nTypes(2, 5, 4) = tChar: m_nChars(2, 5, 4) = "'"
    m_nTypes(2, 5, 8) = tChar: m_nChars(2, 5, 8) = "&"
    
    m_nTypes(2, 8, 6) = tChar: m_nChars(2, 8, 6) = "_"
    m_nTypes(2, 8, 7) = tChar: m_nChars(2, 8, 7) = "-"
    m_nTypes(2, 8, 4) = tChar: m_nChars(2, 8, 4) = "."
    m_nTypes(2, 8, 5) = tChar: m_nChars(2, 8, 5) = "?"
    m_nTypes(2, 8, 2) = tChar: m_nChars(2, 8, 2) = "!"

    '3 - Numbers
    m_nTypes(3, 0, 6) = tChar: m_nChars(3, 0, 6) = "2"
    m_nTypes(3, 0, 3) = tChar: m_nChars(3, 0, 3) = "1"
    m_nTypes(3, 0, 4) = tChar: m_nChars(3, 0, 4) = "0"
    m_nTypes(3, 0, 1) = tChar: m_nChars(3, 0, 1) = "<"
    m_nTypes(3, 0, 2) = tChar: m_nChars(3, 0, 2) = ">"

    m_nTypes(3, 3, 0) = tChar: m_nChars(3, 3, 0) = "#"
    m_nTypes(3, 3, 4) = tChar: m_nChars(3, 3, 4) = "3"
    m_nTypes(3, 3, 6) = tChar: m_nChars(3, 3, 6) = "4"

    m_nTypes(3, 6, 0) = tChar: m_nChars(3, 6, 0) = "/"
    m_nTypes(3, 6, 3) = tChar: m_nChars(3, 6, 3) = "*"
    m_nTypes(3, 6, 4) = tChar: m_nChars(3, 6, 4) = "5"
    m_nTypes(3, 6, 7) = tChar: m_nChars(3, 6, 7) = "6"
    m_nTypes(3, 6, 8) = tChar: m_nChars(3, 6, 8) = "7"

    m_nTypes(3, 2, 0) = tChar: m_nChars(3, 2, 0) = "("
    m_nTypes(3, 2, 1) = tChar: m_nChars(3, 2, 1) = ")"
    m_nTypes(3, 2, 4) = tChar: m_nChars(3, 2, 4) = ","
    m_nTypes(3, 2, 5) = tChar: m_nChars(3, 2, 5) = "["
    m_nTypes(3, 2, 8) = tChar: m_nChars(3, 2, 8) = "]"

    m_nTypes(3, 5, 2) = tChar: m_nChars(3, 5, 2) = "+"
    m_nTypes(3, 5, 4) = tChar: m_nChars(3, 5, 4) = "="
    m_nTypes(3, 5, 8) = tChar: m_nChars(3, 5, 8) = "-"
    
    m_nTypes(3, 8, 6) = tChar: m_nChars(3, 8, 6) = "$"
    m_nTypes(3, 8, 7) = tChar: m_nChars(3, 8, 7) = "%"
    m_nTypes(3, 8, 4) = tChar: m_nChars(3, 8, 4) = "."
    m_nTypes(3, 8, 5) = tChar: m_nChars(3, 8, 5) = "8"
    m_nTypes(3, 8, 2) = tChar: m_nChars(3, 8, 2) = "9"

    
End Sub

Public Sub Init()

    m_nLastPos1 = 4
    m_nLastPos2 = 4
    m_nCurMode = mNrm
    m_bModeLocked = False
    
    RaiseEvent NewMode(m_nCurMode, False)
    
    SetupArray

End Sub
