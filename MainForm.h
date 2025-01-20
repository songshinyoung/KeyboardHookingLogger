//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

#include <list>
//---------------------------------------------------------------------------
class TKeyCountData
{
public:
	DWORD  ScanCode;
	DWORD  VKCode;
	DWORD  Count;

	TKeyCountData(DWORD scancode, DWORD vkcode, DWORD count) :
		ScanCode(scancode), VKCode(vkcode), Count(count) { };
};




class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Run1;
	TMenuItem *HookStart1;
	TMenuItem *HookStop1;
	TMenuItem *Exit1;
	TPanel *Panel1;
	TPanel *Panel_HookStarted;
	TTimer *Timer1;
	TMenuItem *View1;
	TMenuItem *KeyName1;
	TMenuItem *ScanCode1;
	TPanel *Panel2;
	TPanel *Panel3;
	TStringGrid *StringGrid1;
	TMemo *Memo1;
	TStringGrid *StringGrid_Sort;
	TMenuItem *Edit1;
	TMenuItem *Clear1;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall HookStart1Click(TObject *Sender);
	void __fastcall HookStop1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall KeyName1Click(TObject *Sender);
	void __fastcall StringGrid_SortDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall Clear1Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
	bool	m_bHookStarted;
	std::list<TKeyCountData *> m_DataList;

	void __fastcall Clear();

	void __fastcall DrawScanCodeName(int nDisplayType);  // 0 : Text Key Name, 1 : Key Scan Code.
	void __fastcall DrawScanCodeCount(bool bClear = false);

	void __fastcall StringGridSubCodeView(TObject *Sender, int ACol, int ARow, TRect &Rect,
			  TColor clBackColor,
			  TColor clFontColor,
			  int nFontSize,
			  bool bTextAlignCenter,
			  bool bTextBold);



	void __fastcall SortKeyData();

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);



	int		m_nScanCodeCound[256]; 	// �ش� Scan Code�� ��� �ԷµǾ����� �����Ͽ� ī��Ʈ �Ѵ�.
	bool	m_bScanCodeInput[256];	// ���� Scan Code�� ���� ���� true�� �����Ͽ� ȭ�鿡 �ֱ� ���̶�� ǥ���ϱ� ����.
	bool	m_bScanCodeDown[256];	// �ش� Ű�� ���������� ���� ��� �߻��ϴ� Event�� �����ϱ� ���� Key Down �� true�� �����ϰ� Up �ÿ� false�� �ʱ�ȭ �ؼ� true�� ��� �߻��ϴ� Event �� ���� �Ѵ�.
	bool	m_bNewEvent;            // Key �� ���� ��� ���� �ٽ� �׷��ֱ� ���� Callback �Լ����� true�� ���� �ȴ�.
	String  m_sKeyName[256];


	void __fastcall UpdateKeyData(DWORD scancode, DWORD vkcode, DWORD count);
	void __fastcall UpdateKeyData(DWORD scancode);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
