#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//window vars
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


using namespace std;

int main()
{
    //glfw: initialize and configure
    //------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //glfw window creation
    //------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    //call framebuffer function on every window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //glad: load all OpenGL function pointers
    //------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

   
    //loop to keep window open and render
    //------------------------
    while(!glfwWindowShouldClose(window))
    {
        //inpute
    	processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    	//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved, etc)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glfw: terminate, clearning all previously allocated GLFW resources
    //------------------------
    glfwTerminate();
    

    return 0;
}



//resize callback function to resize the window
//------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//process all input: query GLFW whether relevant keys are pressed/released
//------------------------
void processInput(GLFWwindow *window)
{
    //check if escape key was pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}