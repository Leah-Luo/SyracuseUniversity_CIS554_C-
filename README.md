# CIS554 Objected Oriented Programming in C++


## Course Objectives
<ol>
	<li>Review the classical software design concepts of the functional decomposition. </li>
	<li>Subsequently learn object-oriented design concepts.</li>
	<li>Be able to design from a functional decomposition perspective.</li>
	<li>Be able to develop similar object oriented designs in C++.</li>
	<li>Be able to compare and contrast different design methodologies and languages.</li>
</ol>

## Topics Covered in Course
- Survey of basic C constructs.
- Operator overloading.
- Standard Template Library (STL) - Array, List, Vector, Map, Stack, Queue.
- Copy constructor, destructor, deep and shallow copying.
- L-value, R-value, move constructor.
- Template.
- Smart pointer, weak pointer, shared pointer.
- Functor, function pointer
- Lambda expression.
- Hash table.
- Static_cast, dynamic_cast, const_cast.
- Inheritance.

## Assignments
<ol>
	<li>HW1. Implement doubly linked list, group all occurrences of the same number together according to the order of appearance.</li>
	<li>Design and implement two member functions using recursion. Loop structures are not allowed, and in-place implementation is required.
		<ol>
			<li>Func1. Re-structure the subtree rooted at a node pointed by a pointer such that at every node, value(left_child) >= value(right_child) >= value(parent). </li>
			<li>Func2. Re-structure the subtree rooted at a node pointed by a pointer such that at every node, value(parent) <= value(left_child) <= value(right_child). In addition, for every subtree, the largest value should be at the bottom right node of the subtree.</li>
		</ol>
	</li>
	<li>Implement STLs & overload operators. Implement the following functions.
		<ol>
			<li>When adding a student, if the student is already in DB, then ignore the operation. </li>
			<li>When adding a course, if the course is already in DB, then ignore the operation.</li>
			<li>When dropping a course, if the course does not exist, then ignore the operation.</li>
			<li>When removing a student, if the student does not exist, then ignore the operation.</li>
			<li>All courses in a semester need to be sorted.</li>
			<li>When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.</li>
		</ol>
	</li>
	<li>Define a class (Ring2D) as generic type. Implement Copy & Move constructors, L & R values and initializer_list.</li>
	<li>Implement comparison functions used in sorting the list elements using regular function, functor, and lambda.</li>
	<li>Implement the member functions using smart pointer, shared pointer, and weak pointer.</li>
	<li>Hash table implementation.</li>
</ol>

## Exam Question
- Design a H-layout binary tree containing 2n-1 nodes (n is number levels in the BT).