//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include "nespal.h"
#include "child.h"
#include "main.h"
#include "goofs.h"
#include "pal.h"
#include "edit.h"
#include "clip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChildForm *ChildForm;

BYTE DefaultPalette[] = {
0x00,0x00,0x00,
0x63,0xCF,0x63,
0xFF,0x33,0x39,
0xFF,0xFF,0xDC,
0x86,0x00,0x33,
0x00,0x73,0xBF,
0xFF,0xCF,0x00,
0xB4,0xEB,0xEF,
0x00,0x00,0x93,
0x00,0xFF,0x51,
0x00,0xAC,0xFF,
0xA4,0x11,0xBC,
0x00,0x00,0x00,
0xF2,0x8C,0x59,
0x9F,0x00,0xB6,
0x00,0xDC,0x83,
0x09,0x00,0x21,
0xFF,0xFF,0xFF,
0xFF,0x9F,0x00,
0xFF,0x00,0x03,
0xFF,0xAF,0xC2,
0xF0,0x00,0x4B,
0xE1,0x36,0xFC,
0x6D,0x04,0x73,
0x00,0x03,0x00,
0xFF,0xF9,0x4B,
0x9F,0xA3,0x00,
0x63,0x60,0x00,
0x00,0x00,0x00,
0xF0,0x5C,0xF9,
0xEF,0x6B,0x84,
0x00,0xFF,0x5D,
0x00,0x00,0x00,
0x99,0xE2,0x00,
0xFF,0x2F,0x4C,
0x5E,0xFF,0xD6,
0x00,0x2D,0x24,
0xFF,0xFF,0x00,
0x4A,0xC2,0x34,
0x48,0x38,0xF5,
0x43,0x00,0xD6,
0xFF,0x00,0x00,
0xE8,0x89,0x0B,
0x00,0xFC,0x84,
0x00,0x40,0x66,
0xFF,0xD2,0x00,
0xBB,0xD9,0x6B,
0xFF,0x00,0x67,
0xFF,0x69,0x00,
0x33,0x00,0x59,
0xFF,0xFF,0x4B,
0x1B,0xAC,0xFB,
0x5E,0xAA,0xE3,
0x4F,0x5D,0xF9,
0xB1,0x2A,0x8E,
0x6D,0xF6,0x74,
0xEB,0x07,0xE3,
0x9E,0xB7,0x6E,
0xEE,0x5F,0xD6,
0x2B,0xF8,0xBA,
0x72,0x33,0x38,
0x5D,0x06,0x3C,
0xDC,0x9C,0x6F,
0xAA,0x2B,0x12,
0x17,0x65,0x99,
0xC6,0x67,0x1B,
0x61,0xEC,0x0D,
0x82,0x01,0x94,
0x97,0x8F,0x12,
0x77,0xEA,0xB5,
0x4A,0x99,0x36,
0x09,0x9F,0xAF,
0x95,0x65,0x58,
0x0F,0xD9,0x72,
0xF2,0x4C,0xA5,
0x47,0xF7,0xA2,
0x06,0x79,0x96,
0xA1,0xAB,0xB4,
0x63,0x30,0x56,
0xE0,0x2D,0x81,
0x2A,0x58,0x36,
0x9D,0xCA,0xE0,
0x65,0xC0,0x43,
0xC4,0xB9,0xD5,
0x11,0xA9,0x83,
0xF6,0xDB,0x7D,
0x87,0x42,0xB1,
0xB1,0x76,0x15,
0x21,0x8E,0x7A,
0xF1,0x57,0x7E,
0x94,0x3F,0x95,
0xEA,0xDD,0xED,
0xC0,0xD7,0x4E,
0xA8,0x40,0x90,
0xA7,0x92,0x52,
0xF8,0xEE,0x81,
0xBC,0xCD,0x29,
0x0E,0xA3,0x76,
0xE5,0xA1,0x01,
0x28,0x44,0x57,
0xB5,0x51,0x2D,
0x2F,0xC6,0x53,
0xEB,0xA1,0x3F,
0x2D,0xFD,0xA6,
0x47,0x90,0x61,
0x41,0xBB,0xDC,
0xC5,0x35,0x97,
0x5F,0x4C,0xBE,
0xBF,0x67,0x49,
0x78,0xAE,0x54,
0xB5,0xBD,0x0C,
0x76,0x41,0xF9,
0x69,0xB4,0xF7,
0xD7,0x04,0x9F,
0x7A,0x48,0x7F,
0x52,0xAD,0x20,
0x6E,0x7F,0x52,
0x5A,0x96,0x33,
0x60,0x7D,0xDB,
0x02,0x35,0x5C,
0xF0,0x72,0x78,
0xE8,0xDE,0x01,
0xA1,0x98,0x35,
0xA0,0xB9,0x0E,
0x98,0xEE,0x91,
0xBC,0x46,0xBD,
0xBD,0x67,0xCE,
0xE8,0x7C,0xA2,
0x7B,0x6C,0xFB,
0x0A,0xCF,0x97,
0xD3,0x68,0x2E,
0x5C,0xFB,0x6A,
0x24,0x3C,0xA9,
0xE9,0x43,0xF2,
0x1D,0x73,0x6F,
0x26,0xF7,0x42,
0x7A,0x8E,0x1A,
0xE7,0x08,0xFD,
0x40,0x06,0xEB,
0xA2,0xAE,0xF0,
0xF0,0x85,0xCB,
0x22,0xDD,0xC2,
0xEB,0x03,0xCB,
0x87,0x92,0x18,
0x5E,0x0F,0x42,
0x3E,0x2F,0x83,
0x73,0x88,0x0A,
0x56,0x70,0x7B,
0x95,0x26,0xA4,
0xA2,0x3E,0x37,
0x29,0x59,0xBE,
0xB1,0x15,0xE2,
0x29,0xF6,0x1D,
0xCA,0x4B,0xC2,
0x23,0x48,0x76,
0x2D,0xC7,0xE5,
0xC7,0x35,0xC2,
0xF4,0x14,0x84,
0x6B,0x7D,0x1D,
0x1C,0x4F,0xAD,
0x79,0xAA,0xC3,
0xA9,0x09,0x49,
0xF4,0xCD,0x7B,
0x7B,0xD0,0xAE,
0x25,0xEA,0x81,
0x2B,0x5E,0x23,
0xB5,0x09,0x61,
0x53,0xDC,0x47,
0xF5,0x8C,0x41,
0x41,0xDC,0xE8,
0x42,0x3A,0xA4,
0xDE,0x38,0x64,
0x2A,0x45,0xA6,
0x01,0x1F,0x57,
0x75,0xA7,0xB4,
0x62,0x1B,0x26,
0xDE,0x88,0xC0,
0xC0,0x5A,0x68,
0xE9,0xAE,0x99,
0x81,0xE7,0xB6,
0x51,0x4F,0x2C,
0x9E,0x72,0xA6,
0x5E,0xF1,0xC2,
0xF7,0x17,0x5A,
0xFD,0x21,0x9A,
0x8E,0xF1,0x52,
0x21,0x71,0xFC,
0x50,0x22,0x58,
0x88,0xC6,0x3A,
0x19,0x45,0xF8,
0x3C,0xAA,0x21,
0xD7,0xA0,0x67,
0x52,0xCC,0xF2,
0x4C,0xE4,0x00,
0x43,0xCC,0x98,
0x1E,0xDC,0xF4,
0x07,0x6F,0x0E,
0xB7,0x91,0x88,
0xAF,0x0F,0x2B,
0x0A,0xD6,0x44,
0xD8,0x53,0x43,
0xB6,0xEC,0xA3,
0x06,0x62,0xBB,
0x5A,0x81,0x6A,
0x26,0xA6,0x0E,
0xC2,0x1E,0x72,
0xDF,0xC2,0x12,
0x28,0x66,0x21,
0xF6,0xFA,0xD6,
0x2B,0xA2,0x7D,
0x5F,0x6F,0x12,
0x30,0x6F,0x18,
0xF8,0x0C,0x80,
0x10,0x66,0xA7,
0xAC,0x78,0x4C,
0x92,0x75,0xFA,
0x28,0xC6,0xD3,
0x2C,0x85,0xD8,
0x8E,0xF0,0x02,
0xE1,0x25,0x71,
0x7A,0x8A,0xFB,
0x2B,0x6B,0x5E,
0x73,0x86,0x2A,
0x44,0xE7,0x6F,
0x9D,0xCD,0xF8,
0x37,0x54,0x93,
0xEA,0x65,0xD1,
0xD7,0x45,0xF0,
0x33,0x52,0xE7,
0xD6,0x48,0xA3,
0xDC,0x30,0xAD,
0x92,0x0F,0xD5,
0xE9,0x57,0x2A,
0x35,0xA9,0x3C,
0x9B,0xFC,0xA9,
0x37,0xF3,0x5D,
0x14,0x3E,0x89,
0x7F,0xA5,0x05,
0xD8,0x5E,0xFA,
0x63,0xDF,0x30,
0xC8,0xCC,0xB8,
0xDD,0x0E,0xA2,
0x1F,0x28,0xD4,
0xDF,0x6D,0xB3,
0xED,0xD7,0xA7,
0x90,0x99,0x54,
0x88,0xBE,0x41,
0x9D,0xBC,0xA7,
0x1B,0x38,0x01,
0x91,0xA0,0xA0,
0xCF,0xD4,0xF6,
0x76,0xCD,0xD7,
0x6D,0x31,0x8A,
0x22,0xD0,0x3B,
0x77,0x50,0xD3,
0x55,0x30,0x80
};

