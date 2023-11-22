#include"ApplicationRenderer.h"



ApplicationRenderer::ApplicationRenderer()
{
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
    
    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

  
    defaultShader = new Shader("Shaders/Light_VertexShader.vert", "Shaders/Light_FragmentShader.frag");
    lightShader = new Shader("Shaders/lighting.vert", "Shaders/lighting.frag");
   
}



void ApplicationRenderer::Start()
{
  
     Sphere = new Model((char*)"Models/DefaultSphere/Sphere_1_unit_Radius.ply",true);
     Sphere->transform.position.x += 5;

     Model* dir = new Model(*Sphere);
     dir->isVisible = false;
   

     Plane = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane->transform.position.x -= 2;
     Plane->transform.scale = glm::vec3(3.0f);

     Plane2 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane2->transform.position.x += 10;
     Plane2->transform.scale = glm::vec3(3.0f);

     Model* interiorAsset1 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-0.obj", true);
     Model* interiorAsset2 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-1.obj", true);
     Model* interiorAsset3 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-2.obj", true);
     Model* interiorAsset4 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-3.obj", true);
     Model* interiorAsset5 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-4.obj", true);
     Model* interiorAsset6 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-5.obj", true);
     Model* interiorAsset7 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-6.obj", true);
     Model* interiorAsset8 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-7.obj", true);
     Model* interiorAsset9 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-8.obj", true);
     Model* interiorAsset10 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-9.obj", true);
     Model* interiorAsset11 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-10.obj", true);
     Model* interiorAsset12 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-11.obj", true);
     Model* interiorAsset13 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-12.obj", true);
     Model* interiorAsset14 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-13.obj", true);
     Model* interiorAsset15 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-14.obj", true);
     Model* interiorAsset16 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-15.obj", true);
     Model* interiorAsset17 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-16.obj", true);
     Model* interiorAsset18 = new Model("Models/Free Sample/House Interior Rooms - Free Sample-17.obj", true);
     Model* TV = new Model("Models/TV/TV.obj", true);


     interiorAsset1->transform.SetScale(glm::vec3(3));
     interiorAsset2->transform.SetScale(glm::vec3(3));
     interiorAsset3->transform.SetScale(glm::vec3(3));
     interiorAsset4->transform.SetScale(glm::vec3(3));
     interiorAsset5->transform.SetScale(glm::vec3(3));
     interiorAsset6->transform.SetScale(glm::vec3(3));
     interiorAsset7->transform.SetScale(glm::vec3(3));
     interiorAsset8->transform.SetScale(glm::vec3(3));
     interiorAsset9->transform.SetScale(glm::vec3(3));
     interiorAsset10->transform.SetScale(glm::vec3(3));
     interiorAsset11->transform.SetScale(glm::vec3(3));
     interiorAsset12->transform.SetScale(glm::vec3(3));
     interiorAsset13->transform.SetScale(glm::vec3(3));
     interiorAsset14->transform.SetScale(glm::vec3(3));
     interiorAsset15->transform.SetScale(glm::vec3(3));
     interiorAsset16->transform.SetScale(glm::vec3(3));
     interiorAsset17->transform.SetScale(glm::vec3(3));
     interiorAsset18->transform.SetScale(glm::vec3(3));

     //TV Model
     TV->transform.SetPosition(glm::vec3(-0.5f,1.1f,-2.1f));
     TV->transform.SetRotation(glm::vec3(0, -90, 0));
     TV->transform.SetScale(glm::vec3(10));

     Light directionLight;
     directionLight.lightType = LightType::DIRECTION_LIGHT;
     directionLight.lightModel = dir;
     directionLight.ambient =  glm::vec3(0.5f);
     directionLight.diffuse =  glm::vec3(0.5f);
     directionLight.specular = glm::vec3(0.5f);


     //Mesh Renderer
     render.AddModelsAndShader(Sphere, lightShader);
     render.AddModelsAndShader(Plane, lightShader);
     render.AddModelsAndShader(Plane2, lightShader);

     render.AddModelsAndShader(interiorAsset1,defaultShader);
     render.AddModelsAndShader(interiorAsset2,defaultShader);
     render.AddModelsAndShader(interiorAsset3,defaultShader);
     render.AddModelsAndShader(interiorAsset4,defaultShader);
     render.AddModelsAndShader(interiorAsset5,defaultShader);
     render.AddModelsAndShader(interiorAsset6,defaultShader);
     render.AddModelsAndShader(interiorAsset7,defaultShader);
     render.AddModelsAndShader(interiorAsset8,defaultShader);
     render.AddModelsAndShader(interiorAsset9,defaultShader);
     render.AddModelsAndShader(interiorAsset10,defaultShader);
     render.AddModelsAndShader(interiorAsset11,defaultShader);
     render.AddModelsAndShader(interiorAsset12,defaultShader);
     render.AddModelsAndShader(interiorAsset13,defaultShader);
     render.AddModelsAndShader(interiorAsset15,defaultShader);
     render.AddModelsAndShader(interiorAsset16,defaultShader);
     render.AddModelsAndShader(interiorAsset17,defaultShader);
     render.AddModelsAndShader(interiorAsset18,defaultShader);
     render.AddModelsAndShader(TV,defaultShader);


     render.AddModelsAndShader(dir,lightShader);
  

     //LightRenderer
     lightManager.AddNewLight(directionLight);

     lightManager.SetUniforms(defaultShader->ID);


     


#pragma region AudioHandler

    // Boss = new AudioId("Audio/boss.mp3", Sphere->transform.position);
    // Jaguar = new AudioId("Audio/jaguar.wav", dir->transform.position);
    //audioHandler.LoadModelAudio(*Boss);
    //audioHandler.PlayAudio(*Boss);
    //audioHandler.LoadModelAudio(*Jaguar);  
    //audioHandler.PlayAudio(*Jaguar);
    ////
    //audioHandler.AddPolygonToManager(1, 1, true, Plane->meshes[0].vertices, Plane->transform.position, Plane->transform.scale);
    //audioHandler.AddPolygonToManager(1, 1, true, Plane2->meshes[0].vertices, Plane2->transform.position, Plane2->transform.position);

#pragma endregion

}

