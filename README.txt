This project is the skeleton for what will become an efficient 2D sprite engine 
for rendering still scenes, animations, or games. For the purposes of the 
project, the code should render a simple scene with two sprites and a background
into a .ppm file, which is convertible to .png for viewing.

The code builds up the concept of a rendered 2D image from colors and color 
palettes to MetaSprites, backgrounds, and layers. They are implemented with 
the following features learned in class
- liberal use of templates where sizes of data structures should be known at 
    compile time
- use of a concept and type traits to define an integral type where useful
- use of variants + visit in dealing with differnt kinds of image formats with 
    incompatible file structures (namely PNG and BMP)
- use of ranges to make for loops across data easier to read
- use of abstract factory design pattern to create different kinds of 
    hard-coded graphics in code
