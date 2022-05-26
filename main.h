//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------

#include "bmp256.h"

class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TOpenDialog *OpenROMDialog;
    TSaveDialog *SaveROMDialog;
    TMenuItem *FileMenu;
    TMenuItem *Open1;
    TMenuItem *Close1;
    TMenuItem *Save1;
    TMenuItem *SaveAs1;
    TMenuItem *Exit1;
    TPanel *ToolBar;
    TSpeedButton *OpenSpdBtn;
    TSpeedButton *SaveSpdBtn;
    TBevel *Bevel1;
    TStatusBar *StatusBar;
    TMenuItem *HelpMenu;
    TMenuItem *Contents1;
    TMenuItem *About1;
    TSpeedButton *ZoomInSpdBtn;
    TSpeedButton *ZoomOutSpdBtn;
    TSpeedButton *GridSpdBtn;
    TOpenPictureDialog *OpenPictureDialog;
    TSavePictureDialog *SavePictureDialog;
    TOpenDialog *OpenPalDialog;
    TSaveDialog *SavePalDialog;
    TMenuItem *WindowMenu;
    TMenuItem *Tile1;
    TMenuItem *Cascade1;
    TMenuItem *ArrangeIcons1;
    TMenuItem *MinimizeAll1;
    TMenuItem *CloseAll1;
    TMenuItem *New1;
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall Close1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    
    void __fastcall Save1Click(TObject *Sender);
    void __fastcall SaveAs1Click(TObject *Sender);
    void __fastcall FileMenuClick(TObject *Sender);
    void __fastcall ZoomInSpdBtnClick(TObject *Sender);
    void __fastcall ZoomOutSpdBtnClick(TObject *Sender);
    void __fastcall GridSpdBtnClick(TObject *Sender);
    
    
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Tile1Click(TObject *Sender);
    void __fastcall Cascade1Click(TObject *Sender);
    void __fastcall ArrangeIcons1Click(TObject *Sender);
    void __fastcall MinimizeAll1Click(TObject *Sender);

    void __fastcall CloseAll1Click(TObject *Sender);
    void __fastcall Contents1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    void __fastcall OpenOneROM(AnsiString filename);
    TForm *ActiveForm;
    TForm *DragOwner;
    BYTE *DragData;
    BYTE *DropData;
    BYTE OldDropData[32];
    bool CanUndoDrop;
    int DragOffset;
//    int DragX, DragY;
//    TForm *DragChild;
    DWORD CopyWidth;
    DWORD CopyHeight;
    DWORD CopySize;
    Bitmap256 CopyBitmap;
    Bitmap256 DragBitmap;
    unsigned __int64 BitPatterns[8][256];
    bool    bClosed;
    bool HasCopied;
    bool CloseAllMDIForms(void);
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
