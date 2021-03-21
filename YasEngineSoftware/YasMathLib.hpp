#ifndef YASMATHLIB_HPP
#define YASMATHLIB_HPP

#include<cmath>

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

// About coordinates: Left handed and Right handed:
// From website:
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/coordinate-systems
//It is also critically important to know which convention is used for the coordinate system when dealing with a
//renderer or any other 3D application. At present, the standard in the industry tends to be the right-hand XYZ
//coordinate system where x points to the right, y is up and z is outward (coming out of the screen).
//Programs and 3D APIs such as Maya and OpenGL use a right-hand coordinate system, while DirectX, pbrt and PRMan
//use a left-hand coordinate system. Note that both Maya and PRMan use a coordinate system in which the up vector
//is called the y-axis and the forward vector is called the z-axis. Essentially, this means that the z-coordinate
//of 3 for a point in one system is -3 in the other. For this reason, we potentially need to reverse the sign of
//an object's z-coordinates when the geometry is exported to the renderer. The choice of coordinate system handedness
//also plays a critical role when it comes to rotation and the cross product of two vectors. We will talk about this
//more in the next few chapters. It's actually easy enough (but painful) to go from one coordinate system to another.
//All that is needed is to scale the point coordinates and the camera-to-world matrix by (1, 1, -1).


//https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
//Remember that they are essentially two conventions when it comes to NDC space. Coordinates are either considered to be defined in the range [-1, 1]. This is the case of most real-time graphics APIs such as OpenGL or Direct3D. Or they can also be defined in the range [0, 1]. The RenderMan specifications define them that way. You are entirely free to choose the convention you prefer. We will stick to the convention used by graphics API because this is essentially within this context that you will see these matrices being used.

// In OpenGL matrices are defined using column major order but it is strange that in perspective matrix it uses row major


struct Vector3GLF
{
    GLfloat vc0;
    GLfloat vc1;
    GLfloat vc2;
    Vector3GLF(float vc0, float vc1, float vc2)
    {
        this->vc0 = vc0;
        this->vc1 = vc1;
        this->vc2 = vc2;
    }
} typedef Vector3F, Vec3GLF;

struct Matrix4GLF
{
    GLfloat me00=1.0F, me01=0.0F, me02=0.0F, me03=0.0F;
    GLfloat me10=0.0F, me11=1.0F, me12=0.0F, me13=0.0F;
    GLfloat me20=0.0F, me21=0.0F, me22=1.0F, me23=0.0F;
    GLfloat me30=0.0F, me31=0.0F, me32=0.0F, me33=1.0F;

} typedef Mat4GLF;

static void normalizeVector(Vector3GLF& vector);
static GLfloat getVectorMagnitude(const Vector3GLF& vector);

static Matrix4GLF multiply(const Matrix4GLF& a,const Matrix4GLF& b)
{
    Matrix4GLF mat =
    {
        a.me00*b.me00 + a.me01*b.me10 + a.me02*b.me20 + a.me03*b.me30, /*|*/ a.me00*b.me01 + a.me01*b.me11 + a.me02*b.me21 + a.me03*b.me31, /*|*/ a.me00*b.me02 + a.me01*b.me12 + a.me02*b.me22 + a.me03*b.me32, /*|*/ a.me00*b.me03 + a.me01*b.me13 + a.me02*b.me23 + a.me03*b.me33,
        a.me10*b.me00 + a.me11*b.me10 + a.me12*b.me20 + a.me13*b.me30, /*|*/ a.me10*b.me01 + a.me11*b.me11 + a.me12*b.me21 + a.me13*b.me31, /*|*/ a.me10*b.me02 + a.me11*b.me12 + a.me12*b.me22 + a.me13*b.me32, /*|*/ a.me10*b.me03 + a.me11*b.me13 + a.me12*b.me23 + a.me13*b.me33,
        a.me20*b.me00 + a.me21*b.me10 + a.me22*b.me20 + a.me23*b.me30, /*|*/ a.me20*b.me01 + a.me21*b.me11 + a.me22*b.me21 + a.me23*b.me31, /*|*/ a.me20*b.me02 + a.me21*b.me12 + a.me22*b.me22 + a.me23*b.me32, /*|*/ a.me20*b.me03 + a.me21*b.me13 + a.me22*b.me23 + a.me23*b.me33,
        a.me30*b.me00 + a.me31*b.me10 + a.me32*b.me20 + a.me33*b.me30, /*|*/ a.me30*b.me01 + a.me31*b.me11 + a.me32*b.me21 + a.me33*b.me31, /*|*/ a.me30*b.me02 + a.me31*b.me12 + a.me32*b.me22 + a.me33*b.me32, /*|*/ a.me30*b.me03 + a.me31*b.me13 + a.me32*b.me23 + a.me33*b.me33
    };
    return mat;
}

