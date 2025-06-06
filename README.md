# Acorn

Acorn is a minimal example of a programming language that compiles to Java bytecode and runs on the JVM. Its initial version supports a single statement:

```
print <int value>
```

When compiled and executed, this statement prints the specified integer value to the console.


## Example
Given the following Acorn source code:

```
print 42
```

Compiling and running this will output:

```
42
```

## Building
This project uses CMake (3.x or newer) and requires a C++ compiler and Java (for running the generated bytecode).

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

To compile an Acorn source file:

```
./acorn altair.aco
```

This will generate a `Altair.class` file. To run the compiled program on the JVM:

```
java Altair
```

Or, you can run the Acorn 'interpreter': 

```
./acorn altair.aco
```
which compiles and runs the program in one step.




## License
MIT License

