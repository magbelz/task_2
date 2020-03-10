//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>
#include <string>
using namespace std;
/*
  ���� ������ sqlite
  done - ���������, ������� ��� ���� ������ ����� ���������, �������� �� ����� ���������� ������� � �������� ������� ������.
  done - �� ������ �� ������ �������� �������������� ����������.
  done - �������� ��������� ������ - � �� ����������, � �� ��.
  done - ������� ������� ������� - �������� ���� ������ �� �������.

*/

//---------------------------------------------------------------------------
typedef struct  // ���������� ���������
{
        int ID;  // �������������
        wstring URL; // ����� ������
        wstring PageName; // ��� ��������
        wstring Date; // ����
        int VisitCount; // ����� ��������� ��������
} MyNodeType;


class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *MyStringTree;
        TLabel *Message;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
        TLabel *VisitCount;
        TLabel *Label1;
	void __fastcall MyStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall MyStringTreeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
        void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
