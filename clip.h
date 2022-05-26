//---------------------------------------------------------------------------
#ifndef clipH
#define clipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#define CLIP_WIDTH 24
#define CLIP_HEIGHT 16

typedef struct tagClipTile {
    TChildForm *owner;   // child form that owns tile
    BYTE *data; // ptr to tile data, NULL if slot not occupied
    TTileFormat fmt;   // format of encoded tile
    int pal;
    int ofs;
    int bpp;
    int size;
    int xpos, ypos;
    bool xflip, yflip;
} ClipTile;

//---------------------------------------------------------------------------
class TClipForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *DragLabel;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
    void __fastcall FormDragDrop(TObject *Sender, TObject *Source, int X,
          int Y);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
    __fastcall TClipForm(TComponent* Owner);
    bool        IsDrawing;
    RGBTRIPLE   Palette[256];
    BYTE        FGColor, BGColor;
    Bitmap256   ClipBitmap;
    ClipTile    ClipBoard[CLIP_HEIGHT][CLIP_WIDTH];
    ClipTile    *ClipEntry;
    int         PalSelect;
};
//---------------------------------------------------------------------------
extern PACKAGE TClipForm *ClipForm;
//---------------------------------------------------------------------------
#endif
