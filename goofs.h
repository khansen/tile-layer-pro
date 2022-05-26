//---------------------------------------------------------------------------
#ifndef goofsH
#define goofsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGotoForm : public TForm
{
__published:	// IDE-managed Components
    TRadioGroup *RadixGroup;
    TGroupBox *OffsetBox;
    TEdit *GotoEdit;
    TRadioGroup *MethodGroup;
    TButton *GoButton;
    TButton *CancelButton;
    void __fastcall CancelButtonClick(TObject *Sender);
    void __fastcall GoButtonClick(TObject *Sender);
    
    void __fastcall GotoEditKeyPress(TObject *Sender, char &Key);
    void __fastcall RadixGroupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TGotoForm(TComponent* Owner);
    int GoOffset;
};
//---------------------------------------------------------------------------
extern PACKAGE TGotoForm *GotoForm;
//---------------------------------------------------------------------------
#endif
