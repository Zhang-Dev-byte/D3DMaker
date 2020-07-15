#pragma once
#include "Application.h"
namespace DM {
    extern Application* CreateApplication();
    extern void MouseCallback(MouseEvent& me) {
        auto app = CreateApplication();
        app->OnMouseEvent(me);
    }
    extern void KeyCallback(KeyboardEvent& kbe) {
        auto app = CreateApplication();
        app->OnKeyboardEvent(kbe);
    }
}
int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
) {
    Window wnd;
    if (!wnd.Initialize(hInstance, "Window", "D3DW", 1280, 720)) {
        return -1;
    }
    auto app = DM::CreateApplication();
    try {
        app->OnRun(wnd.GetGraphics());
    }
    catch (const WException& e)
    {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    wnd.SetMouseCallback(DM::MouseCallback);
    wnd.SetKeyCallback(DM::KeyCallback);

    while (wnd.ProcessMessages()) {
        wnd.Update();
        try {
            app->OnRender(wnd.GetGraphics());
        }
        catch (const WException& e)
        {
            MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
        }
        catch (const std::exception& e)
        {
            MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
        }
        catch (...)
        {
            MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
        }
        wnd.SwapBuffers();
    }
}