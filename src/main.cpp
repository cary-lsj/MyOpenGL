#include "core/Command.h"
#include "modules/triangle/Triangle.h"
#include "modules/triangle/Triangle1.h"
#include "modules/texture/MyTexture.h"
Command* command;
int input=3;
//bool DEBUG = true;
bool DEBUG = false;

void showPptions() {
	std::cout << "请输入你的选项" << std::endl;
	std::cout << "1：彩色三角形" << std::endl;
	std::cout << "2：时间上线性变色三角形" << std::endl;
	std::cout << "3：纹理" << std::endl;
	std::cout << "0：关闭程序" << std::endl;
}
void init() {
	switch (input) {
		case 1:
			command = new Triangle();
			break;
		case 2:
			command = new Triangle1();
			break;
		case 3:
			command = new MyTexture();
			break;
	}
	command->init();
}

void render() {
	command->render();
}

void exit() {
	command->exit();
}

//动态设置屏幕大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//输入
void processInput(GLFWwindow* window);
int createWindw();
// settings
//屏幕大小
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;
bool isClose;

int main()
{
	isClose = true;
	if (DEBUG) {
		createWindw();
		return 0;
	}
	while (isClose) {
		showPptions();
		std::cin >> input;

		if (input > 0) {
			createWindw(); 
		}
		else {
			isClose = false;
		}
	}
	return 0;
}

int createWindw() {

	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建一个GLFW窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建glfw窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	//渲染窗口
	glfwMakeContextCurrent(window);
	//窗口大小改变时执行framebuffer_size_callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "加载失败" << std::endl;
		return -1;
	}

	init();

	//持续渲染
	while (!glfwWindowShouldClose(window))
	{
		//检测输入
		processInput(window);

		//渲染内容
		render();

		//交换颜色缓冲
		glfwSwapBuffers(window);
		//检测事件
		glfwPollEvents();
	}
	glfwTerminate();
	exit();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}


