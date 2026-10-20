# SysRT
A small linux JS Runtime for System Level programming

# Just Running it

<h3>Step 1:</h3>

Go to releases on GitHub and click and download it (sha256sums provided)

<h3>Step 2:</h3>

Run with your .js file as the first argument.

<code>./SysRT hi.js</code>


# Build Instructions 

<h3>Step 1:</h3>

Git clone this repository:

```
git clone https://github.com/Adock90/SysRT
```

Or download as ZIP

<h3>Step 2:</h3>

Run the build file (you might need to enable execute permissions).

```
./build.sh
```

For changing permissions.

```
chmod +x ./build.sh
```

Alternatively run:

```
g++ -o build/SysRT main.cpp -luv -lv8 -std=c++20 -I ./src
```

or

```
clang++ -o build/SysRT main.cpp -luv -lv8 -std=c++20 -I ./src
```

<h1>Step 3</h1>

cd into the build directory.

```
cd build/
```

Run with your .js file as the first argument.

```
./SysRT hi.js
```
