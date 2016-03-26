//Created by Daniel Kostinskiy.
#include <windows.h>
#include <string>
#include "uimain.h"
#include "ui_uimain.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <fstream>
UiMain::UiMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->enterButton,SIGNAL(clicked()),this,SLOT(openWord()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveToFile()));
}

UiMain::~UiMain()
{
    delete ui;
}
std::string UiMain::checkClicked(){
    std::string input = getString();
    if(ui->Bold->isChecked()){
        input[0] = '1';
    }
    else{
        input[0] = '0';
    }
    if(ui->Italic->isChecked()){
        input[1] = '1';
    }
    else{
        input[1] = '0';
    }
    if(ui->Underline->isChecked()){
        input[2] = '1';
    }
    else{
        input[2] = '0';
    }
    if(ui->Center->isChecked()){
        input[3] = '1';
    }
    else if(ui->Right->isChecked()){
        input[3] = '2';
    }
    else if ( ui->Justify->isChecked()){
        input[3] = '3';
    }
    else{
        input[3] = '0';
    }
    setString(input);
    return input;
}
QString UiMain::getFont(){
    return ui->Font->currentText();
}

QString UiMain::getFontSize(){
    return ui->FontSize->currentText();
}

void UiMain::parseClicks(std::string formatting){
    // three key combos!
        INPUT ip;
        INPUT sec;
        INPUT third;


        // Setup the three keyboard events.
           ip.type = INPUT_KEYBOARD;
           ip.ki.wScan = 0;
           ip.ki.time = 0;
           ip.ki.dwExtraInfo = 0;

           sec.type = INPUT_KEYBOARD;
           sec.ki.wScan = 0;
           sec.ki.time = 0;
           sec.ki.dwExtraInfo = 0;

           third.type = INPUT_KEYBOARD;
           third.ki.wScan = 0;
           third.ki.time = 0;
           third.ki.dwExtraInfo = 0;
        // the different options you have.
        int choices[6] = { 0x42, 0x49, 0x55, 0x45,0x52, 0x4A  };
        for(unsigned int i = 0; i<formatting.length();i++){
            if(formatting[i] != '0' && i!=3){
                ip.ki.wVk = 0x11;  //  "ctrl" key
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
                sec.ki.wVk = choices[i];
                sec.ki.dwFlags = 0;
                SendInput(1, &sec, sizeof(INPUT));
                // release the two keys.
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));

                sec.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &sec, sizeof(INPUT));
            }

            else if(i == 3){
                ip.ki.wVk = 0x11;  //  "ctrl" key
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
                if(formatting[i] == '1'){
                    sec.ki.wVk = choices[3]; // + some other key.
                    sec.ki.dwFlags = 0;
                    SendInput(1, &sec, sizeof(INPUT));
                }
                else if(formatting[i] == '2'){
                    sec.ki.wVk = choices[4];
                    sec.ki.dwFlags = 0;
                    SendInput(1,&sec,sizeof(INPUT));
                }
                else if(formatting[i] == '3'){
                    sec.ki.wVk = choices[5];
                    sec.ki.dwFlags = 0;
                    SendInput(1,&sec,sizeof(INPUT));
                }
                // release the two keys.
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));

                sec.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &sec, sizeof(INPUT));
            }

        }
        // open font menu.
        ip.ki.wVk = 0x11;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));

        sec.ki.wVk = 0x10;
        sec.ki.dwFlags = 0;
        SendInput(1, &sec, sizeof(INPUT));

        third.ki.wVk = 0x46;
        third.ki.dwFlags = 0;
        SendInput(1, &third, sizeof(INPUT));

        // turn off the key presses.
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        sec.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &sec, sizeof(INPUT));

        third.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &third, sizeof(INPUT));

        QString font = getFont();
        std::string str = font.toStdString();
        for(int i = 0 ; i <font.length();i++){
            int x = toupper(str.at(i));
            sec.ki.wVk = x;
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));
        }

            QString Size = getFontSize();
            std::string fontSize = Size.toStdString();
            // choose the font size, by tabbing twice
            // first to get to the menu.
            sec.ki.wVk = 0x09;
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.wVk = 0x09;
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));

            // grab the first  number to input.
            sec.ki.wVk = (int)fontSize[0];
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));

            // grab the second number to input.
            sec.ki.wVk = (int)fontSize[1];
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));
        // get out of the menu.
        sec.ki.wVk = 0x0D;
        sec.ki.dwFlags = 0;
        SendInput(1, &sec, sizeof(INPUT));

        sec.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &sec, sizeof(INPUT));


}

void UiMain::openWord(){
  // get the string
  std::string input = UiMain::checkClicked();
  // Use shell to turn on  Windows Word!
  SHELLEXECUTEINFO sei= { 0 };
  sei.cbSize = sizeof(SHELLEXECUTEINFO);
  sei.fMask = SEE_MASK_NOCLOSEPROCESS;
  sei.lpVerb = L"open";
  sei.lpFile = L"WINWORD.exe";
  //sei.lpDirectory = directory.c_str();
  sei.nShow = SW_SHOWNORMAL;
  // when it is turned on wait till Word is waiting for something from the user.
  if(ShellExecuteEx(&sei)) {

    // =::?
    int r = WaitForInputIdle(sei.hProcess, INFINITE);

    // 0 means idle. If not idle wait half a second.
    while(r != 0) {
      r = WaitForInputIdle(sei.hProcess, INFINITE);
      Sleep(500);
    }
    parseClicks(input);


  }
}
void UiMain::saveToFile(){

    if(fileName=="")
       fileName = QFileDialog::getSaveFileName(this,
        tr("Save Styles"),"",
         tr("Styles(*.abk);;All Files (*)"));

    QFile file(fileName);
      if (!file.open(QIODevice::Append)) {
        QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
          return;
        }
        QDataStream out(&file);
          out.setVersion(QDataStream::Qt_4_5);
          QString output = (ui->saveEdit->text()).replace(" ","");
          out<< output;
          out<<QString::fromStdString(getString());
          out<<getFont();
          out<<getFontSize()<<'\n';
}
/*
void UiMain::loadFromFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
          tr("Open Style"),"",
          tr("Styles(*.abk);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {

           QFile file(fileName);

           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }

           QDataStream in(&file);
           in.setVersion(QDataStream::Qt_4_5);
           contacts.clear();   // clear existing contacts
           in >> contacts;
           if (contacts.isEmpty()) {
                      QMessageBox::information(this, tr("No contacts in file"),
                          tr("The file you are attempting to open contains no contacts."));
                  } else {
                      QMap<QString, QString>::iterator i = contacts.begin();
                      nameLine->setText(i.key());
                      addressText->setText(i.value());
                  }
              }

}
*/
