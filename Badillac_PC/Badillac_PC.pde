//Program by Jeremy Blum
//www.jeremyblum.com
//Give you the temperature

import processing.serial.*;
Serial port;
String line1 = "";
String line2 = "";
String line3 = "";
String data = "";
int index = 0;
int index2 = 0;
PFont font;

void setup()
{
  size(600,400);
  port = new Serial(this, "COM3", 9600);
  port.bufferUntil('.'); 
  font = loadFont("ArialMT-48.vlw");
  textFont(font, 32);
}

void draw()
{
  background(0,0,0);
  fill(46, 209, 2);
  text(line1, 30, 75);
  fill(0, 102, 153);
  text(line2, 30, 100);
  fill(46, 209, 2);
  text(line3, 30, 125);
}
  
void serialEvent (Serial port)
{
  data = port.readStringUntil('.');
  data = data.substring(0, data.length() - 1);
  
  // look for the comma between line1 and line 2
  index = data.indexOf(",");
  index2 = data.indexOf("|");
  // fetch the first line
  line1 = data.substring(0, index);
  // fetch the 2nd line
  line2 = data.substring(index+1, index2);
  
  
  line3 = data.substring(index2+1, data.length());
  
}
