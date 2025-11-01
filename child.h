//---------------------------------------------------------------------------
#ifndef childH
#define childH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include "bmp256.h"
#define MAX_UNDOS 64

typedef struct tagUNDOENTRY {
    BYTE *ptr;
    BYTE data[32];
    TTileFormat fmt;
    int bpp;
    int ofs;
    int size;
} UNDOENTRY;

enum TPalType { pfRGB = 0, pfNES, pfSNES };

class TChildForm : public TForm
{
__published:	// IDE-managed Components
    TScrollBar *ScrollBar;
    TMainMenu *MainMenu1;
    TMenuItem *Edit1;
    TMenuItem *Window1;
    TMenuItem *Copy1;
    TMenuItem *Paste1;
    TMenuItem *Goto1;
    TMenuItem *Size1;
    TMenuItem *N1x1;
    TMenuItem *N2x1;
    TMenuItem *N3x1;
    TMenuItem *N4x1;
    TMenuItem *Gridlines1;
    TMenuItem *GotoAgain1;
    TMenuItem *Palette1;
    TMenuItem *Load1;
    TMenuItem *Save1;
    TMenuItem *SaveAs1;
    TMenuItem *ImportBitmap1;
    TMenuItem *ExportBitmap1;
    TMenuItem *Format1;
    TMenuItem *N1BPP1;
    TMenuItem *NES1;
    TMenuItem *GameBoy1;
    TMenuItem *VirtualBoy1;
    TMenuItem *NGPC1;
    TMenuItem *SNES3BPP1;
    TMenuItem *SNES1;
    TMenuItem *SMS1;
    TMenuItem *Genesis1;
    TMenuItem *Format2;
    TMenuItem *RGB1;
    TMenuItem *NES2;
    TMenuItem *GBC2;
    TLabel *DragLabel;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *Transfertoclipboard1;
    TMenuItem *N5;
    TMenuItem *ClearArranger1;
    TMenuItem *Undodrop1;
    TMenuItem *Entries1;
    TMenuItem *N161;
    TMenuItem *N321;
    TMenuItem *N641;
    TMenuItem *N1281;
    TMenuItem *N2561;
    TMenuItem *GBA1;
    TMenuItem *GBA2;
    TMenuItem *SNES2;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall N4x1Click(TObject *Sender);
    void __fastcall Gridlines1Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall Goto1Click(TObject *Sender);
    void __fastcall GotoAgain1Click(TObject *Sender);
    void __fastcall Copy1Click(TObject *Sender);
    void __fastcall Paste1Click(TObject *Sender);
    void __fastcall ExportBitmap1Click(TObject *Sender);
    void __fastcall Save1Click(TObject *Sender);
    void __fastcall SaveAs1Click(TObject *Sender);
    void __fastcall Load1Click(TObject *Sender);
    void __fastcall ScrollBarScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall ScrollBarChange(TObject *Sender);
    
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Genesis1Click(TObject *Sender);
    void __fastcall RGB1Click(TObject *Sender);
    void __fastcall FormDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
    void __fastcall FormDragDrop(TObject *Sender, TObject *Source, int X,
          int Y);
    
    void __fastcall Transfertoclipboard1Click(TObject *Sender);
    void __fastcall ClearArranger1Click(TObject *Sender);
    void __fastcall Edit1Click(TObject *Sender);
    void __fastcall Undodrop1Click(TObject *Sender);
    void __fastcall ImportBitmap1Click(TObject *Sender);
    void __fastcall N161Click(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
    Controls::TWndMethod OldPanelWP;
    void __fastcall NewPanelWP(TMessage &Msg);

    void __fastcall PasteMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall PasteMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall PasteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
public:		// User declarations
    int UndoCount;
    UNDOENTRY UndoBuffer[MAX_UNDOS];
    RGBTRIPLE Palette[256];
    bool PalModified;
    int PalEntrySize;
    int NumPalEntries;
    TPalType PalType;
    BYTE *FilePtr;
    AnsiString ROMFileName;
    AnsiString ROMFileExt;
    AnsiString PalFileName;
    int PalSelect;
    int FileSize;
    int FileOffset;
    void *FileHandle;
    TTileFormat TileFormat;
    int TileCols;
    int TileRows;
    int RowSize;
    int PageSize;
    int TileSize;
    int TileWidth;
    int TileHeight;
    int ZoomTileWidth;
    int ZoomTileHeight;
    int BPP;
	unsigned long NumBytes;
    int Zoom;
    bool Modified;

    Bitmap256 *CopyBitmap;
    Bitmap256 Bitmap;       // ROM window bitmap
    Graphics::TBitmap *OffScreen;      // Virtual screen for doing all drawing operations
    TImage *PasteImage;
    TPanel *PastePanel;     // Panel used as container for PasteImage
    TRect rect;

    BYTE FGColor;
    BYTE BGColor;
    BYTE *TileData;
    int TileOffset;

    int MarkOffset;
    int MarkWidth;
    int MarkHeight;
    int MarkTop;
    int MarkLeft;
    int MarkBottom;
    int MarkRight;
    bool IsMarking;
    bool HasSelected;
    
    int PasteLeft;
    int PasteTop;
    int PasteDeltaX;
    int PasteDeltaY;
    bool HasPasted;
    bool IsDragging;

    int OldTick;
    int NewTick;
    int DblClkTime;

    bool ScrollHandled;
    POINT StartPt, MovePt;
    char buffer[256];
    void __fastcall DoPaste(void);
    void __fastcall PutBitmapPixel(Bitmap256 *bmp, int X, int Y, BYTE Color);
    void __fastcall FillBitmapTile(Bitmap256 *bmp, int X, int Y, BYTE Color);
    void __fastcall CopyBitmapTile(Bitmap256 *dest, int destX, int destY, Bitmap256 *src, int srcX, int srcY);
    void __fastcall Create256ColorBitmap(Bitmap256 *bmp, HDC hdc);
    void __fastcall DecodeToBitmap(BYTE *data, Bitmap256 *bmp);
    void __fastcall EncodeFromBitmap(Bitmap256 *bmp, BYTE *data);
    int __fastcall LoadROM(AnsiString fname);
    void __fastcall SaveROM(AnsiString fname);
    bool __fastcall LoadPalette(AnsiString fname);
    void __fastcall SavePalette(AnsiString fname);
    void __fastcall SetWindowSize(void);
    void __fastcall SetTileFormat(TTileFormat fmt);
    void __fastcall SetPalType(TPalType pt);
    void __fastcall DrawSelection(void);
    void __fastcall ShowFileOffset(void);
    BYTE GetBP(BYTE *data, int bp);
    __fastcall TChildForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChildForm *ChildForm;
//---------------------------------------------------------------------------
#endif
