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

// Keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 600;
int g_gl_height = 600;
GLFWwindow* g_window = NULL;
const char WINDOW_NAME[] = "Moving Triangle";

int main() {

  assert(restart_gl_log());
	// All the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	assert(start_gl());
	// Tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

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

  const int NUMBER_OF_CHARS = 1024 * 256;

  char vertex_shader[NUMBER_OF_CHARS];
	char fragment_shader[NUMBER_OF_CHARS];

  // Shader Source
	assert(parse_file_into_str("vertex_shader.glsl", vertex_shader,
    NUMBER_OF_CHARS));
	assert(parse_file_into_str("fragment_shader.glsl", fragment_shader,
    NUMBER_OF_CHARS));

  const GLchar* pointer;

  // Vertex Shader
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  pointer = (const GLchar*)vertex_shader;
	glShaderSource(vs, 1, &pointer, NULL);
	glCompileShader(vs);
  logShaderCompilationStatus(vs, "Vertex Shader");

  // Fragment Shader
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  pointer = (const GLchar*)fragment_shader;
  glShaderSource(fs, 1, &pointer, NULL);
  glCompileShader(fs);
  logShaderCompilationStatus(fs, "Fragment Shader");

  // Shader Programme
  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);

  // Insert location binding code here
  glBindAttribLocation(shader_programme, 0, "vertex_position");
  glBindAttribLocation(shader_programme, 1, "vertex_colour");

  glLinkProgram(shader_programme);

  // Get the location of the `gWorld` variable
  gWorldLocation = glGetUniformLocation(shader_programme, "gWorld");

  while (!glfwWindowShouldClose (g_window)) {

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

    // Pass the productMatrix in as the value for the `gWorld`
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

    handleUserInput(g_window);

    // Put the stuff we've been drawing onto the display
    glfwSwapBuffers(g_window);
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
