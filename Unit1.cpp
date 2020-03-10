//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
sqlite3 *Chrome_DB = NULL;  // ���������� ���������� ��
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	MyStringTree->NodeDataSize = sizeof(MyNodeType); // ��������� ������ �� ������ ����
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MyStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;
   	MyNodeType *nodeData = (MyNodeType*)MyStringTree->GetNodeData(Node);   // ������ ��������� ������ �� ����������� ����

   	switch(Column) // ����� ��� ����������� ��������
        {
        	case 0: CellText = UnicodeString(nodeData->ID); break;
        	case 1: CellText = UnicodeString(nodeData->URL.c_str()); break;
        	case 2: CellText = UnicodeString(nodeData->PageName.c_str()); break;
        	case 3: CellText = UnicodeString(nodeData->Date.c_str()); break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)  // ������ �������� � ��������� �������
{
	sqlite3_stmt *pStatement; // ���������� �������

	if (FILE *file = fopen("History", "r")) // �������� �� ������������� �����
        {
		Message->Caption = UnicodeString("File exists");
     	}
     	else {
        	Message->Caption = UnicodeString("File is missing!");
	        return;
     	}

	int db_connect = sqlite3_open16(L"History", &Chrome_DB); //��������� ���������� � ��
     	if(db_connect)     // �������� ��������� (����� ������� == 0)
        {
        	Message->Caption = sqlite3_errmsg(Chrome_DB);
        	sqlite3_close(Chrome_DB);
        	return;
     	}
     	else
        {
        	Message->Caption = UnicodeString("Database has been loaded");
     	}

     	const char *sql_statement = "SELECT urls.id, urls.url, urls.title, "\
        	        "datetime(urls.last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'), "\
        		"visit_count FROM urls order by urls.id;"; //  sql-������
     	int result = sqlite3_prepare_v2(Chrome_DB, sql_statement, -1, &pStatement, NULL); //���������� �������
     	if (result != SQLITE_OK) // �������� ��������� ����������
        {
        	 Message->Caption = sqlite3_errmsg(Chrome_DB);
     	}

	MyStringTree->Clear(); // ������� � ����� ������
        MyStringTree->BeginUpdate();  // ������ ���������� ���������
     	while(true) // �������� �� ���������� �������
        {
		result = sqlite3_step(pStatement);   //���������� �������
        	if (result != SQLITE_ROW) break;   // ��������� ������

        	PVirtualNode newNode = MyStringTree->AddChild(MyStringTree->RootNode); //���������� ����
        	MyNodeType *nodeData = (MyNodeType*)MyStringTree->GetNodeData(newNode);  //������ ��������� ������ �� ����������� ����
                 // ���������� ���� �������
        	nodeData->ID = sqlite3_column_int(pStatement, 0);
        	nodeData->URL = (wchar_t *)sqlite3_column_text16(pStatement, 1);
        	nodeData->PageName = (wchar_t *)sqlite3_column_text16(pStatement, 2);
        	nodeData->Date = (wchar_t *)sqlite3_column_text16(pStatement, 3);
        	nodeData->VisitCount = sqlite3_column_int(pStatement, 4);
     	}
     	if (result != SQLITE_DONE)   // �������� ��������� ����������
        {
         	Message->Caption = sqlite3_errmsg(Chrome_DB);
     	}
     	MyStringTree->EndUpdate(); // ����� ���������� ���������
     	sqlite3_finalize(pStatement); //���������� ��������� �������
     	sqlite3_close(Chrome_DB); // �������� ���������� � ��
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MyStringTreeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node)
    // ����� ���������� � ���������� ��������� ��������
{
	if(!Node) return;

	MyNodeType *nodeData = (MyNodeType*)MyStringTree->GetNodeData(Node);
	VisitCount->Caption = UnicodeString(nodeData->VisitCount);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
// �������� ���������� ������
{
	PVirtualNode selectedNode = MyStringTree->FocusedNode;
        MyNodeType *nodeData = (MyNodeType*)MyStringTree->GetNodeData(selectedNode);

        if (selectedNode != NULL) {
                int selected_id = nodeData->ID;
                char *buffer;
		int ret = snprintf(buffer, sizeof(buffer), "%ld", selected_id);
                string id_string = buffer;

                int db_connect = sqlite3_open16(L"History", &Chrome_DB);
                if(db_connect)
                {
                	Message->Caption = sqlite3_errmsg(Chrome_DB);
                	sqlite3_close(Chrome_DB);
                	return;
                }
                else {
        		Message->Caption = UnicodeString("Database has been loaded");
                }
                  // sql-������ �� �������� ������
                const char *sql = ("DELETE FROM urls WHERE id = " + id_string + " ;").c_str();
                sqlite3_stmt *pStatement;
                int result = sqlite3_prepare_v2(Chrome_DB, sql, -1, &pStatement, NULL); // ����������
                if (result != SQLITE_OK)
                {
        		Message->Caption = sqlite3_errmsg(Chrome_DB);
		}

                result = sqlite3_step(pStatement); // ����������
                if (result != SQLITE_DONE)
                {
        		Message->Caption = sqlite3_errmsg(Chrome_DB);
		}
                else
                {
                        MyStringTree->DeleteNode(selectedNode); // ���� �������� ���������� �������-��������� ������
                        Message->Caption = UnicodeString("Row has been deleted successfully");
                }
                sqlite3_finalize(pStatement); // ����������
                sqlite3_close(Chrome_DB);
        }
        else
        {
            Message->Caption = UnicodeString("Select row first");
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender) // ������� ������� ��
{
	char *errMsg = 0;

        int db_connect = sqlite3_open16(L"History", &Chrome_DB);
        if(db_connect)
        {
                Message->Caption = sqlite3_errmsg(Chrome_DB);
                sqlite3_close(Chrome_DB);
                return;
        }
        else {
                Message->Caption = UnicodeString("Database has been loaded");
        }

        const char *sql = "delete from urls;"; //sql-������ �� ��������
        int result = sqlite3_exec(Chrome_DB, sql, NULL, NULL, &errMsg); // ���������� ��������� � ���������� �������
        if (result != SQLITE_OK)
        {
                Message->Caption = sqlite3_errmsg(Chrome_DB);
        }
        else
        {
                MyStringTree->Clear();
                Message->Caption = UnicodeString("Table has been cleared successfully");
        }
        sqlite3_close(Chrome_DB);
}
//---------------------------------------------------------------------------

