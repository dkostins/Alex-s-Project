  //Created by Daniel Kostinskiy.
  // this is the driver to the parse function. 
  #include <string>
  #include <iostream>
  #include <windows.h>
  #include "Parse.h"
  int main(int argc, char** argv){
    //grab from user the directory of word.
    //std::cout << "please specify the directory of Word"<< std::endl;
    //std::string directory;
    //std::getline(std::cin,directory);
    
    // instructions and  grab formatting for word. 
    std::cout << "Format:1 yes 0 no, and type font to use.Text alignment is a bit different." <<std::endl;
    std::cout << "text alignment has four choices; left/center/right/justify ( type a number 0-3)" << std::endl;
    std::cout << "No spaces except for in font name. " <<std::endl;
    std::cout << std::endl;
    
    std::cout << "Type choices as follows:" << std::endl;
    std::cout << "1.bold 2.italic 3.underline 4.Text alignment 5.change font" <<std::endl;
    std::string formatting;
    std::getline(std::cin, formatting);
    std::cout<<std::endl;
    
    std::cout << "Finally please specify font size.(if less then 10 specify a zero, so like 09)" << std::endl;
    std::cout << "If default 11 is fine press enter!"<< std::endl;
    std::string size;
    std::getline(std::cin, size);
   
    // Use shell to turn on  Windows Word!
    SHELLEXECUTEINFO sei = { 0 };
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = "open";
    sei.lpFile = "WINWORD.exe";
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
        
        // use macros when it is idle. 
        parseClicks(formatting,size);
    }

    return 0;
  }

