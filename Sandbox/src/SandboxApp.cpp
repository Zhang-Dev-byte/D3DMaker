#include <Window.h>

void MouseCallback(MouseEvent& me) {
    std::string out = "X: ";
    out += std::to_string(me.GetPosX());
    out += ", Y: ";
    out += std::to_string(me.GetPosY());
    out += "\n";
    OutputDebugStringA(out.c_str());
}
void KeyboardCallback(KeyboardEvent& kbe) {
    std::string out = "";
    if (kbe.IsPress()) {
        out += "Press: ";
    }
    if (kbe.IsRelease()) {
        out += "Release: ";
    }
    out += kbe.GetKeyCode();
    out += "\n";
    OutputDebugStringA(out.c_str());
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

    wnd.SetMouseCallback(MouseCallback);
    wnd.SetKeyCallback(KeyboardCallback);

    while (wnd.ProcessMessages()) {
        wnd.Update();
        float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        wnd.GetGraphics().GetContext()->ClearRenderTargetView(wnd.GetGraphics().GetTarget().Get(), bgcolor);
        wnd.SwapBuffers();
    }
    return 0;
}