#include <string>
#include <iostream>
#include <windows.h>

//  macros. 
void parseClicks(std::string yeah,std::string fontSize)
{
    INPUT ip;
    INPUT sec;
    INPUT third;
    // the different options you have.
    int choices[5] = { 0x42, 0x49, 0x55, 0x45, 0x10 };
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
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
    for(unsigned int i = 0; i < 4; i++) {
        if(yeah[i] != '0') {
            // Press the key.
            ip.ki.wVk = 0x11;  // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));
            // Press a different key.
            sec.ki.wVk = choices[i];
            sec.ki.dwFlags = 0;
            SendInput(1, &sec, sizeof(INPUT));
            // Release the "A" key
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));

            sec.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &sec, sizeof(INPUT));
        }
    }
    
    ip.ki.wVk = 0x11;
    ip.ki.dwFlags = 0;
    SendInput(1,&ip,sizeof(INPUT));
    
    sec.ki.wVk = 0x10;
    sec.ki.dwFlags =0;
    SendInput(1,&sec,sizeof(INPUT));
    
    third.ki.wVk = 0x46;
    third.ki.dwFlags = 0;
    SendInput(1,&third,sizeof(INPUT));
    
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&ip,sizeof(INPUT));
    
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
    
    third.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&third,sizeof(INPUT));
    for(unsigned int i = 4; i < yeah.length(); i++) {
        int x = toupper(yeah[i]);
        sec.ki.wVk = x;
        sec.ki.dwFlags = 0;
        
        SendInput(1, &sec, sizeof(INPUT));

        sec.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &sec, sizeof(INPUT));
    }
    sec.ki.wVk = 0x09;
    sec.ki.dwFlags = 0;
    SendInput(1,&sec,sizeof(INPUT));
   
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.wVk = 0x09;
    sec.ki.dwFlags = 0;
    SendInput(1,&sec,sizeof(INPUT));
   
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.wVk = (int)fontSize[0];
    sec.ki.dwFlags= 0;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
    
     sec.ki.wVk = (int)fontSize[1];
    sec.ki.dwFlags= 0;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.wVk = 0x0D;
    sec.ki.dwFlags = 0;
    SendInput(1,&sec,sizeof(INPUT));
    
    sec.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&sec,sizeof(INPUT));
}

int main(int argc, char** argv)
{
    std::cout << " please specify the directory of Word"<< std::endl;
    std::string directory;
    std::getline(std::cin,directory);
    std:: cout << "Format:1 yes 0 no , and type font to use." <<std::endl;
    std::cout << "No spaces except for in font name. " <<std::endl;
    std::cout << "five choices; 1. bold 2.italic. 3. underline 4. center text 5. change font 6.change size of font." <<std::endl;
    std::string yeah;
    std::getline(std::cin, yeah);
    std::cout << "Finally please specify font size" <<std::endl;
    std::string size;
    std::getline(std::cin, size);
    // Use shell to turn on  Windows Word!
    
    SHELLEXECUTEINFO sei = { 0 };
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = "open";
    sei.lpFile = "WINWORD.exe";
    sei.lpDirectory = directory.c_str();
    sei.nShow = SW_SHOWNORMAL;
    // when it is turned on wait till Word is waiting for something from the user.
    if(ShellExecuteEx(&sei)) {
        // =::?
        int r = WaitForInputIdle(sei.hProcess, INFINITE);
        while(r != 0) {
            r = WaitForInputIdle(sei.hProcess, INFINITE);
            Sleep(500);
        }
        // use macros to set what the user wants.
        parseClicks(yeah,size);
    }

    return 1;
}
