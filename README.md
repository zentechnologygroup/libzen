# libzen

LibZen is a C++ library for petroleum-domain units management and conversion.

## Features

* Runtime entirely written in C++14.
* Tested on gcc, clang and Intel (icc), compilable on any platform that supports any of these.
* The library is compilable for Windows, OSX, Linux, and Solaris operating systems.
* Fully reentrant code, which makes it multithreaded.
* Chainable to any system.


## Dependencies 

### Aleph-w

Download the latest version of Aleph-w, available at: https://github.com/lrleon/Aleph-w

Download it in the directory of your preference. It is not necessary to compile this library. 

The makefiles will search for an environment variable called ALEPHW, which could be defined as follows:
```
	ALEPHW = directory-where-alephw-is
	export $ALEPHW
```
  
These lines can be placed in the `.bashrc` file, so that each time a console is opened the variable is already defined.


### Imake

For a distribution based on Debian it can be installed by executing:
```
	sudo apt-get install xutils-dev
```
	
For other distributions, follow the instructions available at: http://www.snake.net/software/imake-stuff/imake-faq.html#where-to-get


## Generation of `makefiles`

The first time you download the sources, execute:

```
	$xmkmf
	$make Makefiles
	$make depend
```

The command `make depend` generates compilation "dependencies", which allow you to detect when the sources have to be recompiled.

Each time you add a new header file to the `include` directory, execute `make depend`.

## Generation of executables

To generate all the executables, run:


```
  $make all
```


## Tests

After compiling, the directory test/ which contains the test executables is generated.

**test-conversion** : Basic converter, for a single source value. For more details consult the help system by executing the command:
```
   $ ./test-conversion --help
```

Example
```
   $ ./test-conversion -S Fahrenheit -s 350 -T Celsius
```
   
   where,
  
    -S : source unit
    -s : value you need to convert
    -T : target unit
   

**vector-conversion** : Advanced converter, for multiple source values. Convert a list of values with a single instruction. For more details consult the help system by executing the command:
m by executing the command:

```
$ ./vector-conversion --help
```

Example
```
./vector-conversion   -T Celsius -S Fahrenheit 350 365 380
```
where,
  
    -S : source unit
    -s : value you need to convert
    values you need to convert

   


To list the physical quantities implemented in the unit converter, use the following command:


```
$./test-conversion -l

```



## Authors

####  Software Architect and Lead Developer
* PhD. Leandro Rabindranath Leon - (leandro.r.leon@gmail.com)

#### Domain Driven Analyst and  Designer
* MSc. Alberto Valderrama - (alberto.valderrama@zentech.group)

#### Developer and Tester
* Ixhel Mejías -  (ixhel.mejias@zentech.group)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
