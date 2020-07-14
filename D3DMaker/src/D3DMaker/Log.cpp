#include "Log.h"

void DM::Log(std::string msg)
{
	OutputDebugStringA(msg.c_str());
}
