object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Keyboard Hooking Logger'
  ClientHeight = 670
  ClientWidth = 1164
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 535
    Width = 1164
    Height = 111
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'D2Coding'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
    ExplicitTop = 529
    ExplicitWidth = 1159
    ExplicitHeight = 117
  end
  object Panel1: TPanel
    Left = 0
    Top = 646
    Width = 1164
    Height = 24
    Align = alBottom
    BevelOuter = bvNone
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 1
    ExplicitTop = 446
    ExplicitWidth = 635
    object Panel_HookStarted: TPanel
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 24
      Height = 18
      Align = alLeft
      BevelOuter = bvLowered
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 0
    end
  end
  object StringGrid1: TStringGrid
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 1158
    Height = 529
    Align = alTop
    ColCount = 16
    DefaultColWidth = 70
    FixedCols = 0
    RowCount = 32
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #45208#45588#44256#46357
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnDrawCell = StringGrid1DrawCell
    ExplicitWidth = 1153
  end
  object MainMenu1: TMainMenu
    Left = 144
    Top = 48
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Run1: TMenuItem
      Caption = 'Run'
      object HookStart1: TMenuItem
        Caption = 'Hook Start'
        OnClick = HookStart1Click
      end
      object HookStop1: TMenuItem
        Caption = 'Hook Stop'
        OnClick = HookStop1Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object KeyName1: TMenuItem
        Caption = 'Key Name'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = KeyName1Click
      end
      object ScanCode1: TMenuItem
        Caption = 'Scan Code'
        GroupIndex = 1
        RadioItem = True
        OnClick = KeyName1Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 200
    OnTimer = Timer1Timer
    Left = 24
    Top = 8
  end
end
