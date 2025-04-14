#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool threeRow(int board[3][3]) {
    bool row = false;
    // check horizontals
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] == board[i][2] && (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0)) {
            row = true;
        }
    }
    //check verticals
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] == board[2][i] && (board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0)) {
            row = true;
        }
    }
    //check diagonals
    if ((board[0][0] == board[1][1] == board[2][2] && (board[0][0] !=0 && board[1][1] !=0 && board[2][2]!=0))|| (board[0][2] == board[1][1] == board[2][0] && (board[0][2] !=0 && board[1][1] !=0 && board[2][0] != 0))) {
        row = true;
    }

    return row;
}
void printBoard(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                std::cout << ' ';
            } else if (board[i][j] == 1) {
                std::cout << "x";
            } else if (board[i][j] == 2) {
                std::cout << "o";
            }
            if (j != 2) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        std::cout << "----------" << std::endl;
    }
}
void text_based() {
    bool running = true;
    int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    bool xTurn = true;
    while (running) {
        int mark = 0;

        if (xTurn) {
            std::cout <<"it is X's turn\nPlease select where you would like to place your move in the format <x y>" <<std::endl;
            mark = 1;

        } else {
            std::cout <<"it is O's turn\nPlease select where you would like to place your move in the format <y x>" <<std::endl;
            mark = 2;
        }
        int x;
        int y;
        jump:
        std::cin >> x;
        std::cin >> y;
        if (x>3 || y>3 || x<=0 || y<=0) {
            std::cout << "Please ensure your moves are within bounds" <<std::endl;
            goto jump;
        }
        if (board[y-1][x-1] != 0) {
            std::cout << "This spot is already taken :|" << std::endl;
            goto jump;
        }
        board[y-1][x-1] = mark;
        printBoard(board);
        xTurn = !xTurn;
        running = !threeRow(board);
    }
    if (xTurn) {
        std::cout << "gg, X won"<<std::endl;
    }
    else {
        std::cout << "gg, Y won"<<std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {

    std::string move;
    std::cout << "Hello and welcome to Tic Tac Toe in C++" << "!\n";
    std::cout << "testing gui only \n" << std::endl;

    bool gui = true;
    if (gui) {

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        GLFWwindow* window = glfwCreateWindow(800, 600, "Tic Tac Toe in C++", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


        while(!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

    } else {
        text_based();
    }
    return 0;
}
