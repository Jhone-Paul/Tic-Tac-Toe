#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
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
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int gameBoard[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
bool xTurn = true;

void handleCellClick(float x, float y)
{
    int row = -1, col = -1;

    // Determine column (x coordinate)
    if (x < -0.33f)
        col = 0;
    else if (x < 0.33f)
        col = 1;
    else if (x <= 0.8f)
        col = 2;

    // Determine row (y coordinate)
    if (y < -0.33f)
        row = 2;
    else if (y < 0.33f)
        row = 1;
    else if (y <= 0.8f)
        row = 0;

    if (row >= 0 && row < 3 && col >= 0 && col < 3 && gameBoard[row][col] == 0)
    {
        // Place X or O based on whose turn it is
        gameBoard[row][col] = xTurn ? 1 : 2;
        xTurn = !xTurn;
        printBoard(gameBoard);
        // Check for win condition
        if (threeRow(gameBoard))
        {
            std::cout << "Game over! " << (xTurn ? "O" : "X") << " wins!" << std::endl;
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float x = (2.0f * xpos) / width - 1.0f;
        float y = 1.0f - (2.0f * ypos) / height;

        std::cout << x << " " << y << std::endl;
        handleCellClick(x, y);
    }
}
void drawO(int row, int col) {
    // Calculate the center of the cell
    float centerX = -0.56f + col * 0.56f;
    float centerY = 0.56f - row * 0.56f;
    float radius = 0.2f;
    int segments = 20;

    std::vector<float> circleVertices;

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);

        circleVertices.push_back(x);
        circleVertices.push_back(y);
        circleVertices.push_back(0.0f);
    }

    unsigned int oVBO, oVAO;
    glGenVertexArrays(1, &oVAO);
    glGenBuffers(1, &oVBO);

    glBindVertexArray(oVAO);
    glBindBuffer(GL_ARRAY_BUFFER, oVBO);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINE_LOOP, 0, segments + 1);

    glDeleteVertexArrays(1, &oVAO);
    glDeleteBuffers(1, &oVBO);
}
void drawX(int row, int col) {
    // Calculate the center of the cell
    float centerX = -0.56f + col * 0.56f;
    float centerY = 0.56f - row * 0.56f;
    float size = 0.2f;

    float xVertices[] = {
        centerX - size, centerY - size, 0.0f,
        centerX + size, centerY + size, 0.0f,

        centerX - size, centerY + size, 0.0f,
        centerX + size, centerY - size, 0.0f
    };

    unsigned int xVBO, xVAO;
    glGenVertexArrays(1, &xVAO);
    glGenBuffers(1, &xVBO);

    glBindVertexArray(xVAO);
    glBindBuffer(GL_ARRAY_BUFFER, xVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(xVertices), xVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, 2); // First diagonal
    glDrawArrays(GL_LINES, 2, 2); // Second diagonal

    glDeleteVertexArrays(1, &xVAO);
    glDeleteBuffers(1, &xVBO);
}
void drawTicTacToe(int board[3][3], unsigned int VAO, unsigned int shaderProgram ) {
    // First draw the grid lines
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    glDrawArrays(GL_LINES, 6, 2);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == 1) {
                drawX(row, col);
            } else if (board[row][col] == 2) {
                drawO(row, col);
            }
        }
    }
}
int main() {

    std::string move;
    std::cout << "Hello and welcome to Tic Tac Toe in C++" << "!\n";
    std::cout << "testing gui only \n" << std::endl;

    bool gui = true;
    if (gui) {

        float vertices[] = {
            -0.33f, -0.8f, 0.0f,
            -0.33f,  0.8f, 0.0f,

            0.33f, -0.8f, 0.0f,
            0.33f,  0.8f, 0.0f,

            -0.8f,  0.33f, 0.0f,
             0.8f,  0.33f, 0.0f,

            -0.8f, -0.33f, 0.0f,
             0.8f, -0.33f, 0.0f
        };



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

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);


        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // 2. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glfwSetMouseButtonCallback(window, mouse_button_callback);


        while(!glfwWindowShouldClose(window))
        {
            processInput(window);


            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            drawTicTacToe(gameBoard, VAO, shaderProgram);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

    } else {
        text_based();
    }
    return 0;
}
