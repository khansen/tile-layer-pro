//---------------------------------------------------------------------------
#ifndef editH
#define editH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include "bmp256.h"
#include <Buttons.hpp>

enum TDrawingTool { dtPencil, dtLine, dtFill };

class TEditForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ToolPanel;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SpeedButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    UNDOENTRY TempBuffer[MAX_UNDOS];
    bool IsUndo;
    
    TChildForm *Owna;
    TChildForm *child;
    BYTE *TileData;
    TTileFormat TileFmt;
    BYTE FGColor, BGColor;
    int TileOffset;
    int TileSize;
    int BPP;
    bool IsClipTile;
    bool IsDrawing;
    TDrawingTool DrawingTool;
    TMouseButton btn;
    Bitmap256 EditBitmap;       // Edit window bitmap
    void __fastcall UpdateTile(void);
    __fastcall TEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditForm *EditForm;
//---------------------------------------------------------------------------
#endif
