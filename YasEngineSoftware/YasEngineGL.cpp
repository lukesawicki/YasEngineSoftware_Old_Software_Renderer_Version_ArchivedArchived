#include"YasEngineGL.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

std::string YasEngineGL::engineName = "YasEngine";
std::string YasEngineGL::applicationName = "YasEngine Demo Application";
std::string YasEngineGL::shadersPath = "Shaders\\";

LRESULT CALLBACK YasEngineGL::windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		switch (message) {
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0);
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void YasEngineGL::extractFunctionsPointers()
{
    // For working with shaders
    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
    
    // For error checking and logging
    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));
    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));

    // For rendering
    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
    glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(wglGetProcAddress("glGetUniformLocation"));
    glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FEXTPROC>(wglGetProcAddress("glProgramUniform1f"));

    // New ones
    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
    glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(wglGetProcAddress("glUniformMatrix4fv"));
    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));
    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
    // End new ones
}

YasEngineGL::YasEngineGL(HINSTANCE hInstance)
{
    windowWidth = 600;
	windowHeight = 600;
	
    windowXposition = 0;
	windowYposition = 0;

	windowed = true;
	style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    // Allocates a new console for the calling process.
	AllocConsole();

    // Attaches the calling process to the console of the specified process.
	AttachConsole(GetCurrentProcessId());

    // Stream object
	FILE* file;

    // fropen_s open existing file with another name
	freopen_s(&file, "CON", "w", stdout);
	freopen_s(&file, "CON", "w", stderr);
    
    std::string consoleTitle = engineName + " logging window";

	SetConsoleTitle(consoleTitle.c_str());
    std::cout.clear();

    applicationHandle = hInstance;
}

std::string YasEngineGL::loadShaderCode(std::string fileName)
{
    std::ifstream shaderCodeFile;
    shaderCodeFile.open(shadersPath + fileName);

    std::string line;
    std::string shaderCode;
    while (std::getline(shaderCodeFile, line))
    {
        shaderCode.append(line + "\n");
    }
    shaderCodeFile.close();
    return shaderCode;
}

GLuint YasEngineGL::createShaderProgram()
{
    GLint vertexShaderCompiled;
    GLint fragmentShaderCompiled;
    GLint shadersLinked;

    std::string shaderCodeVert = loadShaderCode("squareVertexShader.vert");
    const char *vertexShaderSource = shaderCodeVert.c_str();

    std::string shaderCodeFrag = loadShaderCode("squareFragmentShader.frag").c_str();
	const char *fragmentShaderSource = shaderCodeFrag.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
    // glShaderSource gives table of integers with lenghts of each line in shader code 
    // and if is null the program automatically create this table but only if each line will
    // be null-terminated \0
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
    if(vertexShaderCompiled == 1)
    {
        std::cout << "Vertex shader compilation success" << std::endl;
    }
    else
    {
        std::cout << "Vertex shader compilation failed" << std::endl;
    }

	glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
    if(fragmentShaderCompiled == 1)
    {
        std::cout << "Fragment shader compilation success." << std::endl;
    }
    else
    {
        std::cout << "Fragment shader compilation failed." << std::endl;
    }

    GLuint vertexAndFragmentShaderProgram = glCreateProgram();
		
	glAttachShader(vertexAndFragmentShaderProgram, vertexShader);
	glAttachShader(vertexAndFragmentShaderProgram, fragmentShader);
	glLinkProgram(vertexAndFragmentShaderProgram);

    checkOpenGLError();

    glGetProgramiv(vertexAndFragmentShaderProgram, GL_LINK_STATUS, &shadersLinked);
    
    if(shadersLinked == 1)
    {
        std::cout << "Shaders linking succeeded." << std::endl;
    }
    else
    {
        std::cout << "Shaders linking failed." << std::endl;
        printProgramLog(vertexAndFragmentShaderProgram);
    }

	return vertexAndFragmentShaderProgram;
}

