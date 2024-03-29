#include"ApplicationRenderer.h"


ApplicationRenderer::ApplicationRenderer()
{
    camera = new Camera();
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



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
   
   

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 2.0f;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Query and print OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else 
    {
        std::cerr << "Failed to retrieve OpenGL version\n";
     
    }


    FrameBufferSpecification specification;

    specification.width = windowWidth;
    specification.height = WindowHeight;

    frameBuffer = new FrameBuffer(specification);

    EditorLayout::GetInstance().applicationRenderer = this;
  
    defaultShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag");
    solidColorShader = new Shader("Shaders/SolidColor_Vertex.vert", "Shaders/SolidColor_Fragment.frag", SOLID);
    stencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag", OPAQUE);
   
    alphaBlendShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_BLEND);
    alphaBlendShader->blendMode = ALPHA_BLEND;

    alphaCutoutShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_CUTOUT);
    alphaCutoutShader->blendMode = ALPHA_CUTOUT;

    skyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");
    skyboxShader->modelUniform = false;

    GraphicsRender::GetInstance().defaultShader = defaultShader;
    GraphicsRender::GetInstance().solidColorShader = solidColorShader;

    DebugModels::GetInstance().defaultCube = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    DebugModels::GetInstance().defaultSphere = new Model("Models/DefaultSphere/DefaultSphere.fbx", false, true);

    Model* skyBoxMod = new Model("Models/DefaultCube/DefaultCube.fbx",false, true);

    skyBoxMod->meshes[0]->meshMaterial = new SkyboxMaterial();

    SkyboxMaterial* _skyBoxMaterial = skyBoxMod->meshes[0]->meshMaterial->skyboxMaterial();

    std::vector<std::string> faces
    {
       ("Textures/skybox/right.jpg"),
       ("Textures/skybox/left.jpg"),
       ("Textures/skybox/top.jpg"),
       ("Textures/skybox/bottom.jpg"),
       ("Textures/skybox/front.jpg"),
       ("Textures/skybox/back.jpg")
    };
    _skyBoxMaterial->skyBoxTexture->LoadTexture(faces);

    GraphicsRender::GetInstance().SkyBoxModel = skyBoxMod;
   // render.AddModelsAndShader(render.SkyBoxModel, SkyboxShader);

    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");
    GraphicsRender::GetInstance().AssignStencilShader(stencilShader);
    GraphicsRender::GetInstance().AssignCamera(camera);
  //  camera->SetCameraType(ORTHOGRAPHIC);
   // camera->SetProjection();

    camera->IntializeCamera();
 //   camera->transform.position = glm::vec3(0, 0, - 1.0f);

    isImguiPanelsEnable = true;

    GraphicsInitialize();
}

void ApplicationRenderer::GraphicsInitialize()
{
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glDepthFunc(GL_LESS));
    GLCALL(glEnable(GL_STENCIL_TEST));
    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}



void ApplicationRenderer::Start()
{
   // Model* PlayerBall = new Model(*DebugModels::GetInstance().defaultCube);
   // PlayerBall->transform.SetPosition(glm::vec3(0, 5, 5));
   // GraphicsRender::GetInstance().AddModelAndShader(PlayerBall, defaultShader);



    GameComponents();

   


     Light* directionLight = new Light();
     directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
     directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

     directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
     directionLight->SetAttenuation(1, 1, 0.01f);
     directionLight->SetInnerAndOuterCutoffAngle(11, 12);

     directionLight->transform.SetRotation(glm::vec3(-24.5f, -24, 5));
     directionLight->transform.SetPosition(glm::vec3(0, 0, 5));
     directionLight->isVisible = false;

    

     Model* roadFloor = new Model("Models/Road/Road_Crossroads_1.fbx");
    // roadFloor->transform.SetPosition(glm::vec3(0, -2.60f, 0));
     roadFloor->transform.SetScale(glm::vec3(5));
     roadFloor->name = "Floor";
     roadFloor->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0.5f, 0.75f, 0.5f, 1));
     GraphicsRender::GetInstance().AddModelAndShader(roadFloor, defaultShader);

   // Model* bus = new Model("Models/Zombie/zombies.obj");
   // GraphicsRender::GetInstance().AddModelAndShader(bus, defaultShader);
   // bus->transform.LookAt(playerController->transform);



}

void ApplicationRenderer::GameComponents()
{
    playerController = new PlayerController();
    playerController->SetCamera(camera);

    thirdpersonCamera = new ThirdPersonCameraController(playerController);
    thirdpersonCamera->IntializeCamera();
    thirdpersonCamera->SetCamera(camera);
    //   thirdpersonCamera->SetPlayer(&PlayerBall->transform);

    EnemyObject* enemy1 = new EnemyObject();
    enemy1->name = "Enemy 1";
    enemy1->SetEnemyState(EnemyBehaviourType::NONE);
    enemy1->SetEnemyPosition(glm::vec3(11.90, 0, 0));
    enemy1->SetTarget(&playerController->transform);

    EnemyObject* enemy2 = new EnemyObject();
    enemy2->name = "Enemy 2";
    enemy2->SetEnemyState(EnemyBehaviourType::FLEE);
    enemy2->SetEnemyPosition(glm::vec3(5.80f, 0, -8));
    enemy2->SetTarget(&playerController->transform);

    EnemyObject* enemy3 = new EnemyObject();
    enemy3->name = "Enemy 3";
    enemy3->SetEnemyState(EnemyBehaviourType::SEEK);
    enemy3->SetEnemyPosition(glm::vec3(-32.0f, 0, -8));
    enemy3->SetTarget(&playerController->transform);


    EnemyObject* enemy4 = new EnemyObject();
    enemy4->name = "Enemy 4";
    enemy4->SetEnemyState(EnemyBehaviourType::PURSUE);
    enemy4->SetEnemyPosition(glm::vec3(-6.20f, 0, -8));
    enemy4->SetTarget(&playerController->transform);


    EnemyObject* enemy5 = new EnemyObject();
    enemy5->name = "Enemy 5";
    enemy5->SetEnemyState(EnemyBehaviourType::EVADE);
    enemy5->SetEnemyPosition(glm::vec3(31.90f, 0, -8));
    enemy5->SetTarget(&playerController->transform);


    EnemyObject* enemy6 = new EnemyObject();
    enemy6->name = "Enemy 6";
    enemy6->SetEnemyState(EnemyBehaviourType::APPROACH);
    enemy6->SetEnemyPosition(glm::vec3(-18.90f, 0, -8));
    enemy6->SetTarget(&playerController->transform);
}

