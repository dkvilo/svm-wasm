# Simple Stack Based VM written in C, and Compiled to Webassembly

A stack-based virtual machine written in C, compiled to WASM, This is project for me to try out WASM, i have plans add more features tho.

Supported Operations (Only integers are supported for now):

- Addition
- Subtraction
- Multiplication
- Division

## Building Webassembly

You need to have **clang** installed to build this project.

```zsh
  $ make
```

## Usage

Currently, there is no language-like syntax/interface for the VM. In the future, I will probably add a simple parser (Something like this).

```javascript
const vm = new VM();
vm.execute(`
  PUSH 10;
  PUSH 20;
  ADD;
  PRINT;
`);
```

# Supported Operations and their Stack Behavior

```javascript
const OP_CODE = {
  HALT: -0x01,
  ADD: 0x01,
  SUB: 0x02,
  MUL: 0x03,
  DIV: 0x04,
  PUSH: 0x05,
};

async function init() {
  const { instance } = await WebAssembly.instantiateStreaming(
    fetch("./app.wasm"),
    {
      env: {
        memory: new WebAssembly.Memory({ initial: 256, maximum: 256 }),
        table: new WebAssembly.Table({
          initial: 1,
          maximum: 1,
          element: "...",
        }),
        abort: function (msg, file, line) {
          throw new Error(msg);
        },
      },
    }
  );

  const { execute } = instance.exports;
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 20), "]");
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 30), "]");
  console.log("ADD  -> [", execute(OP_CODE.ADD), "]");
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 40), "]");
  console.log("SUB  -> [", execute(OP_CODE.SUB), "]");
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 50), "]");
  console.log("MUL  -> [", execute(OP_CODE.MUL), "]");
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 60), "]");
  console.log("DIV  -> [", execute(OP_CODE.DIV), "]");
  console.log("PUSH -> [", execute(OP_CODE.PUSH, 70), "]");
  console.log("ADD  -> [", execute(OP_CODE.ADD), "]");

  // HALT returns -1 (it should be 0x00) according to the Unix spec but who cares.
  console.log("HALT -> [", execute(OP_CODE.HALT), "]");
}

init();
```