ATOM YasEngineGL::registerWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX windowClassEx;
    ZeroMemory(&windowClassEx, sizeof(windowClassEx));
    std::cout << "Preaparing windowClassEx for window" << std::endl;
    // Size of windowClassEx object
    windowClassEx.cbSize                        = sizeof(WNDCLASSEX);

    // Window style. Look and behavior
    windowClassEx.style                         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

    // Pointer to window procedure
    windowClassEx.lpfnWndProc                   = windowProcedure;

    // Size of extra memory for the application
    windowClassEx.cbClsExtra                    = 0;

    // Size of extra memory for window created using this window class
    windowClassEx.cbWndExtra                    = 0;

    // handle to application
    windowClassEx.hInstance                     = applicationHandle;

    // Appliction icon in the alt + tab dialog
    windowClassEx.hIcon                         = LoadIcon(0, IDI_APPLICATION);

    // Handle to cursor displayed when cursor is over the window
    windowClassEx.hCursor                       = LoadCursor(0, IDC_CROSS);

    // Handle to brush for redrawing window
    windowClassEx.hbrBackground                 = (HBRUSH)GetStockObject(WHITE_BRUSH);

    // Handle to menu which will be attached to this window
    windowClassEx.lpszMenuName                  = 0;

    // Name of window
    windowClassEx.lpszClassName                 = applicationName.c_str();

    // Handle to icon whitch will be show on windows bar.
    windowClassEx.hIconSm                       = LoadIcon(0, IDI_APPLICATION);

    // Function whtch create, set values and register window class in the system.
    return RegisterClassEx(&windowClassEx);
}

