# Smart_Calc_MVC
My new and improved calculator which is now entirely written in C++ using a pattern MVC.
The calculator has the ability to calculate basic and trigonometric functions, build a graph, use of variable "x" and credit calculator.

## Pattern MVC

![MVC-Process](https://user-images.githubusercontent.com/88627479/186530391-58e5aba0-6a38-421d-b432-3fa798014847.png)

## The rules
1. If you have x in the expression, enter it on the line below.
![calc_example_x](https://user-images.githubusercontent.com/88627479/186529182-b18424e1-7d24-4ad4-a73d-67eef416dd28.gif)

2. When you enter "x" in the expression and press the "graph" button, a new window will open where you can plot
  the graph. You can choose the range (X min, X max) and the interval of axes (-X; X) and (-Y; Y) by entering a positive number X and Y for them. Use the "Draw" button to draw a graph.
![calc_example_graph](https://user-images.githubusercontent.com/88627479/186529359-56707e50-82d5-443d-953c-a4e09cbb496f.gif)

3. Since the calculator is smart it will not let you enter incorrect combinations in most cases. For example:
  2--3, sin(+), etc.

4. To use "mod" or "^" in the right-hand part, you must explicitly specify the unary sign with brackets. For example: 102mod(-100) or 3^(-2).

5. If you enter an expression incorrectly, you will be asked to enter the expression again. In some cases, the calculator can tell you exactly what you have entered wrong.

To remove the user program. Can use the make uninstall command