//OpenGL Right Handed Coordination System and thata are
// In OpenGL default matrices order are column-major(column vectors);
// from OpenGL 4.x you can change that and this matrix below is ****row-major****
// IN GLM IT IS (GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_ONE) == false
//ROW MAJOR
static Matrix4GLF buildPerspectiveMatrixGLF(const float& fieldOfViewY, const float& aspectRatio, const float& zNearPlane, const float& zFarPlane)
{
    Matrix4GLF mat =
    {
        static_cast<GLfloat>(1.0F / ((tan(fieldOfViewY/2.0F)) * aspectRatio)), 0.0F,                                                    0.0F,                                                                                0.0F,  //0
        0.0F,                                                                  static_cast<GLfloat>(1.0F / (tan(fieldOfViewY/2.0F))),   0.0F,                                                                                0.0F,  //1
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>( - (zFarPlane + zNearPlane)/( zFarPlane - zNearPlane) ),        -1.0F, //2
        0.0F,                                                                  0.0F,                                                    static_cast<GLfloat>(- (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane) ),    0.0F   //3
    };
    return mat;
}

//ROW MAJOR
static Matrix4GLF buildTranslationMatrixRowMajorGLFloat(const Vector3GLF& vector)
{
    Matrix4GLF mat =
    {
        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
        mat.me30 = vector.vc0,    mat.me31 = vector.vc1,    mat.me32 = vector.vc2,    mat.me33 = 1.0F
    };

    return mat;
}

GLfloat getVectorMagnitude(const Vector3GLF& vector)
{
    return sqrt(pow(vector.vc0, 2) + pow(vector.vc1, 2) + pow(vector.vc2, 2));
}

void normalizeVector(Vector3GLF& vector)
{
    GLfloat vectorMagnitude = getVectorMagnitude(vector);
    vector.vc0 = vector.vc0 / vectorMagnitude;
    vector.vc1 = vector.vc1 / vectorMagnitude;
    vector.vc2 = vector.vc2 / vectorMagnitude;
}


static Matrix4GLF buildAllRotationMatrix(const float& p, const float& vc1, const float& r)
{
    Matrix4GLF mat =
    {
        mat.me00 = cos(r)*cos(vc1),                        mat.me01 = sin(r)*cos(vc1),                             mat.me02 = sin(vc1),         mat.me03 = 0.0F,
        mat.me10 = sin(r)*cos(p) + cos(r)*sin(vc1)*sin(p), mat.me11 = cos(r)*cos(p) -(sin(r)*sin(vc1)*sin(p)),     mat.me12 = -sin(p)*cos(vc1), mat.me13 = 0.0F,
        mat.me20 = sin(r)*sin(p) - cos(r)*sin(vc1)*cos(p), mat.me21 = cos(r)*sin(p) + sin(r)*sin(vc1)*cos(p),      mat.me22 = cos(vc1)*cos(p),  mat.me23 = 0.0F,
        mat.me30 = 0.0F,                                 mat.me31 = 0.0F,                                      mat.me32 = 0.0F,           mat.me33 = 1.0F,
    };

    return mat;
}

