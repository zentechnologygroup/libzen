# libzen
---

libzen is a C++ library for petroleum-domain units management and conversion.

## Features

* Runtime entirely written in C++14.
* Tested on gcc, clang and Intel (icc), compilable on any platform that supports any of these.
* The library is compilable for Windows, OSX, Linux, and Solaris operating systems.
* Fully reentrant code, which makes it multithreaded.
* Chainable to any system.

#### Physical magnitudes supported by the converter

|      Physical Magnitude     |    Unit symbol              |    LaTeX symbol                   |
| --------------------------  | --------------------------- | --------------------------------- |
|        Absolute Roughness   |     ft_ar                   |    ft_ar                          |           
|        Absolute Roughness   |     in_ar                   |    in_ar                          |
|        Absolute Roughness   |     mm_ar                   |    mm_ar                          |
|                    Angle    |     deg                     |    \degree                        |
|                    Angle    |     rad                     |    rad                            |
|                     Area    |     ft2                     |    ft2                            |
|                     Area    |     in2                     |    in2                            |
|    Compressibility Factor   |     zFactor                 |    Undefined                      |
|                  Current    |     amp                     |    amp                            |
|                  Density    |     gr/cm3                  |    g/cm^{3}                       |
|                  Density    |     kg/m3                   |    kg/m^{3}                       |
|                  Density    |     kg/L                    |    kg/L                           |
|                  Density    |     lb/ft3                  |    lb/ft^{3}                      |
|                  Density    |     lb/gal                  |    lb/gal                         |
|                  Density    |     lb/inch3                |    lb/in^{3}                      |
|                  Density    |     Sg                      |    sg water=1\ at\ 60\ \degree{F} |
|                DummyUnit    |     TU                      |    TU                             |
|         Dynamic Viscosity   |     kg/m*s                  |    kg/m \cdot s                   |
|         Dynamic Viscosity   |     lb/ft*s                 |    lb/ft \cdot s                  |
|         Dynamic Viscosity   |     g/cm*s                  |    g/cm \cdot s                   |
|         Dynamic Viscosity   |     cP                      |    cP                             |
|         Dynamic Viscosity   |     Pa*s                    |    Pa \cdot s                     |
|         Dynamic Viscosity   |     lb/ft*h                 |    lb/ft \cdot h                  |
|         Dynamic Viscosity   |     poise                   |    P                              |
|         Dynamic Viscosity   |     mP                      |    mP                             |
|           FVF volume Ratio  |     RB/STB                  |    RB/STB                         |
|           FVF volume Ratio  |     Rm3/Sm3                 |    Rm^{3}/Sm^{3}                  |
|           Flow Efficiency   |     FlowEff                 |    Dmnl                           |
|                Flow Rate    |     bpd                     |    bpd                            |
|                 Flow Rate   |     gpm                     |    gpm                            |
|                 Flow Rate   |     cmd                     |    cmd                            |
|                 Flow Rate   |     cms                     |    cms                            |
|                Frequency    |     Hz                      |    Hz                             |
|                Frequency    |     RPM                     |    RPM                            |
|           Friction Factor   |     fFactor                 |    Non-dimensional factor         |
|        GORGLR volume Ratio  |     scf/STB                 |    scf/STB                        |
|        GORGLR volume Ratio  |     Mscf/STB                |    Mscf/STB                       |
|        GORGLR volume Ratio  |     MMscf/STB               |    MMscf/STB                      |
|        GORGLR volume Ratio  |     Sm3/Sm3                 |    Sm^{3}/Sm^{3}                  |
|                   Gas FVF   |     rcf/scf                 |    rcf/scf                        |
|                   Gas FVF   |     rm3/sm3                 |    Rm^{3}/Sm^{3}                  |
|                   Gas FVF   |     rcf/Mscf                |    rcf/Mscf                       |
|                   Gas FVF   |     RB/scf                  |    RB/scf                         |
|                   Gas FVF   |     RB/Mscf                 |    RB/Mscf                        |
|              Gas Flow Rate  |     MMscf/d                 |    MMscf/d                        |
|       Gas Specific Gravity  |     Sgg                     |    air=1                          |
|       Gas Specific Gravity  |     kg/m3atStandCond        |    kg/m^{3}\ at\ STP              |
|       Gas Specific Gravity  |     lb/ft3atStandCond       |    lb/ft^{3}\ at\ STP             |
|       Geothermal Gradient   |     degF/Ft                 |    \degree{F}/ft                  |
|       Geothermal Gradient   |     degC/Km                 |    \degree{C}/km                  |
|                     Head    |     Hft                     |    Hft                            |
|                     Head    |     Hmts                    |    Hmts                           |
|  Heat Transfer Coefficient  |     Btu (th)/d/ft2/degF     |    Btu (th)/d/ft^{2}/^{\circ}F    |
|       Interfacial Tension   |     dynes/cm                |    dyne/cm                        |
|       Interfacial Tension   |     N/m                     |    N/m                            |
|       Interfacial Tension   |     mN/m                    |    mN/m                           |
|       Interfacial Tension   |     gram-force/cm           |    gf/cm                          |
|       Interfacial Tension   |     pound-force/inch        |    lbf/in                         |
|       Interfacial Tension   |     pound-mass/s^2          |    lbm/s^2                        |
|Isothermal Compressibility   |     Pa^-1                   |    Pa^{-1}                        |
|Isothermal Compressibility   |     MPa^-1                  |    MPa^{-1}                       |
|Isothermal Compressibility   |     psia^-1                 |    psia^{-1}                      |
|Isothermal Compressibility   |     bar^-1                  |    bar^{-1}                       |
|Isothermal Compressibility   |     atm^-1                  |    atm^{-1}                       |
|            Liquid Gravity   |     g                       |    g                              |
|  Non Hydrocarbons Fraction  |     MoleFraction            |    mol\ fraction                  |
|  Non Hydrocarbons Fraction  |     VolumeFraction          |    vol\ fraction                  |
|  Non Hydrocarbons Fraction  |     MolePercent             |    mol\%                          |
|  Non Hydrocarbons Fraction  |     VolumePercent           |    vol\%                          |
|        OGRLGR volume Ratio  |     STB/scf                 |    STB/scf                        |
|        OGRLGR volume Ratio  |     STB/Mscf                |    STB/Mscf                       |
|        OGRLGR volume Ratio  |     STB/MMscf               |    STB/MMscf                      |
|        OGRLGR volume Ratio  |     Sm3 Liquid/Sm3          |    Sm^{3}/Sm^{3}                  |
|               Oil Gravity   |     api                     |    \degree{API}                   |
|               Oil Gravity   |     sg_do water=1\ at\ 60\  |    \degree{F}                     |
|                 Pressure    |     bar                     |    bar                            |
|                 Pressure    |     Pa                      |    Pa                             |
|                 Pressure    |     kPa                     |    kPa                            |
|                 Pressure    |     MPa                     |    MPa                            |
|                 Pressure    |     psia                    |    psia                           |
|                 Pressure    |     psig                    |    psig                           |
|                 Pressure    |     atm                     |    atm                            |
|         Pressure Gradient   |     psi/ft                  |    psi/ft                         |
|         Pressure Gradient   |     kPa/m                   |    kPa/m                          |
|            Pressure Ratio   |     Ppr                     |    Dmnl                           |
|        Relative Roughness   |     Non-dimensional         |    roughness                      |
|             Specific Heat   |     kilojoule/kilogram/K    |    kilojoule/kilogram/K           |
|             Specific Heat   |     Btu (th)/pound/°F       |    Btu (th)/pound/degF            |
|              Temperature    |     degK                    |    K                              |
|              Temperature    |     degC                    |    \degree{C}                     |
|              Temperature    |     degF                    |    \degree{F}                     |
|              Temperature    |     degR                    |    \degree{R}                     |
|         Temperature Ratio   |     Tpr                     |    Dmnl                           |
|      Thermal Conductivity   |     watt/mt/K               |    watt/mt/K                      |
|      Thermal Conductivity   |     Btu (th)/hour/foot/degF |    Btu (th)/hour/foot/degF        |
|      Thermal Conductivity   |     Btu (th)/day/foot/degF  |    Btu (th)/day/foot/degF         |
|                 Water Cut   |     wc_p                    |    Undefined                      |
|                 Water Cut   |     wc_f                    |    Undefined                      |
|     Water Specific Gravity  |     pwl_lb/ft3              |    lb/ft^{3}                      |
|     Water Specific Gravity  |     dissolvedSaltPercent    |    wt\%                           |
|     Water Specific Gravity  |     swsg water=1\ at\ 60\   |    \degree{F}                     |
|     Water Specific Gravity  |     dissolvedSaltPPM        |    wt\ ppm                        |
|     Water Specific Gravity  |     mol_NaCl/Kg_H2O         |    mol\ NaCl/kg\ H_2O             |
|     Water Specific Gravity  |     g_NaCl/L                |    g\ NaCl/L\ H_2O                |
|     Water Specific Gravity  |     dissolvedSaltFraction   |    Mass\ fraction\ NaCl           |
|                Wet Gas FVF  |     RCF Gas/STB             |    rcf/STB                        |
|                Wet Gas FVF  |     RB Gas/STB              |    RB/STB                         |           

