//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "child.h"
#include "pal.h"
#include "goofs.h"
#include "edit.h"
#include "clip.h"
#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Open1Click(TObject *Sender)
{
OpenROMDialog->FileName = "";
if (!OpenROMDialog->Execute())
    return;
OpenOneROM(OpenROMDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenOneROM(AnsiString filename)
{
// Tell the user that a ROM is being loaded
StatusBar->SimpleText = "Loading ROM...";
Cursor = crHourGlass;
Application->ProcessMessages();

// Show some windows
WindowMenu->Visible = true;
PalForm->Visible = true;
ClipForm->Visible = true;
EditForm->Visible = true;

// Create child window and load the friggin ROM
LockWindowUpdate(Application->MainForm->ClientHandle);
TChildForm *child = new TChildForm(Application);   // Create child form
int result = child->LoadROM(filename);       // Load ROM
if (result == -1)
    {   // file open error
    char buf[256];
    wsprintf(buf, "Error: Could not open the file \'%s\'.", filename.c_str());
    Application->MessageBox(buf, "Tile Layer Pro", MB_OK | MB_ICONERROR);
    delete child;
    }
else if (result == 0)
    {   // mem alloc error
    Application->MessageBox("Fatal error: Could not allocate memory for file.", "Tile Layer Pro", MB_OK | MB_ICONERROR);
    if (MDIChildCount == 1)
        Application->Terminate();
    delete child;
    }
else
    {   // success
    child->SetWindowSize();
    child->Caption = ExtractFileName(child->ROMFileName);
    LockWindowUpdate(NULL);
    child->OnActivate = child->FormActivate;    // Hook OnActivate handler
    child->OnActivate(this);

    // Enable the speed buttons
    SaveSpdBtn->Enabled = true;
    ZoomInSpdBtn->Enabled = true;
    ZoomOutSpdBtn->Enabled = true;
    GridSpdBtn->Enabled = true;
    }   // success

// Set back the cursor
Cursor = crDefault;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Close1Click(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
child->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
MainForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
if (!CloseAllMDIForms())
    Action = caNone;
else// Cleanup
    {
    DeleteObject(CopyBitmap.bmHandle);
    DeleteObject(DragBitmap.bmHandle);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Save1Click(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
child->SaveROM(child->ROMFileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveAs1Click(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
SaveROMDialog->FileName = child->ROMFileName;
if (SaveROMDialog->Execute())
    {
    if (ExtractFileExt(SaveROMDialog->FileName) == "")
        SaveROMDialog->FileName = SaveROMDialog->FileName + ExtractFileExt(child->ROMFileName);
    child->ROMFileName = SaveROMDialog->FileName;
    Save1Click(Sender);
    child->Caption = ExtractFileName(child->ROMFileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileMenuClick(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
bool bActive = (child != NULL); // bActive = false if no child active
if (child)
    Save1->Enabled = child->Modified;
else
    Save1->Enabled = false;
Close1->Enabled = bActive;
SaveAs1->Enabled = bActive;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ZoomInSpdBtnClick(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
if (child->Zoom < 4)
    {
    child->Zoom++;
    child->SetWindowSize();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ZoomOutSpdBtnClick(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
if (child->Zoom > 1)
    {
    child->Zoom--;
    child->SetWindowSize();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GridSpdBtnClick(TObject *Sender)
{
TChildForm *child = dynamic_cast<TChildForm*>(ActiveMDIChild);
if (child == NULL)
    return; // Exit if no MDI window active
child->Gridlines1Click(Sender); // Toggle gridlines on/off
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
// Create bit patterns
for (int z=0; z<8; z++)
    for (int y=0; y<256; y++)
        for (int x=0; x<8; x++)
            ((BYTE *)BitPatterns[z])[(y << 3) + x] = (BYTE)(((y >> (x ^ 7)) & 1) << z);

// Create DragBitmap
DragBitmap.bmTileWidth = 8;
DragBitmap.bmTileCols = 1;
DragBitmap.bmTileHeight = 8;
DragBitmap.bmTileRows = 1;
ChildForm->Create256ColorBitmap(&DragBitmap, MainForm->Canvas->Handle);

// Init it
DragBitmap.encinfo.top = 0;
DragBitmap.encinfo.left = 0;
DragBitmap.encinfo.tlskip = 0;
DragBitmap.encinfo.cols = 1;
DragBitmap.encinfo.rows = 1;

DragBitmap.decinfo.top = 0;
DragBitmap.decinfo.left = 0;
DragBitmap.decinfo.tlskip = 0;
DragBitmap.decinfo.cols = 1;
DragBitmap.decinfo.rows = 1;

Application->HelpFile = GetCurrentDir() + "\\tlp.hlp";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Tile1Click(TObject *Sender)
{
Tile();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Cascade1Click(TObject *Sender)
{
Cascade();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ArrangeIcons1Click(TObject *Sender)
{
ArrangeIcons();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MinimizeAll1Click(TObject *Sender)
{
for (int i=0; i<MDIChildCount; i++)
    MDIChildren[i]->WindowState = wsMinimized;
ActiveMDIChild->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

bool TMainForm::CloseAllMDIForms(void)
{
// Try to close all MDI windows
for (int i=0; i<MDIChildCount; i++)
    {
    MDIChildren[i]->Close();    // Attempt to close one MDI window
    if (!bClosed)       // bClosed is false if the user pressed
        return false;
    }
    return true;
}

void __fastcall TMainForm::CloseAll1Click(TObject *Sender)
{
CloseAllMDIForms();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Contents1Click(TObject *Sender)
{
Application->HelpContext(3002);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject *Sender)
{
AboutForm->Position = poScreenCenter;
AboutForm->ShowModal();
}
//---------------------------------------------------------------------------

