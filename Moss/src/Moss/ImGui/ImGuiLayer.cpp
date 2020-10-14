

#include "mspch.h"
#include "ImGuiLayer.h"

#include "../Application.h"

#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Moss {

	ImGuiLayer::ImGuiLayer() 
			: Layer("ImGuiLayer"){

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {

		//从imgui_impl_opengl3中的main复制

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate() {

	
		/*

		//改写到begin
		//在这之前设置size
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//middle 用户自己控制什么时候显示
		static bool show = true;
		ImGui::ShowDemoWindow(&show);


		//改写到end
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		*/
	}


	//begin a new frame
	void ImGuiLayer::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {

	}

	//void ImGuiLayer::OnEvent(Event& e) {

	//	EventDispatch dispatcher(e);
	//	dispatcher.Dispatch<MouseButtonPressedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
	//	dispatcher.Dispatch<MouseButtonReleasedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
	//	dispatcher.Dispatch<MosueMovedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnMosueMovedEvent));
	//	dispatcher.Dispatch<MouseScrolledEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
	//	dispatcher.Dispatch<KeyPressedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
	//	dispatcher.Dispatch<KeyReleasedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
	//	dispatcher.Dispatch<KeyReleasedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
	//	dispatcher.Dispatch<KeyTypedEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	//	dispatcher.Dispatch<WindowResizeEvent>(MS_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

	//}

	//bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[e.GetMouseButton()] = true; //参考imgui的glfw版本示例
	//	return false;
	//}

	//bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[e.GetMouseButton()] = false;
	//	return false;
	//}

	//bool ImGuiLayer::OnMosueMovedEvent(MosueMovedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MousePos = ImVec2(e.GetX(), e.GetY());
	//	return false;
	//}

	//bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseWheelH += e.GetXOffset();
	//	io.MouseWheel += e.GetYOffset();

	//	return false;
	//}

	//bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.KeysDown[e.GetKeyCode()] = true;
	//	
	//	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT];
	//	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	//	return false;
	//}

	//bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.KeysDown[e.GetKeyCode()] = false;

	//	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT];
	//	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	//	return false;
	//}

	//bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent & e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddInputCharacter(e.GetKeyCode());
	//	return false;
	//}

	//bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	//	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	//	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	//	return false;
	//}


	//void ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e){}
	//void ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e){}
	//void ImGuiLayer::OnMosueMovedEvent(MosueMovedEvent& e){}
	//void ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e){}
	//void ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e){}
	//void ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e){}
	//void ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e){}
	//bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e){}
}