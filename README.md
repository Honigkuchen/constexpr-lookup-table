# Lookup-Table for constant expressions

This repository holds my implementation for a lookup-table which can be used in constant expressions.
The intention of this lookup table is to compute the values at compile time and have them available at compile-time and/or run-time for fast lookup.

I always wanted to have something like the following (the complete example can be checked in main.cc):

```c++
[...]
static constexpr auto lut_40_20 = create_LUT<40, 20>();
[...]

int main()
{
  return std::get<0>(lut_40_20(20, 10)); // Which should return 254, see main.cc
}
```

which then results in (Release mode with debug information):

```
0000000000001040 <main>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	b8 fe 00 00 00       	mov    $0xfe,%eax
    1049:	c3                   	retq   
    104a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
```

where you can see that with $0xfe which is 254 in decimal the value is returned without any call to the actual lookup table.

# Installing

The lookup table is intended to be used as a header-only library.

# Credits

Author: Jonas 'HONIGKUCHEN' Haubold
Year: 2022

# License

The code in this project is licensed under MIT license.