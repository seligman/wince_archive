VERSION 5.00
Begin VB.Form frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "Form1"
   ClientHeight    =   8850
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9885
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   8850
   ScaleWidth      =   9885
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox pctSmaller 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   495
      Left            =   4320
      ScaleHeight     =   495
      ScaleWidth      =   1215
      TabIndex        =   1
      Top             =   4200
      Width           =   1215
   End
   Begin VB.PictureBox pctMain 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   120
      ScaleHeight     =   375
      ScaleWidth      =   615
      TabIndex        =   0
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function PolyBezier Lib "gdi32" (ByVal hdc As Long, lppt As POINTAPI, ByVal cPoints As Long) As Long
Private Type POINTAPI
    x As Long
    y As Long
End Type
Private m_bDown As Boolean

Private Sub Form_Click()

   m_bDown = True

   'DrawLines
   'DoEvents
   'DrawLetters mNrm
   'DoEvents
   LoadBG
   DrawPad
   DoEvents
   
   MakeSmaller
   
   Dim sFile As String
   sFile = App.Path & "\keypad_down.bmp"
   If Dir(sFile) <> "" Then Kill sFile
   SavePicture pctSmaller.Image, sFile
   Unload Me

End Sub

Private Sub LoadBG()

    pctSmaller.Picture = LoadPicture(App.Path & "\keypad_down_bg.bmp")
    Dim x As Long
    Dim y As Long
    Dim x2 As Long
    Dim y2 As Long
    For x = 0 To 79
        For y = 0 To 79
            For x2 = 0 To 3
                For y2 = 0 To 3
                    pctMain.PSet ((x * 4 + x2) * 15, 15 * (y * 4 + y2)), pctSmaller.Point(x * 15, 15 * y)
                Next
            Next
        Next
        DoEvents
    Next

End Sub

Private Sub DrawPad()

'   pctMain.BackColor = RGB(128, 128, 128)
'   pctMain.Cls
   
   FindSmallest

   Dim x As Long
   Dim y As Long
   
   DrawButton 0, 0, 40, 19, "Tab", False 'Tab 20
   DrawButton 40, 0, 40, 19, "BkSp", False 'Bksp 21
   
   DrawButton 0, 19, 20, 20, "Esc", False ' Escape 22
   DrawButton 20, 19, 20, 20, Chr(147), True ' Up 23 147
   DrawButton 40, 19, 20, 20, "Del", False ' Delete 24

   DrawButton 0, 39, 20, 19, Chr(145), True ' left 26 145
   DrawButton 20, 39, 20, 19, Chr(148), True ' down 27 148
   DrawButton 40, 39, 20, 19, Chr(146), True ' right 28 146
   
   DrawButton 0, 58, 40, 20, "", False 'space 29

pctMain.FontSize = pctMain.FontSize * 2
   DrawButton 60, 19, 20, 59, "", True, 1 '25 enter "8"
   DrawButton 40, 58, 40, 20, "8", True, 2
   
   
   

'
   

End Sub

Private Sub DrawButton(ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, sChar As String, bSpecial As Boolean, Optional zEnter As Long = 0)

   x = x * 4 * 15
   y = y * 4 * 15
   cx = cx * 4 * 15
   cy = cy * 4 * 15

   Dim bg As OLE_COLOR
   Dim fg As OLE_COLOR
   Dim tmp As OLE_COLOR
   
   bg = RGB(64, 64, 64)
   fg = RGB(196, 196, 196)
   
   If m_bDown Then
      tmp = bg
      bg = fg
      fg = tmp
   End If

   Dim c As Long
   For c = 0 To 7 * 15 Step 15
      'pctMain.Line (x + c, y + cy - c)-(x + cx - c, y + cy - c), bg
      'pctMain.Line (x + cx - c, y + c)-(x + cx - c, y + cy - c), bg
      
      'pctMain.PSet (x + cx - c, y + cy - c), bg
      
      If zEnter = 2 Then
         'pctMain.Line (x + c, y + c)-(x + cx - (20 * 4 * 15), y + c), fg
      Else
         'pctMain.Line (x + c, y + c)-(x + cx - c, y + c), fg
      End If
      If zEnter = 1 Then
         'pctMain.Line (x + c, y + c)-(x + c, y + cy - (((20 * 4) - 8) * 15)), fg
      Else
         'pctMain.Line (x + c, y + c)-(x + c, y + cy - c), fg
      End If
      
   Next

   If bSpecial Then
      pctMain.FontName = "Wingdings 3"
   Else
      pctMain.FontName = "Arial"
   End If
   
   pctMain.CurrentX = (x + (cx / 2)) - (pctMain.TextWidth(sChar) / 2)
   pctMain.CurrentY = (y + (cy / 2)) - (pctMain.TextHeight(sChar) / 2)
   If m_bDown Then
      pctMain.CurrentX = pctMain.CurrentX + 4 * 15
      pctMain.CurrentY = pctMain.CurrentY + 4 * 15
   End If
   
   pctMain.Print sChar;

End Sub

