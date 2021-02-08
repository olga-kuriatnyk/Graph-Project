# Self-Evaluation

## Name(s): 

Out of 20 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes/No

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: ENTER_NUMBER

- -1 for each public function not implemented
- Constructors:  Graph()
- Destructor: ~Graph()
- Helpers: contains, verticesSize, edgesSize, vertexDegree, getEdgesAsString
- Modifiers: add, connect, disconnect, readFile
- Algorithms: dfs, bfs, dijkstra, mstPrim

Q: Bonus function - mstKruskal: ENTER_NUMBER

- +1 if Minimum Spanning Tree using Kruskal's algorithm has been implemented

Q: -1 for each compilation warning, min -3: ENTER_NUMBER

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: ENTER_NUMBER

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: ENTER_NUMBER

- Check under *4. clang-format does not find any formatting issues*

Q: Runs and produces correct output: ENTER_NUMBER

- Try running "./a.out". assert statement should test the code

Q: -2 for any detected memory leak: ENTER_NUMBER

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code, min -6: ENTER_NUMBER

- All public functions should be called at least once.
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documented (min -3): ENTER_NUMBER

- You need at least 1-line of comments
- -1 for each function not documented

Q: Total points: ADD_ALL_POINTS
