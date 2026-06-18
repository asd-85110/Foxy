/*
Note: This license has also been called the “New BSD License” or “Modified BSD License”. See also the 2-clause BSD License.

Copyright 2026-2028 asd-85110

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include<imconfig.h>
#include<imgui.h>
#include<imgui_impl_opengl3.h>
#include<imgui_impl_opengl3_loader.h>
#include<imgui_impl_glfw.h>
#include<GLFW/glfw3.h>
#include<imgui_internal.h>
#include<imstb_rectpack.h>
#include<imstb_textedit.h>
#include<imstb_truetype.h>
#include"include/tools.hpp"
#include<libintl.h>
#include<clocale>
int main(void){
    setlocale(LC_ALL, "");
    bindtextdomain("modifier", "../locale");
    bind_textdomain_codeset("modifier", "UTF-8");
    textdomain("modifier");
    if(!glfwInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    GLFWwindow* window = glfwCreateWindow(800, 450, gettext("Foxy Modifier"), NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }
    int width=16, height=16;
    GLFWimage* icon = Tools::load_png("../res/Modifier.png", &width, &height);
    if(icon){
        glfwSetWindowIcon(window, 1, icon);
        free(icon->pixels);
        delete icon;
    }else{
        delete icon;
        return -1;
    }
    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    glfwSwapInterval(1);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = "../ModifierImGuiConfigure.ini";
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("../res/Font/SourceHanSansHWSC-Bold.otf", 15.0f,nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 3.0f;
    style.WindowRounding = 5.0f;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin(gettext("LICENSE window"));
            ImGui::Text("LICENSE:BSD 3-Clause License");
            ImGui::Text("Copyright (c) 2026~2028, asd-85110");
        ImGui::End();
        ImGui::Begin(gettext("Modifier Window"));
            if(ImGui::InputInt(gettext("Health"),&Tools::Values[0])){}
            ImGui::SameLine();
            if(ImGui::Button(gettext("Set health"),ImVec2(60,20))){}
            if(ImGui::InputInt(gettext("Speed"),&Tools::Values[1])){}
            ImGui::SameLine();
            if(ImGui::Button(gettext("Set speed"),ImVec2(60,20))){}
            if(ImGui::InputInt(gettext("Damge"),&Tools::Values[2])){}
            ImGui::SameLine();
            if(ImGui::Button(gettext("Set damge"),ImVec2(60,20))){}
            if(ImGui::InputInt(gettext("XP"),&Tools::Values[3])){}
            ImGui::SameLine();
            if(ImGui::Button(gettext("Set XP"),ImVec2(60,20))){}
        ImGui::End();
        ImGui::Begin(gettext("Count Window"));
        ImGui::End();
        ImGui::EndFrame();
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}