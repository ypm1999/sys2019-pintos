#include <stdio.h>
#include "userprog/syscall.h"
#include <syscall-nr.h>
#include <devices/input.h>
#include <filesys/filesys.h>
#include <threads/malloc.h>
#include <filesys/file.h>
#include <threads/pte.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "pagedir.h"
#include "devices/shutdown.h"
#include "lib/user/syscall.h"
#include "process.h"

static void syscall_handler (struct intr_frame *);
/* Implementation by ypm Started */
static void syscall_halt (struct intr_frame *f);
static void syscall_exit (struct intr_frame *f, int return_value);
static void syscall_exec (struct intr_frame *f, const char *cmd_line);
static void syscall_wait (struct intr_frame *f, pid_t pid);
static void syscall_open (struct intr_frame *f, const char *name);
static void syscall_create (struct intr_frame *f, const char *name, unsigned initial_size);
static void syscall_remove (struct intr_frame *f, const char *name);
static void syscall_filesize (struct intr_frame *f, int fd);
static void syscall_read (struct intr_frame *f, int fd, const void *buffer, unsigned size);
static void syscall_write (struct intr_frame *f, int fd, const void *buffer, unsigned size);
static void syscall_seek (struct intr_frame *f, int fd, unsigned position);
static void syscall_tell (struct intr_frame *f, int fd);
static void syscall_close (struct intr_frame *f, int fd);
/* Implementation by ypm Ended */



void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{

  /* Implementation by ypm Started */
  if (!syscall_check_user_buffer(f->esp, 4))
    thread_exit_with_return_value(f, -1);

  int call_num = *((int *) f->esp);
  void *arg1 = f->esp + 4, *arg2 = f->esp + 8, *arg3 = f->esp + 12;

  switch (call_num){
    case SYS_EXIT:
    case SYS_EXEC:
    case SYS_WAIT:
    case SYS_TELL:
    case SYS_CLOSE:
    case SYS_REMOVE:
    case SYS_OPEN:
    case SYS_FILESIZE:
      if (!syscall_check_user_buffer(arg1, 4))
        thread_exit_with_return_value(f, -1);
      break;

    case SYS_CREATE:
    case SYS_SEEK:
      if (!syscall_check_user_buffer(arg1, 8))
        thread_exit_with_return_value(f, -1);
      break;

    case SYS_READ:
    case SYS_WRITE:
      if (!syscall_check_user_buffer(arg1, 12))
        thread_exit_with_return_value(f, -1);
      break;

    default: break;
  }

  switch (call_num)
    {
      case SYS_HALT:
        syscall_halt (f);
        break;

      case SYS_EXIT:
        syscall_exit (f, *((int *) arg1));
        break;

      case SYS_EXEC:
        syscall_exec (f, *((void **) arg1));
        break;

      case SYS_WAIT:
        syscall_wait (f, *((pid_t *) arg1));
        break;

      case SYS_TELL:
        syscall_tell (f, *((int *) arg1));
        break;

      case SYS_CLOSE:
        syscall_close (f, *((int *) arg1));
        break;

      case SYS_REMOVE:
        syscall_remove (f, *((void **) arg1));
        break;

      case SYS_OPEN:
        syscall_open (f, *((void **) arg1));
        break;

      case SYS_FILESIZE:
        syscall_filesize (f, *((int *) arg1));
        break;

      case SYS_CREATE:
        syscall_create (f, *((void **) arg1), *((unsigned *) arg2));
        break;

      case SYS_SEEK:
        syscall_seek (f, *((int *) arg1), *((unsigned *) arg2));
        break;

      case SYS_READ:
        syscall_read (f, *((int *) arg1), *((void **) arg2), *((unsigned *) arg3));
        break;

      case SYS_WRITE:
        syscall_write (f, *((int *) arg1), *((void **) arg2), *((unsigned *) arg3));
        break;

      default:
        thread_exit_with_return_value(f, -1);
    }
  /* Implementation by ypm Ended */
}


/* Implementation by Wang Started */
static void
syscall_exec (struct intr_frame *f, const char *cmd_line)
{
  if (!pagedir_translate_vaddr(cmd_line))
    thread_exit_with_return_value(f, -1);
  f->eax = (uint32_t)process_execute (cmd_line);
  struct list_elem *e;
  struct thread *cur = thread_current ();
  struct child_message *l;
  for (e = list_begin (&cur->child_list); e != list_end (&cur->child_list); e = list_next (e))
  {
    l = list_entry (e, struct child_message, elem);
    if (l->tid == f->eax)
    {
      sema_down (l->sema_started);
      if (l->load_failed)
        f->eax = (uint32_t)-1;
      return;
    }
  }
}

