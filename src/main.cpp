#include <iostream> 
#include <glad/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow* createWindow();
void initVertexShader(unsigned int vertexShader);
void initFragmentShader(unsigned int fragmentShader);
bool shaderSuccessful(unsigned int shader);
bool programSuccessful(unsigned int program);
unsigned int compileShader(unsigned int shader, const char* shaderSource);
void processInput(GLFWwindow* window);
const char* initVertexShaderSource();
const char* initFragmentShaderSource();

int main() {
	std::cout << "Running application...\n";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = createWindow();
	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0) {
		std::cerr << "Unable to load GLAD\n";
		return -1;
	}

	glViewport(0, 0, 800, 600);
	float vertices[] = {	    //colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f //top
	};
	const char* vertexShaderSource = initVertexShaderSource();
	const char* fragmentShaderSource = initFragmentShaderSource();
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource), 
		     fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource),
		     shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);	
	glLinkProgram(shaderProgram);

	if (!programSuccessful(shaderProgram)) {
		std::cerr << "Exiting application...\n";
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);	

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* createWindow() {
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to open window\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	return window;
}


unsigned int compileShader(unsigned int shaderType, const char* shaderSource) {
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	
	if (!shaderSuccessful(shader)) {
			std::cerr << "Exiting applicaiton...\n";
			glDeleteShader(shader);
			return -1;
	}

	return shader;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
}



const char* initVertexShaderSource() {
        return "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out  vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos, 1.0);\n"
    "  ourColor = aColor;\n"
    "}\0";
}

const char* initFragmentShaderSource() {
        return "#version 330 core\n"
          "out vec4 FragColor;\n"
	  "in vec3 ourColor;\n"
          "void main() {\n"
          "FragColor = vec4(ourColor, 1.0);\n"
          "}\n";
}


bool shaderSuccessful(unsigned int shader) {
	int success, length = 512;
	char infoLog[length];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(shader, length, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
			  << infoLog << std::endl;
		return false;
	}

	return true;
}

bool programSuccessful(unsigned int program) {
	int success, length = 512;
	char infoLog[length];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, length, NULL, infoLog);
		std::cerr << "ERROR::PROGRAM::LINKED_FAILED\n"
			  << infoLog << std::endl;
		return false;
	}

	return true;
}
