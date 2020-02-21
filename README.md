<img src="image/main.jpg" align="middle" width="3000"/>

# c++ Marble Crash Game (Beta)

**c++ Marble Crash Game** (Marble Crash Game) is an puzzle game Which received the idea from Puyo Puyo Tertis game. I created a game with retro graphic style and simple operation as a part of a computer graphic at University. One of the main goals of this project is understanding to process of creating game. We use many OpenGl libraries in this project that you can see in the "Requirement". We recommend to use visual studio to run this project.
<br/>


<br/>
I developed this game by visual studio 2019(https://visualstudio.microsoft.com/) that is one of IDE(Integrated Development Environment). The source code is in this repository.

**Feature**
<br/>
Object Transformation
<br/>
Keyboard Event


**Requirement**
<br/>
- Visual Studio(https://visualstudio.microsoft.com/)
<br/>
- freeglut(OpenGL library)
<br/>
- SOIL(OpenGL library)
<br/>

**Setup**
<br/>
- setup freeglut in Visual Studio(https://www.wikihow.com/Set-Up-an-OpenGL-FreeGLUT-GLEW-Template-Project-in-Visual-Studio)
<br/>
- setup SOIL in Visual Studio(https://github.com/Friduric/simple-opengl-image-library)
<br/>



**Process of game**

<br/>
1) Marble dropped from upper to bottom .
<br/>
<img src="image/how1.jpg" align="middle" width="500"/>
<br/>
2) When time count to Demon time, it adds  Gray Marble. 
<br/>
<img src="image/how2.jpg" align="middle" width="500"/>
<br/>
<br/>
<img src="image/gray.jpg" align="middle" width="500"/>
<br/>
** Gray Marble was created only this event.
<br/>
<br/>
3) If same color Marbles was next to each other, it will delete those Marbles.
(Gray Marble will be missing after Surrounded by color Marble)
<br/>
<img src="image/how4.jpg" align="middle" width="500"/>
<br/>
- When point over 100, you win.
<br/>
<img src="image/win.jpg" align="middle" width="500"/>
<br/>
- When Marble pile up over line, you lose.
<br/>
<img src="image/lose.jpg" align="middle" width="500"/>


**Running**
It have .exe file in this repository is in the Debug folder.  You can run the executable .exe file, named game3.exe to play.
