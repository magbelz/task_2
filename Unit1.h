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
  База данных sqlite
  done - Программа, которая эту базу данных будет открывать, выводить на экран содержимое таблицы с наиболее важными полями.
  done - По щелчку на ячейку выводить дополнительную информацию.
  done - Удаление выбранной записи - и из визуальной, и из бд.
  done - Функция очистки таблицы - удаление всех данных из таблицы.

*/

//---------------------------------------------------------------------------
typedef struct  // объявление структуры
{
        int ID;  // идентификатор
        wstring URL; // адрес ссылки
        wstring PageName; // имя страницы
        wstring Date; // дата
        int VisitCount; // число посещений страницы
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
