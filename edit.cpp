//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "child.h"
#include "edit.h"
#include "main.h"
#include "clip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditForm *EditForm;
//---------------------------------------------------------------------------
__fastcall TEditForm::TEditForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (TileData != NULL)
    {
    btn = Button;
    IsDrawing = true;

    if (btn == mbLeft)
        ChildForm->PutBitmapPixel(&EditBitmap, X / 16, Y / 16, FGColor);  // fg
    else
        ChildForm->PutBitmapPixel(&EditBitmap, X / 16, Y / 16, BGColor);  // bg
    FormPaint(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if (IsDrawing == true)
    {
    switch (DrawingTool)
        {
        case dtPencil:
        if (X > 127)
            X = 127;
        else if (X < 0)
            X = 0;
        if (Y > 127)
            Y = 127;
        else if (Y < 0)
            Y = 0;
        if (btn == mbLeft)
            ChildForm->PutBitmapPixel(&EditBitmap, X / 16, Y / 16, FGColor);  // fg
        else
            ChildForm->PutBitmapPixel(&EditBitmap, X / 16, Y / 16, BGColor);  // bg
        FormPaint(Sender);
        break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (TileData == NULL)
    return;

IsDrawing = false;
UpdateTile();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormPaint(TObject *Sender)
{
StretchDIBits(Canvas->Handle,
                0,
                0,
                ClientWidth-80,
                ClientHeight,
                0,
                0,
                EditBitmap.bminfo.bmiHeader.biWidth,
                -EditBitmap.bminfo.bmiHeader.biHeight,
                EditBitmap.bmptr,
                (BITMAPINFO *) &EditBitmap.bminfo,
                DIB_RGB_COLORS,
                SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormCreate(TObject *Sender)
{
// Create EditBitmap
EditBitmap.bmTileWidth = 8;
EditBitmap.bmTileCols = 1;
EditBitmap.bmTileHeight = 8;
EditBitmap.bmTileRows = 1;
ChildForm->Create256ColorBitmap(&EditBitmap, Canvas->Handle);

// Init it
EditBitmap.encinfo.top = 0;
EditBitmap.encinfo.left = 0;
EditBitmap.encinfo.tlskip = 0;
EditBitmap.encinfo.cols = 1;
EditBitmap.encinfo.rows = 1;
EditBitmap.decinfo.top = 0;
EditBitmap.decinfo.left = 0;
EditBitmap.decinfo.tlskip = 0;
EditBitmap.decinfo.cols = 1;
EditBitmap.decinfo.rows = 1;
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormClose(TObject *Sender, TCloseAction &Action)
{
DeleteObject(EditBitmap.bmHandle);
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormActivate(TObject *Sender)
{
if (MainForm->ActiveForm == NULL)
    return;

child = dynamic_cast<TChildForm*>(MainForm->ActiveForm);
if (child)
    {
    FGColor = child->FGColor;
    BGColor = child->BGColor;
    }
else
    {   // ClipForm
    FGColor = ClipForm->FGColor;
    BGColor = ClipForm->BGColor;
    }
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::SpeedButton1Click(TObject *Sender)
{
if (TileData == NULL)
    return;
// Flip X
BYTE oldline[8];
int bmpos = 0;
for (int y=0; y<8; y++)
    {
    CopyMemory(oldline, &((BYTE *)EditBitmap.bmptr)[bmpos], 8);
    for (int x=0; x<8; x++)
        ((BYTE *)EditBitmap.bmptr)[bmpos+x] = oldline[7-x];
    bmpos += EditBitmap.bminfo.bmiHeader.biWidth;
    }
FormPaint(Sender);
UpdateTile();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::UpdateTile(void)
{
// Add current tiledata to undo buffer
CopyMemory(TempBuffer, Owna->UndoBuffer, sizeof(UNDOENTRY)*MAX_UNDOS);
CopyMemory(&Owna->UndoBuffer[1], TempBuffer, sizeof(UNDOENTRY)*(MAX_UNDOS-1));
Owna->UndoBuffer[0].ptr = TileData;
Owna->UndoBuffer[0].ofs = TileOffset;
Owna->UndoBuffer[0].size = TileSize;
Owna->UndoBuffer[0].bpp = BPP;
Owna->UndoBuffer[0].fmt = TileFmt;
CopyMemory(Owna->UndoBuffer[0].data, TileData, TileSize);
if (Owna->UndoCount < MAX_UNDOS)
    Owna->UndoCount++;
SpeedButton4->Enabled = true;

// Encode tile to ROM
EditBitmap.encinfo.tlsize = TileSize;
EditBitmap.encinfo.tlbpp = BPP;
EditBitmap.encinfo.tlfmt = TileFmt;
ChildForm->EncodeFromBitmap(&EditBitmap, TileData);
Owna->Modified = true;

// Update every instance of current tile in clipboard
for (int y=0; y<CLIP_HEIGHT; y++)
    {
    for (int x=0; x<CLIP_WIDTH; x++)
        {
        if (ClipForm->ClipBoard[y][x].data == TileData)
            {
            ChildForm->CopyBitmapTile(&ClipForm->ClipBitmap, x, y, &EditBitmap, 0, 0);
            }
        }
    }
    ClipForm->FormPaint(this);

// Update ROM window only if necessary
if ((TileOffset >= Owna->FileOffset)
    && (TileOffset < (Owna->FileOffset+Owna->PageSize)))
    {
    Owna->DecodeToBitmap(&Owna->FilePtr[Owna->FileOffset], &Owna->Bitmap);
    Owna->FormPaint(this);
    }
}

//---------------------------------------------------------------------------

void __fastcall TEditForm::SpeedButton2Click(TObject *Sender)
{
if (TileData == NULL)
    return;
// Flip Y
BYTE oldlines[8*8];
CopyMemory(oldlines, (BYTE *)EditBitmap.bmptr, 8*8);
for (int y=0; y<8; y++)
    CopyMemory(&((BYTE *)EditBitmap.bmptr)[y*8], &oldlines[(7-y)*8], 8);
FormPaint(Sender);
UpdateTile();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::SpeedButton3Click(TObject *Sender)
{
if (TileData == NULL)
    return;
// Rotate 90 degrees
int bmpos = 0;
BYTE oldlines[8*8];
CopyMemory(oldlines, (BYTE *)EditBitmap.bmptr, 8*8);
for (int y=0; y<8; y++)
    {
    for (int x=0; x<8; x++)
        ((BYTE *)EditBitmap.bmptr)[bmpos+x] = oldlines[y+((7-x)*8)];
    bmpos += EditBitmap.bminfo.bmiHeader.biWidth;
    }
FormPaint(Sender);
UpdateTile();
}
//---------------------------------------------------------------------------


void __fastcall TEditForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (TileData == NULL)
    return;
if (!Shift.Contains(ssShift))
    return;

BYTE oldlines[8*8];
CopyMemory(oldlines, (BYTE *)EditBitmap.bmptr, 8*8);

switch (Key)
    {
    case VK_LEFT:   // Shift tile left
    for (int y=0; y<64; y+=8)
        for (int x=0; x<8; x++)
            ((BYTE *)EditBitmap.bmptr)[y+x] = oldlines[y+((x+1)&7)];
    break;
    case VK_RIGHT:  // Shift tile right
    for (int y=0; y<64; y+=8)
        for (int x=0; x<8; x++)
            ((BYTE *)EditBitmap.bmptr)[y+((x+1)&7)] = oldlines[y+x];
    break;
    case VK_UP:   // Shift tile up
    CopyMemory((BYTE *)EditBitmap.bmptr, &oldlines[8], 8*7);
    CopyMemory(&((BYTE *)EditBitmap.bmptr)[8*7], oldlines, 8);
    break;
    case VK_DOWN:     // Shift tile down
    CopyMemory(&((BYTE *)EditBitmap.bmptr)[8], oldlines, 8*7);
    CopyMemory(&((BYTE *)EditBitmap.bmptr)[0], &oldlines[8*7], 8);
    break;

    default:
    return;
    }
FormPaint(Sender);
UpdateTile();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::SpeedButton4Click(TObject *Sender)
{
// UNDO -------------------------------------

if (Owna->UndoCount == 0)
    return;
CopyMemory(Owna->UndoBuffer[0].ptr, Owna->UndoBuffer[0].data, Owna->UndoBuffer[0].size);

// Update ROM window only if necessary
if ((Owna->UndoBuffer[0].ofs >= Owna->FileOffset)
    && (Owna->UndoBuffer[0].ofs < (Owna->FileOffset+Owna->PageSize)))
    {
    Owna->DecodeToBitmap(&Owna->FilePtr[Owna->FileOffset], &Owna->Bitmap);
    Owna->FormPaint(this);
    }

BYTE tempbmp[64];
int oldbpp, oldsize;
TTileFormat oldfmt;

// Preserve current bitmap
CopyMemory(tempbmp, EditBitmap.bmptr, 64);
oldfmt = TileFmt;
oldbpp = BPP;
oldsize = TileSize;

// Decode undo-tile on bitmap
EditForm->EditBitmap.decinfo.tlfmt = Owna->UndoBuffer[0].fmt;
EditForm->EditBitmap.decinfo.tlbpp = Owna->UndoBuffer[0].bpp;
EditForm->EditBitmap.decinfo.tlsize = Owna->UndoBuffer[0].size;
ChildForm->DecodeToBitmap(Owna->UndoBuffer[0].ptr, &EditForm->EditBitmap);

// Update every instance of current tile in clipboard
for (int y=0; y<CLIP_HEIGHT; y++)
    {
    for (int x=0; x<CLIP_WIDTH; x++)
        {
        if (ClipForm->ClipBoard[y][x].data == Owna->UndoBuffer[0].ptr)
            {
            ChildForm->CopyBitmapTile(&ClipForm->ClipBitmap, x, y, &EditBitmap, 0, 0);
            }
        }
    }
ClipForm->FormPaint(this);

// restore old bitmap
CopyMemory(EditBitmap.bmptr, tempbmp, 64);
EditForm->EditBitmap.decinfo.tlfmt = oldfmt;
EditForm->EditBitmap.decinfo.tlbpp = oldbpp;
EditForm->EditBitmap.decinfo.tlsize = oldsize;

// Update editor window if necessary
if (Owna->UndoBuffer[0].ptr == TileData)
    {
    EditForm->EditBitmap.decinfo.tlfmt = TileFmt;
    EditForm->EditBitmap.decinfo.tlbpp = BPP;
    EditForm->EditBitmap.decinfo.tlsize = TileSize;
    ChildForm->DecodeToBitmap(TileData, &EditForm->EditBitmap);
    }

// Update undo buffer
CopyMemory(TempBuffer, Owna->UndoBuffer, sizeof(UNDOENTRY)*MAX_UNDOS);
CopyMemory(Owna->UndoBuffer, &TempBuffer[1], sizeof(UNDOENTRY)*(MAX_UNDOS-1));
Owna->UndoCount--;
if (Owna->UndoCount == 0)
    SpeedButton4->Enabled = false;
FormPaint(Sender);
}
//---------------------------------------------------------------------------