void ApplicationRenderer::PreRender()
{
   // Sphere->transform.position.x += 5 * deltaTime;
   // audioHandler.UpdateListenerPosition(camera.Position, -camera.Front, camera.Up, -1.0f);

   // audioHandler.UpdatePositionOnChannel(*Boss, Sphere->transform.position);
  


}
void ApplicationRenderer::Render()
{
    Start();
    Material material(128.0f);
    
    while (!glfwWindowShouldClose(window))
    {
        Clear();


     
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window);


        glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)WindowHeight, 0.1f, 100.0f);
        glm::mat4 _view = camera.GetViewMatrix();


        PreRender();

        defaultShader->Bind();
        lightManager.UpdateUniformValues(defaultShader->ID);
        material.SetMaterialProperties(*defaultShader);
       
         defaultShader->setMat4("projection", _projection);
         defaultShader->setMat4("view", _view);

         lightShader->Bind();
         lightShader->setVec3("objectColor", glm::vec3(1, 1, 1));
         lightShader->setMat4("projection", _projection);
         lightShader->setMat4("view", _view);

         render.Draw();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}


void ApplicationRenderer::Clear()
{
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed=25;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        std::cout << "W pressed " << std::endl;

        camera.ProcessKeyboard(FORWARD, deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime * cameraSpeed);

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime * cameraSpeed);

    }


}

 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {
           //  audioHandler.audioManager->PlaySoundFile(Boss->audioPath.c_str());
         }
         if (key == GLFW_KEY_B && action == GLFW_PRESS)
         {
           
         }
     
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
        if (firstMouse)
        {

        }

         if (firstMouse)
         {
             lastX = xpos;
             lastY = ypos;
             firstMouse = false;
         }
     
         float xoffset = xpos - lastX;
         float yoffset = lastY - ypos;
     
         lastX = xpos;
         lastY = ypos;
     
         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
         {
             camera.ProcessMouseMovement(xoffset, yoffset);
         }
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     camera.ProcessMouseScroll(static_cast<float>(yoffset));
 }
