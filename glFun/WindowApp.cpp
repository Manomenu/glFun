#include "WindowApp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>

#define ERR(source) (perror(source), fprintf(stdout, "%s:%d\n", __FILE__, __LINE__), glfwTerminate(), exit(EXIT_FAILURE))

const int WIDTH = 1600;
const int HEIGHT = 1200;
const int VERSION_MAJOR = 3;
const int VERSION_MINOR = 3;
const float FRONT = 0.1f;
const float BACK = 100.0f;
const glm::vec4 BACKGROUNDCOLOR = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec3 LIGHTPOS = glm::vec3(1.2f, 1.5f, 2.0f);
const std::string TITLE = "Sztanga Window";

CameraData* WindowApp::camData = new CameraData(WIDTH, HEIGHT);

void WindowApp::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void WindowApp::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* cam = camData->camera;
    if (cam->firstMouse)
    {
        camData->lastX = xpos;
        camData->lastY = ypos;
        cam->firstMouse = false;
    }

    float xoffset = xpos - camData->lastX;
    float yoffset = camData->lastY - ypos;
    camData->lastX = xpos;
    camData->lastY = ypos;
    cam->ProcessMouseMovement(xoffset, yoffset);
}

void WindowApp::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camData->camera->ProcessMouseScroll(yoffset);
}

void WindowApp::processInput()
{
    Camera* cam = camData->camera;
    WindowData* wd = winData;

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(wd->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(wd->window, true);
    if (glfwGetKey(wd->window, GLFW_KEY_W) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(wd->window, GLFW_KEY_S) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(wd->window, GLFW_KEY_A) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(wd->window, GLFW_KEY_D) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

WindowApp::WindowApp() :
    vertices
    {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    },
    lightVertices
    {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    },
    cubePositions
    {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    }
{
    lastFrame = deltaTime = 0.0f;

    if (glfwInit() == GLFW_FALSE)
        ERR("glfwInit");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    winData = new WindowData(TITLE, WIDTH, HEIGHT);

    if (!winData->window)
        ERR("Failed to create GLFW window");
    glfwMakeContextCurrent(winData->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ERR("Failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(winData->window, framebufferSizeCallback);

    shadersConfig();
    buffersConfig();
    texturesConfig();
    cameraConfig();
}

void WindowApp::texturesConfig()
{
    texture = loadTexture(std::string("./images/container2.png").c_str());
    specularMap = loadTexture(std::string("./images/container2_specular.png").c_str());
}

void WindowApp::buffersConfig()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal vector attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lightVertices.size(), &lightVertices[0], GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void WindowApp::shadersConfig()
{
    shader = new Shader("./shaders/shader.vs", "./shaders/shader.fs");
    lightShader = new Shader("./shaders/shader.vs", "./shaders/lightShader.fs");
}

void WindowApp::cameraConfig()
{
    glfwSetInputMode(winData->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(winData->window, mouseCallback);
    glfwSetScrollCallback(winData->window, scrollCallback);
}

void WindowApp::runLoop()
{
    glm::mat4 model;

    shader->use();
    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setFloat("material.shininess", 32.0f);
    shader->setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
    shader->setVec3("light.diffuse", 0.6f, 0.6f, 0.6f); // darken diffuse light a bit
    shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    //shader->setVec3("light.position", LIGHTPOS);
    // shader->setVec3("light.direction", -LIGHTPOS.x, -LIGHTPOS.y, -LIGHTPOS.z);
    shader->setFloat("light.constant", 1.0f);
    shader->setFloat("light.linear", 0.09f);
    shader->setFloat("light.quadratic", 0.032f);
    shader->setFloat("light.cutOff", glm::cos(glm::radians(7.5f)));
    shader->setFloat("light.outerCutOff", glm::cos(glm::radians(12.5f)));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(winData->window))
    {
        // input
        // -----
        processInput();

        // render
        // ------
        glClearColor(
            BACKGROUNDCOLOR.x,
            BACKGROUNDCOLOR.y,
            BACKGROUNDCOLOR.y,
            BACKGROUNDCOLOR.z
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        shader->setVec3("light.position", camData->camera->Position);
        shader->setVec3("light.direction", camData->camera->Front);
        
        shader->setVec3("viewPos", camData->camera->Position);
        shader->setMat4("view", camData->camera->GetViewMatrix());
        glm::mat4 projection = glm::perspective(glm::radians(camData->camera->Zoom), 
            winData->width / (float)winData->height, FRONT, BACK);
        shader->setMat4("projection", projection);

        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        lightShader->use();

        lightShader->setMat4("view", camData->camera->GetViewMatrix());
        projection = glm::perspective(glm::radians(camData->camera->Zoom),
            winData->width / (float)winData->height, FRONT, BACK);
        lightShader->setMat4("projection", projection);
        model = glm::mat4(1.0f);
        model = glm::translate(model, LIGHTPOS);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader->setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(winData->window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
    glfwTerminate();
}

WindowApp::~WindowApp()
{
    delete winData;
    delete camData;
}

unsigned int WindowApp::loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}