void ApplicationRenderer::PreRender()
{
    glm::mat4 _projection = camera->GetProjectionMatrix();
    glm::mat4 _view = camera->GetViewMatrix();
    glm::mat4 _skyboxview = glm::mat4(glm::mat3(camera->GetViewMatrix()));
  


   // defaultShader->Bind();
    // material.SetMaterialProperties(*defaultShader);
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultShader);
    //  lightManager.UpdateUniformValues(defaultShader->ID);


    defaultShader->setMat4("projection", _projection);
    defaultShader->setMat4("view", _view);
    defaultShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    alphaBlendShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaBlendShader);
    alphaBlendShader->setMat4("projection", _projection);
    alphaBlendShader->setMat4("view", _view);
    alphaBlendShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", false);

    alphaCutoutShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaCutoutShader);
    alphaCutoutShader->setMat4("projection", _projection);
    alphaCutoutShader->setMat4("view", _view);
    alphaCutoutShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", false);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", _projection);
    solidColorShader->setMat4("view", _view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", _projection);
    stencilShader->setMat4("view", _view);

    glDepthFunc(GL_LEQUAL);
    skyboxShader->Bind();
    skyboxShader->setMat4("projection", _projection);
    skyboxShader->setMat4("view", _skyboxview);

    GraphicsRender::GetInstance().SkyBoxModel->Draw
    (*skyboxShader);
    glDepthFunc(GL_LESS);


    /* ScrollShader->Bind();
       ScrollShader->setMat4("ProjectionMatrix", _projection);*/

}

void ApplicationRenderer::Render()
{
   
    Start();
  
    EditorLayout::GetInstance().InitializeEditors();

    Time::GetInstance().lastFrame = glfwGetTime();
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    while (!glfwWindowShouldClose(window))
    {

        Time::GetInstance().SetCurrentTime(glfwGetTime());

       
      
        scrollTime += Time::GetInstance().deltaTime;

        ProcessInput(window);
    
        // Imgui

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        frameBuffer->Bind();

        if (isImguiPanelsEnable)
        {
            PanelManager::GetInstance().Update((float)windowWidth, (float)WindowHeight);
        }

        ImGui::Render();

        Clear();

        PreRender(); //Update call BEFORE  DRAW
        
         // make models that it should not write in the stencil buffer
       
        if (isPlayMode)
        {
            EntityManager::GetInstance().Update(Time::GetInstance().deltaTime);
        }
       

         GraphicsRender::GetInstance().Draw();
         PostRender(); // Update Call AFTER  DRAW
        frameBuffer->Unbind();

         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ApplicationRenderer::PostRender()
{
   // glDisable(GL_BLEND);

 //   PhysicsEngine.UpdatePhysics(deltaTime);
}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
   //glStencilMask(0x00);
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed=25;
    if (isPlayMode)
    {
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(FORWARD, Time::GetInstance().deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(BACKWARD, Time::GetInstance().deltaTime * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(LEFT, Time::GetInstance().deltaTime * cameraSpeed);

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(RIGHT, Time::GetInstance().deltaTime * cameraSpeed);

    }
    
   // InputManager::GetInstance().UpdateMousePosition(window);

}

 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {

            
             std::cout << "V pressed" << std::endl;

             std::vector<Model*> listOfModels = GraphicsRender::GetInstance().GetModelList();
            
          

             selectedModelCount++;

             if (selectedModelCount > listOfModels.size()-1)
             {
                 selectedModelCount = 0;
             }

            
             GraphicsRender::GetInstance().selectedModel = listOfModels[selectedModelCount];


         }

         if (action == GLFW_PRESS)
         {
             playerController->OnKeyPressed(key);
         }
         else if (action == GLFW_RELEASE)
         {
             playerController->OnKeyReleased(key);
         }
         else if(action == GLFW_REPEAT)
         {
             playerController->OnKeyHold(key);
         }
     
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     

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
     
         if (!EditorLayout::GetInstance().IsViewPortHovered())
         {
             return;
         }
         InputManager::GetInstance().OnMouseMove(window, xposIn, yposIn);

         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
         {
             if (!isPlayMode)
             {
                 camera->ProcessMouseMovement(xoffset, yoffset);
             }
         
            
         }
        

 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     camera->ProcessMouseScroll(static_cast<float>(yoffset));
 }
