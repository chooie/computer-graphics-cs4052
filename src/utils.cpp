void logShaderCompilationStatus(GLuint shaderID, const char* shaderName) {
  GLint status;
  char message[] = "%s compiled successfully.\n";
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

  if (status == GL_TRUE) {
    printf(message, shaderName);
  } else {
    printf("Error in %s:\n", shaderName);
    char buffer[512];
    glGetShaderInfoLog(shaderID, 512, NULL, buffer);
    printf("%s", buffer);
  }
}
