//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "bmp256.h"
#include "main.h"
#include "child.h"
#include "clip.h"
#include "edit.h"
#include "pal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClipForm *ClipForm;
//---------------------------------------------------------------------------
__fastcall TClipForm::TClipForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClipForm::FormCreate(TObject *Sender)
{
// Create ClipBitmap
ClipBitmap.bmTileWidth = 8;
ClipBitmap.bmTileCols = CLIP_WIDTH;
ClipBitmap.bmTileHeight = 8;
ClipBitmap.bmTileRows = CLIP_HEIGHT;
ChildForm->Create256ColorBitmap(&ClipBitmap, ClipForm->Canvas->Handle);

FillMemory(ClipBitmap.bmptr, ClipBitmap.bmsize, 16);    // grey
FGColor = 1;
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormClose(TObject *Sender, TCloseAction &Action)
{
DeleteObject(ClipBitmap.bmHandle);
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
Accept = true;
}
//---------------------------------------------------------------------------
// Drop a tile on the clipboard.

void __fastcall TClipForm::FormDragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
int DropX = X / 16;
int DropY = Y / 16;
// Init clipboard entry
ClipEntry = &ClipBoard[DropY][DropX];
ClipEntry->owner = (TChildForm *)MainForm->DragOwner;
ClipEntry->xpos = DropX;
ClipEntry->ypos = DropY;
ClipEntry->data = MainForm->DragData;
ClipEntry->ofs = MainForm->DragOffset;
ClipEntry->fmt = MainForm->DragBitmap.decinfo.tlfmt;
ClipEntry->bpp = MainForm->DragBitmap.decinfo.tlbpp;
ClipEntry->size = MainForm->DragBitmap.decinfo.tlsize;
ClipEntry->pal = 0;

// Decode tile to clipboard
ClipBitmap.decinfo.left = DropX;
ClipBitmap.decinfo.top = DropY;
ClipBitmap.decinfo.tlfmt = ClipEntry->fmt;
ClipBitmap.decinfo.tlbpp = ClipEntry->bpp;
ClipBitmap.decinfo.tlsize = ClipEntry->size;
ClipBitmap.decinfo.cols = 1;
ClipBitmap.decinfo.rows = 1;
ChildForm->DecodeToBitmap(MainForm->DragData, &ClipBitmap);
FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormPaint(TObject *Sender)
{
StretchDIBits(Canvas->Handle,
                0,
                0,
                ClientWidth,
                ClientHeight,
                0,
                0,
                ClipBitmap.bminfo.bmiHeader.biWidth,
                -ClipBitmap.bminfo.bmiHeader.biHeight,
                ClipBitmap.bmptr,
                (BITMAPINFO *) &ClipBitmap.bminfo,
                DIB_RGB_COLORS,
                SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button == mbLeft)
    {
    int tileX = X / 16;
    int tileY = Y / 16;
    ClipEntry = &ClipBoard[tileY][tileX];
    if (ClipEntry->data == NULL)
        return; // No data in slot

    // Copy tile to editor
    ChildForm->CopyBitmapTile(&EditForm->EditBitmap, 0, 0, &ClipBitmap, tileX, tileY);
    EditForm->Owna = ClipEntry->owner;
    EditForm->TileData = ClipEntry->data;
    EditForm->TileOffset = ClipEntry->ofs;
    EditForm->TileFmt = ClipEntry->fmt;
    EditForm->TileSize = ClipEntry->size;
    EditForm->BPP = ClipEntry->bpp;
    CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, ClipBitmap.bminfo.bmiColors, 16*4);
    EditForm->IsClipTile = true;
    PalForm->BPP = ClipEntry->bpp;
    PalForm->InitPalette();
    EditForm->FormPaint(Sender);

    // Undo shit
    if (ClipEntry->owner->UndoCount == 0)
        EditForm->SpeedButton4->Enabled = false;
    else
        EditForm->SpeedButton4->Enabled = true;

    // Prepare drag & drop
    MainForm->DragData = ClipEntry->data;
    MainForm->DragBitmap.decinfo.tlsize = ClipEntry->size;
    MainForm->DragBitmap.decinfo.tlfmt = ClipEntry->fmt;
    MainForm->DragBitmap.decinfo.tlbpp = ClipEntry->bpp;
    DragLabel->BeginDrag(false);
    }
else
    {   // mbRight
    if (MainForm->DragData != NULL)
        {
        IsDrawing = true;
        FormDragDrop(0, 0, X, Y);

        int tileX = X / 16;
        int tileY = Y / 16;
        ClipEntry = &ClipBoard[tileY][tileX];
        if (ClipEntry->data == NULL)
            return; // No data in slot

        // Copy tile to editor
        ChildForm->CopyBitmapTile(&EditForm->EditBitmap, 0, 0, &ClipBitmap, tileX, tileY);
        EditForm->Owna = ClipEntry->owner;
        EditForm->TileData = ClipEntry->data;
        EditForm->TileOffset = ClipEntry->ofs;
        EditForm->TileFmt = ClipEntry->fmt;
        EditForm->TileSize = ClipEntry->size;
        EditForm->BPP = ClipEntry->bpp;
        CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, ClipBitmap.bminfo.bmiColors, 16*4);
        EditForm->IsClipTile = true;
        PalForm->BPP = ClipEntry->bpp;
        PalForm->InitPalette();
        EditForm->FormPaint(Sender);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormActivate(TObject *Sender)
{
if ((ClipEntry == NULL)
    || (ClipEntry->data == NULL))
    return;

// Give palette info to palette editor...
MainForm->ActiveForm = this;
PalForm->ActiveBitmap = &ClipBitmap;
PalForm->Palette = &Palette[0];
PalForm->FGColor = FGColor;
PalForm->BGColor = BGColor;

    // Copy tile to editor
    ChildForm->CopyBitmapTile(&EditForm->EditBitmap, 0, 0, &ClipBitmap, ClipEntry->xpos, ClipEntry->ypos);
    EditForm->Owna = ClipEntry->owner;
    EditForm->TileData = ClipEntry->data;
    EditForm->TileOffset = ClipEntry->ofs;
    EditForm->TileFmt = ClipEntry->fmt;
    EditForm->TileSize = ClipEntry->size;
    EditForm->BPP = ClipEntry->bpp;
    CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, ClipBitmap.bminfo.bmiColors, 16*4);
    EditForm->IsClipTile = true;
    PalForm->BPP = ClipEntry->bpp;
    PalForm->PalSelect = PalSelect; // ClipEntry->pal
    PalForm->InitPalette();
    EditForm->FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if (IsDrawing)
    {
    FormDragDrop(0, 0, X, Y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
IsDrawing = false;
}
//---------------------------------------------------------------------------

