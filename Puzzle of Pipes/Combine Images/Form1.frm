VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   495
      Left            =   360
      ScaleHeight     =   495
      ScaleWidth      =   1215
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

    Dim i As Long
    Dim p As StdPicture
    Dim v As Variant
    v = Array("blocked.bmp", "cross.bmp", "vertical.bmp", "start_ri.bmp", "start_le.bmp", "start_do.bmp", "top_righ.bmp", "bottom_r.bmp", "top_left.bmp", "bottom_l.bmp", "horizont.bmp", "blank.bmp", "start_to.bmp", "2tart_to.bmp", "2tart_le.bmp", "2tart_ri.bmp", "2tart_do.bmp")
    Dim vi As Variant
    
    Me.Picture1.Width = 28 * 15
    Me.Picture1.Height = 28 * 15 * 17
    
    i = 0
    For Each vi In v
        Set p = LoadPicture(App.Path & "\..\" & vi)
        Picture1.PaintPicture p, 0, i * 15
        i = i + 28
    Next
    
    SavePicture Picture1.Image, App.Path & "\..\All Images.bmp"

End Sub
