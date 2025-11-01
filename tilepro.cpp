//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("tilepro.res");
USEFORM("main.cpp", MainForm);
USEFORM("child.cpp", ChildForm);
USEFORM("pal.cpp", PalForm);
USEFORM("goofs.cpp", GotoForm);
USEFORM("edit.cpp", EditForm);
USEFORM("clip.cpp", ClipForm);
USEFORM("about.cpp", AboutForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TGotoForm), &GotoForm);
        Application->CreateForm(__classid(TPalForm), &PalForm);
        Application->CreateForm(__classid(TEditForm), &EditForm);
        Application->CreateForm(__classid(TClipForm), &ClipForm);
        Application->CreateForm(__classid(TAboutForm), &AboutForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
