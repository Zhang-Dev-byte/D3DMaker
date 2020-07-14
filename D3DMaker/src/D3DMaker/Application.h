#pragma once
#include <Window.h>
namespace DM {
	class Application {
	public:
		virtual void OnRun() = 0;
		virtual void OnKeyboardEvent(KeyboardEvent& kbe) = 0;
		virtual void OnMouseEvent(MouseEvent& me) = 0;
		virtual void OnRender(Graphics& g) = 0;
	};
}