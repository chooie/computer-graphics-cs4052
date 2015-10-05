// Include GLEW and new version of GL on Windows.
// Always include before glfw
#include "../../../lib/GL/glew.h"
// GLFW helper library
#include "../../../lib/GLFW/glfw3.h"
#include <stdio.h>

// Called whenever GLFW encounters an error
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const char WINDOW_NAME[] = "Hello Triangle";

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

  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
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

  // glEnable(GL_CULL_FACE); // cull face
  // glCullFace(GL_BACK); // cull back face
  // glFrontFace(GL_CW); // GL_CCW for counter clock-wise

  float points[] = {
     0.5f,  0.5f,  0.0f, // Top-right
     0.5f, -0.5f,  0.0f, // Bottom-right
    -0.5f, -0.5f,  0.0f, // Bottom-left

    -0.5f, -0.5f,  0.0f, // Bottom-left
    -0.5f,  0.5f,  0.0f, // Top-left
     0.5f,  0.5f,  0.0f  // Top-right
  };

  float colours[] = {
    1.0f, 0.0f, 0.0f, // Top-right
    1.0f, 1.0f, 0.0f, // Bottom-right
    1.0f, 1.0f, 0.0f, // Bottom-left

    1.0f, 1.0f, 0.0f, // Bottom-left
    1.0f, 0.0f, 0.0f, // Top-left
    1.0f, 0.0f, 0.0f  // Top-right
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
    "out vec3 colour;"
    "void main() {"
    "  colour = vertex_colour;"
    "  gl_Position = vec4 (vertex_position, 1.0);"
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
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);

  // Insert location binding code here
  glBindAttribLocation(shader_programme, 0, "vertex_position");
  glBindAttribLocation(shader_programme, 1, "vertex_colour");

  glLinkProgram(shader_programme);

  while (!glfwWindowShouldClose (window)) {
    // Wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // Draw points 0-6 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Update other events like input handling
    glfwPollEvents();
    // Put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);

    // Set window close flag when the user presses the esc key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  // Close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
