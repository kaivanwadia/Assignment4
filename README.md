Class project for CS380C Compilers. Creating a pass for Dead Code Elimination and Loop Invariant Code Motion.

Mark Gray and Kaivan Wadia


Q. What is the direction of the dataflow analysis?
A. Bottom up

Q. What is the meet operator?
A. Intersection

Q. What are the lattice elements?
A. Top (Undefined), Bottom (Live), Faint

Q. What are the values of top and bottom?
A. Top is undefined and Bottom is Live

Q. How do you initialize the iterative algorithm?
A. Universal Set

Q. Are dataflow facts required at BB level or instruction level?
A. Basic block.

Q. What should you do if your analysis works on a different level?
A. Have the map do something different.

Q. What are the transfer functions ?
A. 	If Terminator Instruction then add RHS to Kill Set
	If LHS is not in Faint Set or is in Kill Set then add RHS to Kill Set
	IN = (OUT - KILL) + GEN