// ???????? MAJOR
static Matrix4GLF rotationAroundArbitraryAxies(Vector3GLF axisVector, const float& angle)
{
    float c = cos(angle);
    float s = sin(angle);
    
    normalizeVector(axisVector);

    //Matrix4GLF mat =
    //{
    //    mat.me00 = c+((1.0F - c)*axisVector.vc0)* axisVector.vc0,               mat.me01 = ((1.0F-c)*axisVector.vc0)*axisVector.vc1 + s*axisVector.vc2, mat.me02 = ((1.0F-c)*axisVector.vc0)*axisVector.vc2 - s*axisVector.vc1, mat.me03 = 0.0F,
    //    mat.me10 = ((1.0F-c)*axisVector.vc1)*axisVector.vc0 - s*axisVector.vc2, mat.me11 = c+((1.0F - c)*axisVector.vc1)*axisVector.vc1,                mat.me12 = ((1.0F-c)*axisVector.vc1)*axisVector.vc2 + s*axisVector.vc0, mat.me13 = 0.0F,
    //    mat.me20 = ((1.0F-c)*axisVector.vc2)*axisVector.vc0 + s*axisVector.vc1, mat.me21 = ((1.0F-c)*axisVector.vc2)*axisVector.vc1 - s*axisVector.vc0, mat.me22 = c+((1.0F - c)*axisVector.vc2)*axisVector.vc2,                mat.me23 = 0.0F,
    //    mat.me30 = 0.0F,                                                        mat.me31 = 0.0F,                                                        mat.me32 = 0.0F,                                                        mat.me33 = 1.0F,
    //};

    Matrix4GLF mat =
    {
        mat.me00 = c+((1.0F - c)*axisVector.vc0)* axisVector.vc0,               mat.me01 = ((1.0F-c)*axisVector.vc0)*axisVector.vc1 - s*axisVector.vc2, mat.me02 = ((1.0F-c)*axisVector.vc0)*axisVector.vc2 + s*axisVector.vc1, mat.me03 = 0.0F,
        mat.me10 = ((1.0F-c)*axisVector.vc1)*axisVector.vc0 + s*axisVector.vc2, mat.me11 = c+((1.0F - c)*axisVector.vc1)*axisVector.vc1,                mat.me12 = ((1.0F-c)*axisVector.vc1)*axisVector.vc2 - s*axisVector.vc0, mat.me13 = 0.0F,
        mat.me20 = ((1.0F-c)*axisVector.vc2)*axisVector.vc0 - s*axisVector.vc1, mat.me21 = ((1.0F-c)*axisVector.vc2)*axisVector.vc1 + s*axisVector.vc0, mat.me22 = c+((1.0F - c)*axisVector.vc2)*axisVector.vc2,                mat.me23 = 0.0F,
        mat.me30 = 0.0F,                                                        mat.me31 = 0.0F,                                                        mat.me32 = 0.0F,                                                        mat.me33 = 1.0F,
    };

    return mat;
}

#endif YASMATHLIB_HPP

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|


//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------Temporary notes and code fragments---------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//struct Vector4GLF {
//    GLfloat vc0;
//    GLfloat vc1;
//    GLfloat vc2;
//    GLfloat vc3;
//    Vector4GLF(float vc0, float vc1, float vc2, float vc3)
//    {
//        this->vc0 = vc0;
//        this->vc1 = vc1;
//        this->vc2 = vc2;
//        this->vc3 = vc3;
//    }
//} typedef Vector4GLF, Vec4GLF;

//static Matrix4GLF buildTranslationMatrixRowMajorGLFloat(const GLfloat& vc0, const GLfloat& vc1, const GLfloat&  vc2)
//{
//    Matrix4GLF mat = {
//        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
//        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
//        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
//        mat.me30 = vc0,    mat.me31 = vc1,    mat.me32 = vc2,    mat.me33 = 1.0F
//    };
//
//    return mat;
//}

//static Matrix4GLF buildTranslationMatrixColumnMajorGLFloat(const GLfloat& vc0, const GLfloat& vc1, const GLfloat&  vc2)
//{
//    Matrix4GLF mat = {
//        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = vc0,
//        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = vc1,
//        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = vc2,
//        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me32 = 0.0,  mat.me33 = 1.0F
//    };
//    
//    return mat;
//}
//
//static Matrix4GLF buildTranslationMatrixColumnMajorGLFloat(const Vector3GLF& vector)
//{
//    Matrix4GLF mat = {
//        mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = vector.vc0,
//        mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = vector.vc1,
//        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = vector.vc2,
//        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me32 = 0.0,  mat.me33 = 1.0F
//    };
//    
//    return mat;
//}

