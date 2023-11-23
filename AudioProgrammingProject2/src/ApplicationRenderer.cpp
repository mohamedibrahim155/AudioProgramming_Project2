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

    camera.Position = glm::vec3(0, 1, 0);
   
}



void ApplicationRenderer::Start()
{
    //Used for TV
     Sphere = new Model((char*)"Models/DefaultSphere/Sphere_1_unit_Radius.ply",true);
     Sphere->transform.SetScale(glm::vec3(0.25f));

     //Used for door
     Sphere2 = new Model(*Sphere);
     Sphere2->transform.SetScale(glm::vec3(0.25f));

     Sphere3 = new Model(*Sphere);
     Sphere3->transform.SetScale(glm::vec3(0.25f));


   

     Plane = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane->transform.SetPosition(glm::vec3(-5, 1, 0));
     Plane->transform.SetScale(glm::vec3(5));
    // Plane->isVisible = false;

     Plane2 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane2->transform.SetPosition(glm::vec3(0, 1, -5));
     Plane2->transform.SetRotation(glm::vec3(0, 90, 0));
     Plane2->transform.SetScale(glm::vec3(5));
    // Plane2->isVisible = false;


     Plane3 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane3->transform.SetPosition(glm::vec3(0, 1, 5));
     Plane3->transform.SetRotation(glm::vec3(0, 90, 0));
     Plane3->transform.SetScale(glm::vec3(5));
   //  Plane3->isVisible = false;

     Plane4 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane4->transform.SetPosition(glm::vec3(5, 1, 0));
     Plane4->transform.SetRotation(glm::vec3(0, 0, 0));
     Plane4->transform.SetScale(glm::vec3(5));
    // Plane4->isVisible = false;


     Plane5 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane5->transform.SetPosition(glm::vec3(0, 5.5f, 0));
     Plane5->transform.SetRotation(glm::vec3(0, 0, 90));
     Plane5->transform.SetScale(glm::vec3(5));
     // Plane5->isVisible = false;


     Plane6 = new Model((char*)"Models/Plane/Plane.obj", true);
     Plane6->transform.SetPosition(glm::vec3(0, -0.5f, 0));
     Plane6->transform.SetRotation(glm::vec3(0, 0, 90));
     Plane6->transform.SetScale(glm::vec3(5));
     // Plane6->isVisible = false;


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
     Model* Car1 = new Model("Models/Car/Car_1_1.fbx", true);
     Model* Car2 = new Model("Models/Car/Car_3_3.fbx", true);
      ambulance = new Model("Models/Car/Ambulance.fbx", true);


      interiorAsset1->transform.SetScale(glm::vec3(5));
      interiorAsset2->transform.SetScale(glm::vec3(5));
      interiorAsset3->transform.SetScale(glm::vec3(5));
      interiorAsset4->transform.SetScale(glm::vec3(5));
      interiorAsset5->transform.SetScale(glm::vec3(5));
      interiorAsset6->transform.SetScale(glm::vec3(5));
      interiorAsset7->transform.SetScale(glm::vec3(5));
      interiorAsset8->transform.SetScale(glm::vec3(5));
      interiorAsset9->transform.SetScale(glm::vec3(5));
     interiorAsset10->transform.SetScale(glm::vec3(5));
     interiorAsset11->transform.SetScale(glm::vec3(5));
     interiorAsset12->transform.SetScale(glm::vec3(5));
     interiorAsset13->transform.SetScale(glm::vec3(5));
     interiorAsset14->transform.SetScale(glm::vec3(5));
     interiorAsset15->transform.SetScale(glm::vec3(5));
     interiorAsset16->transform.SetScale(glm::vec3(5));
     interiorAsset17->transform.SetScale(glm::vec3(5));
     interiorAsset18->transform.SetScale(glm::vec3(5));

     //TV Model
     TV->transform.SetPosition(glm::vec3(-1,1.7f,-4));
     TV->transform.SetRotation(glm::vec3(0, -90, 0));
     TV->transform.SetScale(glm::vec3(15));



     //Blue Car
     Car1->transform.SetPosition(glm::vec3(0,0.5f,0));
     Car1->transform.SetRotation(glm::vec3(0, -72, 0));
     Car1->transform.SetScale(glm::vec3(0.1f));

     Car2->transform.SetPosition(glm::vec3(-1, 0.5f, -1));
     Car2->transform.SetRotation(glm::vec3(0, 45, 0));
     Car2->transform.SetScale(glm::vec3(0.1f));


     // Taxi
     ambulance->transform.SetPosition(glm::vec3(4, 0.5f, 1));
     ambulance->transform.SetScale(glm::vec3(0.1f));

     Light directionLight;
     directionLight.lightType = LightType::DIRECTION_LIGHT;
     directionLight.lightModel = Sphere2;
     directionLight.ambient =  glm::vec3(0.5f);
     directionLight.diffuse =  glm::vec3(0.5f);
     directionLight.specular = glm::vec3(0.5f);


#pragma region Mesh Renderer


     //Mesh Renderer

     //Sphere models 
     render.AddModelsAndShader(Sphere, lightShader);
     render.AddModelsAndShader(Sphere2, lightShader);
     render.AddModelsAndShader(Sphere3, lightShader);
     //Plane
     render.AddModelsAndShader(Plane, lightShader);
     render.AddModelsAndShader(Plane2, lightShader);
     render.AddModelsAndShader(Plane3, lightShader);
     render.AddModelsAndShader(Plane4, lightShader);
     render.AddModelsAndShader(Plane5, lightShader);
     render.AddModelsAndShader(Plane6, lightShader);

     //Interior models
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

     // Toy models
     render.AddModelsAndShader(TV,defaultShader);
     render.AddModelsAndShader(Car1,defaultShader);
     render.AddModelsAndShader(Car2,defaultShader);
     render.AddModelsAndShader(ambulance,defaultShader);


#pragma endregion 

     //LightRenderer
     lightManager.AddNewLight(directionLight);

     lightManager.SetUniforms(defaultShader->ID);


     


#pragma region AudioHandler

     Sphere->transform.SetPosition(glm::vec3(-1, 1.8f, -3.7f));  //TV's  audio Position
     Sphere2->transform.SetPosition(glm::vec3(4, 3.5f, -4));     //Door bell's audio Postion
     Sphere3->transform.SetPosition(glm::vec3(4, 0.5f, 1));     //Ambulance's audio Postion

     Tv_Sound = new AudioId("Audio/Tv_News.mp3", Sphere->transform.position);
     doorBell_Sound = new AudioId("Audio/doorBell.mp3", Sphere2->transform.position);
     siren_Sound = new AudioId("Audio/Siren.mp3", Sphere3->transform.position);
  
     //SET all the volumes for the
     Tv_Sound->setVolume(0.2f);
     doorBell_Sound->setVolume(0.5f);
     siren_Sound->setVolume(0.25f);

   //TV SOUND 
    audioHandler.LoadModelAudio(*Tv_Sound);
    audioHandler.AddDSPBasedOnTypeAndOrder(Tv_Sound->audioPath.c_str(), DSPType::HIGHPASS, 0);
    audioHandler.AddDSPBasedOnTypeAndOrder(Tv_Sound->audioPath.c_str(), DSPType::DISTORTION, 1);

    float highpass=10000;
    float distortionvalue =0.9f;
    audioHandler.PlayAudio(*Tv_Sound);
    audioHandler.SetVolume(*Tv_Sound, Tv_Sound->volume);
    audioHandler.SetDSPBasedOnType(Tv_Sound->audioPath.c_str(), DSPType::HIGHPASS, highpass);
    audioHandler.SetDSPBasedOnType(Tv_Sound->audioPath.c_str(), DSPType::DISTORTION, distortionvalue);

    // Door Bell Sound 
    audioHandler.LoadModelAudio(*doorBell_Sound, false);  
    audioHandler.AddDSPBasedOnTypeAndOrder(doorBell_Sound->audioPath.c_str(), DSPType::CHORUS, 0);
    audioHandler.PlayAudio(*doorBell_Sound);
    audioHandler.SetVolume(*doorBell_Sound, doorBell_Sound->volume);

    float chorusMix = 500;
    float chorusRate = 0.9f;
    float chorusDepth= 7;
    audioHandler.SetDSPBasedOnType(doorBell_Sound->audioPath.c_str(), DSPType::CHORUS, chorusMix, chorusRate, chorusDepth);

    // Ambulance Siren Sound 
    audioHandler.LoadModelAudio(*siren_Sound);

    //audioHandler.PlayAudio(*siren_Sound);
    //audioHandler.SetVolume(*siren_Sound, 0.5f);



    //// Adding plane's to culling
    audioHandler.AddPolygonToManagerWithRotation(1, 1, true, 
        Plane->meshes[0].vertices, 
        Plane->transform.position,
        Plane->transform.scale,
        Plane->transform.GetUp(),
        Plane->transform.GetForward());

    audioHandler.AddPolygonToManagerWithRotation(1, 1, true, 
        Plane2->meshes[0].vertices,
        Plane2->transform.position,
        Plane2->transform.scale,
        Plane2->transform.GetUp(), 
        Plane2->transform.GetForward());

    audioHandler.AddPolygonToManagerWithRotation(1, 1, true, 
        Plane3->meshes[0].vertices,
        Plane3->transform.position,
        Plane3->transform.scale,
        Plane3->transform.GetUp(), 
        Plane3->transform.GetForward());

    audioHandler.AddPolygonToManagerWithRotation(1, 1, true, 
        Plane4->meshes[0].vertices, 
        Plane4->transform.position, 
        Plane4->transform.scale,
        Plane4->transform.GetUp(), 
        Plane4->transform.GetForward());

    audioHandler.AddPolygonToManagerWithRotation(1, 1, true, 
        Plane5->meshes[0].vertices,
        Plane5->transform.position,
        Plane5->transform.scale,
        Plane5->transform.GetUp(),
        Plane5->transform.GetForward());

    audioHandler.AddPolygonToManagerWithRotation(1, 1, true,
        Plane6->meshes[0].vertices,
        Plane6->transform.position, 
        Plane6->transform.scale,
        Plane6->transform.GetUp(), 
        Plane6->transform.GetForward());

#pragma endregion

}

