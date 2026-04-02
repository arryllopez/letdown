#pragma once

int getJX(); 
int getJY();
void pollPad();
void pollLatch();
int isKeyHold(int key);    
int isKeyDown(int key);
int isKeyUp(int key);