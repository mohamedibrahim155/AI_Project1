#include "SceneViewportPanel.h"

void SceneViewportPanel::OnRender(float windowWidth, float windowHeight)
{
   // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("SceneView", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
      //  ImGui::PopStyleVar();
        return;

    }


    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    if (viewportSize.x!= viewPortPanelSize.x ||viewportSize.y !=viewPortPanelSize.y)
    {
        viewportSize = viewPortPanelSize;

        frameBuffer->Resize((uint32_t)viewPortPanelSize.x, (uint32_t)viewPortPanelSize.y);
        //sceneViewportCamera->Resize(viewPortPanelSize.x, viewPortPanelSize.y);
    }

   // ImVec2 imageSize = ImVec2(windowWidth, windowHeight);
    ImGui::Image((void*)frameBuffer->GetColorAttachmentID(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();



}
