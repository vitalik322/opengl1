#include <fstream>
#include <sstream>

class ShaderProgram {
public:
    ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
        this->isError = false;
        unsigned int vertexShader = compileShader_(vertexShaderPath, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader_(fragmentShaderPath, GL_FRAGMENT_SHADER);
        if (this->isError)
            return;
        linkShaderProgram_(vertexShader, fragmentShader);
    }

    void use() {
        glUseProgram(program_);
    }

    bool isError;
private:
    unsigned int program_;

    unsigned int compileShader_(std::string &shaderPath, GLenum sType) {
        std::cout << "Reading shader: " << shaderPath << std::endl;
        std::ifstream shaderFile;
        shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        std::string shaderSource;
        try {
            shaderFile.open(shaderPath);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderSource  = shaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            this->isError = true;
            return 0;
        }
        const char* shaderCode = shaderSource.c_str();

        unsigned int shader;
        shader = glCreateShader(sType);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            this->isError = true;
        }
        return shader;
    }

    unsigned int linkShaderProgram_(unsigned int vertexShader, unsigned int fragmentShader) {
        unsigned int shaderProgram;
        program_ = glCreateProgram();
        glAttachShader(program_, vertexShader);
        glAttachShader(program_, fragmentShader);
        glLinkProgram(program_);

        int success;
        char infoLog[200];
        glGetProgramiv(program_, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(program_, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            this->isError = true;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
};
