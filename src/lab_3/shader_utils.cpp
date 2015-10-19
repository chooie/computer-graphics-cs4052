#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

std::string readShaderSource(const std::string& fileName) {
	std::ifstream file(fileName.c_str());
	if(file.fail()) {
		cout << "error loading shader called " << fileName;
		exit (1);
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();

	return stream.str();
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText,
  GLenum ShaderType) {

  // Create a shader object
  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(0);
  }
  
	std::string outShader = readShaderSource(pShaderText);
	const char* pShaderSource = outShader.c_str();

	// Bind the source code to the shader, this happens before compilation
	glShaderSource(ShaderObj, 1, (const GLchar**)&pShaderSource, NULL);
	// Compile the shader and check for errors
  glCompileShader(ShaderObj);
  GLint success;
	// Check for shader related errors using glGetShaderiv
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType,
      InfoLog);
    exit(1);
  }
	// Attach the compiled shader object to the program object
  glAttachShader(ShaderProgram, ShaderObj);
}

GLuint CompileShaders() {
	// Start the process of setting up our shaders by creating a program ID
	// Note: we will link all the shaders together into this ID
  GLuint shaderProgramID = glCreateProgram();
  if (shaderProgramID == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

	// Create two shader objects, one for the vertex, and one for the fragment
  // shader
  AddShader(shaderProgramID, "./shaders/simpleVertexShader.glsl",
    GL_VERTEX_SHADER);
  AddShader(shaderProgramID, "./shaders/simpleFragmentShader.glsl",
    GL_FRAGMENT_SHADER);

  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

	// After compiling all shader objects and attaching them to the program, we
  // can finally link it
  glLinkProgram(shaderProgramID);
	// Check for program related errors using glGetProgramiv
  glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
	}

	// Program has been successfully linked but needs to be validated to check
  // whether the program can execute given the current pipeline state
  glValidateProgram(shaderProgramID);
	// Check for program related errors using glGetProgramiv
  glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &Success);
  if (!Success) {
    glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }
	// Finally, use the linked shader program
	// Note: this program will stay in effect for all draw calls until you replace
  // it with another or explicitly disable its use
  glUseProgram(shaderProgramID);

	return shaderProgramID;
}
