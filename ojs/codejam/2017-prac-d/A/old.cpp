#include <message.h>
#include <stdio.h>
#include "again.h"

#define MASTER_NODE 0
#define SENDING_DONE -1
#define LARGE_PRIME 1000000007

int main() {
  if (MyNodeId() == MASTER_NODE) {
    long long result = 0;
    for (int node = 1; node < NumberOfNodes(); ++node) {
      while (true) {
        Receive(node);
        long long value = GetLL(node);
        if (value == SENDING_DONE) {
          break;
        } else {
          result = (result + value) % LARGE_PRIME;
        }
      }
    }
    printf("%lld\n", result);
    return 0;
  } else {
    for (long long i = 0; i < GetN(); ++i) {
      for (long long j = 0; j < GetN(); ++j) {
        long long value = GetA(i) * GetB(j);
        if ((i + j) % NumberOfNodes() == MyNodeId()) {
          PutLL(MASTER_NODE, value);
          Send(MASTER_NODE);
        }
      }
    }
    PutLL(MASTER_NODE, SENDING_DONE);
    Send(MASTER_NODE);
  }
  return 0;
}
