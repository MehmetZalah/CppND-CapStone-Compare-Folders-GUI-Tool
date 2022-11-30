/*
    main.cpp
    Compare Folders GUI Tool
	
    @author Mohamed Salah Abdelfatah
	@version 1.0 30/11/2022
*/

#include <wx/wx.h>
#include "UserDirectory.h"

//currentTextField
wxTextCtrl* TextCtrl1;

//ComparedWithTextField
wxTextCtrl* TextCtrl2;

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
protected:
    void OnQuit(wxCommandEvent& event);
    void Compare(wxCommandEvent& event);
private:
    enum { ID_Quit = wxID_HIGHEST + 1, ID_Compare };
};

bool MyApp::OnInit()
{
    /* Title */
    wxFrame* frame = new MyFrame(wxT("Compare Folders GUI - Udacity Capstone Project"), wxPoint(50, 50),wxSize(540, 170));

    /* Labels */
    wxStaticBox* StaticBox1 = new wxStaticBox(frame, wxID_ANY, _("Current Directory Path:"), wxPoint(16, 16), wxSize(216, 64), 0, _T("ID_STATICBOX1"));
    wxStaticBox* StaticBox2 = new wxStaticBox(frame, wxID_ANY, _("Compare it with Directory Path:"), wxPoint(248, 16), wxSize(220, 64), 0, _T("ID_STATICBOX2"));

    /* TextFiels */
    TextCtrl2 = new wxTextCtrl(frame, wxID_ANY, wxEmptyString, wxPoint(256, 40), wxSize(200, 32), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl1 = new wxTextCtrl(frame, wxID_ANY, wxEmptyString, wxPoint(24, 40), wxSize(200, 32), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  
    /* Placeholders */
  	TextCtrl1->SetValue("/home/workspace/folder1");
    TextCtrl2->SetValue("/home/workspace/folder2");
    
    /* Show Frame */
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame((wxFrame*)NULL, -1, title, pos, size)
{
    /* Menu */
    wxMenuBar* menu = new wxMenuBar;
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Compare, wxT("&Compare"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, wxT("&Exit"));
    menu->Append(menuFile, "&Action");
    SetMenuBar(menu);
    
    /* Events */
    Connect(ID_Compare, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::Compare));
    Connect(ID_Quit, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnQuit));

    CreateStatusBar();
    SetStatusText(wxT("Developed By Mohamed Salah Abdelfatah"));
   
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::Compare(wxCommandEvent& WXUNUSED(event))
{
    std::string Result = "\n\n";
    
    /* User Inputs */
    auto CurrentDirectory = TextCtrl1->GetValue();
    auto ComparedDirectory = TextCtrl2->GetValue();

    UserDirectory firstDirectory;
    UserDirectory secondDirectory;

    bool isModified = false;
    
    /* Check if Directory is Exist */
    if(!firstDirectory.setDirectoryPath(std::string(CurrentDirectory)))
    {
      Result += "Directory " + firstDirectory.getDirectoryPath() + " does not exist!";
      wxMessageBox(wxT("" + Result + ""), wxT("Result"), wxOK | wxICON_INFORMATION, this);
      return;
    }
  
    /* Check if Directory is Exist */
    if(!secondDirectory.setDirectoryPath(std::string(ComparedDirectory)))
    {
      Result += "Directory " + secondDirectory.getDirectoryPath() + " does not exist!";
      wxMessageBox(wxT("" + Result + ""), wxT("Result"), wxOK | wxICON_INFORMATION, this);
      return;
    }
    
    /* Get Directories Files */
    firstDirectory.getDirectoryFiles();
    secondDirectory.getDirectoryFiles();

    /* Get Files HASH */
    auto firstDirectoryHASHS = firstDirectory.getFilesHASH();
    auto secondDirectoryHASHS = secondDirectory.getFilesHASH();

    auto fDH = firstDirectoryHASHS.begin();
    auto sDH = secondDirectoryHASHS.begin();

    /* Check for Added / Modified Files */
    while (sDH != secondDirectoryHASHS.end())
    {
        if (firstDirectoryHASHS[sDH->first] != sDH->second)
        {
            isModified = true;
            if (firstDirectoryHASHS[sDH->first].empty())
            {
                //std::cout << "File Added: " << sDH->first << "---- HASH: " << sDH->second << std::endl;
                Result += "File Added: " + sDH->first + "---- HASH: " + sDH->second + "\n\n";
            }
            else
            {
                //std::cout << "File Modified: " << sDH->first << "---- HASH: " << sDH->second << std::endl;
                Result += "File Modified: " + sDH->first + "---- HASH: " + sDH->second + "\n\n";
            }
        }

        sDH++;
    }

    /* Check for Deleted Files */
    while (fDH != firstDirectoryHASHS.end())
    {
        if (secondDirectoryHASHS.find(fDH->first) == secondDirectoryHASHS.end())
        {
            isModified = true;
            //std::cout << "File Deleted: " << fDH->first << "---- HASH: " << fDH->second << std::endl;
            Result += "File Deleted: " + fDH->first + "---- HASH: " + fDH->second + "\n\n";
        }
        fDH++;
    }

    /* Check if there is output */
    if (!isModified)
    {
        //std::cout << "No files Added, Deleted or Modified!" << std::endl;
        Result += "No files Added, Deleted or Modified!";
    }
    
    /* Return the result into console also */
    std::cout << "Result:" << std::endl;
    std::cout << Result << std::endl;
    
    /* Results */
    wxMessageBox(wxT("" + Result + ""), wxT("Result"), wxOK | wxICON_INFORMATION, this);
}
