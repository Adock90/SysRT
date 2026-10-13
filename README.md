# SysRT
A small linux JS Runtime for System Level programming

# Just Running it

<h1>Step 1:</h1>

Go to releases on github and click and download it (sha256sums provided)

<h1>Step 2:</h1>

Run with your .js file as the first argument.

<code>./SysRT hi.js</code>


# Build Instructions 

<h1>Step 1:</h1>

Git clone this repository:

<code>git clone https://github.com/Adock90/SysRT</code>

Or download as ZIP

<h1>Step 2:</h1>

Run the build file (you might need to enable execute permissions).

<code>./build.sh</code>

For changing permissions.

<code>chmod +x ./build.sh</code>

Alternatively run:

<code>g++ -o build/SysRT main.cpp -luv -lv8 -std=c++20 -I ./src</code>

or

<code>clang++ -o build/SysRT main.cpp -luv -lv8 -std=c++20 -I ./src</code>

<h1>Step 3</h1>

cd into the build directory.

<code>cd build/</code>

Run with your .js file as the first argument.

<code>./GassinRT hi.js</code>
