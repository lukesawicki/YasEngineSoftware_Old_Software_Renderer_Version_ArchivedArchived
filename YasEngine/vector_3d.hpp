#ifndef VECTOR_3D_HPP

template <typename Type>
struct Vector3D {
  Type components[4];
  Type* x = components[0];
  Type* y = components[1];
  Type* z = components[2];

  Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }

  Vector3D(Type x, Type y, Type z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vector3D(const Vector3D<Type>& vector) {
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
  }

  static void NormalizeVector3D(Vector3D<Type>& vector) {}

  static Vector3D<Type> GetNormalizedVector3D(const Vector3D<Type>& vector) {
    return nullptr;
  }

  static Type GetVector3DMagnitude(const Vector3D<Type>& vector) {
    return nullptr;
  }

  static Type GetVector3DMagnitude(Type x0, Type y0, Type x1, Type y1) {
    return nullptr;
  }

  static Type CrossProduct3D(const Vector3D<Type>& u, const Vector3D& v) {
    return nullptr;
  }

  static Type DotProduct3D(const Vector3D<Type>& u, const Vector3D& v) {
    return nullptr;
  }

  static Type AngleBetweenTwo3DVectors(const Vector3D<Type>& u,
                                       const Vector3D& v) {
    return nullptr;
  }

  static void Rotate3DVectorOverTheAngle(Vector3D<Type>* v, float angle) {
    
  }
};
