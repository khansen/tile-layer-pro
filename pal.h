//---------------------------------------------------------------------------
#ifndef palH
#define palH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

#include "bmp256.h"

class TPalForm : public TForm
{
__published:	// IDE-managed Components
    TScrollBar *RedBar;
    TScrollBar *GreenBar;
    TScrollBar *BlueBar;
    TShape *BGShape;
    TShape *FGShape;
    TEdit *REdit;
    TEdit *GEdit;
    TEdit *BEdit;
    TShape *Shape1;
    TShape *Shape2;
    TShape *Shape3;
    TShape *Shape4;
    TShape *Shape5;
    TShape *Shape6;
    TShape *Shape7;
    TShape *Shape8;
    TShape *Shape9;
    TShape *Shape10;
    TShape *Shape11;
    TShape *Shape12;
    TShape *Shape13;
    TShape *Shape14;
    TShape *Shape15;
    TShape *Shape16;
    TColorDialog *ColorDialog;
    TUpDown *PalUpDown;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    void __fastcall RedBarChange(TObject *Sender);
    
    void __fastcall REditChange(TObject *Sender);
    void __fastcall REditKeyPress(TObject *Sender, char &Key);
    void __fastcall Shape1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall PalUpDownClick(TObject *Sender, TUDBtnType Button);
    
    void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    TChildForm *child;
    Bitmap256 *ActiveBitmap;
    BYTE FGColor, BGColor;
    int NumCols, ColIndex, BPP, PalSelect, NumPalEntries;
    RGBTRIPLE *Palette;

    TShape *OldShape;
    DWORD DblClkTime;
    DWORD OldTick;
    DWORD NewTick;
    bool REditChangeEnable;
    bool RedBarChangeEnable;
    __fastcall TPalForm(TComponent* Owner);
    void __fastcall SetPalette(void);
    void __fastcall InitPalette(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPalForm *PalForm;
//---------------------------------------------------------------------------
#endif
