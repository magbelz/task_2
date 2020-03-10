object Form1: TForm1
  Left = 0
  Top = 0
  Align = alCustom
  Caption = 'Form1'
  ClientHeight = 374
  ClientWidth = 552
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Message: TLabel
    Left = 239
    Top = 317
    Width = 234
    Height = 13
    Transparent = True
  end
  object VisitCount: TLabel
    Left = 155
    Top = 317
    Width = 3
    Height = 13
  end
  object Label1: TLabel
    Left = 56
    Top = 317
    Width = 93
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1087#1086#1089#1077#1097#1077#1085#1080#1081':'
  end
  object MyStringTree: TVirtualStringTree
    Left = 0
    Top = 0
    Width = 552
    Height = 297
    Align = alTop
    Header.AutoSizeIndex = 0
    Header.Options = [hoAutoResize, hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowRoot, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages]
    TreeOptions.SelectionOptions = [toFullRowSelect]
    OnAddToSelection = MyStringTreeAddToSelection
    OnGetText = MyStringTreeGetText
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 78
      end
      item
        Position = 1
        Text = 'URL'
        Width = 122
      end
      item
        Position = 2
        Text = 'Page Name'
        Width = 174
      end
      item
        Position = 3
        Text = 'Last Time Visited'
        Width = 174
      end>
  end
  object Button1: TButton
    Left = 56
    Top = 336
    Width = 129
    Height = 25
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 232
    Top = 336
    Width = 105
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 360
    Top = 336
    Width = 113
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 3
    OnClick = Button3Click
  end
end
