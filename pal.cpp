//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "child.h"
#include "pal.h"
#include "main.h"
#include "edit.h"
#include "clip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPalForm *PalForm;
//---------------------------------------------------------------------------
__fastcall TPalForm::TPalForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPalForm::RedBarChange(TObject *Sender)
{
if (RedBarChangeEnable == false)
    return;
if (MainForm->ActiveForm == NULL)
    return; // Exit if no window active
REditChangeEnable = false;
REdit->Text = IntToStr(RedBar->Position);
GEdit->Text = IntToStr(GreenBar->Position);
BEdit->Text = IntToStr(BlueBar->Position);
REditChangeEnable = true;

Palette[ColIndex+FGColor].rgbtRed = (BYTE)RedBar->Position;
Palette[ColIndex+FGColor].rgbtGreen = (BYTE)GreenBar->Position;
Palette[ColIndex+FGColor].rgbtBlue = (BYTE)BlueBar->Position;

TColor newcolor = (TColor)RGB(Palette[ColIndex+FGColor].rgbtRed,
                                    Palette[ColIndex+FGColor].rgbtGreen,
                                    Palette[ColIndex+FGColor].rgbtBlue);
TShape *Shapes[16] = { Shape1, Shape2, Shape3, Shape4,
                       Shape5, Shape6, Shape7, Shape8,
                       Shape9, Shape10, Shape11, Shape12,
                       Shape13, Shape14, Shape15, Shape16 };
FGShape->Brush->Color = newcolor;
Shapes[FGColor]->Brush->Color = newcolor;

child = dynamic_cast<TChildForm*>(MainForm->ActiveForm);
if (child)
    child->PalModified = true;

SetPalette();
}
//---------------------------------------------------------------------------

