#include "Shader.h"
#include <stdio.h>
#include <sstream>
#include <glad/glad.h>
#include <vector>

namespace LATIN
{
    void Shader::Create(const char* path)
    {
        FILE* shaderfile = fopen(path, "r");
        if (!shaderfile)
        {
            printf("Failed to find shader: %s", path);
			return;
        }

        bool isVertex = true;
        char buffer[512];
        std::stringstream vertexSource;
        std::stringstream fragmentSource;
        while (fgets(buffer, 512, shaderfile))
        {
            if (buffer[0] == '#')
            {
                switch (buffer[1])
                {
                    case 'V': isVertex = true; continue;
                    case 'F': isVertex = false; continue;
                }
            }

            isVertex ? vertexSource << buffer : fragmentSource << buffer;
        }

        fclose(shaderfile);

        Create(vertexSource.str().c_str(), fragmentSource.str().c_str());
    }
    void Shader::Create(const char* vertexSource, const char* fragmentSource)
    {

			// Create an empty vertex shader handle
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource;
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			printf("%s\n", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource;
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			printf("%s\n", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			printf("%s\n", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
    }
	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}
	void Shader::Destroy()
	{
		glDeleteProgram(m_RendererID);
	}
	void Shader::UploadUniformIV1(const char* name, int* values, unsigned int count)
	{
		glUniform1iv(GetShaderLocation(name), count, values);
	}
	void Shader::UploadUniformI1(const char* name, int value)
	{
		glUniform1i(GetShaderLocation(name), value);
	}
	void Shader::UploadUniformF1(const char* name, float value)
	{
		glUniform1f(GetShaderLocation(name), value);
	}
	void Shader::UploadUniformF2(const char* name, float value1, float value2)
	{
		glUniform2f(GetShaderLocation(name), value1, value2);
	}
	void Shader::UploadUniformF3(const char* name, float value1, float value2, float value3)
	{
		glUniform3f(GetShaderLocation(name), value1, value2, value3);
	}
	void Shader::UploadUniformMat4(const char* name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(GetShaderLocation(name), 1, GL_FALSE, &mat[0][0]);
	}
	int Shader::GetShaderLocation(const char* name)
	{
		int result = glGetUniformLocation(m_RendererID, name);
		if (result == -1)
		{
			printf("Could not find uniform: %s\n", name);
		}
		return result;
	}
}