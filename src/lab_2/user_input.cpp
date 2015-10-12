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

  // Press `Q` - Translate positive x
  if (glfwGetKey(window, GLFW_KEY_Q)) {
    printf("Transl. Pos X!\n");
  }
  // Press `W` - Translate negative x
  if (glfwGetKey(window, GLFW_KEY_W)) {
    printf("Transl. Neg X!\n");
  }
  // Press `E` - Translate positive y
  if (glfwGetKey(window, GLFW_KEY_E)) {
    printf("Transl. Pos Y!\n");
  }
  // Press `R` - Translate negative y
  if (glfwGetKey(window, GLFW_KEY_R)) {
    printf("Transl. Neg Y!\n");
  }
  // Press `T` - Translate positive z
  if (glfwGetKey(window, GLFW_KEY_T)) {
    printf("Transl. Pos Z!\n");
  }
  // Press `Y` - Translate negative z
  if (glfwGetKey(window, GLFW_KEY_Y)) {
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

  // Press `A` - Scale Non-Uniform Negative X
  if (glfwGetKey(window, GLFW_KEY_A)) {
    printf("Scale Non-Uniform Neg X!\n");
  }
  // Press `S` - Scale Non-Uniform Positive X
  if (glfwGetKey(window, GLFW_KEY_S)) {
    printf("Scale Non-Uniform Pos X!\n");
  }
  // Press `D` - Scale Non-Uniform Negative Y
  if (glfwGetKey(window, GLFW_KEY_D)) {
    printf("Scale Non-Uniform Neg Y!\n");
  }
  // Press `F` - Scale Non-Uniform Positive Y
  if (glfwGetKey(window, GLFW_KEY_F)) {
    printf("Scale Non-Uniform Pos Y!\n");
  }
  // Press `G` - Scale Non-Uniform Negative Z
  if (glfwGetKey(window, GLFW_KEY_G)) {
    printf("Scale Non-Uniform Neg Z!\n");
  }
  // Press `H` - Scale Non-Uniform Positive Z
  if (glfwGetKey(window, GLFW_KEY_H)) {
    printf("Scale Non-Uniform Pos Z!\n");
  }
}
