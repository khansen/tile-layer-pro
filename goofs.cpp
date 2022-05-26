//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "goofs.h"
#include "child.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGotoForm *GotoForm;
//---------------------------------------------------------------------------
__fastcall TGotoForm::TGotoForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGotoForm::CancelButtonClick(TObject *Sender)
{
GotoForm->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TGotoForm::GoButtonClick(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(MainForm->ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active

if (GotoEdit->Text == "")
    return;

if (RadixGroup->ItemIndex == 0) // Radix = hex?
    GoOffset = StrToInt("0x"+GotoEdit->Text);
else
    GoOffset = StrToInt(GotoEdit->Text);

if (MethodGroup->ItemIndex == 0)
    child->FileOffset = GoOffset;   // Absolute
else
    child->FileOffset += GoOffset;  // Relative

if (child->FileOffset > child->ScrollBar->Max)
    child->FileOffset = child->ScrollBar->Max;
child->ScrollBar->Position = child->FileOffset;
GotoForm->ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TGotoForm::GotoEditKeyPress(TObject *Sender, char &Key)
{
if (Key == VK_BACK)
    return;
if (Key == VK_RETURN)
    {
    GoButtonClick(Sender);
    return;
    }
Key = UpCase(Key);
if (RadixGroup->ItemIndex == 0)
    {   // hex
    if ((Key < '0') || (Key > 'F'))
        Key = 0;
    else if ((Key > '9') && (Key < 'A'))
        Key = 0;
    }
else
    {   // dec
    if ((Key < '0') || (Key > '9'))
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGotoForm::RadixGroupClick(TObject *Sender)
{
if (GotoEdit->Text == "")
    return;
if (RadixGroup->ItemIndex == 1)
    {   // Convert current offset to decimal
    GoOffset = StrToInt("0x"+GotoEdit->Text);
    GotoEdit->Text = IntToStr(GoOffset);
    }
else
    {   // Convert current offset to hex
    GoOffset = StrToInt(GotoEdit->Text);
    char buf[256];
    wsprintf(buf, "%X", GoOffset);
    GotoEdit->Text = buf;
    }
}
//---------------------------------------------------------------------------

