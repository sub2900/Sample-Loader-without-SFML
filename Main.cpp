#include <iostream>
#include <string>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <keyauth.h>
#include <GLFW/glfw3.h>

// Configuration variables
std::string name = "";
std::string ownerid = "";
std::string secret = "";
std::string version = "1.0";

// Function to handle login
bool login(const char* username, const char* password)
{
    // Call keyauth login API with provided credentials
    return keyauth::login(name, ownerid, secret, version, username, password);
}

// Function to handle user registration
bool register_user(const char* username, const char* password, const char* email)
{
    // Call keyauth register API with provided credentials
    return keyauth::register_user(name, ownerid, secret, version, username, password, email);
}

// Form for login
void login_form()
{
    static char username[128] = "";
    static char password[128] = "";
    static bool remember_me = false;

    ImGui::Text("Login");
    ImGui::InputText("Username", username, 128);
    ImGui::InputText("Password", password, 128, ImGuiInputTextFlags_Password);
    ImGui::Checkbox("Remember me", &remember_me);

    if (ImGui::Button("Login"))
    {
        if (login(username, password))
        {
            // Login successful, perform appropriate actions
            std::cout << "Login successful!" << std::endl;
        }
        else
        {
            // Login failed, show error message
            std::cout << "Login failed!" << std::endl;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Register"))
    {
        // Switch to register form
    }
}

// Form for user registration
void register_form()
{
    static char username[128] = "";
    static char password[128] = "";
    static char key[128] = "";

    ImGui::Text("Register");
    ImGui::InputText("Username", username, 128);
    ImGui::InputText("Password", password, 128, ImGuiInputTextFlags_Password);
    ImGui::InputText("Key", key, 128);

    if (ImGui::Button("Register"))
    {
        if (register_user(username, password, key))
        {
            // Registration successful, perform appropriate actions
            std::cout << "Registration successful!" << std::endl;
        }
        else
        {
            // Registration failed, show error message
            std::cout << "Registration failed!" << std::endl;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Back"))
    {
        // Switch to login form
    }
}

// Home page after successful login
void home_page()
{
    ImGui::Text("Welcome to the home page!");
}

// Main menu to switch between login and register forms
void main_menu()
{
    static bool show_login_form = true;
    static bool show_register_form = false;
    static bool logged_in = false;

    if (!logged_in)
    {
        if (show_login_form)
        {
            login_form();
        }
        else if (show_register_form)
        {
            register_form();
        }

        if (ImGui::Button("Switch to Register"))
        {
            show_login_form = false;
            show_register_form = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Switch to Login"))
        {
            show_login_form = true;
            show_register_form = false;
        }
    }
    else
    {
        home_page();
    }
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Login/Register/Home Form", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Set up ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        main_menu();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
