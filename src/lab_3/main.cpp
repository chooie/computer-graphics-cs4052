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

// My utils
#include "user_input.cpp"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "teapot.h"
#include "shader_utils.cpp"

typedef double DWORD;

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;
GLuint shaderProgramID;

unsigned int teapot_vao = 0;
GLuint loc1;
GLuint loc2;

// Keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 800.0;
int g_gl_height = 600.0;
GLFWwindow* g_window = NULL;

void generateObjectBufferTeapot() {

  GLuint vp_vbo = 0;

	loc1 = glGetAttribLocation(shaderProgramID, "vertex_position");
	loc2 = glGetAttribLocation(shaderProgramID, "vertex_normals");

	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof (float),
    teapot_vertex_points, GL_STATIC_DRAW);

  GLuint vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof (float),
    teapot_normals, GL_STATIC_DRAW);

	glGenVertexArrays(1, &teapot_vao);
	glBindVertexArray(teapot_vao);

	glEnableVertexAttribArray(loc1);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(loc2);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void display() {

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	// Declare your uniform variables that will be used in your shader
	int matrix_location = glGetUniformLocation(shaderProgramID, "model");
	int view_mat_location = glGetUniformLocation(shaderProgramID, "view");
	int proj_mat_location = glGetUniformLocation(shaderProgramID, "proj");

	// Here is where the code for the viewport lab will go, to get you started I
  // have drawn a t-pot in the bottom left. The model transform rotates the
  // object by 45 degrees, the view transform sets the camera at -40 on the
  // z-axis, and the perspective projection is setup using Antons method

	// bottom-left
	mat4 view = translate(identity_mat4(), vec3(0.0, 0.0, -40.0));
	mat4 persp_proj = perspective(
    45.0,
    (float)g_gl_width / (float)g_gl_height,
    0.1,
    100.0
  );
	mat4 model = rotate_z_deg(identity_mat4(), 45);

	glViewport (0, 0, g_gl_width / 2, g_gl_height / 2);
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, persp_proj.m);
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view.m);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, model.m);
	glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);

	// bottom-right

	// top-left

	// top-right

}

void init() {

	// Create 3 vertices that make up a triangle that fits on the viewport
	GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, 1.0,
		 1.0f, -1.0f, 0.0f, 1.0,
		 0.0f,  1.0f, 0.0f, 1.0
  };
	// Create a color array that identfies the colors of each vertex
  // (format R, G, B, A)
	GLfloat colors[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
  };

  // Set up the shaders
	GLuint shaderProgramID = CompileShaders();

  // Load teapot mesh into a vertex buffer array
  generateObjectBufferTeapot();

}

int main(int argc, char** argv){

	assert(restart_gl_log());
	// All the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	assert(start_gl());

  init();

  while (!glfwWindowShouldClose(g_window)) {
    _update_fps_counter (g_window);
    display();
    glfwPollEvents();
    handleUserInput(g_window);
    glfwSwapBuffers(g_window);
  }

  return 0;
}
