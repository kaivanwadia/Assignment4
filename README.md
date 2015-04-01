Class project for CS380C Compilers. Creating a pass for Dead Code Elimination and Loop Invariant Code Motion.

Mark Gray and Kaivan Wadia


Q. What is the direction of the dataflow analysis?
A. Bottom up

Q. What is the meet operator?
A. Union (A special union taking into consideration phi nodes)

Q. What are the lattice elements?
A. Top, Bottom, Live and Faint

Q. What are the values of top and bottom?
A. 

Q. How do you initialize the iterative algorithm?
A. Empty Set

Q. Are dataflow facts required at BB level or instruction level?
A. Basic block.

Q. What should you do if your analysis works on a different level?
A. Have the map do something different

Q. What are the transfer functions ?
A. This is the question!


Pair structure : 

If TerminatorInst and ReturnInst then rhs is live
If LHS is faint then rhs is faint
If LHS is live then rhs is live

Every LHS is added to kill