Private Sub MakeSmaller()

    Dim x As Long
    Dim y As Long
    
    Dim x2 As Long
    Dim y2 As Long
    
    Dim r As Long
    Dim g As Long
    Dim b As Long
'    Dim c As Long
    
    For x = 0 To 159
        For y = 0 To 79
        
            r = 0
            g = 0
            b = 0
            For x2 = 0 To 3
                For y2 = 0 To 3
                    r = r + (pctMain.Point((x * 4 + x2) * 15, (y * 4 + y2) * 15) And &HFF&)
                    g = g + (pctMain.Point((x * 4 + x2) * 15, (y * 4 + y2) * 15) And &HFF00&) \ &H100&
                    b = b + (pctMain.Point((x * 4 + x2) * 15, (y * 4 + y2) * 15) And &HFF0000) \ &H10000
                Next
            Next
            r = r \ 16
            g = g \ 16
            b = b \ 16
            pctSmaller.PSet (x * 15, y * 15), RGB(r, g, b)
        Next
        DoEvents
    Next
                    
End Sub

Private Sub FindSmallest()

    Dim nc As Double
    nc = 80 / 9

    Dim nTry As Double
    Dim sMaxX As String
    Dim sMaxY As String
    Dim i As Long
    
    pctMain.FontSize = 100
    For i = 33 To 126
        If pctMain.TextWidth(sMaxX) < pctMain.TextWidth(Chr(i)) Then
            sMaxX = Chr(i)
        End If
        If pctMain.TextHeight(sMaxY) < pctMain.TextHeight(Chr(i)) Then
            sMaxY = Chr(i)
        End If
    Next

    nTry = 40
    pctMain.FontSize = nTry
    Do
        nTry = nTry - 0.1
        pctMain.FontSize = nTry
    Loop Until pctMain.TextHeight(sMaxY) < nc * 15 * 4 And pctMain.TextWidth(sMaxX) < nc * 15 * 4
    
    nTry = pctMain.FontSize
    
End Sub

Private Sub DrawLetters(nTheMode As ModeEnum)

   FindSmallest

    'Debug.Print pctMain.FontSize, sMaxX, sMaxY

    Dim x As Long
    Dim y As Long
    
    Dim mvm As New clsMovement
    mvm.Init
    Dim nType As TypeEnum
    Dim s As String
    Dim z As Long
    mvm.m_nCurMode = nTheMode
    For z = 1 To 1
    
        DoIt z, mvm, 0, 0, 2, 0, 0, 0
        DoIt z, mvm, 1, 0, 2, 0, 1, 0
        DoIt z, mvm, 2, 0, 2, 0, 2, 0
        DoIt z, mvm, 0, 1, 2, 0, 0, 1
        DoIt z, mvm, 0, 2, 2, 0, 0, 2
        
        DoIt z, mvm, 0, 3, 1, 2.5, 0, 0
        DoIt z, mvm, 0, 4, 1, 2.5, 0, 1
        DoIt z, mvm, 0, 5, 1, 2.5, 0, 2
        
        DoIt z, mvm, 0, 6, 0, 5, 0, 0
        DoIt z, mvm, 0, 7, 0, 5, 0, 1
        DoIt z, mvm, 0, 8, 0, 5, 0, 2
        DoIt z, mvm, 1, 8, 0, 5, 1, 2
        DoIt z, mvm, 2, 8, 0, 5, 2, 2
        
        DoIt z, mvm, 3, 0, 8, 0, 0, 0
        DoIt z, mvm, 4, 0, 8, 0, 1, 0
        DoIt z, mvm, 5, 0, 8, 0, 2, 0
    
        '---
        'start here
        DoIt z, mvm, 6, 0, 17, 0, -2, 0
        DoIt z, mvm, 7, 0, 17, 0, -1, 0
        DoIt z, mvm, 8, 0, 17, 0, 0, 0
        DoIt z, mvm, 8, 1, 17, 0, 0, 1
        DoIt z, mvm, 8, 2, 17, 0, 0, 2
        
        DoIt z, mvm, 8, 3, 16, 2.5, 0, 0
        DoIt z, mvm, 8, 4, 16, 2.5, 0, 1
        DoIt z, mvm, 8, 5, 16, 2.5, 0, 2
        
        DoIt z, mvm, 8, 6, 12, 5, 2, 0
        DoIt z, mvm, 8, 7, 12, 5, 2, 1
        DoIt z, mvm, 8, 8, 12, 5, 2, 2
        DoIt z, mvm, 7, 8, 12, 5, 1, 2
        DoIt z, mvm, 6, 8, 12, 5, 0, 2
        
        DoIt z, mvm, 3, 8, 6, 8, 0, 0
        DoIt z, mvm, 4, 8, 6, 8, 1, 0
        DoIt z, mvm, 5, 8, 6, 8, 2, 0
    Next
 
