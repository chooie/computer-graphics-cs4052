const int INCREMENT = 2.0;

void handleUserInput(GLFWwindow* window) {

  // Set window close flag when the user presses the esc key
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, 1);
  }

  if (glfwGetKey(window, GLFW_KEY_A)) {
    xPos -= INCREMENT;
  }

  if (glfwGetKey(window, GLFW_KEY_D)) {
    xPos += INCREMENT;
  }

  if (glfwGetKey(window, GLFW_KEY_S)) {
    yPos -= INCREMENT;
  }

  if (glfwGetKey(window, GLFW_KEY_W)) {
    yPos += INCREMENT;
  }

  if (glfwGetKey(window, GLFW_KEY_Q)) {
    zPos -= INCREMENT;
  }

  if (glfwGetKey(window, GLFW_KEY_E)) {
    zPos += 1.0;
  }

}
