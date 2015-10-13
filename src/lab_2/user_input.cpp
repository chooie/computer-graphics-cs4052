#include <math.h>

void translate() {
  World.m[0][3] = sin(transX);
  World.m[1][1] = cos(rotX); World.m[1][2] = -sin(rotX); World.m[1][3] = sin(transY);
  World.m[2][1] = sin(rotX); World.m[2][2] = cos(rotX); World.m[2][3] = sin(transZ);
}

void rotateX() {
  World.m[1][1] = cos(rotX); World.m[1][2] = -sin(rotX);
  World.m[2][1] = sin(rotX); World.m[2][2] = cos(rotX);
}

void rotateY() {
  World.m[0][0] = cos(rotY);  World.m[0][2] = sin(rotY);
  World.m[2][0] = -sin(rotY); World.m[2][2] = cos(rotY);
}

void rotateZ() {
  World.m[0][0] = cos(rotZ);  World.m[0][1] = -sin(rotZ);
  World.m[1][0] = sin(rotZ); World.m[1][1] = cos(rotZ);
}

void scaleUniformly() {
  World.m[0][0] = sinf(uniformScale);
  World.m[1][1] = sinf(uniformScale);
  World.m[2][2] = sinf(uniformScale);
}

void handleUserInput(GLFWwindow* window) {

  // Set window close flag when the user presses the esc key
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, 1);
  }

  /* Rotation */

  // Press `1` - Rotate positive x
  if (glfwGetKey(window, GLFW_KEY_1)) {
    rotX += 0.1;
    rotateX();
    printf("Rot. Pos X!\n");
  }
  // Press `2` - Rotate negative x
  if (glfwGetKey(window, GLFW_KEY_2)) {
    rotX -= 0.1;
    rotateX();
    printf("Rot. Neg X!\n");
  }
  // Press `3` - Rotate positive y
  if (glfwGetKey(window, GLFW_KEY_3)) {
    rotY += 0.1;
    rotateY();
    printf("Rot. Pos Y!\n");
  }
  // Press `4` - Rotate negative y
  if (glfwGetKey(window, GLFW_KEY_4)) {
    rotY -= 0.1;
    rotateY();
    printf("Rot. Neg Y!\n");
  }
  // Press `5` - Rotate positive z
  if (glfwGetKey(window, GLFW_KEY_5)) {
    rotZ += 0.1;
    rotateZ();
    printf("Rot. Pos Z!\n");
  }
  // Press `6` - Rotate negative z
  if (glfwGetKey(window, GLFW_KEY_6)) {
    rotZ -= 0.1;
    rotateZ();
    printf("Rot. Neg Z!\n");
  }

  /* Translation */

  // Press `D` - Translate positive x
  if (glfwGetKey(window, GLFW_KEY_D)) {
    transX += 0.01;
    translate();
    printf("Transl. Pos X!\n");
  }
  // Press `A` - Translate negative x
  if (glfwGetKey(window, GLFW_KEY_A)) {
    transX -= 0.01;
    translate();
    printf("Transl. Neg X!\n");
  }
  // Press `W` - Translate positive y
  if (glfwGetKey(window, GLFW_KEY_W)) {
    transY += 0.01;
    translate();
    printf("Transl. Pos Y!\n");
  }
  // Press `S` - Translate negative y
  if (glfwGetKey(window, GLFW_KEY_S)) {
    transY -= 0.01;
    translate();
    printf("Transl. Neg Y!\n");
  }
  // Press `Q` - Translate positive z
  if (glfwGetKey(window, GLFW_KEY_Q)) {
    transZ += 0.01;
    translate();
    printf("Transl. Pos Z!\n");
  }
  // Press `E` - Translate negative z
  if (glfwGetKey(window, GLFW_KEY_E)) {
    transZ -= 0.01;
    translate();
    printf("Transl. Neg Z!\n");
  }

  /* Scaling - Uniform */

  // Press `-` - Scale Uniform Negative
  if (glfwGetKey(window, GLFW_KEY_MINUS)) {
    uniformScale -= 0.01f;
    scaleUniformly();
    printf("Scale Uniform Neg!\n");
  }
  // Press `+` - Scale Uniform Positive
  if (glfwGetKey(window, GLFW_KEY_EQUAL)) {
    uniformScale += 0.01f;
    scaleUniformly();
    printf("Scale Uniform Plus!\n");
  }

  /* Scaling - Non-Uniform */

  // Press `Z` - Scale Non-Uniform Negative X
  if (glfwGetKey(window, GLFW_KEY_Z)) {
    scaleX -= 0.01;
    printf("Scale Non-Uniform Neg X!\n");
  }
  // Press `X` - Scale Non-Uniform Positive X
  if (glfwGetKey(window, GLFW_KEY_X)) {
    scaleX += 0.01;
    printf("Scale Non-Uniform Pos X!\n");
  }
  // Press `C` - Scale Non-Uniform Negative Y
  if (glfwGetKey(window, GLFW_KEY_C)) {
    scaleY -= 0.01;
    printf("Scale Non-Uniform Neg Y!\n");
  }
  // Press `V` - Scale Non-Uniform Positive Y
  if (glfwGetKey(window, GLFW_KEY_V)) {
    scaleY += 0.01;
    printf("Scale Non-Uniform Pos Y!\n");
  }
  // Press `B` - Scale Non-Uniform Negative Z
  if (glfwGetKey(window, GLFW_KEY_B)) {
    scaleZ -= 0.01;
    printf("Scale Non-Uniform Neg Z!\n");
  }
  // Press `N` - Scale Non-Uniform Positive Z
  if (glfwGetKey(window, GLFW_KEY_N)) {
    scaleZ -= 0.01;
    printf("Scale Non-Uniform Pos Z!\n");
  }
}