End Sub
'mvmt
'grid start
'4x4 place
Private Sub DoIt(z As Long, mvm As clsMovement, x1 As Double, y1 As Double, x2 As Double, y2 As Double, x3 As Double, y3 As Double)
    Dim s As String
    Dim nType As TypeEnum
    Dim nc As Double
    Dim nc2 As Double
    nc = 80 / 9
    nc2 = 160 / 13.5
    
    mvm.GetInfo x1, y1, nType, s
    
    pctMain.FontName = "Arial"
    pctMain.ForeColor = RGB(0, 0, 128)
    Select Case nType
        Case tAlt
            
            s = "#"
        Case tBackSpace
            s = "¡"
            pctMain.FontName = "WingDings 3"
        Case tCap
            s = "A"
        Case tChar
            pctMain.ForeColor = vbBlack
        Case tEnter
            pctMain.FontName = "WingDings 3"
            s = "8"
        Case tNothing
            s = ""
        Case tNum
            s = "3"
        Case tSpace
            pctMain.FontName = "WingDings 3"
            s = "¢"
    End Select
            
    
'    Dim bTwo As Boolean
'    bTwo = True
'    pctMain.CurrentX = (x2 * nc * 4 * 15) + (x3 * nc2 * 4 * 15)
'    pctMain.CurrentY = (y2 * nc * 4 * 15) + (y3 * nc2 * 4 * 15)
'    If nType = tNum Then
'        Dim i As Long
'        For i = nc * 2 * 15 To 0 Step -1
'            pctMain.CurrentX = (x2 * nc * 4 * 15) + (x3 * nc2 * 4 * 15)
'            pctMain.CurrentY = (y2 * nc * 4 * 15) + (y3 * nc2 * 4 * 15)
'            If bTwo Then
'                pctMain.Circle (pctMain.CurrentX + (pctMain.TextWidth(s) / 2), (pctMain.TextHeight(s) / 2) + pctMain.CurrentY), i, RGB(128, 128, 255)
'            Else
'                pctMain.Circle (pctMain.CurrentX + (pctMain.TextWidth(s) / 2), (pctMain.TextHeight(s) / 2) + pctMain.CurrentY), i, RGB(0, 0, 128)
'                Exit For
'            End If
'        Next
'        If bTwo Then
'            pctMain.ForeColor = vbWhite
'        End If
'    End If
    pctMain.CurrentX = (x2 * nc * 4 * 15) + (x3 * nc2 * 4 * 15)
    pctMain.CurrentY = (y2 * nc * 4 * 15) + (y3 * nc2 * 4 * 15)
    
    'pctMain.CurrentX = x2 * nc * 4 * 15 + ((nc * 4 * 15 - TextWidth(s)) / 2)
    'pctMain.CurrentY = y2 * nc * 4 * 15
    pctMain.Print s

End Sub

Private Sub DrawLines()

    Dim pts(0 To 6) As POINTAPI
    
    pctMain.Circle (pctMain.Width / 2, pctMain.Height / 2), (80 / 9) * 1.5 * 4 * 15
    
    Dim nc As Double
    nc = 80 / 9
    Dim z As Long
    For z = 1 To 2
        sp pts(), 0, nc, z, 7, 0
        sp pts(), 1, nc, z, 7.5, 3
        sp pts(), 2, nc, z, 7.5, 3
        sp pts(), 3, nc, z, 2, 4
        PolyBezier pctMain.hdc, pts(0), 4
        
        sp pts(), 0, nc, z, 1, 2.5
        sp pts(), 1, nc, z, 8.5, 4
        sp pts(), 2, nc, z, 8.5, 5
        sp pts(), 3, nc, z, 1, 6.5
        PolyBezier pctMain.hdc, pts(0), 4
        
        sp pts(), 0, nc, z, 0, 5
        sp pts(), 1, nc, z, 7.5, 6
        sp pts(), 2, nc, z, 7.5, 6
        sp pts(), 3, nc, z, 4.5, 9
        PolyBezier pctMain.hdc, pts(0), 4
        
        sp pts(), 0, nc, z, 5, 9
        sp pts(), 1, nc, z, 9, 6
        sp pts(), 2, nc, z, 9, 6
        sp pts(), 3, nc, z, 11, 9
        PolyBezier pctMain.hdc, pts(0), 4
    Next

End Sub

Private Sub sp(pts() As POINTAPI, n, nc, z, x, y)

    If z = 2 Then
        x = 2 + (16 - x)
        y = 9 - y
        '
    End If
    pts(n).x = x * nc * 4
    pts(n).y = y * nc * 4

End Sub


Private Sub Form_Load()

    pctMain.Width = 160 * 4 * 15
    pctMain.Height = 80 * 4 * 15
    
    'pctSmaller.Width = 160 * 15
    pctSmaller.Width = 80 * 15
    pctSmaller.Height = 80 * 15
    
    pctMain.Top = 15 * 15
    pctMain.Left = 15 * 15
    
    pctSmaller.Top = pctMain.Top + pctMain.Height + 15 * 15
    pctSmaller.Left = 15 * 15
    
    Me.Width = Width - ScaleWidth + pctMain.Width + 30 * 15
    Height = Height - ScaleHeight + pctMain.Height + pctSmaller.Height + 45 * 15

    'pctMain.Visible = False

End Sub