void __fastcall TPalForm::REditChange(TObject *Sender)
{
if (REditChangeEnable == false)
    return;
TEdit *edit = dynamic_cast<TEdit*>(Sender);
if (edit->Text == "")
    edit->Text = "0";
int Value = StrToInt(edit->Text);
if (Value > 255)
    {
    Value = 255;
    edit->Text = "255";
    }
if (edit == REdit)
    RedBar->Position = Value;
else if (edit == GEdit)
    GreenBar->Position = Value;
else
    BlueBar->Position = Value;
RedBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPalForm::REditKeyPress(TObject *Sender, char &Key)
{
if ((Key < '0')
    || (Key > '9'))
    if (Key != 8)
        Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TPalForm::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (MainForm->ActiveForm == NULL)
    return; // Exit if no window active
TShape *shape = dynamic_cast<TShape*>(Sender);
if (Button == mbLeft)
    {   // change foreground color
    DblClkTime = GetDoubleClickTime();
    NewTick = GetTickCount();
    if (((NewTick - OldTick) <= DblClkTime)
        && (shape == OldShape))
        {   // Double click
        ColorDialog->Color = shape->Brush->Color;
        if (ColorDialog->Execute() == true)
            {
            shape->Brush->Color = ColorDialog->Color;
            FGShape->Brush->Color = ColorDialog->Color;
            Palette[ColIndex+FGColor].rgbtRed = GetRValue(ColorDialog->Color);
            Palette[ColIndex+FGColor].rgbtGreen = GetGValue(ColorDialog->Color);
            Palette[ColIndex+FGColor].rgbtBlue = GetBValue(ColorDialog->Color);

            child = dynamic_cast<TChildForm*>(MainForm->ActiveForm);
            if (child)
                child->PalModified = true;

            SetPalette();
            }
        }
    else
        {   // Single click
        FGColor = (BYTE)shape->Tag;
        FGShape->Brush->Color = shape->Brush->Color;
        }

    RedBarChangeEnable = false; // Don't want handler to get called
    REditChangeEnable = false;  // Ditto

    RedBar->Position = Palette[ColIndex+FGColor].rgbtRed;
    GreenBar->Position = Palette[ColIndex+FGColor].rgbtGreen;
    BlueBar->Position = Palette[ColIndex+FGColor].rgbtBlue;

    REdit->Text = IntToStr(Palette[ColIndex+FGColor].rgbtRed);
    GEdit->Text = IntToStr(Palette[ColIndex+FGColor].rgbtGreen);
    BEdit->Text = IntToStr(Palette[ColIndex+FGColor].rgbtBlue);

    RedBarChangeEnable = true;
    REditChangeEnable = true;

    OldShape = (TShape *)Sender;
    OldTick = NewTick;
    }
else    // Right mouse button --> change background color
    {
    BGColor = (BYTE)shape->Tag;
    BGShape->Brush->Color = shape->Brush->Color;
    }
}

//---------------------------------------------------------------------------

void __fastcall TPalForm::InitPalette(void)
{
if (MainForm->ActiveForm == NULL)
    return; // Exit if no window active

RedBarChangeEnable = false;
REditChangeEnable = false;

// Get pointers to all color boxes
TShape *Shapes[16] = { Shape1, Shape2, Shape3, Shape4,
                       Shape5, Shape6, Shape7, Shape8,
                       Shape9, Shape10, Shape11, Shape12,
                       Shape13, Shape14, Shape15, Shape16 };

// Calc some vars
NumCols = 1 << BPP;
ColIndex = PalSelect * NumCols;

// Setup shape colors
for (int i=0; i<NumCols; i++)
    Shapes[i]->Brush->Color = (TColor)RGB(Palette[i+ColIndex].rgbtRed,
                                          Palette[i+ColIndex].rgbtGreen,
                                          Palette[i+ColIndex].rgbtBlue);

FGShape->Brush->Color = Shapes[FGColor]->Brush->Color;
BGShape->Brush->Color = Shapes[BGColor]->Brush->Color;

// Setup R,G,B scrollbars
RedBar->Position = Palette[ColIndex+FGColor].rgbtRed;
GreenBar->Position = Palette[ColIndex+FGColor].rgbtGreen;
BlueBar->Position = Palette[ColIndex+FGColor].rgbtBlue;

// Setup text associated with scrollbars
REdit->Text = IntToStr(RedBar->Position);
GEdit->Text = IntToStr(GreenBar->Position);
BEdit->Text = IntToStr(BlueBar->Position);

RedBarChangeEnable = true;
REditChangeEnable = true;

// Show needed amount of boxes, hide the rest
for (int i=0; i<NumCols; i++)
    Shapes[i]->Visible = true;
for (int i=NumCols; i<16; i++)
    Shapes[i]->Visible = false;

// Set up palette color boxes according to BPP
int left = Shapes[0]->Left;
int top = Shapes[0]->Top;
int width, height;
switch (BPP)
    {
    case 1:
    width = 64;
    height = 50;
    for (int x=0; x<2; x++)
        {
        Shapes[x]->Left = left;
        Shapes[x]->Top = top;
        Shapes[x]->Width = width;
        Shapes[x]->Height = height;
        left += width;
        }
    break;

    case 2:
    width = 32;
    height = 50;
    for (int x=0; x<4; x++)
        {
        Shapes[x]->Left = left;
        Shapes[x]->Top = top;
        Shapes[x]->Width = width;
        Shapes[x]->Height = height;
        left += width;
        }
    break;

    case 3:
    width = 16;
    height = 50;
    for (int x=0; x<8; x++)
        {
        Shapes[x]->Left = left;
        Shapes[x]->Top = top;
        Shapes[x]->Width = width;
        Shapes[x]->Height = height;
        left += width;
        }
    break;

    case 4:
    width = 16;
    height = 25;
    for (int y=0; y<16; y+=8)
        {
        for (int x=0; x<8; x++)
            {
            Shapes[x+y]->Left = left;
            Shapes[x+y]->Top = top;
            Shapes[x+y]->Width = width;
            Shapes[x+y]->Height = height;
            left += width;
            }
        top += height;
        left -= width * 8;
        }
    break;
    }

// Setup UpDown
PalUpDown->Position = (short)PalSelect;
PalUpDown->Max = (short)(NumPalEntries / (1 << BPP));
PalUpDown->Enabled = true;

SetPalette();
}

//---------------------------------------------------------------------------

void __fastcall TPalForm::SetPalette(void)
{
if (MainForm->ActiveForm == NULL)
    return;

for (int i=0; i<NumCols; i++)
    {
    ActiveBitmap->bminfo.bmiColors[i].rgbRed = Palette[i+ColIndex].rgbtRed;
    ActiveBitmap->bminfo.bmiColors[i].rgbGreen = Palette[i+ColIndex].rgbtGreen;
    ActiveBitmap->bminfo.bmiColors[i].rgbBlue = Palette[i+ColIndex].rgbtBlue;
    ActiveBitmap->bminfo.bmiColors[i].rgbReserved = 0;
    }
if (MainForm->ActiveForm == ClipForm)
    {
    ActiveBitmap->bminfo.bmiColors[16].rgbRed = 64;
    ActiveBitmap->bminfo.bmiColors[16].rgbGreen = 64;
    ActiveBitmap->bminfo.bmiColors[16].rgbBlue = 64;
    ActiveBitmap->bminfo.bmiColors[16].rgbReserved = 0;
    }

MainForm->ActiveForm->OnPaint(this);

if (EditForm->TileData != NULL)
    {   // Update tile editor palette
//    if (EditForm->IsClipTile == false)
//        {   // Copy child palette to editor window
        CopyMemory(EditForm->EditBitmap.bminfo.bmiColors, ActiveBitmap->bminfo.bmiColors, NumCols*4);
        EditForm->FormPaint(this);
//        }
    }
}

//---------------------------------------------------------------------------

void __fastcall TPalForm::PalUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
if (MainForm->ActiveForm == NULL)
    return;
else if (MainForm->ActiveForm == ClipForm)
    {
    ClipTile *ct = ClipForm->ClipEntry;
    if ((ct == NULL)
        || (ct->data == NULL))
        return;
    int maxpal = (256 / (1 << ct->bpp)) - 1;
    if (Button == btNext)
        {
        if (ct->pal == maxpal)
            ct->pal = 0;
        else
            ct->pal++;
        }
    else
        {
        if (ct->pal == 0)
            ct->pal = maxpal;
        else
            ct->pal--;
        }
    // Set palette bits
    Bitmap256 *bmp = &ClipForm->ClipBitmap;
    int destpos = (ct->ypos * bmp->bmTileHeight * bmp->bminfo.bmiHeader.biWidth) + (ct->xpos * bmp->bmTileWidth);
    BYTE palor = (BYTE)(ct->pal << ct->bpp);
    BYTE paland = (BYTE)((1 << ct->bpp) - 1);
    for (int y=0; y<bmp->bmTileHeight; y++)
        {
        for (int x=0; x<bmp->bmTileWidth; x++)
            {
            ((BYTE *)bmp->bmptr)[destpos+x] &= paland;
            ((BYTE *)bmp->bmptr)[destpos+x] |= palor;
            }
        destpos += bmp->bminfo.bmiHeader.biWidth;
        }
    //
    ClipForm->FormPaint(Sender);
    }
else
    {
    if (PalUpDown->Position == PalUpDown->Min)
        PalUpDown->Position = (short)(PalUpDown->Max - 1);
    else if (PalUpDown->Position == PalUpDown->Max)
        PalUpDown->Position = 0;
    PalSelect = PalUpDown->Position;
    ColIndex = PalSelect * NumCols;
    InitPalette();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPalForm::FormDeactivate(TObject *Sender)
{
if (MainForm->ActiveForm == NULL)
    return;
TChildForm *child = dynamic_cast<TChildForm*>(MainForm->ActiveForm);
if (child)
    {   // MDI child
    child->FGColor = FGColor;
    child->BGColor = BGColor;
    child->PalSelect = PalSelect;
    }
else
    {   // clipboard
    ClipForm->FGColor = FGColor;
    ClipForm->BGColor = BGColor;
    ClipForm->PalSelect = PalSelect;
    }
}
//---------------------------------------------------------------------------

