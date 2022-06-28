#pragma once

#include <vector>
#include <Windows.h>
#include <unordered_set>
#include <string>

class App{
        
    private:
        int dog = 1;
        HHOOK hHook{ NULL };

    public:
        static std::vector<DWORD> active_keys;
        static std::vector<std::unordered_set<DWORD>> hotkeys;

        App() = default;
        void OnPress(DWORD vkCode); //handle keys being pressed
        void OnRelease(DWORD vkCode); //handle keys being released
        void CheckHotkeys(); // call on every keypress


        static LRESULT CALLBACK KeyboardCallback(const int nCode, const WPARAM wParam, const LONG_PTR lParam);
        LRESULT CALLBACK MouseHook(const int nCode, const WPARAM wParam, const LONG_PTR lParam);
        
        void StartListening();
};