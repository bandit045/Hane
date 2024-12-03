#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	constructShaderProgram(vertexFile, fragmentFile);
}


void Shader::constructShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	compileErrors(vertexShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to th Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deactivate the shader
void Shader::Deactivate()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::sendBool(const std::string& varName, const bool& boolValue)
{
	glUniform1i(glGetUniformLocation(ID, varName.c_str()), boolValue);
}

void Shader::sendVec3f(const std::string& varName,const glm::vec3& vec3)
{
	glUniform3f(glGetUniformLocation(ID, varName.c_str()), vec3.x, vec3.y, vec3.z);
}
void Shader::sendVec3f(const std::string& varName, const float& x, const float& y, const float& z)
{
	glUniform3f(glGetUniformLocation(ID, varName.c_str()), x, y, z);
}

void Shader::sendVec2f(const std::string& varName, const glm::vec2& vec2)
{
	glUniform2f(glGetUniformLocation(ID, varName.c_str()), vec2.x, vec2.y);
}
void Shader::sendVec2f(const std::string& varName, const float& x, const float& y)
{
	glUniform2f(glGetUniformLocation(ID, varName.c_str()), x, y);
}

void Shader::sendVec1f(const std::string& varName, const float& x)
{
	glUniform1f(glGetUniformLocation(ID, varName.c_str()), x);
}

void Shader::sendMatrix3x3f(const std::string& varName, const glm::mat3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::sendMatrix4x4f(const std::string& varName, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::sendUniformBufferStructBool(const char* nameOfUnifformStructInShader, int _numberOfElementsInside, const RenderFlags& structData)
{
	unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(ID, "ControlsOfState");
	glUniformBlockBinding(ID, uniformBlockIndexRed, 0);

	//unsigned int renderFlagsUnifformObject;
	glGenBuffers(1, &renderFlagsUnifformObject);

	glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(structData) * sizeof(int), nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, renderFlagsUnifformObject, 0, sizeof(structData) * sizeof(int));

	int renderFlagsInt[8] = {
		structData.isPointLightReducingOnDistance ? 1 : 0,
		structData.isPhong ? 1 : 0,
		structData.isBlinnPhong ? 1 : 0,
		structData.isSpecularMap ? 1 : 0,
		structData.isDirectionalLight ? 1 : 0,
		structData.isPointLight ? 1 : 0,
		structData.isAutomaticLuminosity ? 1 : 0,
		structData.isManuelLuminosity ? 1 : 0,
	};

	glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(renderFlagsInt), &renderFlagsInt);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Shader::BindUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
}

void Shader::UnbindUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

// This metod is private
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}