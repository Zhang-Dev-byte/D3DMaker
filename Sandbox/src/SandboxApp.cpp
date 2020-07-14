#include <D3DMaker.h>

class Sandbox : public DM::Application {
public:
    virtual void OnRun() override {

    }
    virtual void OnKeyboardEvent(KeyboardEvent& kbe) override {

    }
    virtual void OnMouseEvent(MouseEvent& me) override {

    }
    virtual void OnRender(Graphics& g) override {
        float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        g.GetContext()->ClearRenderTargetView(g.GetTarget().Get(), bgcolor);
    }
};

DM::Application* DM::CreateApplication() {
    return new Sandbox();
}