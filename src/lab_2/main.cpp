#define __MAIN__
// Include GLEW and new version of GL on Windows.
// Always include before glfw
#include "../../lib/GL/glew.h"
// GLFW helper library
#include "../../lib/GLFW/glfw3.h"
#include <stdio.h>

#include <math.h>

// Anton's Math Lib
#include "../../lib/Math/maths_funcs.cpp"

// Anton's Util Lib
#include "../../lib/GL_UTILS/gl_utils.cpp"

// My Libs
#include "./globals.h"
#include "./../utils.cpp"
#include "user_input.cpp"

const mat4 IDENTITY_MATRIX = mat4(
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f
);

mat4 productMatrix;

vec3 translationVector;

vec3 scaleVector;

GLuint gWorldLocation;

// Called whenever GLFW encounters an error
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 600;
int g_gl_height = 600;
GLFWwindow* g_window = NULL;
const char WINDOW_NAME[] = "Moving Triangle";

int main() {

  // Register callback that is called when an error occurs
  glfwSetErrorCallback(error_callback);

  // Start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

	// Uncomment these lines if on Apple OS X
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(g_gl_width, g_gl_height,
    WINDOW_NAME, NULL, NULL);

  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  // Start GLEW extension handler
  glewExperimental = GL_TRUE; // Try to get latest OpenGL features

  GLenum err = glewInit();

  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }

  // Must have OpenGL v4.0
  if (!glewIsSupported("GL_VERSION_4_0")) {
    fprintf(stderr, "ERROR: must have OpenGL v4.0+\n");
  }

  // Get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // Tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // Enable depth-testing
  glDepthFunc(GL_LESS); // Depth-testing interprets a smaller value as "closer"

  float points[] = {
     0.0f,  0.5f,  0.0f, // Top
     0.5f, -0.5f,  0.0f, // Bottom-right
    -0.5f, -0.5f,  0.0f, // Bottom-left
  };

  float colours[] = {
    1.0f, 0.0f, 0.0f, // Top
    0.0f, 1.0f, 0.0f, // Bottom-right
    0.0f, 0.0f, 1.0f, // Bottom-left
  };

  // Vertex Buffer Objects
  // Generate an empty buffer
  GLuint points_vbo;
  glGenBuffers(1, &points_vbo);
  // Set it as current buffer in OpenGL's state machine
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  // Copy points into currently bound buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  GLuint colours_vbo;
  glGenBuffers(1, &colours_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

  // Vertex Attribute Object
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Enable points attribute
  glEnableVertexAttribArray(0);
  // Enable colours attribute
  glEnableVertexAttribArray(1);

  const char* vertex_shader =
    "#version 400\n"
    "layout(location = 0) in vec3 vertex_position;"
    "layout(location = 1) in vec3 vertex_colour;"
    "uniform mat4 gWorld;"
    "out vec3 colour;"
    "void main() {"
    "  colour = vertex_colour;"
    "  gl_Position = gWorld * vec4(vertex_position, 1.0);"
    "}";

  const char* fragment_shader =
    "#version 400\n"
    "in vec3 colour;"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(colour, 1.0);"
    "}";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  logShaderCompilationStatus(vs, "Vertex Shader");

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  logShaderCompilationStatus(fs, "Fragment Shader");

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);

  // Insert location binding code here
  glBindAttribLocation(shader_programme, 0, "vertex_position");
  glBindAttribLocation(shader_programme, 1, "vertex_colour");

  glLinkProgram(shader_programme);

  gWorldLocation = glGetUniformLocation(shader_programme, "gWorld");

  while (!glfwWindowShouldClose (window)) {

    // Wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, g_gl_width, g_gl_width);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);

    /* Triangle 1 */

    // Translation
    translationVector = vec3(transX, transY, transZ);
    productMatrix = translate(IDENTITY_MATRIX, translationVector);

    // Rotation
    productMatrix = rotate_x_deg(productMatrix, rotX);
    productMatrix = rotate_y_deg(productMatrix, rotY);
    productMatrix = rotate_z_deg(productMatrix, rotZ);

    // Scaling
    scaleVector = vec3(scaleX, scaleY, scaleZ);
    productMatrix = scale(productMatrix, scaleVector);

    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, (float *)&productMatrix);
    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Triangle 2 */

    // Translation
    translationVector = vec3(-transX, -transY, -transZ);
    productMatrix = translate(IDENTITY_MATRIX, translationVector);

    // Rotation
    productMatrix = rotate_x_deg(productMatrix, -rotX / 2);
    productMatrix = rotate_y_deg(productMatrix, -rotY / 3);
    productMatrix = rotate_z_deg(productMatrix, -rotZ / 4);

    // Scaling
    scaleVector = vec3(scaleX * 0.6, scaleY * 1.1f, scaleZ * 0.75f);
    productMatrix = scale(productMatrix, scaleVector);

    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, (float *)&productMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Update other events like input handling
    glfwPollEvents();

    handleUserInput(window);

    // Put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  }

  glDeleteProgram(shader_programme);
  glDeleteShader(fs);
  glDeleteShader(vs);
  glDeleteBuffers(1, &points_vbo);
  glDeleteBuffers(1, &colours_vbo);
  glDeleteVertexArrays(1, &vao);

  // Close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
