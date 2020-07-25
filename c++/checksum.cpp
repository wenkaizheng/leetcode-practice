#include <iostream>
#include <stdlib.h>
static uint16_t check_sum(void* src_ptr, uint16_t len, uint16_t src)
{
  uint32_t sum = 0;
  uint16_t count;
  uint8_t* walker = (uint8_t*)src_ptr;
  while (len > 1) {
    count = ((uint16_t)(*walker)) << 8;
    walker++;
    count |= (*walker);
    walker++;
    sum += count;
    std::cout << sum << std::endl;
    len -= 2;
  }
  if (len > 0) {
    count = ((uint16_t)(*walker)) << 8;
    sum += count;
  }
  std::cout << sum << std::endl;
  // add first 16 bits and last 16 bits
  sum = (sum >> 16) + (sum & 0x0000ffff);
  std::cout << sum << std::endl;
  // if it is bigger than 0xffff
  if ((sum & 0xffff0000) != 0) {
    sum = (sum >> 16) + (sum & 0x0000ffff);
  }

  count = ~(uint16_t)sum;
  if (src== count){
      std::cout << "CheckSum is OK" << std::endl;
  }
  else{
       std::cout << "CheckSum is not OK" << std::endl;
  }
  return count;
}

int main() {
// 45 00 00 3c 00 00 00 00 40 11 6d 36 c0 a8 2b c3 08 08 08 08 11
  uint8_t* test = (uint8_t*)malloc(sizeof(uint8_t)*19);
  test[0] = 0x45;
  test[1] = 0x00;
  test[2] = 0x00;
  test[3] = 0x3c;
  test[4] = 0x00;
  test[5] = 0x00;
  test[6] = 0x00;
  test[7] = 0x00;
  test[8] = 0x40;
  test[9] = 0x11;
  test[10] = 0xc0;
  test[11] = 0xa8;
  test[12] = 0x2b;
  test[13] = 0xc3;
  test[14] = 0x08;
  test[15] = 0x08;
  test[16] = 0x08;
  test[17] = 0x08;
  test[18] = 0x11;
  std::cout << check_sum(test,19,0x6d36) <<std::endl;
  
}