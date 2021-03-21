#ifndef YASENGINEGL_HPP
#define YASENGINEGL_HPP
#include<cstring>
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<gl/gl.h>
#include<glext.h>
#include<wglext.h>
#include"TimePicker.hpp"
#include"YasMathLib.hpp"
#include"YasLog.hpp"
//#define NO_DELTA_T
//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class YasEngineGL
{
    public:
                    YasEngineGL(HINSTANCE hInstance);
        void        prepareWindow(int nCmdShow);
        void        run(int nCmdShow);
        void        destroy();

        void        clear();
        void        render(double deltaTime);
        void        swapBuffers();

        void        initShaders();
        std::string loadShaderCode(std::string fileName);
        // GLuint - shorthand for “unsigned int”, provided by OpenGL.
        GLuint      createShaderProgram();
 
    private:
        //WinAPI

        static      LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        ATOM        registerWindowClass(HINSTANCE hInstance);
        
        YasLog<double> log;
        int helperCounter = 0;

        HINSTANCE applicationHandle;
        HWND      windowHandle;
        LPTSTR    windowClassName;
        DWORD     style;
        HDC       deviceContext;
        HGLRC     renderingContext;

        int windowXposition;
        int windowYposition;
        int windowWidth;
        int windowHeight;

		bool windowed;

        // Engine specific variables:
        static std::string engineName;
        static std::string applicationName;
        static std::string shadersPath;
        
        //OpenGL
        void extractFunctionsPointers();
        void printShaderLog(GLuint shader);
        void printProgramLog(int prog);
        bool checkOpenGLError();
        void setupVertices();

        char* openGlVersion;
        char* openGlVendor;
        char* openGlRenderer;
        
        static const int NUMBER_OF_VERTEX_ARRAY_OBJECTS = 1;
        static const int NUMBER_OF_VERTEX_BUFFER_OBJECTS = 2;

        GLuint shaderProgram;
        GLuint vertexArrayObjectIds[1];

        GLuint renderingProgram;

        GLuint vertexArrayObject[NUMBER_OF_VERTEX_ARRAY_OBJECTS];
        GLuint vertexBufferObject[NUMBER_OF_VERTEX_BUFFER_OBJECTS];

        // OpenGL and extension function pointers:

        // For working with shaders
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLSHADERSOURCEPROC glShaderSource;
        PFNGLCOMPILESHADERPROC glCompileShader;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
        PFNGLBINDVERTEXARRAYPROC glBindVertexArray;


        // For error checking and logging
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

        // For rendering
        PFNGLUSEPROGRAMPROC glUseProgram;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1f;

        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

        // CUBE EXAMPLE START

        float cameraX;
        float cameraY;
        float cameraZ;

        float cubeLocationX;
        float cubeLocationY;
        float cubeLocationZ;

        float aspect;

        // Transformations data
        float movingStepX = 0.0F;
        float movingStepY = 0.0F;
        float movingStepZ = 0.0F;
        float movingStepFactorX = 0.35F;
        float movingStepFactorY = 0.52F;
        float movingStepFactorZ = 0.7F;

        float rotationStep = 0.0F;
        float rotationSpeedFactor = 0.95F;

        Matrix4GLF allRotationsMatrix;

        Matrix4GLF perspectiveMatrix;

        Matrix4GLF viewMatrix;

        Matrix4GLF modelMatrix;

        Matrix4GLF modelViewMatrix;

        Matrix4GLF modelTranslationMatrix;
        Matrix4GLF rotationModelMatrix;

        GLuint modelViewLocation;
        GLuint projectionLocation;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
