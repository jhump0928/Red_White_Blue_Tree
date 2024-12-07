This document gives important information about how to use our Red Black Tree visualization, and also outlines
some of the constraints in our tree.

As you can see when you run the program, the tree begins as empty, with three icons in the top left corner - "I Insert",
"R Remove", and "F Find". Pressing one of these keys allows you to enter input for that operation. To confirm a number
you inputted, simply press 'c', and the operation will be performed with that number. To backspace, press 'x', and to
completely exit from an operation, backspace until the entry box is empty, and press 'c' for confirm. To clear the tree,
press 'k'. And finally, to exit SDL Plotter, simply hit 'esc'.

Some of the restrictions on our tree include:
- The maximum displayable height of our tree is 6 levels, supporting a maximum of 61 nodes in a perfect binary tree.
  You are still able to observe all tree operations/coloring with this tree size.
- The numbers available for insertion, deletion, and find are 0-99. Likewise, all tree operations are observable with
  this limited data set.