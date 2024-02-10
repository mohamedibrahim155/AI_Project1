#include "InputManager.h"



InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) 
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    mouseX = xpos;
    mouseY = ypos;

    // Calculate the mouse movement in both X and Y axes
    double xOffset = xpos - lastMouseX;
    double yOffset = lastMouseY - ypos;  // Reversed since y-coordinates go from bottom to top

    offsetX = xOffset;
    offsetY = yOffset;

    SetMouseDelta(glm::vec2(xOffset, yOffset));
    
    // Update last mouse position for the next frame
    lastMouseX = xpos;
    lastMouseY = ypos;
   

}

void InputManager::UpdateMousePosition(GLFWwindow* window)
{
   // glfwGetCursorPos(window, &lastMouseX, &lastMouseY);

   // double xOffset = lastMouseX - mouseX;
   // double yOffset = lastMouseY - mouseY;  

   // offsetX = xOffset;
   //  offsetY = yOffset;

   //  mouseX = glm::clamp((float)offsetX, -1.0f, 1.0f);

}

double InputManager::GetMouseX()
{
    return mouseX;
}

double InputManager::GetMouseY() {
    return mouseY;
}

void InputManager::SetMouseDelta(glm::vec2 mouseDelta)
{
    this->mouseDelta = mouseDelta;
}

