#include "shader_program.hpp"
#include "glfw3.h"

GLFWwindow* window = nullptr;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "TESTSs";
const char* SHADER_SOURCE = "shaders" PATH_SEP "Basic.shader";
GLuint shader_program, vao, vbo, ibo;
GLint tex_location;

bool initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Falhou ao tentar inicializar o GLFW." << std::endl;
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Falha ao criar a janela a partir do GLFW." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

bool initGLAD() {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Não foi possível iniciar o contexto OpenGL." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    return true;
}

void start() {
    ShaderProgramSource shader_source = parserShader(SHADER_SOURCE);
    shader_program = createProgram(shader_source.vertex_source, shader_source.fragment_source);
    GLCall(glUseProgram(shader_program));

    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    static const GLfloat vertices[] = {
        -0.5f, 0.0f, 0.0f,  // position
        1.0f, 0.0f, 0.0f,   // color

        0.5f, 0.0f, 0.0f,   // position
        0.0f, 1.0f, 0.0f,   // color

        0.0f, 0.5f, 0.0f,   // position
        0.0f, 0.0f, 1.0f,   // color
        };
    
    static const GLuint indices[] = {
        0, 1, 2
    };
    
    GLCall(glGenBuffers(1, &vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    // especifica o atributo de posição
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0));

    // especifica o atributo de cor
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat))));

    // criar um buffer de índices
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // encerra as vinculações
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}

void render() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    GLCall(glUseProgram(shader_program));

    GLCall(glBindVertexArray(vao));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

    glfwSwapBuffers(window);
}

void loop() {
    start();

    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwPollEvents();
    }

    GLCall(glDisableVertexAttribArray(0));
    GLCall(glDisableVertexAttribArray(1));
    GLCall(glDisableVertexAttribArray(2));
    GLCall(glDeleteBuffers(1, &vbo));
    GLCall(glDeleteBuffers(1, &ibo));
    GLCall(glDeleteVertexArrays(1, &vao));
    GLCall(glDeleteProgram(shader_program));

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    if (!initGLFW()) {
        return EXIT_FAILURE;
    }

    if (!initGLAD()) {
        return EXIT_FAILURE;
    }

    loop();

    return 0;
}