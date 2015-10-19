mat4 ortho(float left, float right, float bottom, float top, float near,
  float far) {

  float a0 = 2 / (right - left);
  float d0 = -( (left + right) / (right - left) );
  float b1 = 2 / (top - bottom);
  float d1 = -( (top + bottom) / (top - bottom) );
  float c2 = -2 / (far - near);
  float d2 = -( (far + near) / (far - near ) );
  float d3 = 1.0;

  // Row-major format
  mat4 m = mat4(
    a0, 0,  0,  d0, // 0
    0,  b1, 0,  d1, // 1
    0,  0,  c2, d2, // 2
    0,  0,  0,  d3  // 3
  );
  
  // Put into column-major format
  return transpose(m);

}
