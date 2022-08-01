// Simple Stack Machine
// This is a simple integer stack machine implementation.
//
// NO STANDARD LIBs, NO MALLOC
//
// NOTE (David): all dk_* functions are introduced to replace the standard C
// functions (Some of them).
// So we can compile the program with --no-standard-libraries
//

// PREPROCESSOR DIRECTIVES //

#define NULL ((void*)0)
#define internal static
#define global_variable extern
#define inlined static inline __attribute__((always_inline))
#define i8 char
#define i16 short
#define i32 int
#define i64 long long
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define u64 unsigned long long
#define f32 float
#define f64 double
#define bool int
#define true 1
#define false 0

// PRE DECLARATION OF dk_* //

internal void
dk_memset(void* dst, i32 c, i32 n);

internal i32
dk_strchr(i8* str, i8 c);

internal i8*
dk_strtok(i8* str, i8* delim);

// IMPLEMENTATION of dk_* //

internal i8*
dk_strtok(i8* str, i8* delim)
{
  static i8* last = NULL;
  if (str == NULL) {
    str = last;
  }
  i8* token = str;
  while (*token != '\0' && dk_strchr(delim, *token) != NULL) {
    token++;
  }
  if (*token == '\0') {
    return NULL;
  }
  i8* start = token;
  while (*token != '\0' && dk_strchr(delim, *token) == NULL) {
    token++;
  }
  if (*token != '\0') {
    *token = '\0';
    token++;
  }
  last = token;
  return start;
}

internal int
dk_strcmp(const i8* str1, const i8* str2)
{
  while (*str1 && *str2)
    if (*str1 != *str2)
      return *str1 - *str2;
    else
      str1++;
  return *str1 - *str2;
}

internal i32
dk_atoi(const i8* str)
{
  i32 result = 0;
  i32 sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  while (*str) {
    result = result * 10 + (*str - '0');
    str++;
  }
  return result * sign;
}

internal void
dk_memset(void* dst, i32 c, i32 n)
{
  i32* p = (i32*)dst;
  while (n--) {
    *p++ = c;
  }
}

internal i32
dk_strchr(i8* str, i8 c)
{
  i32 i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      return i;
    }
  }
  return -1;
}

// APPLICATION Impl //

typedef enum
{
  OP_HALT = -0x01,
  OP_ADD = 0x01,
  OP_SUB = 0x02,
  OP_MUL = 0x03,
  OP_DIV = 0x04,
  OP_PUSH = 0x05,
  OP_POP = 0x06,
  OP_COUNT
} Op_t;

typedef struct
{
  Op_t op;
  i32 value;
} Instruction_t;

#define STACK_SIZE 1024
internal i32 stack[STACK_SIZE] = { 0 };

internal i32
push(i32 value)
{
  stack[++stack[0]] = value;
  return stack[stack[0]];
}

internal i32
pop()
{
  return stack[stack[0]--];
}

internal i32
vm(Instruction_t* instruction)
{

  if (instruction->op == OP_HALT) {
    return -1;
  }

  if (instruction->op == OP_PUSH) {
    return push(instruction->value);
  }

  if (instruction->op == OP_POP) {
    return pop();
  }

  if (instruction->op == OP_ADD) {
    i32 a = pop();
    i32 b = pop();
    return push(a + b);
  }

  if (instruction->op == OP_SUB) {
    i32 a = pop();
    i32 b = pop();
    return push(b - a);
  }

  if (instruction->op == OP_MUL) {
    i32 a = pop();
    i32 b = pop();
    return push(a * b);
  }

  if (instruction->op == OP_DIV) {
    i32 a = pop();
    i32 b = pop();
    return push(b / a);
  }

  return OP_HALT;
}

i32
execute(i32 op_code, i32 value)
{
  Instruction_t instruction = { .op = op_code, .value = value };
  i32 result = vm(&instruction);
  return result;
}
