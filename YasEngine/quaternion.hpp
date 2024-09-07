#ifndef QUATERNION_HPP
#define QUATERNION_HPP

class Quaternion {
 public:
  float element_0_0_ = 0.0F; // the real part
  float element_0_1_ = 0.0F; // the imaginary part xi+yj+zk
  float element_0_2_ = 0.0F; // the imaginary part xi+yj+zk
  float element_0_3_ = 0.0F; // the imaginary part xi+yj+zk
  // here based on book Tricks of The 3d game programming gurus elements are defined
  // in order element 0_0_ w alement_0_1_ x and y and z
};

#endif