## Dependencies 


### cmake

For a Debian-based distribution, it can be installed by executing:

```
$ sudo apt-get install cmake
```

For other distributions, or if Debian's repositories don't include cmake versión 3.7+, download the [sources](https://cmake.org/download/) and build it by doing:

```
$ ./bootstrap
$ make
$ sudo make install
```

### Submodules

If you clone the porject, fetch submodules in order to be able to build it:

```
$ git submodule init
$ git submodule update
```

## Build

To build the project, do:

```
$ mkdir build && cd build
$ cmake ..
$ make
```

## Tests

After compiling, the test executables are generated in the directory `bin`. To run all tests, do:

```
$ ./bin/ztgunitmanagertest
```

To list the physical quantities implemented in the unit converter, use the following command:


```
$ ./bin/ztgunitmanagertest -P
```

To list all options available for testing, do:

```
$ ./bin/ztgunitmanagertest --help
```

## Authors

####  Software Architect
* PhD. Leandro Rabindranath Leon - (leandro.r.leon@gmail.com)

#### Developer
* Álvaro Araujo -  (alvaro.araujo@zentech.group)

#### Developer
* Jhonathan Abreu -  (jhonathan.abreu@zentech.group)

#### Domain Driven Analyst and  Designer
* MSc. Alberto Valderrama - (alberto.valderrama@zentech.group)

#### Developer and Tester
* Ixhel Mejías -  (ixhel.mejias@zentech.group)



## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details
