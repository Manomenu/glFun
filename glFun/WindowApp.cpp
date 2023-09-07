#include "WindowApp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>

#define ERR(source) (perror(source), fprintf(stdout, "%s:%d\n", __FILE__, __LINE__), glfwTerminate(), exit(EXIT_FAILURE))

const int WIDTH = 800;
const int HEIGHT = 600;
const int VERSION_MAJOR = 3;
const int VERSION_MINOR = 3;
const float FRONT = 0.1f;
const float BACK = 100.0f;
const glm::vec4 BACKGROUNDCOLOR = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec3 LIGHTPOS = glm::vec3(1.2f, 1.0f, 2.0f);
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
    TextureData& td = texData;
    glGenTextures(1, &td.texture);
    glBindTexture(GL_TEXTURE_2D, td.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    td.data = stbi_load("./images/container2.png", &td.width, &td.height, &td.nrChannels, 0);
    if (td.data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, td.width, td.height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, td.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        ERR("Failed to load texture");
    stbi_image_free(td.data);
    stbi_set_flip_vertically_on_load(false);
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
    shader->use();
    // gold
    shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    shader->setFloat("material.shininess", 32.0f);
    shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
    shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", LIGHTPOS);

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

        shader->setVec3("viewPos", camData->camera->Position);
        shader->setMat4("view", camData->camera->GetViewMatrix());
        glm::mat4 projection = glm::perspective(glm::radians(camData->camera->Zoom), 
            winData->width / (float)winData->height, FRONT, BACK);
        shader->setMat4("projection", projection);

        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.1f), glm::vec3(0.5f, 1.0f, 0.0f));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);

        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::rotate(model, (glm::sin((float)glfwGetTime()) + 1.0f) / 2.0f * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
        glBindVertexArray(0);


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
        glDrawArrays(GL_TRIANGLES, 0, lightVertices.size() / 3);
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