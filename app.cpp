#include "app.h"
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

std::vector<DWORD> App::active_keys;

LRESULT CALLBACK App::KeyboardCallback(const int nCode, const WPARAM wParam, const LPARAM lParam) {
        KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD vkCode = kbdStruct->vkCode;
        App app;

    if (wParam == WM_KEYDOWN) 
		app.OnPress(vkCode);
	
    else if (wParam == WM_KEYUP)
        app.OnRelease(vkCode);

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void App::OnRelease(DWORD vkCode){
        
    
    if(std::find(active_keys.begin(), active_keys.end(), vkCode) == active_keys.end())
        return;
    std::vector<DWORD>::iterator position = std::find(active_keys.begin(), active_keys.end(), vkCode);
    active_keys.erase(position);
    for (int i =0; i < active_keys.size(); i++)
        std::cout<< active_keys[i];
    std::cout<<std::endl;
        

}

void App::OnPress(DWORD vkCode){
//     std::cout<<"dog";
    if(std::find(active_keys.begin(), active_keys.end(), vkCode) != active_keys.end())
        return;

	active_keys.push_back((int)vkCode);
  
    for (int i =0; i < active_keys.size(); i++)
            std::cout<< active_keys[i];
        std::cout<<std::endl;
}



void App:: StartListening(){
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardCallback, NULL, 0);

	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	while (GetMessage(NULL, NULL, 0, 0));
    std::cout<<"bye bye!"<<std::endl;
}