/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  flush_cache();

  int try_addr = 0;
  access_cache(try_addr);
  while(access_cache(++try_addr));

  flush_cache();
  return try_addr;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  flush_cache();
  
  int block_size = get_block_size();
  int try_block = 0, try_addr = 0;
  while(1){
      try_addr = try_block* block_size;
      access_cache(try_addr);
      
      int replace_addr  = 0;
      int replace_found = 0;
      for(;replace_addr < try_addr && !replace_found;replace_addr ++){
          if(!access_cache(replace_addr)){
              replace_found = 1;
              break;
          }
      }
      if(replace_found) break;
      
      try_block++;    
  }

  flush_cache();
  return try_block * block_size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc() {
  flush_cache();
  //int block_size = get_block_size();
  int cache_size = get_cache_size(0);
  int block_size = get_block_size();
  int addr = 0, replace_addr = 0;

  for (; addr < cache_size; addr += block_size){
      access_cache(addr);
  }

  int special_addr = cache_size * 2 - block_size; // 11111...
  access_cache(special_addr);
  for(; replace_addr < cache_size && access_cache(replace_addr); replace_addr += block_size);

  return cache_size / (replace_addr + block_size);
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
