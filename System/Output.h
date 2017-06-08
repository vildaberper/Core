#pragma once

#include <string>
#include <iostream>

static std::ostream& outc = std::cout;

static void printc(const std::string& message) { outc << message; }
static void printcln(const std::string& message = "") { printc(message + "\n"); }
