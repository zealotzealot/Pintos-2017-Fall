#ifndef VM_PAGE_H
#define VM_PAGE_H

#include "lib/kernel/hash.h"
#include "userprog/process.h"
#include "userprog/syscall.h"

enum page_type {
  PAGE_FILE,
  PAGE_STACK,
  PAGE_SWAP,
  PAGE_MMAP,
  PAGE_LOADED,
};

struct page {
  // Common fields
  enum page_type type;
  uint8_t *upage;
  uint8_t *kpage;
  bool writable;
  bool pin;

  // Fields for file
  struct file *file;
  off_t ofs;
  size_t page_read_bytes;
  size_t page_zero_bytes;

  // No fields for stack

  // Fields for swap
  int slot;

  // Fileds for mmap
  struct mte *mte;

  struct hash_elem elem_hash;
};

bool page_add_mmap(struct mte *, off_t, uint8_t *, size_t, size_t, bool);
void page_write_mmap(void *);
void page_free_mmap(void *);

void page_set_pin(void *, unsigned, bool);

void page_init(struct hash *);
void page_destroy(struct hash *);

void page_add_file(struct file *, off_t, uint8_t *, size_t, size_t, bool);
void page_add_stack(void *);
bool page_change_swap(struct hash *, void *, int, bool, pid_t);
bool page_load(void *);

#endif
