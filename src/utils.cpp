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

double getRandomDoubleBetween0And1() {
  const double MIN_THRESHOLD = 0.2L;
  const double MAX_THRESHOLD = 0.8L;
  const double BUFFER = 0.2L;

  double randomNumber = (double) rand() / RAND_MAX;

  if (randomNumber < MIN_THRESHOLD) {
    randomNumber += BUFFER;
  }
  else if (randomNumber > MAX_THRESHOLD) {
    randomNumber -= BUFFER;
  }

  return randomNumber;
}
