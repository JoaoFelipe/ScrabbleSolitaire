

Errors and Warnings:
We forgot to copy the errors so we will explain what was the errors and how we fixed it:

warning C4018: '<' : signed/unsigned mismatch : This warning occurred a lot of times and we fixed it by type casting
An error ocurred with the pdb file when the project was converted from VS2010 into VS2012. We fixed it by deleting it 
Another error ocurred when we tried to debug the project. It said that the pdb file was missing. We fixed by running the Visual Studio as Administrator
A runtime error ocurred with the variable score that was being declared, but not initialized and used. We fixed it by initializating its value to 0
A runtime error ocurred when we deleted a wrong position that was being used after the delete statement. We fixed it by moving the position of the delete statement.
An error ocurred when we checked if the position played intersected the current word. We forgot to update the current position, so it wasn't checking right 

