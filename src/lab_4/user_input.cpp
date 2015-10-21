void handleUserInput(GLFWwindow* window) {

  // Set window close flag when the user presses the esc key
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, 1);
  }

}
