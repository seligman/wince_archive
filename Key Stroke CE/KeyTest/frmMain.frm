VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Key Test"
   ClientHeight    =   4965
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3735
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4965
   ScaleWidth      =   3735
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox pctCell 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      Height          =   1650
      Left            =   1920
      ScaleHeight     =   1650
      ScaleWidth      =   1650
      TabIndex        =   2
      Top             =   3120
      Visible         =   0   'False
      Width           =   1650
   End
   Begin VB.PictureBox pctMain 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      Height          =   1650
      Left            =   120
      ScaleHeight     =   1650
      ScaleWidth      =   1650
      TabIndex        =   1
      Top             =   3120
      Width           =   1650
   End
   Begin VB.TextBox txtMain 
      Height          =   2895
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   3375
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'http://www.mrl.nyu.edu/perlin/demos/quikwriting.html

Option Explicit

Private WithEvents m_Movement As clsMovement
Attribute m_Movement.VB_VarHelpID = -1

Private Sub Form_Load()

    pctCell.Width = 240 * 15
    pctCell.Height = 80 * 15
    Set pctCell.Picture = LoadPicture(App.Path & "\Cells.gif")
    Dim s As String
    Dim X As Long
    Dim Y As Long
    Dim n As Long
    
    For Y = 0 To 79
        For X = 0 To 239
            n = 9
            Select Case pctCell.Point(X * 15, Y * 15)
                Case RGB(20, 0, 0)
                    n = 0
                Case RGB(40, 0, 0)
                    n = 1
                Case RGB(60, 0, 0)
                    n = 2
                Case RGB(80, 0, 0)
                    n = 3
                Case RGB(100, 0, 0)
                    n = 4
                Case RGB(120, 0, 0)
                    n = 5
                Case RGB(140, 0, 0)
                    n = 6
                Case RGB(160, 0, 0)
                    n = 7
                Case RGB(180, 0, 0)
                    n = 8
                Case RGB(0, 0, 20)
                    n = 21
                Case RGB(0, 0, 40)
                    n = 22
                Case RGB(0, 0, 60)
                    n = 23
                Case RGB(0, 0, 80)
                    n = 24
                Case RGB(0, 0, 100)
                    n = 25
                Case RGB(0, 0, 120)
                    n = 26
                Case RGB(0, 0, 140)
                    n = 27
                Case RGB(0, 0, 160)
                    n = 28
            End Select
'            Debug.Assert n = 9
'            Debug.Print n
            s = s & Chr(n)
        Next
    Next
    Debug.Assert False
    Open "c:\documents and settings\scott\desktop\cells.dat" For Output As #1
    Print #1, s;
    Close #1
    End
    
            

    Set m_Movement = New clsMovement
    m_Movement.Init

End Sub

Private Sub m_Movement_CharEntered(nType As TypeEnum, sChar As String)

    Select Case nType
        Case tBackSpace
            If txtMain.SelLength > 0 Then
                txtMain.SelText = ""
            ElseIf txtMain.SelStart > 1 Then
                txtMain.SelStart = txtMain.SelStart - 1
                txtMain.SelLength = 1
                txtMain.SelText = ""
            End If
        Case tChar
            txtMain.SelText = sChar
        Case tEnter
            txtMain.SelText = vbNewLine
        Case tSpace
            txtMain.SelText = " "
    End Select

    Debug.Print sChar

End Sub

Private Sub m_Movement_NewMode(nMode As ModeEnum, bLock As Boolean)

    Dim sMode As String
    Select Case nMode
        Case mAlt: sMode = "Alt"
        Case mCap: sMode = "Cap"
        Case mNrm: sMode = "Nrm"
        Case mNum: sMode = "Num"
    End Select
    pctMain.Picture = LoadPicture(App.Path & "\" & sMode & IIf(bLock, "Locked", "") & ".gif")

End Sub

Private Sub pctMain_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)

    Select Case pctCell.Point(X, Y)
        Case RGB(20, 0, 0)
            m_Movement.IntoPosition 0
        Case RGB(40, 0, 0)
            m_Movement.IntoPosition 1
        Case RGB(60, 0, 0)
            m_Movement.IntoPosition 2
        Case RGB(80, 0, 0)
            m_Movement.IntoPosition 3
        Case RGB(100, 0, 0)
            m_Movement.IntoPosition 4
        Case RGB(120, 0, 0)
            m_Movement.IntoPosition 5
        Case RGB(140, 0, 0)
            m_Movement.IntoPosition 6
        Case RGB(160, 0, 0)
            m_Movement.IntoPosition 7
        Case RGB(180, 0, 0)
            m_Movement.IntoPosition 8
    End Select

End Sub
