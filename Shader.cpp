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
	GLCall(glShaderSource(vertexShader, 1, &vertexSource, NULL));
	// Compile the Vertex Shader into machine code
	GLCall(glCompileShader(vertexShader));
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	GLCall(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
	// Compile the Vertex Shader into machine code
	GLCall(glCompileShader(fragmentShader));
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to th Shader Program
	GLCall(glAttachShader(ID, vertexShader));
	GLCall(glAttachShader(ID, fragmentShader));
	// Wrap-up/Link all the shaders together into the Shader Program
	GLCall(glLinkProgram(ID));
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
}

// Activates the Shader Program
void Shader::Activate()
{
	GLCall(glUseProgram(ID)); // CHECK CONSOLE FOR SHADER ERROR!!!!!!!!!!
}

// Deactivate the shader
void Shader::Deactivate()
{
	GLCall(glUseProgram(0));
}

// Deletes the Shader Program
void Shader::Delete()
{
	GLCall(glDeleteProgram(ID));
}

void Shader::sendBool(const std::string& varName, const bool& boolValue)
{
	GLCall(glUniform1i(glGetUniformLocation(ID, varName.c_str()), boolValue));
}

void Shader::sendVec3f(const std::string& varName,const glm::vec3& vec3)
{
	GLCall(glUniform3f(glGetUniformLocation(ID, varName.c_str()), vec3.x, vec3.y, vec3.z));
}
void Shader::sendVec3f(const std::string& varName, const float& x, const float& y, const float& z)
{
	GLCall(glUniform3f(glGetUniformLocation(ID, varName.c_str()), x, y, z));
}

void Shader::sendVec2f(const std::string& varName, const glm::vec2& vec2)
{
	GLCall(glUniform2f(glGetUniformLocation(ID, varName.c_str()), vec2.x, vec2.y));
}
void Shader::sendVec2f(const std::string& varName, const float& x, const float& y)
{
	GLCall(glUniform2f(glGetUniformLocation(ID, varName.c_str()), x, y));
}

void Shader::sendFloat(const std::string& varName, const float& x)
{
	GLCall(glUniform1f(glGetUniformLocation(ID, varName.c_str()), x));
}

void Shader::sendMatrix3x3f(const std::string& varName, const glm::mat3& matrix)
{
	GLCall(glUniformMatrix3fv(glGetUniformLocation(ID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)));
}
void Shader::sendMatrix4x4f(const std::string& varName, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(ID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)));
}

// This metod is private
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[2048];
	if (type != "PROGRAM")
	{
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled));
		if (hasCompiled == GL_FALSE)
		{
			GLCall(glGetShaderInfoLog(shader, 2048, NULL, infoLog));
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n";
			std::cout << infoLog << std::endl;
		}
	}
	else
	{
		GLCall(glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled));
		if (hasCompiled == GL_FALSE)
		{
			GLCall(glGetProgramInfoLog(shader, 2048, NULL, infoLog));
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n";
			std::cout << infoLog << std::endl;
		}
	}
}