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

float xPos = 0.0f;
float yPos = 0.0f;
float zPos = 0.0f;

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
GLfloat rotatey = 0.0f;

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

void drawTeaPot(int& proj_mat_location, int& view_mat_location,
  int& matrix_location, mat4 persp_proj, mat4 view, mat4 global) {

  glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, persp_proj.m);
  glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view.m);
  glUniformMatrix4fv (matrix_location, 1, GL_FALSE, global.m);
  glDrawArrays (GL_TRIANGLES, 0, teapot_vertex_count);

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

	// Hierarchy of Teapots

	// Root of the Hierarchy
	mat4 view = identity_mat4();
	mat4 persp_proj = perspective(
    45.0,
    (float)g_gl_width/(float)g_gl_height,
    0.1,
    1000.0
  );
	mat4 local = identity_mat4();
	local = translate(local, vec3(0.0, 0.0, -200.0f));
  local = translate(local, vec3(xPos, yPos, zPos));

	// For the root, we orient it in global space
	mat4 global1 = local;
	// Update uniforms & draw
	drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global1);

	// Child of hierarchy
	local = identity_mat4();
	// Translation is 15 units in the y direction from the parents coordinate
  // system
	local = translate(local, vec3(0.0, 15.0, 0.0));
	// Global of the child is got by pre-multiplying the local of the child by the
  // global of the parent
	mat4 global2 = global1 * local;
	drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global2);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  local = rotate_y_deg(local, rotatey);
  mat4 global3 = global2 * local;
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global3);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  local = rotate_y_deg(local, -2 * rotatey);
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global3 * local);

  // Forward, tilted
  local = identity_mat4();
  local = rotate_x_deg(local, 90.0);
  local = translate(local, vec3(0.0, 0.0, 15.0));
  mat4 global4 = global3 * local;
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global4);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global4 * local);

  // Right, tilted
  local = identity_mat4();
  local = rotate_z_deg(local, -90.0);
  local = translate(local, vec3(15.0, 0.0, 0.0));
  mat4 global5 = global3 * local;
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global5);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global5 * local);

  // Backward, tilted
  local = identity_mat4();
  local = rotate_x_deg(local, -90.0);
  local = translate(local, vec3(0.0, 0.0, -15.0));
  mat4 global6 = global3 * local;
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global6);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global6 * local);

  // Left, tilted
  local = identity_mat4();
  local = rotate_z_deg(local, 90.0);
  local = translate(local, vec3(-15.0, 0.0, 0.0));
  mat4 global7 = global3 * local;
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global7);

  local = identity_mat4();
  local = translate(local, vec3(0.0, 15.0, 0.0));
  drawTeaPot(proj_mat_location, view_mat_location, matrix_location,
    persp_proj, view, global7 * local);

}

void init() {

  // Set up the shaders
	shaderProgramID = CompileShaders();

  // Load teapot mesh into a vertex buffer array
  generateObjectBufferTeapot();

}

int main(int argc, char** argv) {

	assert(restart_gl_log());
	// All the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	assert(start_gl());

  init();

  while (!glfwWindowShouldClose(g_window)) {
    // Change degrees
    rotatey += 1;

    if (rotatey >= 360) {
      rotatey = 0;
    }

    _update_fps_counter (g_window);
    display();
    glfwPollEvents();
    handleUserInput(g_window);
    glfwSwapBuffers(g_window);
  }

  return 0;
}