char *TileFormatStrings[] = { "Monochrome [1BPP]",
                            "NES [2BPP]",
                            "Game Boy [2BPP]",
                            "Virtual Boy [2BPP]",
                            "NGPC [2BPP]",
                            "SNES [3BPP]",
                            "SNES [4BPP]",
                            "SMS [4BPP]",
                            "Genesis [4BPP]",
                            "GBA [4BPP]" };

//---------------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
if (Modified) // ROM modified?
    {   // If so, ask if user wants to save changes
    wsprintf(buffer, "Save changes to %s?", (ExtractFileName(ROMFileName).c_str()));
    int result = Application->MessageBox(buffer, "Tile Layer Pro", MB_YESNOCANCEL | MB_ICONQUESTION);
    if (result == ID_CANCEL)
        {   // "Cancel" --> don't close form
        MainForm->bClosed = false;
        Action = caNone;
        return;
        }
    else if (result == ID_YES)  // "Yes" --> save file
        SaveROM(ROMFileName);
    }   // "No" --> close down form

MainForm->bClosed = true;
Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormPaint(TObject *Sender)
{
// Draw main (ROM) bitmap
StretchDIBits(OffScreen->Canvas->Handle,
                0,
                0,
                OffScreen->Width,
                OffScreen->Height,
                0,
                0,
                Bitmap.bminfo.bmiHeader.biWidth,
                -Bitmap.bminfo.bmiHeader.biHeight,
                Bitmap.bmptr,
                (BITMAPINFO *) &Bitmap.bminfo,
                DIB_RGB_COLORS,
                SRCCOPY);

if (Gridlines1->Checked)
    {   // Draw gridlines
    OffScreen->Canvas->Pen->Color = clSilver;
    OffScreen->Canvas->Pen->Mode = pmCopy;
    int linepos = ZoomTileWidth;
    for (int i=1; i<TileCols; i++)
        {
        OffScreen->Canvas->MoveTo(linepos, 0);
        OffScreen->Canvas->LineTo(linepos, ClientHeight); // Draw vertical line
        linepos += ZoomTileWidth;
        }
    linepos = ZoomTileHeight;
    for (int i=1; i<TileRows; i++)
        {
        OffScreen->Canvas->MoveTo(0, linepos);
        OffScreen->Canvas->LineTo(ClientWidth, linepos);  // Draw horizontal line
        linepos += ZoomTileHeight;
        }
    }

if (HasSelected)
    {   // Draw the currently selected tile area
    DrawSelection();
    }

// Copy the whole thing to the screen
rect = Rect(0, 0, OffScreen->Width, OffScreen->Height);
Canvas->CopyRect(rect, OffScreen->Canvas, rect);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::N4x1Click(TObject *Sender)
{
((TMenuItem *)(Sender))->Checked = true;
Zoom = ((TMenuItem *)Sender)->Tag;
SetWindowSize();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Gridlines1Click(TObject *Sender)
{
Gridlines1->Checked = !(Gridlines1->Checked);   // Toggle gridlines
FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormActivate(TObject *Sender)
{
if (TileData != NULL)
    {
    // Decode tile to editor
    EditForm->EditBitmap.decinfo.tlfmt = TileFormat;
    EditForm->EditBitmap.decinfo.tlbpp = BPP;
    EditForm->EditBitmap.decinfo.tlsize = TileSize;
    ChildForm->DecodeToBitmap(TileData, &EditForm->EditBitmap);
    // Copy selected tile to editor
    EditForm->Owna = this;
    EditForm->TileData = TileData;
    EditForm->TileOffset = TileOffset;
    EditForm->TileFmt = TileFormat;
    EditForm->TileSize = TileSize;
    EditForm->BPP = BPP;
    CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, Bitmap.bminfo.bmiColors, 16*4);
    EditForm->IsClipTile = false;
    }
else {
    FillBitmapTile(&EditForm->EditBitmap, 0, 0, 0);
    }
EditForm->FormPaint(Sender);

// Undo shit
if (UndoCount == 0)
    EditForm->SpeedButton4->Enabled = false;
else
    EditForm->SpeedButton4->Enabled = true;

// Write file size (in K) to statusbar
MainForm->StatusBar->Panels->Items[0]->Text = IntToStr(FileSize / 1024) + "K";
// Write file offset (in hex) to statusbar
ShowFileOffset();
MainForm->StatusBar->Panels->Items[2]->Text = TileFormatStrings[TileFormat];

// Give palette info to palette editor...
MainForm->ActiveForm = this;
PalForm->ActiveBitmap = &Bitmap;
PalForm->Palette = &Palette[0];
PalForm->FGColor = FGColor;
PalForm->BGColor = BGColor;
PalForm->BPP = BPP;
PalForm->PalSelect = PalSelect;
PalForm->NumPalEntries = NumPalEntries;
PalForm->InitPalette();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (HasPasted)
    {
    // Encode pasted bitmap at its current position
    HasPasted = false;
    PastePanel->Visible = false;

    // Calculate ROM offset where insert will begin
    int PasteOffset = FileOffset + (PasteLeft * TileSize) + (PasteTop * RowSize);
    CopyBitmap->encinfo.top = 0;
    CopyBitmap->encinfo.left = 0;
    CopyBitmap->encinfo.tlskip = TileCols - CopyBitmap->bmTileCols;
    CopyBitmap->encinfo.tlsize = TileSize;
    CopyBitmap->encinfo.tlbpp = BPP;
    CopyBitmap->encinfo.tlfmt = TileFormat;
    CopyBitmap->encinfo.cols = CopyBitmap->bmTileCols;
    CopyBitmap->encinfo.rows = CopyBitmap->bmTileRows;
    EncodeFromBitmap(CopyBitmap, &FilePtr[PasteOffset]);
    Modified = true;    // ROM has been modified!
    DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
    FormPaint(Sender);
    }

if (HasSelected)
    {
    // Erase old selection
    DrawSelection();
    // Copy it to screen
    RECT rect = Rect(MarkLeft*ZoomTileWidth, MarkTop*ZoomTileHeight, MarkRight*ZoomTileWidth, MarkBottom*ZoomTileHeight);
    Canvas->CopyRect(rect, OffScreen->Canvas, rect);
    }

if (Button == mbRight)
    {
    IsMarking = true;
    MarkLeft = X / ZoomTileWidth;
    MarkTop = Y / ZoomTileHeight;
    MarkRight = MarkLeft+1;
    MarkBottom = MarkTop+1;

    // Draw new selection
    DrawSelection();
    // Copy it to screen
    RECT rect = Rect(MarkLeft*ZoomTileWidth, MarkTop*ZoomTileHeight, MarkRight*ZoomTileWidth, MarkBottom*ZoomTileHeight);
    Canvas->CopyRect(rect, OffScreen->Canvas, rect);

    HasSelected = true;
    }
else
    {   // mbLeft
    HasSelected = false;

    // Get tile location
    int tileX = X / ZoomTileWidth;
    int tileY = Y / ZoomTileWidth;
    TileOffset = FileOffset + (tileX * TileSize) + (tileY * RowSize);
    if (TileOffset >= FileSize)
        return;
    TileData = &FilePtr[TileOffset];

    // Copy tile to editor
    ChildForm->CopyBitmapTile(&EditForm->EditBitmap, 0, 0, &Bitmap, tileX, tileY);
    EditForm->Owna = this;
    EditForm->TileData = &FilePtr[TileOffset];
    EditForm->TileOffset = TileOffset;
    EditForm->TileFmt = TileFormat;
    EditForm->TileSize = TileSize;
    EditForm->BPP = BPP;
    CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, Bitmap.bminfo.bmiColors, 16*4);
    EditForm->IsClipTile = false;
    EditForm->FormPaint(Sender);

    // Setup drag & drop
    MainForm->CanUndoDrop = false;
    MainForm->DragOwner = this;
    MainForm->DragData = &FilePtr[TileOffset];
    MainForm->DragOffset = TileOffset;
    MainForm->DragBitmap.decinfo.tlsize = TileSize;
    MainForm->DragBitmap.decinfo.tlfmt = TileFormat;
    MainForm->DragBitmap.decinfo.tlbpp = BPP;
    DragLabel->BeginDrag(false);
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
// Make sure mouse coordinates are in proper range
if (X >= (ClientWidth-16))
    X = ClientWidth-(16+1);
if (Y >= ClientHeight)
    Y = ClientHeight-1;

if (IsMarking)
    {   // User is selecting tile area
    // Erase old selection
    DrawSelection();
    RECT rect = Rect(MarkLeft*ZoomTileWidth, MarkTop*ZoomTileHeight, MarkRight*ZoomTileWidth, MarkBottom*ZoomTileHeight);
    // Update marking vars
    MarkRight = (X / ZoomTileWidth) + 1;
    MarkBottom = (Y / ZoomTileHeight) + 1;
    // Draw new selection
    DrawSelection();
    // Copy it to screen
    Canvas->CopyRect(rect, OffScreen->Canvas, rect);
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button == mbRight)
    IsMarking = false;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::PasteMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    IsDragging = true;
    PasteDeltaX = X;
    PasteDeltaY = Y;
    SetCapture(PastePanel->Handle);
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::PasteMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if (IsDragging)
    {   // User is positioning pasted bitmap
    PastePanel->Left = PastePanel->Left + (X - PasteDeltaX);
    PastePanel->Top = PastePanel->Top + (Y - PasteDeltaY);
    }
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::PasteMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
IsDragging = false;

// Make sure panel coords are in proper range

if (PastePanel->Left < 0)
    PastePanel->Left = 0;
else if (PastePanel->Left >= (ClientWidth-16))
    PastePanel->Left = ClientWidth-17;
if (PastePanel->Top < 0)
    PastePanel->Top = 0;
else if (PastePanel->Top >= ClientHeight)
    PastePanel->Top = ClientHeight-1;

PastePanel->Left = (PastePanel->Left / ZoomTileWidth) * ZoomTileWidth;
PastePanel->Top = (PastePanel->Top / ZoomTileHeight) * ZoomTileHeight;
PasteLeft = PastePanel->Left / ZoomTileWidth;
PasteTop = PastePanel->Top / ZoomTileHeight;
ReleaseCapture();
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::DrawSelection(void)
{
int top = MarkTop*ZoomTileHeight;
int bottom = MarkBottom*ZoomTileHeight;
int left = MarkLeft*ZoomTileWidth;
int right = MarkRight*ZoomTileWidth;

OffScreen->Canvas->Pen->Mode = pmXor;
OffScreen->Canvas->Pen->Style = psSolid;
OffScreen->Canvas->Pen->Color = clWhite;

for (int i=top; i<bottom; i++)
    {
    OffScreen->Canvas->MoveTo(left,i);
    OffScreen->Canvas->LineTo(right,i);
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormCreate(TObject *Sender)
{
// Set default tile display variables
TileWidth = 8;
TileHeight = 8;
TileCols = 16;
TileRows = 16;

// Initalize various vars
//StartPt = Point(0, 0);
//MovePt = Point(0, 0);
FGColor = 1;
CopyBitmap = &MainForm->CopyBitmap;

OffScreen = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SetWindowSize(void)
{
OnResize = NULL;    // Don't want resize handler to be called now

RowSize = TileSize * TileCols;
PageSize = RowSize * TileRows;
int Max = FileSize - PageSize;
if (Max < 0)
    ScrollBar->Max = 0;
else
    ScrollBar->Max = Max;

ZoomTileWidth = TileWidth * Zoom;
ZoomTileHeight = TileHeight * Zoom;

// Initialize OffScreen & Bitmap
OffScreen->Width = Zoom * TileWidth * TileCols;
OffScreen->Height = Zoom * TileHeight * TileRows;
if ((Bitmap.bmTileRows != TileRows)
    || (Bitmap.bmTileCols != TileCols))
    {   // Create bitmap of new dimensions
    Bitmap.bmTileWidth = TileWidth;
    Bitmap.bmTileHeight = TileHeight;
    Bitmap.bmTileCols = TileCols;
    Bitmap.bmTileRows = TileRows;
    Create256ColorBitmap(&Bitmap, OffScreen->Canvas->Handle);
    }

Bitmap.decinfo.cols = TileCols;
Bitmap.decinfo.rows = TileRows;

ClientWidth = OffScreen->Width + 16;
ClientHeight = OffScreen->Height;

DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
FormPaint(this);

OnResize = FormResize;  // Re-enable the resize handler
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormResize(TObject *Sender)
{
TileCols = (ClientWidth-16) / ZoomTileWidth;
TileRows = ClientHeight / ZoomTileWidth;
if (TileCols < 8)
    TileCols = 8;
else if (TileCols > 64)
    TileCols = 64;  // Max 64 cols
if (TileRows < 8)
    TileRows = 8;
else if (TileRows > 64)
    TileRows = 64; // Max 64 rows
SetWindowSize();
}
//---------------------------------------------------------------------------

int __fastcall TChildForm::LoadROM(AnsiString fname)
{
ROMFileName = fname;
// Open file for reading
FileHandle = CreateFile(ROMFileName.c_str(),
            			GENERIC_READ,
            			NULL,
            			NULL,
            			OPEN_EXISTING,
            			FILE_ATTRIBUTE_NORMAL,
            			NULL);
if (FileHandle == INVALID_HANDLE_VALUE)
    return -1;  // Couldn't open file

// Get file size
FileSize = GetFileSize(FileHandle, NULL);
// Allocate memory for file
FilePtr = (BYTE *)GlobalAlloc(GMEM_FIXED,
					FileSize);
if (FilePtr == NULL)
    return 0;     // Couldn't allocate memory

// Read file
ReadFile(FileHandle,
    	FilePtr,
    	FileSize,
    	&NumBytes,
    	NULL);
CloseHandle(FileHandle);

// "Autodetect" tileformat based on filename extension
ROMFileExt = UpperCase(ExtractFileExt(ROMFileName));
if (ROMFileExt == ".NES")
    SetTileFormat(tfNES);
else if (ROMFileExt == ".SMC")
    SetTileFormat(tfSNES);
else if ((ROMFileExt == ".GB")
        || (ROMFileExt == ".GBC"))
    SetTileFormat(tfGameBoy);
else if (ROMFileExt == ".VB")
    SetTileFormat(tfVirtualBoy);
else if (ROMFileExt == ".NGP")
    SetTileFormat(tfNGPC);
else if (ROMFileExt == ".SMS")
    SetTileFormat(tfSMS);
else if (ROMFileExt == ".SMD")
    SetTileFormat(tfGenesis);
else if (ROMFileExt == ".GBA")
    SetTileFormat(tfGBA);
else
    SetTileFormat(tf1BPP);

// Figure out the default palette filename: <romname>.TPL
if (ROMFileExt == "")  // No extension, just add .TPL
    PalFileName = ROMFileName + ".TPL";
else
    {   // Change extension to .TPL
    PalFileName = ROMFileName;
    int ExtLen = ROMFileExt.Length();
    int ExtPos = UpperCase(ROMFileName).AnsiPos(ROMFileExt);
    PalFileName.Delete(ExtPos, ExtLen);
    PalFileName += ".TPL";
    }

if (!LoadPalette(PalFileName))
    {   // Use Tile Layer Pro default 256-color palette
    SetPalType(pfRGB);
    NumPalEntries = 256;
    CopyMemory(Palette, DefaultPalette, 256*3);
    N2561->Checked = true;
    }

// Initialize some variables
Zoom = 3;           // Default zoom = 3x

if (MainForm->MDIChildCount == 1)
    {
    Transfertoclipboard1Click(this);
    }
return 1;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SetTileFormat(TTileFormat fmt)
{
TileFormat = fmt;
ScrollBar->Max = 0x7FFFFFFF;
switch(TileFormat)
    {
    case tf1BPP:
    BPP = 1;
    N1BPP1->Checked = true;
    ScrollBar->Min = 0;
    break;

    case tfNES:
    BPP = 2;
    NES1->Checked = true;
    ScrollBar->Min = 0;
    if ((FilePtr[0] == 'N')
        && (FilePtr[1] == 'E')
        && (FilePtr[2] == 'S')
        && (FilePtr[3] == 0x1A))
        {   // Is NES ROM
        ScrollBar->Min = 0x10 + (FilePtr[5] * 8192);
        }
    break;

    case tfGameBoy:
    BPP = 2;
    GameBoy1->Checked = true;
    ScrollBar->Min = 0x150;
    break;

    case tfVirtualBoy:
    BPP = 2;
    VirtualBoy1->Checked = true;
    ScrollBar->Min = 0;
    break;

    case tfNGPC:
    BPP = 2;
    NGPC1->Checked = true;
    ScrollBar->Min = 0;
    break;

    case tfSNES3BPP:
    BPP = 3;
    SNES3BPP1->Checked = true;
    ScrollBar->Min = 0x200;
    break;

    case tfSNES:
    BPP = 4;
    SNES1->Checked = true;
    ScrollBar->Min = 0x200;
    break;

    case tfSMS:
    BPP = 4;
    SMS1->Checked = true;
    ScrollBar->Min = 0;
    break;

    case tfGenesis:
    BPP = 4;
    Genesis1->Checked = true;
    ScrollBar->Min = 0x200;
    break;

    case tfGBA:
    BPP = 4;
    GBA1->Checked = true;
    ScrollBar->Min = 0xC0;
    break;

    case tfSNES8BPP:
    BPP = 8;
    ScrollBar->Min = 0x200;
    break;

    case tfRAW8:
    BPP = 8;
    ScrollBar->Min = 0;
    break;
    }

// Check for header ---------
if (FileOffset < ScrollBar->Min)
    FileOffset = ScrollBar->Min;

TileSize = (BPP * TileWidth * TileHeight) / 8;
RowSize = TileSize * TileCols;
PageSize = RowSize * TileRows;
if ((FileSize - PageSize - ScrollBar->Min) >= 0) {
    ScrollBar->Max = FileSize - PageSize;
    if (FileOffset > ScrollBar->Max)
        FileOffset = ScrollBar->Max;
    }
else
    {
    FileOffset = 0;
    ScrollBar->Min = 0;
    ScrollBar->Max = 0;
    }
ScrollBar->Position = FileOffset;
ShowFileOffset();

// Initialize tile info (for bitmap Draw function)
Bitmap.decinfo.tlsize = TileSize;
Bitmap.decinfo.tlfmt = TileFormat;
Bitmap.decinfo.tlbpp = BPP;
Bitmap.decinfo.tlskip = 0;
Bitmap.decinfo.cols = TileCols;
Bitmap.decinfo.rows = TileRows;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SaveROM(AnsiString fname)
{
if ((ROMFileExt == ".GB")
    || (ROMFileExt == ".GBC"))
    {   // Need to recalc checksum if GameBoy ROM
    DWORD CheckSum = 0;
    for (int i=0; i<(FileSize & 0x0FFF8000); i++)
        CheckSum += (DWORD)FilePtr[i];
    CheckSum -= (DWORD)FilePtr[0x14E];
    CheckSum -= (DWORD)FilePtr[0x14F];
    FilePtr[0x14E] = (BYTE)((CheckSum >> 8) & 0xFF);
    FilePtr[0x14F] = (BYTE)(CheckSum & 0xFF);
    }
else if (ROMFileExt == ".GBA") {
    // Calculate complement
    BYTE comp = 0;
    for (int i=0xA0; i<0xBD; i++)
        comp += FilePtr[i];
    comp ^= 0xFF;
    comp += (BYTE)(1 + 0x19 - 0x32);
    FilePtr[0xBD] = comp;
    // Calculate checksum
    DWORD CheckSum = 0;
    for (int i=0; i<FileSize; i++)
        CheckSum += (DWORD)FilePtr[i];
    CheckSum -= (DWORD)FilePtr[0xBE];
    CheckSum -= (DWORD)FilePtr[0xBF];
    FilePtr[0xBE] = (BYTE)(CheckSum & 0xFF);
    FilePtr[0xBF] = (BYTE)((CheckSum >> 8) & 0xFF);
    }
else if (ROMFileExt == ".BIN")
    {   // Recalc Genesis checksum
    DWORD CheckSum = 0;
    for (int i=0x200; i<FileSize; i++)
        CheckSum += (DWORD)(FilePtr[i] << 8);
    }

FileHandle = CreateFile(fname.c_str(),
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

WriteFile(FileHandle,
	FilePtr,
	FileSize,
	&NumBytes,
	NULL);

CloseHandle(FileHandle);

Modified = false;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Goto1Click(TObject *Sender)
{
GotoForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::GotoAgain1Click(TObject *Sender)
{
GotoForm->GoButtonClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Copy1Click(TObject *Sender)
{
if (HasSelected)
    {   // Copy current tile selection to a bitmap

    // Make sure coords are in proper range (swap if necessary)
    int temp;
    if (MarkRight < MarkLeft)
        {   // swap
        temp = MarkLeft;
        MarkLeft = MarkRight;
        MarkRight = temp;
        }
    if (MarkBottom < MarkTop)
        {   // swap
        temp = MarkTop;
        MarkTop = MarkBottom;
        MarkBottom = temp;
        }

    // Calc marking vars
    MarkOffset = FileOffset + (MarkLeft * TileSize) + (MarkTop * RowSize);
    MarkWidth = MarkRight - MarkLeft;
    MarkHeight = MarkBottom - MarkTop;

    // Init & create bitmap
    CopyBitmap->bmTileWidth = TileWidth;
    CopyBitmap->bmTileHeight = TileHeight;
    CopyBitmap->bmTileCols = MarkWidth;
    CopyBitmap->bmTileRows = MarkHeight;
    Create256ColorBitmap(CopyBitmap, OffScreen->Canvas->Handle);

    // Initialize tile info (for bitmap Draw function)
    CopyBitmap->decinfo.tlsize = TileSize;
    CopyBitmap->decinfo.tlfmt = TileFormat;
    CopyBitmap->decinfo.tlbpp = BPP;
    CopyBitmap->decinfo.tlskip = TileCols - MarkWidth;
    CopyBitmap->decinfo.cols = MarkWidth;
    CopyBitmap->decinfo.rows = MarkHeight;

    // Copy palette
    memcpy(&CopyBitmap->bminfo.bmiColors[0], &Bitmap.bminfo.bmiColors[0], 16*4);

    // Draw selected area on bitmap
    DecodeToBitmap(&FilePtr[MarkOffset], CopyBitmap);
    MainForm->HasCopied = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Paste1Click(TObject *Sender)
{
if (MainForm->HasCopied)
    {
    if (CopyBitmap->decinfo.tlbpp > BPP)
        {
        int result = Application->MessageBox("Source bitmap is of higher bitdepth than destination. The upper bitplanes will be lost. Continue paste anyway?", "Tile Layer Pro", MB_YESNO | MB_ICONQUESTION);
        if (result == IDNO)
            return;
        }
    DoPaste();
    }
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::NewPanelWP(TMessage &Msg)
{
  if (Msg.Msg == WM_ERASEBKGND) Msg.Result = false;
  else OldPanelWP(Msg);
}

//---------------------------------------------------------------------------
// Export current selection to bitmap.

void __fastcall TChildForm::ExportBitmap1Click(TObject *Sender)
{
if (MainForm->SavePictureDialog->Execute())
    {
    MarkWidth = MarkRight - MarkLeft;
    MarkHeight = MarkBottom - MarkTop;
    int bmstart = MarkTop * TileHeight * Bitmap.bminfo.bmiHeader.biWidth
                + MarkLeft * TileWidth;
    int bmwidth = MarkWidth * TileWidth;
    int bmheight = MarkHeight * TileHeight;
    int bmsize = bmwidth * bmheight;
    BYTE *bptr = &((BYTE *)Bitmap.bmptr)[bmstart];
    BITMAPFILEHEADER bmfh;
    BMINFO256 bmih;

    // Fill inn bitmapfileheader...
    bmfh.bfType = 'BM';
    bmfh.bfSize = sizeof(BITMAPFILEHEADER) +
                  sizeof(BMINFO256) +
                  bmsize;
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) +
                     sizeof(BMINFO256);

    // Fill in info header...
    bmih.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmih.bmiHeader.biWidth = bmwidth;
    bmih.bmiHeader.biHeight = bmheight;
    bmih.bmiHeader.biPlanes = 1;
    bmih.bmiHeader.biBitCount = 8;
    bmih.bmiHeader.biCompression = BI_RGB;
    bmih.bmiHeader.biSizeImage = 0;
    bmih.bmiHeader.biXPelsPerMeter = 0;
    bmih.bmiHeader.biYPelsPerMeter = 0;
    bmih.bmiHeader.biClrUsed = 0;
    bmih.bmiHeader.biClrImportant = 0;
    CopyMemory(bmih.bmiColors, Bitmap.bminfo.bmiColors, 16*4);

    FileHandle = CreateFile(MainForm->SavePictureDialog->FileName.c_str(),
            			    GENERIC_WRITE,
            			    NULL,
            			    NULL,
            			    CREATE_ALWAYS,
            			    FILE_ATTRIBUTE_NORMAL,
            			    NULL);

    // Write file header
    WriteFile(FileHandle,
        	&bmfh,
        	sizeof(BITMAPFILEHEADER),
        	&NumBytes,
        	NULL);
    // Write bitmap infoheader
    WriteFile(FileHandle,
        	&bmih,
        	sizeof(BMINFO256),
        	&NumBytes,
        	NULL);
    // Write bitmap bits
    for (int y=(bmih.bmiHeader.biHeight-1); y>=0; y--)
        {
        WriteFile(FileHandle,
            	&bptr[y*Bitmap.bminfo.bmiHeader.biWidth],
            	bmih.bmiHeader.biWidth,
            	&NumBytes,
            	NULL);
        }

    CloseHandle(FileHandle);
    }
}
//---------------------------------------------------------------------------

bool __fastcall TChildForm::LoadPalette(AnsiString fname)
{
FileHandle = CreateFile(fname.c_str(),
            			GENERIC_READ,
            			NULL,
            			NULL,
            			OPEN_EXISTING,
            			FILE_ATTRIBUTE_NORMAL,
            			NULL);
if (FileHandle == INVALID_HANDLE_VALUE)
    return false;

// "Autodetect" palette format based on filename extension
AnsiString PalFileExt;
PalFileExt = UpperCase(ExtractFileExt(fname));
if (PalFileExt == ".TPL") { // Tile Layer Pro palette
    BYTE palhdr[4];
    ReadFile(FileHandle,
           	&palhdr,
           	4,
          	&NumBytes,
           	NULL);
    if ((palhdr[0] != 'T')
        || (palhdr[1] != 'P')
        || (palhdr[2] != 'L'))
        {
        Application->MessageBox("Error: Palette is not a valid Tile Layer Pro palette.", "Tile Layer Pro", MB_OK | MB_ICONERROR);
        CloseHandle(FileHandle);
        return false;
        }
    SetPalType((TPalType)palhdr[3]);
    int fsize = GetFileSize(FileHandle, NULL);
    NumPalEntries = (fsize - 4) / PalEntrySize;
    }
else if (PalFileExt.Pos(".ST") == 1) {    // NESticle Save State
    if (SetFilePointer(FileHandle, 0x5907, 0, FILE_BEGIN) != 0x5907)
        return false;
    SetPalType(pfNES);
    NumPalEntries = 32;
    }
else if (PalFileExt.Pos(".ZS") == 1) {    // ZSNES Save State
    if (SetFilePointer(FileHandle, 0xCC13, 0, FILE_BEGIN) != 0xCC13)
        return false;
    SetPalType(pfSNES);
    NumPalEntries = 256;
    }
else
    return false;   // Unknown format

switch (NumPalEntries)
    {
    case 16:
    N161->Checked = true;
    break;
    case 32:
    N321->Checked = true;
    break;
    case 64:
    N641->Checked = true;
    break;
    case 128:
    N1281->Checked = true;
    break;
    case 256:
    N2561->Checked = true;
    break;
    }

PalFileName = fname;
PalSelect = 0;
PalForm->PalSelect = PalSelect;
PalForm->NumPalEntries = NumPalEntries;

// Copy palette from file to bitmap palette
BYTE entry[3];
for (int i=0; i<NumPalEntries; i++)
    {
    ReadFile(FileHandle,
        	&entry,
        	PalEntrySize,
           	&NumBytes,
        	NULL);
    switch (PalType)
        {
        case pfRGB:
        Palette[i].rgbtRed = entry[0];
        Palette[i].rgbtGreen = entry[1];
        Palette[i].rgbtBlue = entry[2];
        break;

        case pfSNES:
        Palette[i].rgbtRed = (BYTE)((entry[0] & 0x1F) << 3);
        Palette[i].rgbtGreen = (BYTE)(((entry[0] & 0xE0) >> 2) | ((entry[1] & 0x03) << 6));
        Palette[i].rgbtBlue = (BYTE)((entry[1] & 0x7C) << 1);
        break;

        case pfNES:
        Palette[i].rgbtRed = NESPalette[entry[0] << 2];
        Palette[i].rgbtGreen = NESPalette[(entry[0] << 2) + 1];
        Palette[i].rgbtBlue = NESPalette[(entry[0] << 2) + 2];
        break;
        }
    }

CloseHandle(FileHandle);
return true;
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::SavePalette(AnsiString fname)
{
FileHandle = CreateFile(fname.c_str(),
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

BYTE palhdr[4];
palhdr[0] = 'T'; palhdr[1] = 'P'; palhdr[2] = 'L'; palhdr[3] = (BYTE)PalType;
WriteFile(FileHandle,
       	&palhdr,
       	4,
       	&NumBytes,
       	NULL);

BYTE entry[3];
BYTE r, g, b, bestcol;
int diff, bestdiff;
for (int i=0; i<NumPalEntries; i++)
    {
    switch (PalType)
        {
        case pfRGB:
        entry[0] = Palette[i].rgbtRed;
        entry[1] = Palette[i].rgbtGreen;
        entry[2] = Palette[i].rgbtBlue;
        break;
        case pfSNES:
        r = (BYTE)(Palette[i].rgbtRed >> 3);
        g = (BYTE)(Palette[i].rgbtGreen >> 3);
        b = (BYTE)(Palette[i].rgbtBlue >> 3);
        entry[0] = (BYTE)(r | (g << 5));
        entry[1] = (BYTE)((b << 2) | (g >> 3));
        break;
        case pfNES:
        r = Palette[i].rgbtRed;
        g = Palette[i].rgbtGreen;
        b = Palette[i].rgbtBlue;
        bestdiff = 768;
        for (int j=0; j<64; j++)
            {   // match with NES color
            diff = abs(r - NESPalette[j << 2])
                    + abs(g - NESPalette[(j << 2) + 1])
                    + abs(b - NESPalette[(j << 2) + 2]);
            if (diff < bestdiff)
                {
                bestdiff = diff;
                bestcol = (BYTE)j;
                }
            }
        entry[0] = bestcol;
        break;
        }
    WriteFile(FileHandle,
        	&entry,
        	PalEntrySize,
        	&NumBytes,
        	NULL);
    }
CloseHandle(FileHandle);
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::Save1Click(TObject *Sender)
{
SavePalette(PalFileName);
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::SaveAs1Click(TObject *Sender)
{
MainForm->SavePalDialog->FileName = PalFileName;
if (MainForm->SavePalDialog->Execute())
    {
    PalFileName = MainForm->SavePalDialog->FileName;
    Save1Click(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Load1Click(TObject *Sender)
{
if (PalModified)
    {   // Save current palette if desired
    int result = Application->MessageBox("Current palette has been modified. Save changes?", "Tile Layer Pro", MB_YESNO | MB_ICONQUESTION);
    if (result == IDYES)
        SavePalette(PalFileName);
    }
MainForm->OpenPalDialog->FileName = PalFileName;
if (MainForm->OpenPalDialog->Execute())
    {
    if (!LoadPalette(MainForm->OpenPalDialog->FileName))
        Application->MessageBox("Couldn't load palette.", "Tile Layer Pro", MB_OK | MB_ICONERROR);
    else
        PalForm->InitPalette();
    }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::ScrollBarScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
switch (ScrollCode)
    {
    case scLineUp:
    FileOffset -= RowSize;
    break;

    case scLineDown:
    FileOffset += RowSize;
    break;

    case scPageUp:
    FileOffset -= PageSize;
    break;

    case scPageDown:
    FileOffset += PageSize;
    break;

    case scTrack:
    FileOffset = (ScrollPos / RowSize) * RowSize;
    break;

    case scTop:
    FileOffset = ScrollBar->Min;
    break;

    case scBottom:
    FileOffset = ScrollBar->Max;
    break;
    }

if (FileOffset < ScrollBar->Min)
    FileOffset = ScrollBar->Min;
else if (FileOffset > ScrollBar->Max)
    FileOffset = ScrollBar->Max;
ScrollPos = FileOffset;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::ScrollBarChange(TObject *Sender)
{
ShowFileOffset();
HasSelected = false;
DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
FormPaint(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
switch (Key)
    {
    case '1':    // Switch tileformat
    if (TileFormat == tfGenesis)
        SetTileFormat(tf1BPP);
    else
        SetTileFormat((TTileFormat)(TileFormat+1));
    if (FileOffset > ScrollBar->Max)
        {   // Gone too far!
        FileOffset = ScrollBar->Max;
        ScrollBar->Position = FileOffset;
        ShowFileOffset();
        }
    DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
    MainForm->StatusBar->Panels->Items[2]->Text = TileFormatStrings[TileFormat];
    if (BPP != PalForm->BPP) {
        PalSelect = (double)PalSelect * ((double)(1 << PalForm->BPP) / (double)(1 << BPP));
        PalForm->BPP = BPP;
        PalForm->PalSelect = PalSelect;
        }
    PalForm->InitPalette();
    break;

    case 0xBB:  // +
    FileOffset++;
    break;

    case 0xBD:  // -
    FileOffset--;
    break;

    case VK_DELETE:
    case VK_ESCAPE:
    if (HasPasted)
        {   // Delete pasted image
        HasPasted = false;
        PastePanel->Visible = false;
        }
    break;

    case VK_LEFT:
    if (Shift.Contains(ssShift))
        {
        if (TileCols > 8)
            TileCols--;
        SetWindowSize();
        }
    else if (Shift.Contains(ssCtrl))
        FileOffset--;
    else
        FileOffset -= TileSize;
    break;

    case VK_RIGHT:
    if (Shift.Contains(ssShift))
        {
        if (TileCols <= 64)
            TileCols++;
        SetWindowSize();
        }
    else if (Shift.Contains(ssCtrl))
        FileOffset++;
    else
        FileOffset += TileSize;
    break;

    case VK_UP:
    if (Shift.Contains(ssShift))
        {
        if (TileRows > 8)
            TileRows--;
        SetWindowSize();
        }
    else
        FileOffset -= RowSize;
    break;

    case VK_DOWN:
    if (Shift.Contains(ssShift))
        {
        if (TileRows <= 64)
            TileRows++;
        SetWindowSize();
        }
    else
        FileOffset += RowSize;
    break;

    case VK_PRIOR:
    FileOffset -= PageSize;
    break;

    case VK_NEXT:
    FileOffset += PageSize;
    break;

    case VK_HOME:
    FileOffset = ScrollBar->Min;
    break;

    case VK_END:
    FileOffset = ScrollBar->Max;
    break;

    default:
    return;
    }

if (FileOffset < ScrollBar->Min)
    FileOffset = ScrollBar->Min;
else if (FileOffset > ScrollBar->Max)
    FileOffset = ScrollBar->Max;
ScrollBar->Position = FileOffset;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Create256ColorBitmap(Bitmap256 *bmp, HDC hdc)
{
// Delete existing bitmap
DeleteObject(bmp->bmHandle);
// Set up bitmap header
bmp->bminfo.bmiHeader.biWidth = bmp->bmTileWidth * bmp->bmTileCols;
bmp->bminfo.bmiHeader.biHeight = -(bmp->bmTileHeight * bmp->bmTileRows);
bmp->bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
bmp->bminfo.bmiHeader.biPlanes = 1;
bmp->bminfo.bmiHeader.biBitCount = 8;
bmp->bminfo.bmiHeader.biCompression = BI_RGB;
bmp->bminfo.bmiHeader.biSizeImage = 0;
bmp->bminfo.bmiHeader.biXPelsPerMeter = 0;
bmp->bminfo.bmiHeader.biYPelsPerMeter = 0;
bmp->bminfo.bmiHeader.biClrUsed = 0;
bmp->bminfo.bmiHeader.biClrImportant = 0;
bmp->bmsize = bmp->bminfo.bmiHeader.biWidth * (-bmp->bminfo.bmiHeader.biHeight);
// Allocate mem for bitmap data
bmp->bmHandle = CreateDIBSection(hdc,
                                (BITMAPINFO *)&bmp->bminfo,
                                DIB_RGB_COLORS,
                                &bmp->bmptr,
                                NULL,
                                NULL);
}

//---------------------------------------------------------------------------

// Decode tile data from ROM to bitmap.
// Need to know:
// - Tile data info (location, size, format)
// - Where on bitmap (tilex, tiley) to start output
// - # of cols and # of rows to decode
// - # of tiles to skip after each row (can be 0)

void __fastcall TChildForm::DecodeToBitmap(BYTE *data, Bitmap256 *bmp)
{
int TempOffset = 0;
int TileOffset;
int BitIndex;
unsigned __int64 *ScanPtr;
BYTE RowPixels[8];

int rows = bmp->decinfo.rows;
/*
int endsize = (FilePtr+FileSize)-data;
if (endsize < PageSize) {
    rows = endsize / RowSize;
}
*/

// Calc starting pos on bitmap
int bmstart = ((bmp->decinfo.top * bmp->bmTileHeight) * bmp->bminfo.bmiHeader.biWidth)
                + (bmp->decinfo.left * bmp->bmTileWidth);
BYTE *bptr = &((BYTE *)bmp->bmptr)[bmstart];

for (int z=0; z<(bmp->bmTileHeight*rows); z+=bmp->bmTileHeight)
    {   // do a row of tiles
    for (int y=0; y<bmp->bmTileHeight; y++)
	    {   // do one scanline
	    ScanPtr = (unsigned __int64 *)&bptr[(z+y) * bmp->bminfo.bmiHeader.biWidth];
	    for (int x=0; x<bmp->decinfo.cols; x++)
	        {   // do X tiles horizontally
            switch(bmp->decinfo.tlfmt)
                {
                case tf1BPP:
                BitIndex = data[TempOffset + (x << 3) + y];
                ScanPtr[x] = MainForm->BitPatterns[0][BitIndex];
                break;

                case tfNES:
                TileOffset = TempOffset + (x << 4) + y;
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+8]];
                break;

                case tfGameBoy:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+1]];
                break;

                case tfVirtualBoy:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                RowPixels[0] = (BYTE)(data[TileOffset] & 0x03);
                RowPixels[1] = (BYTE)((data[TileOffset] & 0x0C) >> 2);
                RowPixels[2] = (BYTE)((data[TileOffset] & 0x30) >> 4);
                RowPixels[3] = (BYTE)(data[TileOffset++] >> 6);
                RowPixels[4] = (BYTE)(data[TileOffset] & 0x03);
                RowPixels[5] = (BYTE)((data[TileOffset] & 0x0C) >> 2);
                RowPixels[6] = (BYTE)((data[TileOffset] & 0x30) >> 4);
                RowPixels[7] = (BYTE)(data[TileOffset] >> 6);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfNGPC:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                RowPixels[4] = (BYTE)(data[TileOffset] >> 6);
                RowPixels[5] = (BYTE)((data[TileOffset] & 0x30) >> 4);
                RowPixels[6] = (BYTE)((data[TileOffset] & 0x0C) >> 2);
                RowPixels[7] = (BYTE)(data[TileOffset++] & 0x03);
                RowPixels[0] = (BYTE)(data[TileOffset] >> 6);
                RowPixels[1] = (BYTE)((data[TileOffset] & 0x30) >> 4);
                RowPixels[2] = (BYTE)((data[TileOffset] & 0x0C) >> 2);
                RowPixels[3] = (BYTE)(data[TileOffset] & 0x03);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfSNES3BPP:
                TileOffset = TempOffset + (x * 24) + (y << 1);
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+1]]
                            | MainForm->BitPatterns[2][data[TileOffset+16-y]];
                break;

                case tfSNES:
                TileOffset = TempOffset + (x << 5) + (y << 1);
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+1]]
                            | MainForm->BitPatterns[2][data[TileOffset+16]]
                            | MainForm->BitPatterns[3][data[TileOffset+17]];
                break;

                case tfSMS:
                TileOffset = TempOffset + (x << 5) + (y << 2);
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+1]]
                            | MainForm->BitPatterns[2][data[TileOffset+2]]
                            | MainForm->BitPatterns[3][data[TileOffset+3]];
                break;

                case tfGenesis:
                TileOffset = TempOffset + (x << 5) + (y << 2);
                RowPixels[0] = (BYTE)(data[TileOffset] >> 4);
                RowPixels[1] = (BYTE)(data[TileOffset++] & 0x0F);
                RowPixels[2] = (BYTE)(data[TileOffset] >> 4);
                RowPixels[3] = (BYTE)(data[TileOffset++] & 0x0F);
                RowPixels[4] = (BYTE)(data[TileOffset] >> 4);
                RowPixels[5] = (BYTE)(data[TileOffset++] & 0x0F);
                RowPixels[6] = (BYTE)(data[TileOffset] >> 4);
                RowPixels[7] = (BYTE)(data[TileOffset] & 0x0F);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfGBA:
                TileOffset = TempOffset + (x << 5) + (y << 2);
                RowPixels[0] = (BYTE)(data[TileOffset] & 0x0F);
                RowPixels[1] = (BYTE)(data[TileOffset++] >> 4);
                RowPixels[2] = (BYTE)(data[TileOffset] & 0x0F);
                RowPixels[3] = (BYTE)(data[TileOffset++] >> 4);
                RowPixels[4] = (BYTE)(data[TileOffset] & 0x0F);
                RowPixels[5] = (BYTE)(data[TileOffset++] >> 4);
                RowPixels[6] = (BYTE)(data[TileOffset] & 0x0F);
                RowPixels[7] = (BYTE)(data[TileOffset] >> 4);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfSNES8BPP:
                TileOffset = TempOffset + (x << 6) + (y << 1);
                ScanPtr[x] = MainForm->BitPatterns[0][data[TileOffset]]
                            | MainForm->BitPatterns[1][data[TileOffset+1]]
                            | MainForm->BitPatterns[2][data[TileOffset+16]]
                            | MainForm->BitPatterns[3][data[TileOffset+17]]
                            | MainForm->BitPatterns[4][data[TileOffset+32]]
                            | MainForm->BitPatterns[5][data[TileOffset+33]]
                            | MainForm->BitPatterns[6][data[TileOffset+48]]
                            | MainForm->BitPatterns[7][data[TileOffset+49]];
                break;

                case tfRAW8:
                BYTE *PixPtr = &data[TempOffset + (x << 3) + (y << 7)];
                ScanPtr[x] = *(unsigned __int64 *)PixPtr;
                }
            }
        }
    TempOffset += (bmp->decinfo.cols + bmp->decinfo.tlskip) * bmp->decinfo.tlsize;
    }

//
if (rows != bmp->decinfo.rows) {
}
//
}
//---------------------------------------------------------------------------
// Reverse of DecodeToBitmap ;-)

void __fastcall TChildForm::EncodeFromBitmap(Bitmap256 *bmp, BYTE *data)
{
int TempOffset = 0, j;
// Calc starting pos on bitmap
int bmstart = ((bmp->encinfo.top * bmp->bmTileHeight) * bmp->bminfo.bmiHeader.biWidth)
                + (bmp->encinfo.left * bmp->bmTileWidth);
BYTE *bptr = &((BYTE *)bmp->bmptr)[bmstart];

for (int y=0; y<bmp->encinfo.rows; y++)
    {
    for (int x=0; x<bmp->encinfo.cols; x++)
        {   // Encode one tile
        BYTE *TilePtr = &bptr[(x * 8) + (y * bmp->bminfo.bmiHeader.biWidth * 8)];
        switch (bmp->encinfo.tlfmt)
            {
            case tf1BPP:
            for (int i=0; i<8; i++)
                {
                int j = i * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = GetBP(&TilePtr[j], 0);
                }
            break;

            case tfNES:
            for (int i=0; i<8; i++)
                {
                j = i * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = GetBP(&TilePtr[j], 0);
                data[TempOffset+8+i] = GetBP(&TilePtr[j], 1);
                }
            break;

            case tfGameBoy:
            for (int i=0; i<16; i+=2)
                {
                j = (i >> 1) * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = GetBP(&TilePtr[j], 0);
                data[TempOffset+1+i] = GetBP(&TilePtr[j], 1);
                }
            break;

            case tfVirtualBoy:
            for (int i=0; i<16; i+=2)
                {
                j = (i >> 1) * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = BYTE((TilePtr[j+0] & 3)
                                        | ((TilePtr[j+1] & 3) << 2)
                                        | ((TilePtr[j+2] & 3) << 4)
                                        | ((TilePtr[j+3] & 3) << 6));
                data[TempOffset+i+1] = BYTE((TilePtr[j+4] & 3)
                                        | ((TilePtr[j+5] & 3) << 2)
                                        | ((TilePtr[j+6] & 3) << 4)
                                        | ((TilePtr[j+7] & 3) << 6));
                }
            break;

            case tfNGPC:
            for (int i=0; i<16; i+=2)
                {
                j = (i >> 1) * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = BYTE(((TilePtr[j+4] & 3) << 6)
                                        | ((TilePtr[j+5] & 3) << 4)
                                        | ((TilePtr[j+6] & 3) << 2)
                                        | (TilePtr[j+7] & 3));
                data[TempOffset+i+1] = BYTE(((TilePtr[j+0] & 3) << 6)
                                        | ((TilePtr[j+1] & 3) << 4)
                                        | ((TilePtr[j+2] & 3) << 2)
                                        | (TilePtr[j+3] & 3));
                }
            break;

            case tfSNES3BPP:
            for (int i=0; i<16; i+=2)
                {
                j = (i >> 1) * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = GetBP(&TilePtr[j], 0);
                data[TempOffset+1+i] = GetBP(&TilePtr[j], 1);
                data[TempOffset+16+(i>>1)] = GetBP(&TilePtr[j], 2);
                }
            break;

            case tfSNES:
            for (int i=0; i<16; i+=2)
                {
                j = (i >> 1) * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+i] = GetBP(&TilePtr[j], 0);
                data[TempOffset+1+i] = GetBP(&TilePtr[j], 1);
                data[TempOffset+16+i] = GetBP(&TilePtr[j], 2);
                data[TempOffset+17+i] = GetBP(&TilePtr[j], 3);
                }
            break;

            case tfSMS:
            for (int i=0; i<8; i++)
                {
                j = i * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+(i<<2)] = GetBP(&TilePtr[j], 0);
                data[TempOffset+(i<<2)+1] = GetBP(&TilePtr[j], 1);
                data[TempOffset+(i<<2)+2] = GetBP(&TilePtr[j], 2);
                data[TempOffset+(i<<2)+3] = GetBP(&TilePtr[j], 3);
                }
            break;

            case tfGBA:
            for (int i=0; i<8; i++)
                {
                j = i * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+(i<<2)] = (BYTE)((TilePtr[j+1] << 4)
                                            | (TilePtr[j+0] & 0x0F));
                data[TempOffset+(i<<2)+1] = (BYTE)((TilePtr[j+3] << 4)
                                            | (TilePtr[j+2] & 0x0F));
                data[TempOffset+(i<<2)+2] = (BYTE)((TilePtr[j+5] << 4)
                                            | (TilePtr[j+4] & 0x0F));
                data[TempOffset+(i<<2)+3] = (BYTE)((TilePtr[j+7] << 4)
                                            | (TilePtr[j+6] & 0x0F));
                }
            break;

            case tfGenesis:
            for (int i=0; i<8; i++)
                {
                j = i * bmp->bminfo.bmiHeader.biWidth;
                data[TempOffset+(i<<2)] = (BYTE)((TilePtr[j+0] << 4)
                                            | (TilePtr[j+1] & 0x0F));
                data[TempOffset+(i<<2)+1] = (BYTE)((TilePtr[j+2] << 4)
                                            | (TilePtr[j+3] & 0x0F));
                data[TempOffset+(i<<2)+2] = (BYTE)((TilePtr[j+4] << 4)
                                            | (TilePtr[j+5] & 0x0F));
                data[TempOffset+(i<<2)+3] = (BYTE)((TilePtr[j+6] << 4)
                                            | (TilePtr[j+7] & 0x0F));
                }
            break;
            }
        TempOffset += bmp->encinfo.tlsize;
        }
    TempOffset += bmp->encinfo.tlskip * bmp->encinfo.tlsize;
    }
}

//---------------------------------------------------------------------------

BYTE TChildForm::GetBP(BYTE *data, int bp)
{
return BYTE((((data[0] >> bp) & 1) << 7) |
            (((data[1] >> bp) & 1) << 6) |
            (((data[2] >> bp) & 1) << 5) |
            (((data[3] >> bp) & 1) << 4) |
            (((data[4] >> bp) & 1) << 3) |
            (((data[5] >> bp) & 1) << 2) |
            (((data[6] >> bp) & 1) << 1) |
            (((data[7] >> bp) & 1)));
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::Genesis1Click(TObject *Sender)
{
TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
SetTileFormat((TTileFormat)item->Tag);
MainForm->StatusBar->Panels->Items[2]->Text = TileFormatStrings[TileFormat];
DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
if (BPP != PalForm->BPP) {
    PalSelect = (double)PalSelect * ((double)(1 << PalForm->BPP) / (double)(1 << BPP));
    PalForm->BPP = BPP;
    PalForm->PalSelect = PalSelect;
    }
    PalForm->InitPalette();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::RGB1Click(TObject *Sender)
{
TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
SetPalType((TPalType)item->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SetPalType(TPalType pt)
{
PalType = pt;
switch (PalType)
    {
    case pfNES:
    PalEntrySize = 1;
    NES2->Checked = true;
    break;
    case pfSNES:
    PalEntrySize = 2;
    SNES2->Checked = true;
    break;
    default:
    PalEntrySize = 3;
    RGB1->Checked = true;
    break;
    }
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::FormDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
Accept = true;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormDragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
DecodeToBitmap(MainForm->DragData, &MainForm->DragBitmap);

// Calculate drop offset
int DropX = X / ZoomTileWidth;
int DropY = Y / ZoomTileHeight;
int DropOffset = FileOffset + (DropX * TileSize) + (DropY * RowSize);
if (DropOffset >= FileSize)
    return;
MainForm->DropData = &FilePtr[DropOffset];

// Save original data
CopyMemory(MainForm->OldDropData, MainForm->DropData, TileSize);
MainForm->CanUndoDrop = true;

// Perform drop
MainForm->DragBitmap.encinfo.tlsize = TileSize;
MainForm->DragBitmap.encinfo.tlbpp = BPP;
MainForm->DragBitmap.encinfo.tlfmt = TileFormat;
EncodeFromBitmap(&MainForm->DragBitmap, MainForm->DropData);
Modified = true;    // ROM has been modified!
DecodeToBitmap(&FilePtr[FileOffset], &Bitmap);
FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::PutBitmapPixel(Bitmap256 *bmp, int X, int Y, BYTE Color)
{
((BYTE *)bmp->bmptr)[(bmp->bminfo.bmiHeader.biWidth * Y) + X] = Color;
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::FillBitmapTile(Bitmap256 *bmp, int X, int Y, BYTE Color)
{
int bmpos = (Y * bmp->bmTileHeight * bmp->bminfo.bmiHeader.biWidth) + (X * bmp->bmTileWidth);
for (int y=0; y<bmp->bmTileHeight; y++)
    {
    for (int x=0; x<bmp->bmTileWidth; x++)
        {
        ((BYTE *)bmp->bmptr)[bmpos+x] = Color;
        }
    bmpos += bmp->bminfo.bmiHeader.biWidth;
    }
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::CopyBitmapTile(Bitmap256 *dest, int destX, int destY, Bitmap256 *src, int srcX, int srcY)
{
int srcpos = (srcY * src->bmTileHeight * src->bminfo.bmiHeader.biWidth) + (srcX * src->bmTileWidth);
int destpos = (destY * dest->bmTileHeight * dest->bminfo.bmiHeader.biWidth) + (destX * dest->bmTileWidth);
for (int y=0; y<src->bmTileHeight; y++)
    {
    for (int x=0; x<src->bmTileWidth; x++)
        {
        ((BYTE *)dest->bmptr)[destpos+x] = ((BYTE *)src->bmptr)[srcpos+x];
        }
    destpos += dest->bminfo.bmiHeader.biWidth;
    srcpos += src->bminfo.bmiHeader.biWidth;
    }
}
void __fastcall TChildForm::Transfertoclipboard1Click(TObject *Sender)
{
//
CopyMemory(ClipForm->Palette, Palette, 256*3);
for (int i=0; i<16; i++)
    {
    ClipForm->ClipBitmap.bminfo.bmiColors[i].rgbRed = Palette[i].rgbtRed;
    ClipForm->ClipBitmap.bminfo.bmiColors[i].rgbBlue = Palette[i].rgbtBlue;
    ClipForm->ClipBitmap.bminfo.bmiColors[i].rgbGreen = Palette[i].rgbtGreen;
    }
ClipForm->FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::ClearArranger1Click(TObject *Sender)
{
for (int y=0; y<CLIP_HEIGHT; y++)
    {
    for (int x=0; x<CLIP_WIDTH; x++)
        {
        ClipForm->ClipBoard[y][x].data = NULL;
        ChildForm->FillBitmapTile(&ClipForm->ClipBitmap, x, y, 16);
        }
    }
ClipForm->FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Edit1Click(TObject *Sender)
{
Undodrop1->Enabled = MainForm->CanUndoDrop;
Copy1->Enabled = HasSelected;
Paste1->Enabled = MainForm->HasCopied;
ExportBitmap1->Enabled = HasSelected;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Undodrop1Click(TObject *Sender)
{
if (MainForm->CanUndoDrop)
    {
    MainForm->CanUndoDrop = false;
    CopyMemory(MainForm->DropData, MainForm->OldDropData, MainForm->DragBitmap.encinfo.tlsize);
    TChildForm *child = dynamic_cast<TChildForm*>(MainForm->DragOwner);
    child->DecodeToBitmap(&child->FilePtr[child->FileOffset], &child->Bitmap);
    child->FormPaint(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::ImportBitmap1Click(TObject *Sender)
{
if (!MainForm->OpenPictureDialog->Execute())
    return;

Graphics::TBitmap *Bmp = new Graphics::TBitmap();
Bmp->LoadFromFile(MainForm->OpenPictureDialog->FileName);
if (Bmp->Empty)
    {
    Application->MessageBox("Could not open bitmap.", "", MB_OK | MB_ICONERROR);
    return;
    }

Bmp->PixelFormat = pf8bit;
PALETTEENTRY Pal[256];
GetPaletteEntries(Bmp->Palette, 0, 256, Pal);

// Init & create bitmap
CopyBitmap->bmTileWidth = TileWidth;
CopyBitmap->bmTileHeight = TileHeight;
CopyBitmap->bmTileCols = Bmp->Width / TileWidth;
CopyBitmap->bmTileRows = Bmp->Height / TileHeight;
Create256ColorBitmap(CopyBitmap, OffScreen->Canvas->Handle);

// Set palette
for (int i=0; i<256; i++)
    {
    CopyBitmap->bminfo.bmiColors[i].rgbRed = Pal[i].peRed;
    CopyBitmap->bminfo.bmiColors[i].rgbBlue = Pal[i].peBlue;
    CopyBitmap->bminfo.bmiColors[i].rgbGreen = Pal[i].peGreen;
    }

// Read pixel data
for (int y=0; y<-CopyBitmap->bminfo.bmiHeader.biHeight; y++)
    CopyMemory(&((BYTE *)CopyBitmap->bmptr)[y*CopyBitmap->bminfo.bmiHeader.biWidth], (BYTE *)Bmp->ScanLine[y], CopyBitmap->bminfo.bmiHeader.biWidth);

DoPaste();
delete Bmp;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::N161Click(TObject *Sender)
{
TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
NumPalEntries = item->Tag;
item->Checked = true;
PalSelect = 0;
PalForm->PalSelect = PalSelect;
PalForm->NumPalEntries = NumPalEntries;
PalForm->InitPalette();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::DoPaste(void)
{
if (PastePanel)
    {   // Delete old panel
    PastePanel->WindowProc = OldPanelWP;
    delete PasteImage;
    delete PastePanel;
    }

// Create panel
PastePanel = new TPanel(this);
PastePanel->Parent = this;
PastePanel->BorderStyle = bsNone;
PastePanel->BevelInner = bvNone;
PastePanel->BevelOuter = bvNone;
PastePanel->FullRepaint = false;

//subclass the WindowProc to supress the WM_ERASEBKGND message
OldPanelWP = PastePanel->WindowProc;
PastePanel->WindowProc = NewPanelWP;

// Create image to put in panel
PasteImage = new TImage(this);
PasteImage->Left = 0;
PasteImage->Top = 0;
PasteImage->Width = CopyBitmap->bminfo.bmiHeader.biWidth * Zoom;
PasteImage->Height = -(CopyBitmap->bminfo.bmiHeader.biHeight * Zoom);
PasteImage->Canvas->MoveTo(0,0);
PasteImage->Canvas->LineTo(PasteImage->Width,PasteImage->Height);
PasteImage->Cursor = crSizeAll;
PasteImage->Visible = true;

// Put panel at top left corner of window (default position)
PastePanel->Left = 0;
PastePanel->Top = 0;
PastePanel->Width = PasteImage->Width;
PastePanel->Height = PasteImage->Height;

PasteImage->Parent = PastePanel;
PasteImage->Left = 0;
PasteImage->Top = 0;
PasteImage->OnMouseDown = PasteMouseDown;
PasteImage->OnMouseMove = PasteMouseMove;
PasteImage->OnMouseUp = PasteMouseUp;

// Draw pasted bitmap on image
StretchDIBits(PasteImage->Canvas->Handle,
              0,
              0,
              PasteImage->Width,
              PasteImage->Height,
              0,
              0,
              CopyBitmap->bminfo.bmiHeader.biWidth,
              -CopyBitmap->bminfo.bmiHeader.biHeight,
              CopyBitmap->bmptr,
              (BITMAPINFO *) &CopyBitmap->bminfo,
              DIB_RGB_COLORS,
              SRCCOPY);

PasteLeft = 0;
PasteTop = 0;
PastePanel->Visible = true;
HasPasted = true;
ScrollBar->BringToFront();
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::ShowFileOffset(void)
{
MainForm->StatusBar->Panels->Items[1]->Text = "Offset: " +
                                       IntToHex(FileOffset, 8) +
                                       " (" + IntToStr(100 * FileOffset / FileSize) +
                                       "%)";
}

//---------------------------------------------------------------------------

void __fastcall TChildForm::FormDestroy(TObject *Sender)
{
// Free resources associated with child window
delete OffScreen;
GlobalFree(FilePtr);
DeleteObject(Bitmap.bmHandle);
if (PastePanel)
    {
    PastePanel->WindowProc = OldPanelWP;
    delete PastePanel;
    }

// Unregister possible clipboard tiles
for (int y=0; y<CLIP_HEIGHT; y++)
    {
    for (int x=0; x<CLIP_WIDTH; x++)
        {
        if (ClipForm->ClipBoard[y][x].owner == this)
            {
            ClipForm->ClipBoard[y][x].data = NULL;
            ChildForm->FillBitmapTile(&ClipForm->ClipBitmap, x, y, 16);
            }
        }
    }
ClipForm->FormPaint(Sender);

if (EditForm->Owna == this)
    {
    EditForm->TileData = NULL;
    FillBitmapTile(&EditForm->EditBitmap, 0, 0, 0);
    }
    
if (MainForm->MDIChildCount == 1)
    {   // This is the last child, so disable appropriate speed buttons
    MainForm->SaveSpdBtn->Enabled = false;
    MainForm->ZoomInSpdBtn->Enabled = false;
    MainForm->ZoomOutSpdBtn->Enabled = false;
    MainForm->GridSpdBtn->Enabled = false;
    MainForm->WindowMenu->Visible = false;
    PalForm->Visible = false;
    ClipForm->Visible = false;
    EditForm->Visible = false;
    // Clear the statusbar
    MainForm->StatusBar->Panels->Items[0]->Text = "";
    MainForm->StatusBar->Panels->Items[1]->Text = "";
    MainForm->StatusBar->Panels->Items[2]->Text = "";
    MainForm->ActiveForm = NULL;
    }
}
//---------------------------------------------------------------------------

