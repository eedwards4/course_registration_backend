<h1>Course Registration Backend</h1>
Created by Ethan Edwards on 11/1/2023

Simulated backend for a course registration system.

<h2>Commands:</h2>

All commands are proceeded with the name of the program (prerequisite.x)

<ul>
  <li><b>-cyclic [filename]</b> : Determines if the file contains a cycle</li>
  <li><b>-print [filename]</b> : Prints the Key/Value pairs for all objects in the file</li>
  <li><b>-includes [object] [filename]</b> : Outputs whether or not an object is in the file</li>
  <li><b>-together [object 1] [object 2] [filename]</b> : Determines whether two courses can be taken simultaneously</li>
  <li><b>-allpairs [filename]</b> : Performs the -together check on all possible combinations in the file, excluding (n, n) combinations</li>
  <li><b>-chains [object] [filename]</b> : Prints the list of prerequisite chains for the object</li>
  <li><b>-length [object] [filename]</b> : Prints the length of the longest prerequisite chain for the object</li>
  <li><b>-longest [filename]</b> : Prints the longest prerequisite chain in the file</li>
  <li><b>-indegree  [object] [filename]</b> : Prints the number of objects that have the input object as a direct dependancy</li>
</ul>

<h2>Build instructions</h2>
To build: g++ -Wall -std=c++20 *.cpp -o prerequisite.x

To run: See commands list
