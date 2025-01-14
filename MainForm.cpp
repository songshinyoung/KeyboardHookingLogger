//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Windows.h>

#include "MainForm.h"             a

#pragma argsused
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------
HHOOK hHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT *pKbdLLHook = (KBDLLHOOKSTRUCT *)lParam;
			wchar_t buffer[16];
			DWORD nScanCode = pKbdLLHook->scanCode;

			GetKeyNameTextW(nScanCode << 16, buffer, 16);


			// 특정 키 검사 (예: F1 키)
			if (GetAsyncKeyState(VK_F1) & 0x8000) {
				// ShowMessage(L"F1 키가 눌렸습니다!");
			}

			if(pKbdLLHook->scanCode == 0x52 && pKbdLLHook->flags == 1) { // Ins
				nScanCode = 12 * 8 + 0;
			}
			else if(pKbdLLHook->scanCode == 0x47 && pKbdLLHook->flags == 1) { // Home
				nScanCode = 12 * 8 + 1;
			}
			else if(pKbdLLHook->scanCode == 0x53 && pKbdLLHook->flags == 1) { // Del
				nScanCode = 12 * 8 + 2;
			}
			else if(pKbdLLHook->scanCode == 0x4F && pKbdLLHook->flags == 1) { // End
				nScanCode = 12 * 8 + 3;
			}
			else if(pKbdLLHook->scanCode == 0x49 && pKbdLLHook->flags == 1) { // PgUp
				nScanCode = 12 * 8 + 4;
			}
			else if(pKbdLLHook->scanCode == 0x51 && pKbdLLHook->flags == 1) { // PgDn
				nScanCode = 12 * 8 + 5;
			}
			else if(pKbdLLHook->scanCode == 0x45 && pKbdLLHook->flags == 1) { // Num
				nScanCode = 12 * 8 + 6;
			}
			else if(pKbdLLHook->scanCode == 0x37 && pKbdLLHook->flags == 1) { // PrtSc
				nScanCode = 12 * 8 + 7;
			}
			else if(pKbdLLHook->scanCode == 0x35 && pKbdLLHook->flags == 1) { // Num /
				nScanCode = 13 * 8 + 0;
			}
			else if(pKbdLLHook->scanCode == 0x1C && pKbdLLHook->flags == 1) { // Num Enter
				nScanCode = 13 * 8 + 1;
			}
			else if(pKbdLLHook->scanCode == 0 && pKbdLLHook->vkCode == 0xAE) { // Vol -
				nScanCode = 13 * 8 + 2;
			}
			else if(pKbdLLHook->scanCode == 0 && pKbdLLHook->vkCode == 0xAF) { // Vol +
				nScanCode = 13 * 8 + 3;
			}
			else if(pKbdLLHook->scanCode == 0 && pKbdLLHook->vkCode == 0xAD) { // Vol X
				nScanCode = 13 * 8 + 4;
			}
			else if(pKbdLLHook->scanCode == 0 && pKbdLLHook->vkCode == 0xB7) { // VCal.
				nScanCode = 13 * 8 + 5;
			}
			else if(pKbdLLHook->scanCode == 0x48 && pKbdLLHook->vkCode == 0x26 && pKbdLLHook->flags == 1) { // Up
				nScanCode = 14 * 8 + 0;
			}
			else if(pKbdLLHook->scanCode == 0x4B && pKbdLLHook->vkCode == 0x25 && pKbdLLHook->flags == 1) { // Left
				nScanCode = 14 * 8 + 1;
			}
			else if(pKbdLLHook->scanCode == 0x4D && pKbdLLHook->vkCode == 0x27 && pKbdLLHook->flags == 1) { // Right
				nScanCode = 14 * 8 + 2;
			}
			else if(pKbdLLHook->scanCode == 0x50 && pKbdLLHook->vkCode == 0x28 && pKbdLLHook->flags == 1) { // Down
				nScanCode = 14 * 8 + 3;
			}

			if((nScanCode >=0)
			&& (pKbdLLHook->scanCode < ARRAYSIZE(Form1->m_nScanCodeCound))) {
				Form1->m_nScanCodeCound[nScanCode] += 1;
				Form1->m_bNewEvent = true;
				Form1->m_bScanCodeInput[nScanCode] = true;
			}


			String sMsg;
			sMsg.printf(L"Key Name : %-16s, VK_Code : 0x%X, Scan Code : 0x%X, Flags : %d, Time : %d", buffer, pKbdLLHook->vkCode, pKbdLLHook->scanCode, pKbdLLHook->flags, pKbdLLHook->time);

			Form1->Memo1->Lines->Add(sMsg);
		}
	}
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
//---------------------------------------------------------------------------
bool SetHook()
{
    hHook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!hHook)
    {
		//ShowMessage(L"Failed to set hook");
		Form1->Memo1->Lines->Add("Failed to set hook");
		return false;
    }
    else
	{
		//ShowMessage(L"Hook set successfully");
		Form1->Memo1->Lines->Add("Hook set successfully");
		return true;
    }
}
//---------------------------------------------------------------------------
void RemoveHook()
{
    if (hHook)
    {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
		//ShowMessage(L"Hook removed");
		Form1->Memo1->Lines->Add("Hook removed");
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	m_bHookStarted 	= false;
	m_bNewEvent		= false;
	ZeroMemory(m_nScanCodeCound, sizeof(m_nScanCodeCound));
	ZeroMemory(m_bScanCodeInput, sizeof(m_bScanCodeInput));
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	DrawScanCodeName(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if(m_bHookStarted) {
		RemoveHook();
		m_bHookStarted = false;
	}
}
//---------------------------------------------------------------------------









void __fastcall TForm1::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HookStart1Click(TObject *Sender)
{
	if(m_bHookStarted != true) {

		try
		{

			m_bHookStarted = SetHook();

			if(m_bHookStarted) Panel_HookStarted->Color = clLime;

		}
		catch (Exception &exception)
		{
	        Application->ShowException(&exception);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HookStop1Click(TObject *Sender)
{

	RemoveHook();

	m_bHookStarted = false;
	Panel_HookStarted->Color = clBtnFace;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyName1Click(TObject *Sender)
{

    TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
    if (item)
    {
        // 다른 모든 메뉴 아이템을 선택 해제합니다.
        for (int i = 0; i < item->Parent->Count; ++i)
        {
            item->Parent->Items[i]->Checked = false;
        }

        // 클릭된 메뉴 아이템을 선택 상태로 만듭니다.
		item->Checked = true;

		if(item->Caption.Pos("Key Name") >= 1) {
			DrawScanCodeName(0);
		}
		else if(item->Caption.Pos("Scan Code") >= 1){
			DrawScanCodeName(1);
		}
		else {
          	DrawScanCodeName(0);
		}


	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(m_bNewEvent) {
		m_bNewEvent = false;

		DrawScanCodeCount();
	}

	if(m_bHookStarted) {
		Panel_HookStarted->Color = Panel_HookStarted->Color != clLime ? clLime : clWhite;
	}
	else {
     	Panel_HookStarted->Color = clBtnFace;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawScanCodeName(int nDisplayType)
{
	DWORD  scancode = 0;

	wchar_t buffer[16];


	switch(nDisplayType) {
		case 0:
		default:
			for(int row=0; row<32; row++) {
				for(int col=0; col<16; col += 2) {
					scancode = (row * 8) + (col / 2) ;
					ZeroMemory(buffer, sizeof(buffer));

					GetKeyNameTextW(scancode << 16, buffer, 16);

					StringGrid1->Cells[col][row] = buffer;
				}
			}

			// 특수 키 들..
			StringGrid1->Cells[0][12] 	= "Ins";
			StringGrid1->Cells[2][12] 	= "Home";
			StringGrid1->Cells[4][12] 	= "Del";
			StringGrid1->Cells[6][12] 	= "End";
			StringGrid1->Cells[8][12] 	= "PgUp";
			StringGrid1->Cells[10][12] 	= "PgDn";
			StringGrid1->Cells[12][12] 	= "Num";
			StringGrid1->Cells[14][12] 	= "PrtSc";

			StringGrid1->Cells[0][13] 	= "Num /";
			StringGrid1->Cells[2][13] 	= "Num Enter";
			StringGrid1->Cells[4][13] 	= "Vol -";
			StringGrid1->Cells[6][13] 	= "Vol +";
			StringGrid1->Cells[8][13] 	= "Vol X";
			StringGrid1->Cells[10][13] 	= "Cal.";

			StringGrid1->Cells[0][14] 	= "Up";
			StringGrid1->Cells[2][14] 	= "Left";
			StringGrid1->Cells[4][14] 	= "Right";
			StringGrid1->Cells[6][14] 	= "Down";
			break;

		case 1:
			for(int row=0; row<32; row++) {
				for(int col=0; col<16; col += 2) {
					scancode = (row * 8) + (col / 2) ;

					String sMsg;
					sMsg.printf(L"0x%X", scancode);

					StringGrid1->Cells[col][row] = sMsg;
				}
			}
			break;
	}




}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawScanCodeCount()
{
	DWORD  scancode = 0;

	wchar_t buffer[16];

	StringGrid1->Enabled = false;

	for(int row=0; row<32; row++) {
		for(int col=0; col<16; col += 2) {
			scancode = (row * 8) + (col / 2) ;

			StringGrid1->Cells[col+1][row] = m_nScanCodeCound[scancode];
		}
	}

	StringGrid1->Enabled = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
	if(ACol < 0) return;
	if(ARow < 0) return;
	if(ACol >= StringGrid1->ColCount) return;
	if(ARow >= StringGrid1->RowCount) return;

    TColor cBackGround = clBtnFace;
    TColor cFontColor  = clBlack;

	Rect.Left -= 4;

	if((ACol % 2) == 0) {
		// Scan Code Name.

		StringGridSubCodeView(Sender, ACol, ARow, Rect, cBackGround, cFontColor, 10, true, true);

	}
	else {
		// Scan Count.

		bool bTextBold = true;
		cBackGround = clWhite;
		bTextBold   = false;

		DWORD nScanCode =  (ARow * 8) + (ACol - 1) / 2;

		if(StringGrid1->Cells[ACol][ARow] == "0") {
			cFontColor  = clGray;
		}
		else {
			if(m_bScanCodeInput[nScanCode]) {
				m_bScanCodeInput[nScanCode] = false;
				cFontColor  = clWhite;
				cBackGround = clRed;
				bTextBold   = true;
			}
			else {
				cFontColor  = clBlue;
				bTextBold   = true;
			}
		}

		StringGridSubCodeView(Sender, ACol, ARow, Rect, cBackGround, cFontColor, 10, true, bTextBold);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridSubCodeView(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TColor clBackColor,
		  TColor clFontColor,
		  int nFontSize,
		  bool bTextAlignCenter,
		  bool bTextBold)
{
    TStringGrid * pSG = dynamic_cast<TStringGrid *>(Sender);

    if(pSG == NULL) return;

    // 이전 값 기억.
    TColor clOrgBrush  = pSG->Canvas->Brush->Color;
    TColor clOrgFontColor = pSG->Font->Color;
    int nOrgFontSize   = pSG->Font->Size;
    TFontStyles OrgFontStyle = pSG->Canvas->Font->Style;

    // 새로운 값 설정.
	pSG->Canvas->Brush->Color = clBackColor;
	pSG->Canvas->Font->Size = nFontSize;

	if(bTextBold)
        pSG->Canvas->Font->Style = TFontStyles() << fsBold;
	else
        pSG->Canvas->Font->Style = TFontStyles() >> fsBold;


	pSG->Canvas->Pen->Color = clGray;
	pSG->Canvas->FillRect(Rect);
	pSG->Canvas->Rectangle(Rect.left-1, Rect.top-1, Rect.right+1, Rect.Bottom+1);

	int nTextH = pSG->Canvas->TextHeight(pSG->Cells[ACol][ARow]);
	int nTextL = Rect.Left + 2;

    if(bTextAlignCenter) {
		nTextL = Rect.Left + (Rect.Width() - pSG->Canvas->TextWidth(pSG->Cells[ACol][ARow])) / 2;
    }

    int nTextT = Rect.Top + ((Rect.Bottom - Rect.Top) / 2) - (nTextH / 2);
    pSG->Canvas->Font->Color = clFontColor;

	pSG->Canvas->Brush->Style = bsClear;
	pSG->Canvas->TextOut(nTextL, nTextT, pSG->Cells[ACol][ARow]);
	pSG->Canvas->Brush->Style = bsSolid;

	// 이전 값 복원.
    pSG->Canvas->Brush->Color = clOrgBrush;
    pSG->Canvas->Font->Size = nOrgFontSize;
    pSG->Canvas->Font->Color = clOrgFontColor;
    pSG->Canvas->Font->Style = OrgFontStyle;
}


