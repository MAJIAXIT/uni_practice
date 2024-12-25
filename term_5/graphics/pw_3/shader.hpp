#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  private:
    GLuint program;

    std::string readFile(const std::string &filename);
    GLuint compileShader(GLenum type, const std::string &source);

  public:
    Shader();
    ~Shader();

    bool load(const std::string &vertexFile, const std::string &fragmentFile);
    void use();
    void cleanup();
    GLuint getProgram() const { return program; }
};

Shader::Shader() : program(0) {}

Shader::~Shader() { cleanup(); }

std::string Shader::readFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string &source) {
    GLuint shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

bool Shader::load(const std::string &vertexFile,
                  const std::string &fragmentFile) {
    std::string vertexCode = readFile(vertexFile);
    std::string fragmentCode = readFile(fragmentFile);

    if (vertexCode.empty() || fragmentCode.empty()) {
        return false;
    }

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    if (!vertexShader || !fragmentShader) {
        return false;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader program linking error: " << infoLog << std::endl;
        cleanup();
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void Shader::use() {
    glUseProgram(program);
}

void Shader::cleanup() {
    if (program) {
        glDeleteProgram(program);
        program = 0;
    }
}