//static void transpose(Matrix4GLF &mat);
//static void transpose(Matrix4GLF &mat)
//{
//    Matrix4GLF matCopy;
//
//    matCopy.me00=mat.me00; matCopy.me10=mat.me10; matCopy.me20=mat.me20; matCopy.me30=mat.me30;
//    matCopy.me10=mat.me01; matCopy.me11=mat.me11; matCopy.me21=mat.me21; matCopy.me31=mat.me31;
//    matCopy.me20=mat.me02; matCopy.me12=mat.me12; matCopy.me22=mat.me22; matCopy.me32=mat.me32;
//    matCopy.me30=mat.me03; matCopy.me13=mat.me13; matCopy.me23=mat.me23; matCopy.me33=mat.me33;
//
//    mat.me00=matCopy.me00; mat.me01=matCopy.me10; mat.me02=matCopy.me20; mat.me03=matCopy.me30;
//    mat.me10=matCopy.me01; mat.me11=matCopy.me11; mat.me12=matCopy.me21; mat.me13=matCopy.me31;
//    mat.me20=matCopy.me02; mat.me21=matCopy.me12; mat.me22=matCopy.me22; mat.me23=matCopy.me32;
//    mat.me30=matCopy.me03; mat.me31=matCopy.me13; mat.me32=matCopy.me23; mat.me33=matCopy.me33;
//}

//// Rotate around X axis
//static Matrix4GLF buildPitchMatrix(const float& rad)
//{
//    Matrix4GLF mat = {
//        mat.me00 = 1.0F, mat.me01 = 0.0F,     mat.me02 = 0.0F,      mat.me03 = 0.0F,
//        mat.me10 = 0.0F, mat.me11 = cos(rad), mat.me12 = -sin(rad), mat.me13 = 0.0F,
//        mat.me20 = 0.0F, mat.me21 = sin(rad), mat.me22 = cos(rad),  mat.me23 = 0.0F,
//        mat.me30 = 0.0F, mat.me31 = 0.0F,     mat.me32 = 0.0F,      mat.me33 = 1.0F,
//    };
//    return mat;
//}
//
//// Rotate around Y axis
//static Matrix4GLF buildYawMatrix(const float& rad)
//{
//    Matrix4GLF mat = {
//        mat.me00 = cos(rad),  mat.me01 = 0.0F, mat.me02 = sin(rad), mat.me03 = 0.0F,
//        mat.me10 = 0.0F,      mat.me11 = 1.0F, mat.me12 = 0.0F,     mat.me13 = 0.0F,
//        mat.me20 = -sin(rad), mat.me21 = 0.0F, mat.me22 = cos(rad), mat.me23 = 0.0F,
//        mat.me30 = 0.0F,      mat.me31 = 0.0F, mat.me32 = 0.0F,     mat.me33 = 1.0F,
//    };
//    return mat;
//}
//
//// Rotate around Z axis
//static Matrix4GLF buildRollMatrix(const float& rad)
//{
//    Matrix4GLF mat = {
//        mat.me00 = cos(rad), mat.me01 = -sin(rad), mat.me02 = 0.0F, mat.me03 = 0.0F,
//        mat.me10 = sin(rad), mat.me11 = cos(rad),  mat.me12 = 0.0F, mat.me13 = 0.0F,
//        mat.me20 = 0.0F,     mat.me21 = 0.0F,      mat.me22 = 1.0F, mat.me23 = 0.0F,
//        mat.me30 = 0.0F,     mat.me31 = 0.0F,      mat.me32 = 0.0F, mat.me33 = 1.0F,
//    };
//    return mat;
//}

////Scale
//static Matrix4GLF buildScaleMatrix(const float& vc0, const float& vc1, const float& vc2)
//{
//    Matrix4GLF mat =
//    {
//        mat.me00 = vc0,  mat.me01 = 0.0F, mat.me01 = 0.0F, mat.me01 = 0.0F,
//        mat.me10 = 0.0F, mat.me11 = vc1,  mat.me11 = 0.0F, mat.me11 = 0.0F,
//        mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me21 = vc2,  mat.me21 = 0.0F,
//        mat.me30 = 0.0F, mat.me31 = 0.0F, mat.me31 = 0.0F, mat.me31 = 1.0F,
//    };
//
//    return mat;
//}

// Right handed

// Row major

// Column major

//----------------------------------------------------------------------------------------------------------------------

// Left handed

// Row major

// Column major


//----------------------------------------------------------------------------------------------------------------------
//---------------------------------------End of temporary notes and code fragments--------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