static void
syscall_wait (struct intr_frame *f, pid_t pid)
{
  f->eax = (uint32_t)process_wait (pid);
}

/* Implementation by Wang Ended */



/* Implementation by ypm Started */



static void
syscall_halt(struct intr_frame *f){
  shutdown_power_off();
}

static void
syscall_exit(struct intr_frame *f, const int return_value){

  /* Implementation by Wang Started */
  struct thread *cur = thread_current ();
  if (!cur->grandpa_died)
    {
      cur->message_to_grandpa->exited = true;
      cur->message_to_grandpa->return_value = return_value;
    }
  /* Implementation by Wang Ended */

  thread_exit_with_return_value(f, return_value);
}



static void
syscall_open(struct intr_frame *f, const char* name){
  if (!pagedir_check_user_string(name))
    thread_exit_with_return_value(f, -1);

  struct file* tmp_file = filesys_open(name);
  if (tmp_file == NULL){
    f->eax = (uint32_t)-1;
    return;
  }

  static uint32_t fd_next = 2;

  struct file_handle* handle = malloc(sizeof(struct file_handle));
  handle->opened_file = tmp_file;
  handle->owned_thread = thread_current();
  handle->fd = fd_next++;
  thread_file_list_inster(handle);
  f->eax = (uint32_t)handle->fd;
}

static void
syscall_create(struct intr_frame *f, const char * name, unsigned initial_size){
  if (!pagedir_check_user_string(name))
    thread_exit_with_return_value(f, -1);

  f->eax = (uint32_t)filesys_create(name, initial_size);
}

static void
syscall_remove(struct intr_frame *f, const char* name){
  if (!pagedir_check_user_string(name))
    thread_exit_with_return_value(f, -1);
  f->eax = (uint32_t)filesys_remove(name);
}

static void
syscall_filesize(struct intr_frame *f, int fd){
  struct file_handle* t = syscall_get_file_handle(fd);
  if(t != NULL)
    f->eax = (uint32_t)file_length(t->opened_file);
  else
    thread_exit_with_return_value(f, -1);
}

static void
syscall_read(struct intr_frame *f, int fd, const void* buffer, unsigned size){
  if (!syscall_check_user_buffer(buffer, size))
    thread_exit_with_return_value(f, -1);

  if (fd == STDOUT_FILENO)
    thread_exit_with_return_value(f, -1);

  uint8_t * str = buffer;
  if (fd == STDIN_FILENO){
    while(size-- != 0)
      *(char *)str++ = input_getc();
  }
  else{
    struct file_handle* t = syscall_get_file_handle(fd);
    if (t != NULL){
      f->eax = (uint32_t)file_read(t->opened_file, (void*)buffer, size);
    }
    else
      thread_exit_with_return_value(f, -1);
  }
}

static void
syscall_write(struct intr_frame *f, int fd, const void* buffer, unsigned size){
  if (!syscall_check_user_buffer(buffer, size))
    thread_exit_with_return_value(f, -1);

  if (fd == STDIN_FILENO)
    thread_exit_with_return_value(f, -1);

  if (fd == STDOUT_FILENO)
    putbuf(buffer, size);
  else{
    struct file_handle* t = syscall_get_file_handle(fd);
    if (t != NULL){
      f->eax = (uint32_t)file_write(t->opened_file, (void*)buffer, size);
    }
    else
      thread_exit_with_return_value(f, -1);
  }
}

static void
syscall_seek(struct intr_frame *f, int fd, unsigned position){
  struct file_handle* t = syscall_get_file_handle(fd);
  if (t != NULL)
    file_seek(t->opened_file, position);
  else
    thread_exit_with_return_value(f, -1);
}

static void
syscall_tell(struct intr_frame *f, int fd){
  struct file_handle* t = syscall_get_file_handle(fd);
  if (t != NULL)
    f->eax = (uint32_t)file_tell(t->opened_file);
  else
    thread_exit_with_return_value(f, -1);
}

static void
syscall_close(struct intr_frame *f, int fd){
  struct file_handle* t = syscall_get_file_handle(fd);
  if(t != NULL){
    file_close(t->opened_file);
    list_remove(&t->elem);
    free(t);
  }
  else
    thread_exit_with_return_value(f, -1);
}

/* Implementation by ypm Ended */