void ApplicationRenderer::PreRender()
{
   
    audioHandler.UpdateListenerPosition(camera.Position, -camera.Front, camera.Up, -1.0f);

    audioHandler.UpdatePositionOnChannel(*Tv_Sound, Sphere->transform.position);
    audioHandler.UpdatePositionOnChannel(*doorBell_Sound, Sphere2->transform.position);
   
  
    if (glm::distance(ambulance->transform.position, glm::vec3(-20, 0.5f,1))>0.5f && isActivateSiren)
    {
        Sphere3->transform.position.x -= 0.5f * deltaTime;
        ambulance->transform.position.x -= 0.5f * deltaTime;
        audioHandler.UpdatePositionOnChannel(*siren_Sound, Sphere3->transform.position, glm::vec3(100,0,0));
    }


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
             audioHandler.PlayAudio(*doorBell_Sound);
             audioHandler.SetVolume(*doorBell_Sound, doorBell_Sound->volume);
             float chorusMix = 500;
             float chorusRate = 0.9f;
             float chorusDepth = 7;
             audioHandler.SetDSPBasedOnType(doorBell_Sound->audioPath.c_str(), DSPType::CHORUS, chorusMix, chorusRate, chorusDepth);
         }
         if (key == GLFW_KEY_B && action == GLFW_PRESS)
         {
             if (!audioHandler.audioManager->IsChannelPlaying(siren_Sound->audioPath.c_str()))
             {
                 audioHandler.PlayAudio(*siren_Sound);
                 audioHandler.SetVolume(*siren_Sound, siren_Sound->volume);
                 isActivateSiren = !isActivateSiren;
             }
           
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
