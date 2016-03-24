#include <iostream>
#include <string>
#include <windows.h>
#include "Parse.h"

// uses macros to create the styling.
void parseClicks(std::string formatting, std::string fontSize){
    if(formatting.length()==0){
        return; 
    }
    // three key combos!
    INPUT ip;
    INPUT sec;
    INPUT third;

    // the different options you have.
    int choices[5] = { 0x42, 0x49, 0x55, 0x45, 0x10 };

    int orientation[2] = { 0x52, 0x4A };
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

    // first four choices.
    for(unsigned int i = 0; i < 4; i++) {

        // if a choice has been chosen.
        if(formatting[i] != '0' || i == 3) {

            ip.ki.wVk = 0x11;  //  "ctrl" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));

            //choosing the orientation of text. 
            if(i == 3) {
                if(formatting[i] == '0') {
                    ip.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1, &ip, sizeof(INPUT));
                    break;
                }  else if(formatting[i] == '1') {
                      sec.ki.wVk = choices[i]; // + some other key.
                      sec.ki.dwFlags = 0;
                      SendInput(1, &sec, sizeof(INPUT));
                }  else if(formatting[i] == '2') {
                      sec.ki.wVk = orientation[0];
                      sec.ki.dwFlags = 0;
                      SendInput(1, &sec, sizeof(INPUT));
                }   else {
                      sec.ki.wVk = orientation[1];
                      sec.ki.dwFlags = 0;
                      SendInput(1, &sec, sizeof(INPUT));
                }

            } else {
                sec.ki.wVk = choices[i];
                sec.ki.dwFlags = 0;
                SendInput(1, &sec, sizeof(INPUT));
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

    // type in new font.
    for(unsigned int i = 4; i < formatting.length(); i++) {
        int x = toupper(formatting[i]);
        sec.ki.wVk = x;
        sec.ki.dwFlags = 0;

        SendInput(1, &sec, sizeof(INPUT));

        sec.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &sec, sizeof(INPUT));
    }
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