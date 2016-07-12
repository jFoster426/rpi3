#ifndef mcp3301_c
#define mcp3301_c

int mcp3301Convert(int val) {
  if (val > 4095) {
    val = ~val;
    val &= 0x0FFF;
    val = -val;
  }
  val += 4095;
}

#endif
