VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox pctMain 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   495
      Left            =   1740
      ScaleHeight     =   495
      ScaleWidth      =   1215
      TabIndex        =   1
      Top             =   660
      Width           =   1215
   End
   Begin VB.PictureBox pctOther 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   495
      Left            =   1740
      ScaleHeight     =   495
      ScaleWidth      =   1215
      TabIndex        =   0
      Top             =   1380
      Width           =   1215
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_cFiles As Collection

Private Sub Form_Load()

'' Create all of the individual bitmaps for each region
   Set m_cFiles = New Collection

   SnipFrom "key_nrm.bmp", "middle.bmp", 53, 10, 52, 60
   
   SnipFrom "key_nrm.bmp", "state_nrm_1.bmp", 53, 0, 52, 10
   SnipFrom "key_nrm.bmp", "state_nrm_2.bmp", 53, 70, 52, 10
   
   SnipFrom "key_state_alt.bmp", "state_alt_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_alt.bmp", "state_alt_2.bmp", 53, 70, 52, 10
   SnipFrom "key_state_alt_locked.bmp", "state_alt_locked_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_alt_locked.bmp", "state_alt_locked_2.bmp", 53, 70, 52, 10
   
   SnipFrom "key_state_cap.bmp", "state_cap_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_cap.bmp", "state_cap_2.bmp", 53, 70, 52, 10
   SnipFrom "key_state_cap_locked.bmp", "state_cap_locked_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_cap_locked.bmp", "state_cap_locked_2.bmp", 53, 70, 52, 10
   
   SnipFrom "key_state_num.bmp", "state_num_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_num.bmp", "state_num_2.bmp", 53, 70, 52, 10
   SnipFrom "key_state_num_locked.bmp", "state_num_locked_1.bmp", 53, 0, 52, 10
   SnipFrom "key_state_num_locked.bmp", "state_num_locked_2.bmp", 53, 70, 52, 10
   
   SnipFrom "key_nrm.bmp", "key_nrm_1.bmp", 0, 0, 53, 80
   SnipFrom "key_nrm.bmp", "key_nrm_2.bmp", 105, 0, 55, 80

   SnipFrom "key_num.bmp", "key_num_1.bmp", 0, 0, 53, 80
   SnipFrom "key_num.bmp", "key_num_2.bmp", 105, 0, 55, 80

   SnipFrom "key_cap.bmp", "key_cap_1.bmp", 0, 0, 53, 80
   SnipFrom "key_cap.bmp", "key_cap_2.bmp", 105, 0, 55, 80

   SnipFrom "key_alt.bmp", "key_alt_1.bmp", 0, 0, 53, 80
   SnipFrom "key_alt.bmp", "key_alt_2.bmp", 105, 0, 55, 80

'   SnipFrom "keypad.bmp", "keypad.bmp", 0, 0, 80, 80
'   SnipFrom "keypad_down.bmp", "keypad_down.bmp", 0, 0, 80, 80

'' Create the cells.dat file to mark the location of each region   
'   CreateReds

'' Just creates the resource information
'   DoFiles
   
End Sub

Private Sub DoFiles()

   Dim vItem As Variant
   Dim sDesc As String
   Dim nNum As Long
   
   nNum = 1024
   Debug.Print "---"
   For Each vItem In m_cFiles
      sDesc = "IDB_" & Mid(UCase(vItem), 1, Len(vItem) - 4)
      Debug.Print sDesc & " BITMAP  DISCARDABLE     ""Snipper\\" & vItem & """"
   Next
   Debug.Print "---"
   For Each vItem In m_cFiles
      sDesc = "IDB_" & Mid(UCase(vItem), 1, Len(vItem) - 4)
      nNum = nNum + 1
      Debug.Print "#define " & sDesc & " " & Format(nNum)
   Next
   Debug.Print "---"

End Sub

Private Sub CreateReds()

   Set pctMain.Picture = LoadPicture(App.Path & "\..\Artwork\" & "reds.bmp")
   Dim x As Long
   Dim y As Long
   Dim n As Long
   Dim s As String
   
   For y = 0 To 79 * 15 Step 15
      For x = 0 To 159 * 15 Step 15
         Select Case pctMain.Point(x, y)
            Case RGB(20, 0, 0): n = 0
            Case RGB(40, 0, 0): n = 1
            Case RGB(60, 0, 0): n = 2
            Case RGB(80, 0, 0): n = 3
            Case RGB(100, 0, 0): n = 4
            Case RGB(120, 0, 0): n = 5
            Case RGB(140, 0, 0): n = 6
            Case RGB(160, 0, 0): n = 7
            Case RGB(180, 0, 0): n = 8
            Case Else
               Debug.Assert pctMain.Point(x, y) = RGB(255, 255, 255)
               n = 10
         End Select
         s = s & Chr(n)
      Next
   Next
   
   If Dir(App.Path & "\cells.dat") <> "" Then
      Kill App.Path & "\cells.dat"
   End If
   Open App.Path & "\cells.dat" For Output As #1
   Print #1, s;
   Close #1
End Sub

Private Sub SnipFrom(sOrig As String, sOut As String, x As Long, y As Long, cx As Long, cy As Long)

   pctMain.Width = 240 * 15
   pctMain.Height = 80 * 15

   pctOther.Width = cx * 15
   pctOther.Height = cy * 15
   
   pctMain.Cls
   pctOther.Cls
   
   Set pctMain.Picture = LoadPicture(App.Path & "\..\Artwork\" & sOrig)
   pctOther.PaintPicture pctMain, 0, 0, cx * 15, cy * 15, x * 15, y * 15, cx * 15, cy * 15

   SavePicture pctOther.Image, App.Path & "\" & sOut

   m_cFiles.Add sOut

End Sub
