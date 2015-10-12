void handleUserInput(GLFWwindow* window) {
  // Set window close flag when the user presses the esc key
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, 1);
  }

  /* Rotation */

  // Press `1` - Rotate positive x
  if (glfwGetKey(window, GLFW_KEY_1)) {
    printf("Rot. Pos X!\n");
  }
  // Press `2` - Rotate negative x
  if (glfwGetKey(window, GLFW_KEY_2)) {
    printf("Rot. Neg X!\n");
  }
  // Press `3` - Rotate positive y
  if (glfwGetKey(window, GLFW_KEY_3)) {
    printf("Rot. Pos Y!\n");
  }
  // Press `4` - Rotate negative y
  if (glfwGetKey(window, GLFW_KEY_4)) {
    printf("Rot. Neg Y!\n");
  }
  // Press `5` - Rotate positive z
  if (glfwGetKey(window, GLFW_KEY_5)) {
    printf("Rot. Pos Z!\n");
  }
  // Press `6` - Rotate negative z
  if (glfwGetKey(window, GLFW_KEY_6)) {
    printf("Rot. Neg Z!\n");
  }

  /* Translation */

  // Press `D` - Translate positive x
  if (glfwGetKey(window, GLFW_KEY_D)) {
    printf("Transl. Pos X!\n");
  }
  // Press `A` - Translate negative x
  if (glfwGetKey(window, GLFW_KEY_A)) {
    printf("Transl. Neg X!\n");
  }
  // Press `W` - Translate positive y
  if (glfwGetKey(window, GLFW_KEY_W)) {
    printf("Transl. Pos Y!\n");
  }
  // Press `S` - Translate negative y
  if (glfwGetKey(window, GLFW_KEY_S)) {
    printf("Transl. Neg Y!\n");
  }
  // Press `Q` - Translate positive z
  if (glfwGetKey(window, GLFW_KEY_Q)) {
    printf("Transl. Pos Z!\n");
  }
  // Press `E` - Translate negative z
  if (glfwGetKey(window, GLFW_KEY_E)) {
    printf("Transl. Neg Z!\n");
  }

  /* Scaling - Uniform */

  // Press `-` - Scale Uniform Negative
  if (glfwGetKey(window, GLFW_KEY_MINUS)) {
    printf("Scale Uniform Neg!\n");
  }
  // Press `+` - Scale Uniform Positive
  if (glfwGetKey(window, GLFW_KEY_EQUAL)) {
    printf("Scale Uniform Plus!\n");
  }

  /* Scaling - Non-Uniform */

  // Press `Z` - Scale Non-Uniform Negative X
  if (glfwGetKey(window, GLFW_KEY_Z)) {
    printf("Scale Non-Uniform Neg X!\n");
  }
  // Press `X` - Scale Non-Uniform Positive X
  if (glfwGetKey(window, GLFW_KEY_X)) {
    printf("Scale Non-Uniform Pos X!\n");
  }
  // Press `C` - Scale Non-Uniform Negative Y
  if (glfwGetKey(window, GLFW_KEY_C)) {
    printf("Scale Non-Uniform Neg Y!\n");
  }
  // Press `V` - Scale Non-Uniform Positive Y
  if (glfwGetKey(window, GLFW_KEY_V)) {
    printf("Scale Non-Uniform Pos Y!\n");
  }
  // Press `B` - Scale Non-Uniform Negative Z
  if (glfwGetKey(window, GLFW_KEY_B)) {
    printf("Scale Non-Uniform Neg Z!\n");
  }
  // Press `N` - Scale Non-Uniform Positive Z
  if (glfwGetKey(window, GLFW_KEY_N)) {
    printf("Scale Non-Uniform Pos Z!\n");
  }
}
