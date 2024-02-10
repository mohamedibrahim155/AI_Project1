#pragma once


#include "Renderer.h"
#include <iostream>

class InputManager 
{
public:
    // ... (other methods)

    static InputManager& GetInstance();
    // Mouse movement handling
    void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
    void UpdateMousePosition(GLFWwindow* window);

    // Mouse movement retrieval
      double GetMouseX();
      double GetMouseY();
      double offsetX, offsetY;

      void SetMouseDelta(glm::vec2 mouseDelta);
      glm::vec2& GetMouseDelta() { return mouseDelta; }

private:
    // Internal state to store mouse position
   double mouseX, mouseY;
   double lastMouseX=0, lastMouseY;
   bool firstMouse;
   

    double lastFrameX;

    glm::vec2  mouseDelta;;
};

