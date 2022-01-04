## Functionalities

    - After running the application, the user will first have to select a region to operate in among the possible options. After that, the application will go on to download the map for that region from the OpenStreetMap API and save all the nodes and the distances between them as a complete undirected graph. Later, the user will be able to upload the orders (to be delievered) and the inventories they have either with geolocations or addresses as a csv file and they will be able to change and delete the orders within the application. Later, when they are done, they will be able to call the optimization library in order to calculate the best way to deliver the packages across the region.

## Deadlines and deliverables

    We are setting deliverables on Trello for each team member every week to make sure we all have some work to do. Here is a rough sketch of the goals we have for each team:

### 22nd of November

    - Front-End Design: Have a mock application design which is ready to include the functionalities of the core library as well as the interface and the parsing team.

    - Interface and Parsing: Have the code to be able to download different regions of France as a `.pbf` file and parse the map into our graph object.

    - Core Algorithms: Complete the main data structures and the Christofides's Approximation Algorithm for the Travelling Salesman Problem in order to solve the subproblem with 1 inventory. 

## Software Architecture

    We divide the software architecture into three main categories, which is the same with how the teams are divided: core algorithms, interface and parsing, front-end design. The front-end design team is using the QT tools to design the application and its basic front-end capabilities. The interface and parsing team is working on multithreading to make sure the application runs smoothly as well as external communication with APIs in order to enable map based features. 

 ## External Dependencies


