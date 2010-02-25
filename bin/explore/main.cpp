#include "glutmain.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
  fearless::explore::GlutMain m(&argc, argv);
  fearless::explore::Renderer r;
  m.go(r);
}

