#pragma once
#include<string>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>


char mainMenu();
char menuMessage();
std::string inputName();
std::string inputLogin();
std::string inputPass();
std::string inputTo();
std::string massageText();
void incorrectInputMenuMessage();
void incorrectInputMenu(char choice_menu);
void noMessages();
