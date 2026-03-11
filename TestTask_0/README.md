# TestTask - 1

Test task implementation for OMP System. 

## Description

#### Create app that can:
1. #### create ellipse
1. #### create triangle
1. #### create rectangle
1. #### create line that connect objects (start end end of line is center of objects)
1. #### move objects (in real time)
1. #### open file
1. #### save file

## Requirements

* ### C++
* ### Visual Studio 2017
* ### OOP

# File format

Format of this files similar with object file

## Objects

Starts with **o** define symbol. Contains LeftTop and RightBottom points of object. The last value of object is simple integer, object type.
 > `o` LeftTop(x, y) RightBottom(x, y) type(t)

> `o x y x y t`  
