# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?

   A directed graph is one in which each edge has a specific direction. It goes from one vertex to another in a one way direction. A goes to B but B does not go to A. This is useful for weblinks and designing one way streets. An undirected graph has edges without direction. A connection between A and B implies A goes to B and B also goes to A. These are often used to represent mutual relationships like friendships or bidirectional roads.

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   * Assuming you used a heap / priority queue to store the vertices.

   Dijkstra’s algorithm, which is used to find the shortest path in weighted graphs, has different time complexities depending on how vertices are stored. If an array is used, the algorithm runs in O(V^2) time because finding the minimum distance vertex requires scanning all vertices each time. If a heap or priority queue is used, the complexity improves to O((V + E) log V), since insertions and extractions are more efficient. [1]

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 

   For larger graphs, the choice of data structure has a big impact on performance. If you use a simple array time grows quickly as the number of vertices increases. For very large graphs, this approach becomes inefficient because each step requires scanning all vertices to find the next smallest distance. By contrast, using a heap or priority queue reduces the complexity. So when the graph has thousands or millions of nodes and edges, the algorithm can still find shortest paths in a reasonable time. In practice, for large and sparse graphs, the priority queue version is essential because it avoids the heavy cost of repeatedly scanning the entire vertex list.

## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

   For something as large as Google or Apple Maps, I think an adjacency list would probably be better than an adjacency matrix since road networks are sparse and you don’t want to waste space storing nonexistent connections. At the same time, storing the entire world’s graph at once doesn’t seem realistic, so breaking it into smaller regions that load only when needed feels more manageable and closer to how map services actually work. Within those smaller regions, efficient structures like heaps or priority queues could make shortest path searches faster, while caching or saving popular routes would help avoid recalculating the same paths repeatedly. I also wonder if precomputing certain common connections, like between major cities or highways, could give an extra boost, since those are requested more often.


## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops? 

      6! = 720 possible paths

   * How many possible paths are there if you have 10 stops?

      10! = 3,628,800 possible paths

6. What type of growth is this problem? 

   Factorial!

7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it?
   
   The Traveling Salesperson Problem is classified as an NP-hard problem in combinatorial optimization. This means that, as the number of stops increases, the problem becomes computationally infeasible to solve exactly with any known polynomial-time algorithm. The decision version of TSP (asking whether there exists a tour shorter than a given length) is NP-complete, which places it among the hardest problems in computer science. [2]

8. Provide some examples of fields / problems that use TSP.

   The Traveling Salesperson Problem shows up in many fields where efficiency matters. In logistics and transportation, it models delivery routes for trucks or couriers who need to visit multiple stops while minimizing distance or fuel. In telecommunications and networking, it helps design efficient wiring layouts or routing paths. Biology applies it to DNA sequencing by finding the shortest way to connect genetic fragments. [2]



> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

Explain the difference between BFS and DFS. What are some applications of each?

   Breadth First Search and Depth Firth Search are two ways to explore graphs. BFS uses a queue to visit nodes level by level, making it useful for shortest paths in unweighted graphs or level order traversal. DFS uses recursion or a stack to go deep along one path before backtracking, which helps in finding all possible paths. BFS is often applied in social networks to find the shortest connection between people and in web crawlers to explore sites layer by layer. DFS, is used for solving puzzles or mazes and identifying connected components in networks or images.


2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 

[containsDuplicate.c](containsDuplicate.c)


## References

1. GeeksforGeeks. 2025. Time and Space Complexity of Dijkstra’s Algorithm. (July 23, 2025). Retrieved November 15, 2025 from https://www.geeksforgeeks.org/dsa/time-and-space-complexity-of-dijkstras-algorithm/

2. Wikipedia. 2025. Travelling salesman problem. (October 15, 2025). Retrieved November 15, 2025 from https://en.wikipedia.org/wiki/Travelling_salesman_problem
