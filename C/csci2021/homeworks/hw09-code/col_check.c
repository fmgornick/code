typedef struct{
  int cur;            // current value in collatz sequence
  int step;           // step number in collatz sequence
} colinfo_t;
// |       | Byte |   Byte | Packed |
// | Field | Size | Offset |   Bits |
// |-------+------+--------+--------|
// | cur   |    4 |     +0 |   0-31 |
// | step  |    4 |     +4 |  32-64 |

int col_check(colinfo_t info){
  // Analyzes values in the packed struct arg
  // info to detect errors in it. An int
  // comprised of set error bits is
  // returned. Bit 0: cur field was 0 or
  // below, Bit 1: step was negative, Bit 2:
  // cur was 1 but step is negative.

  int cur = info.cur;
  int step = info.step;
  int errs = 0;
  if(cur <= 0){
    errs = errs | 0x1; // 0b0001
  }
  if(step < 0){
    errs = errs | 0x2; // 0b0010
  }
  if(cur==1 && step < 0){
    errs = errs | 0x4; // 0b0100
  }
  
  return errs;
}
