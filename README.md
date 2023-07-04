# Ingritofood-backend
Backend services for ingritofood 

![Backend](https://user-images.githubusercontent.com/72456774/208958257-c1440e8f-288d-4a2e-bddb-9899c951514e.png)

IngritoFood -> See what recipes can be made from the ingredients you have at hand. Made with ReactJS and C++ backend and a
TCP Server is written in C++ to communicate between the [front end](https://github.com/louremipsum/ingritofood) and the back end. Web-based virtual recipe book in which the user can append the ingredients they have on hand and the application parses through
thousands of recipe

📦 Backend Documentation
=====================

## Introduction💡

The backend of the application is responsible for handling the server-side operations, including communication with external APIs, processing client requests, and sending responses back to the client. This documentation provides an overview of the backend components, their functionality, and how they work together to deliver the required functionality.

## Project Structure 📂
The backend code is organized into several files:

1. `CMakeLists.txt`: The CMake configuration file for building the backend project.

2. `get_receipe_by_id.h`: A header file containing the `getRecipeById` class, which provides functionality to retrieve recipe information by its ID from the Spoonacular API.

3. `get_receipe_by_ingri.h`: A header file containing the `getRecipeByIngri` class, which provides functionality to retrieve recipe information by ingredients from the Spoonacular API.

4. `http_tcpserver.h`: A header file defining the `TcpServer` class, which implements a TCP server for handling client connections and processing HTTP requests.

5. `server.cpp`: The main entry point of the backend application, where the `TcpServer` instance is created and started.

6. `http_tcpServer.cpp`: The implementation file for the `TcpServer` class, which includes methods for starting the server, accepting connections, receiving and parsing client requests, and sending responses.

Documentation Details 📄
---------------------

1. `CMakeLists.txt`:
    - **Purpose**: This file is used by CMake to configure the build process for the backend project. It includes necessary dependencies, such as the `cpr` and `nlohmann_json` libraries, and sets up the build targets.
    - **Usage**: This file should be placed in the root directory of the backend project and used with CMake to generate build files for the project.

2. `get_receipe_by_id.h`:
    - **Purpose**: This header file defines the `getRecipeById` class, which encapsulates the functionality to retrieve recipe information by its ID from the Spoonacular API.
    - **Functionality**: The `getRecipeById` class provides a method `makeReq` that takes a recipe ID as input, constructs the API request URL, and performs a GET request to the Spoonacular API. It handles error cases and returns the response text.
    - **Usage**: To use this functionality, include the `get_receipe_by_id.h` header file in the desired source file and create an instance of the `getRecipeById` class. Call the `makeReq` method with the recipe ID to retrieve the recipe information.

3. `get_receipe_by_ingri.h`:
    - **Purpose**: This header file defines the `getRecipeByIngri` class, which provides functionality to retrieve recipe information by ingredients from the Spoonacular API.
    - **Functionality**: The `getRecipeByIngri` class includes a static method `makeReq` that takes a list of ingredients as input, constructs the API request URL, and performs a GET request to the Spoonacular API. It handles error cases and returns the response text.
    - **Usage**: To use this functionality, include the `get_receipe_by_ingri.h` header file in the desired source file. Call the static method `makeReq` of the `getRecipeByIngri` class, passing the list of ingredients as a parameter, to retrieve the recipe information.

4. `http_tcpserver.h`:
    - **Purpose**: This header file defines the `TcpServer` class, which implements a TCP server for handling client connections and processing HTTP requests.
    - **Functionality**: The `TcpServer` class includes methods for starting the server, accepting connections, receiving and parsing client requests, and sending responses. It uses the Winsock library for network communication.
    - **Usage**: To use this class, include the `http_tcpserver.h` header file in the desired source file. Create an instance of the `TcpServer` class, providing the IP address and port number to listen on. Call the `startListen` method to start the server and handle incoming client connections.

5. `server.cpp`:
    - **Purpose**: This file contains the main entry point of the backend application. It creates an instance of the `TcpServer` class and starts the server to listen for incoming client connections.
    - **Usage**: Compile and run this file to start the backend server. Make sure to include the necessary dependencies and configure the project build correctly.

6. `http_tcpServer.cpp`:
    - **Purpose**: This implementation file provides the implementation of the methods defined in the `TcpServer` class.
    - **Functionality**: The `TcpServer` class includes methods for starting the server, accepting connections, receiving and parsing client requests, and sending responses. The `buildResponse` method constructs the HTTP response based on the client request, and the `sendResponse` method sends the response back to the client.
    - **Usage**: This file is already included in the backend project. It is automatically compiled and linked when building the project.

## ⚙️Setup Guide(Experimental⚠️) 

1. Clone the Repository:
   - Open a terminal or command prompt.
   - Navigate to the directory where you want to clone the repository.
   - Run the following command to clone the repository:

     ```
     git clone https://github.com/louremipsum/ingritofood-backend.git
     ```

2. Install Dependencies:
   - Ensure that you have CMake installed on your system. If not, download and install it from the official CMake website (https://cmake.org/).
   - Navigate to the root directory of the cloned repository.
   - Create a build directory:

     ```
     mkdir build
     cd build
     ```

   - Run CMake to generate the build files:

     ```
     cmake ..
     ```

   - This will configure the build process based on the `CMakeLists.txt` file.

3. Build the Project:
   - After running CMake, you can now build the project.
   - Execute the following command:

     ```
     cmake --build .
     ```

   - This will build the backend project and generate the executable file.

4. Run the Backend Server:
   - Once the build process is complete, you can run the backend server.
   - Execute the following command:

     ```
     ./server
     ```

   - The server will start listening for incoming client connections.

5. Interact with the Backend:
   - With the backend server running, you can now interact with it.
   - Open a web browser or use an API testing tool (e.g., Postman) to send HTTP requests to the server's IP address and port number.
   - The server will receive the requests, process them, and send back appropriate responses.

## 🔗 API Endpoints

The backend server exposes the following API endpoints:

* `GET /recipe/{id}`: Retrieves a recipe by its ID.
* `GET /recipes?ingredients={ingredients}`: Retrieves recipes based on specified ingredients.

## 📥 Request Examples

Get Recipe by ID
```bash
GET /recipe/12345
```

Get Recipes by Ingredients
```bash
GET /recipes?ingredients=apple,banana
```
You can check it out in the frontend part too.

That's it! You have now set up the repository and run the backend server. You can start testing and integrating the backend with your application.

Conclusion
-----------
The backend of the application consists of several components working together to handle server-side operations. The `TcpServer` class acts as the server, processing client connections and HTTP requests. The `getRecipeById` and `getRecipeByIngri` classes provide the functionality to retrieve recipe information from the Spoonacular API based on recipe IDs and ingredients, respectively. By understanding the purpose, functionality, and usage of these components, you can effectively utilize and extend the backend to meet your application requirements.
