#include"Main.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
// A value of 0x00000001 indicates that rendering should be performed using High
// Performance Graphics. A value of 0x00000000 indicates that this method should be
// ignored. 
extern "C" {
_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// Main function off windows application. Return int. 0 - there were not errors. !=0 there were errors.
// hInstance handle to this application. hPrevInstance - not using (deprecated)
// lpCmdLine pointer to char table- string with witch applications are call.
// nShowCmd - variable which tell how to show window.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	YasEngineGL yasEngineGl = YasEngineGL(hInstance);
	yasEngineGl.run(nShowCmd);
	system("PAUSE");
	return 0;
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
