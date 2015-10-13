// Include GLEW and new version of GL on Windows.
// Always include before glfw
#include "../../lib/GL/glew.h"
// GLFW helper library
#include "../../lib/GLFW/glfw3.h"

#include <stdio.h>

// Anton's Math Library
#include "../../lib/Math/maths_funcs.h"

// Anton's Utility Library
#include "../../lib/GL_UTILS/gl_utils.cpp"

// My Utils
#include "./../utils.cpp"
#include "./user_input.cpp"

#include "../../lib/GL_UTILS/gl_utils.h" // utility functions discussed in earlier tutorials
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#define GL_LOG_FILE "gl.log"

// Called whenever GLFW encounters an error
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

int main() {

  assert (restart_gl_log ());
	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	assert (start_gl ());
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

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

  char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];

  assert(
    parse_file_into_str("vertex_shader.glsl", vertex_shader, 1024 * 256)
  );
	assert(
    parse_file_into_str("fragment_shader.glsl", fragment_shader, 1024 * 256)
  );

  const GLchar* p;

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  p = (const GLchar*)vertex_shader;
  glShaderSource(vs, 1, &p, NULL);
  glCompileShader(vs);

  logShaderCompilationStatus(vs, "Vertex Shader");

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  p = (const GLchar*)fragment_shader;
  glShaderSource(fs, 1, &p, NULL);
  glCompileShader(fs);
  logShaderCompilationStatus(fs, "Fragment Shader");

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);

  // Insert location binding code here
  glBindAttribLocation(shader_programme, 0, "vertex_position");
  glBindAttribLocation(shader_programme, 1, "vertex_colour");

  glLinkProgram(shader_programme);

  int params = -1;
  glGetProgramiv (shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (
			stderr,
			"ERROR: could not link shader programme GL index %i\n",
			shader_programme
		);
		print_programme_info_log (shader_programme);
		return false;
	}

  while (!glfwWindowShouldClose(g_window)) {
    // Wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Update other events like input handling
    glfwPollEvents();
    // Put the stuff we've been drawing onto the display
    glfwSwapBuffers(g_window);
    handleUserInput(g_window);
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