void YasEngineGL::prepareWindow(int nCmdShow)
{
    windowClassName = MAKEINTATOM(registerWindowClass(applicationHandle));

    // handle if window didn't created

    HWND fakeWindow = CreateWindow(
                    windowClassName, "Fake Window",
                    WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                    0, 0,
                    1, 1,
                    NULL, NULL,
                    applicationHandle, NULL);
   
    HDC fakeDeviceContext = GetDC(fakeWindow);

    PIXELFORMATDESCRIPTOR fakePixelFormatDescriptor;

    ZeroMemory(&fakePixelFormatDescriptor, sizeof(fakePixelFormatDescriptor));
    fakePixelFormatDescriptor.nSize = sizeof(fakePixelFormatDescriptor);
    fakePixelFormatDescriptor.nVersion = 1;
    fakePixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    fakePixelFormatDescriptor.cColorBits = 32;
    fakePixelFormatDescriptor.cAlphaBits = 8;
    fakePixelFormatDescriptor.cDepthBits = 24;
 
    int fakePixelFormatId = ChoosePixelFormat(fakeDeviceContext, &fakePixelFormatDescriptor);
    if(fakePixelFormatId == 0)
    {
        std::cout << "Choosing pixel format failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(SetPixelFormat(fakeDeviceContext, fakePixelFormatId, &fakePixelFormatDescriptor) == false)
    {
        std::cout << "Setting pixel format failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    HGLRC fakeRenderingContext = wglCreateContext(fakeDeviceContext);
 
    if (fakeRenderingContext == 0) {
        std::cout << "wglCreateContext() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
 
    if (wglMakeCurrent(fakeDeviceContext, fakeRenderingContext) == false) {
        std::cout << "wglMakeCurrent() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
    if (wglChoosePixelFormatARB == nullptr) {
        std::cout << "wglGetProcAddress() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
 
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    if (wglCreateContextAttribsARB == nullptr) {
        std::cout << "wglGetProcAddress() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    windowHandle = CreateWindow(windowClassName, applicationName.c_str(), style, windowXposition, windowYposition,
                                windowWidth, windowHeight, NULL, NULL, applicationHandle, NULL);

    deviceContext = GetDC(windowHandle);

	const int pixelAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 4,
		0
	};

	int pixelFormatID;
    UINT formatsNumber;
	const bool status = wglChoosePixelFormatARB(deviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &formatsNumber);

	if (status == false || formatsNumber == 0) {
		std::cout << "wglChoosePixelFormatARB() failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	DescribePixelFormat(deviceContext, pixelFormatID, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);
	SetPixelFormat(deviceContext, pixelFormatID, &pixelFormatDescriptor);

	const int major_min = 4;
    const int minor_min = 3; // minor_min changed from 0 to 3
	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	renderingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttribs);
	if (renderingContext == NULL) {
		std::cout << "wglCreateContextAttribsARB() failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Delete temporary context and window

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(fakeRenderingContext);
	ReleaseDC(fakeWindow, fakeDeviceContext);
	DestroyWindow(fakeWindow);
	if (!wglMakeCurrent(deviceContext, renderingContext)) {
		std::cout << "wglMakeCurrent() failed." << std::endl;
		exit(EXIT_FAILURE);
	}

    openGlVendor = (char*)glGetString(GL_VENDOR);
    openGlVersion = (char*)glGetString(GL_VERSION);
    openGlRenderer = (char*)glGetString(GL_RENDERER);

    std::cout << "OpenGL vendor: " << openGlVendor << std::endl;
    std::cout << "OpenGL version: " << openGlVersion << std::endl;
    std::cout << "OpenGL renderer: " << openGlRenderer << std::endl;

	SetWindowText(windowHandle, reinterpret_cast<LPCSTR>(glGetString(GL_VERSION)));
	ShowWindow(windowHandle, nCmdShow);

    // Brings thread that created this window into the foreground and activates the window.
	SetForegroundWindow(windowHandle);

    // Set focus to specified window.
	SetFocus(windowHandle);

    extractFunctionsPointers();
}

void YasEngineGL::printShaderLog(GLuint shader)
{
    int length = 0;
	int charactersWritten = 0;
	char *log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		log = (char *)malloc(length);
		glGetShaderInfoLog(shader, length, &charactersWritten, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void YasEngineGL::printProgramLog(int shaderProgram)
{
    int length = 0;
	int charactersWritten = 0;
	char *log;
	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		log = (char *)malloc(length);
		glGetProgramInfoLog(shaderProgram, length, &charactersWritten, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool YasEngineGL::checkOpenGLError()
{
    bool foundError = false;
	int glError = glGetError();
	while (glError != GL_NO_ERROR) {
		std::cout << "glError: " << glError << std::endl;
		foundError = true;
		glError = glGetError();
	}
	return foundError;
}

void YasEngineGL::initShaders() {
    shaderProgram = createShaderProgram();
}

void YasEngineGL::setupVertices()
{
    float vertexPositionsCube[108] =
    {
		-1.0F,  1.0F, -1.0F, /*|*/-1.0F, -1.0F, -1.0F, /*|*/ 1.0F, -1.0F, -1.0F, // 1
		 1.0F, -1.0F, -1.0F, /*|*/ 1.0F,  1.0F, -1.0F, /*|*/-1.0F,  1.0F, -1.0F, // 2
		 1.0F, -1.0F, -1.0F, /*|*/ 1.0F, -1.0F,  1.0F, /*|*/ 1.0F,  1.0F, -1.0F, // 3
		 1.0F, -1.0F,  1.0F, /*|*/ 1.0F,  1.0F,  1.0F, /*|*/ 1.0F,  1.0F, -1.0F, // 4
		 1.0F, -1.0F,  1.0F, /*|*/-1.0F, -1.0F,  1.0F, /*|*/ 1.0F,  1.0F,  1.0F, // 5
		-1.0F, -1.0F,  1.0F, /*|*/-1.0F,  1.0F,  1.0F, /*|*/ 1.0F,  1.0F,  1.0F, // 6
		-1.0F, -1.0F,  1.0F, /*|*/-1.0F, -1.0F, -1.0F, /*|*/-1.0F,  1.0F,  1.0F, // 7
		-1.0F, -1.0F, -1.0F, /*|*/-1.0F,  1.0F, -1.0F, /*|*/-1.0F,  1.0F,  1.0F, // 8
		-1.0F, -1.0F,  1.0F, /*|*/ 1.0F, -1.0F,  1.0F, /*|*/ 1.0F, -1.0F, -1.0F, // 9
		 1.0F, -1.0F, -1.0F, /*|*/-1.0F, -1.0F, -1.0F, /*|*/-1.0F, -1.0F,  1.0F, // 10
		-1.0F,  1.0F, -1.0F, /*|*/ 1.0F,  1.0F, -1.0F, /*|*/ 1.0F,  1.0F,  1.0F, // 11
		 1.0F,  1.0F,  1.0F, /*|*/-1.0F,  1.0F,  1.0F, /*|*/-1.0F,  1.0F, -1.0F  // 12
	};

    glGenVertexArrays(NUMBER_OF_VERTEX_ARRAY_OBJECTS, vertexArrayObject); // extracted
	glBindVertexArray(vertexArrayObject[0]); //
    glGenBuffers(NUMBER_OF_VERTEX_BUFFER_OBJECTS, vertexBufferObject); //

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]); //
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionsCube), vertexPositionsCube, GL_STATIC_DRAW); //
}

void YasEngineGL::clear()
{    
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
}

void YasEngineGL::render(double deltaTime)
{
    clear();

    glUseProgram(shaderProgram);

    modelViewLocation = glGetUniformLocation(shaderProgram, "mv_matrix");
    projectionLocation = glGetUniformLocation(shaderProgram, "proj_matrix");

	aspect = static_cast<float>(windowWidth / windowHeight);

    perspectiveMatrix = buildPerspectiveMatrixGLF(1.0472F, aspect, 0.1F, 1000.0F);
    Vector3GLF cameraVector(-cameraX, -cameraY, -cameraZ);

    viewMatrix = buildTranslationMatrixRowMajorGLFloat(cameraVector);
    ++helperCounter;

    movingStepX = movingStepX + movingStepFactorX*deltaTime;
    rotationStep = rotationStep + (-1.75F*deltaTime*rotationSpeedFactor);
        /*
        Vector3GLF vectorModelTranslation(0, 0, 0);

        modelTranslationMatrix = buildTranslationMatrixRowMajorGLFloat(vectorModelTranslation);//1, 1, 1);
        */
        //rotationStep = rotationStep + (-1.75F*deltaTime*rotationSpeedFactor);
        Vector3GLF justX = {1.0F, 0.0F, 0.0F};
        //Vector3GLF justY = {0.0F, 1.0F, 0.0F};
        //Vector3GLF justZ = {0.0F, 0.0F, 1.0F};

        //log.log("RotationStep: ", rotationStep, "");
        rotationModelMatrix = rotationAroundArbitraryAxies(justX, rotationStep);

        if(helperCounter == 5)
        {
            return;
        }

        modelMatrix = multiply(rotationModelMatrix, modelTranslationMatrix);

        modelViewMatrix = multiply(modelMatrix, viewMatrix);

	    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelViewMatrix.me00);
	    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &perspectiveMatrix.me00);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]);
	    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	    glEnableVertexAttribArray(0);

	    glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LEQUAL);

	    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void YasEngineGL::swapBuffers()
{
	SwapBuffers(deviceContext);
}

void YasEngineGL::destroy() {

	wglMakeCurrent(NULL, NULL);
	if (renderingContext) {
		wglDeleteContext(renderingContext);
	}
	if (deviceContext) {
		ReleaseDC(windowHandle, deviceContext);
	}
	if (windowHandle) {
		DestroyWindow(windowHandle);
	}
}

void YasEngineGL::run(int nCmdShow)
{
    prepareWindow(nCmdShow);

    initShaders();

    // CUBE START
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 8.0f;

	cubeLocationX = 0.0f;
    cubeLocationY = -2.0f;
    cubeLocationZ = 0.0f;
    setupVertices();

    // CUBE END

    std::cout << "Windows and OpenGL context Prepared... starting rendering" << std::endl;

    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;
    MSG message;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;
    message.message = WM_NULL;

    while(message.message != WM_QUIT)
    {
        if(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            newTime = timePicker.getSeconds();  
            deltaTime = newTime - time;
            time = newTime;
#ifndef NO_DELTA_T
            render(deltaTime);
#endif
#ifdef NO_DELTA_T
            render(newTime);
#endif
		    swapBuffers();

            ++frames;
            fpsTime = fpsTime + deltaTime;
            if(fpsTime >= 1.0F)
            {
                fps = frames / fpsTime;
                frames = 0;
                fpsTime = 0.0F;
            }
        }

    }
    destroy();
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
